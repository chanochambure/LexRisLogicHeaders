/* FileStream.cpp -- File Stream Source - LexRis Logic Headers

    Copyright (c) 2017 LexRisLogic

    Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
    documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
    rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
    permit persons to whom the Software is furnished to do so.

    The above copyright notice and this permission notice shall be included in all copies or substantial portions of
    the Software.

    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
    THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
    AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
    TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
    SOFTWARE.
*/

#include "../include/LexRisLogic/FileStream.h"

namespace LL
{
    void FileStream::set_path(std::string new_path)
    {
        _V_data.clear();
        _V_file_path=new_path;
    }
    std::string FileStream::get_path()
    {
        return _V_file_path;
    }
    bool FileStream::load()
    {
        clear_file();
        std::ifstream file(_V_file_path.c_str());
        if(file.is_open())
        {
            std::string buffer;
            while(getline(file,buffer))
                _V_data.push_back(buffer);
            file.close();
            return true;
        }
        return false;
    }
    bool FileStream::save()
    {
        std::ofstream file(_V_file_path.c_str(), std::ofstream::out | std::ofstream::trunc);
        if(file.is_open())
        {
            if(_V_data.size())
            {
                unsigned int data_lines=_V_data.size()-1;
                for(unsigned int i=0;i<data_lines;++i)
                    file<<_V_data[i]<<std::endl;
                file<<_V_data[data_lines];
            }
            file.close();
            return true;
        }
        return false;
    }
    void FileStream::clear_file()
    {
        _V_data.clear();
    }
    bool FileStream::insert_line(unsigned int insert_position,unsigned int total_of_new_lines)
    {
        if(insert_position<=_V_data.size())
        {
            std::vector<std::string>::iterator iter=_V_data.begin()+insert_position;
            for(unsigned int i=0;i<total_of_new_lines;++i)
                iter=_V_data.insert(iter,std::string());
            return true;
        }
        return false;
    }
    bool FileStream::remove_line(unsigned int remove_position)
    {
        if(remove_position<_V_data.size())
        {
            _V_data.erase(_V_data.begin()+remove_position);
            return true;
        }
        return false;
    }
    unsigned int FileStream::size()
    {
        return _V_data.size();
    }
    std::string& FileStream::operator [] (unsigned int line_position)
    {
        return _V_data[line_position];
    }
    FileStream::~FileStream()
    {
        clear_file();
    }
}
