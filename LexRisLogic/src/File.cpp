/* File.cpp -- File Source - LexRis Logic Headers

    Copyright (c) 2017-2018 LexRisLogic

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

#include "../include/LexRisLogic/File.h"

namespace LL
{
    FileStream::FileStream()
    {
    }
    void FileStream::set_path(std::string new_path)
    {
        _V_file_path=new_path;
    }
    std::string FileStream::get_path()
    {
        return _V_file_path;
    }
    bool FileStream::set_binary_option(bool new_binary_option)
    {
        if(!_V_input_stream.is_open() && !_V_output_stream.is_open())
        {
            _V_binary_option=new_binary_option;
            return true;
        }
        return false;
    }
    bool FileStream::get_binary_option()
    {
        return _V_binary_option;
    }
    bool FileStream::set_append_option(bool new_append_option)
    {
        if(!_V_output_stream.is_open())
        {
            _V_append_option=new_append_option;
            return true;
        }
        return false;
    }
    bool FileStream::get_append_option()
    {
        return _V_append_option;
    }
    bool FileStream::open(bool mode)
    {
        if(!_V_input_stream.is_open() && !_V_output_stream.is_open())
        {
            if(mode)
            {
                std::ios_base::openmode options=std::ios_base::out;
                if(_V_append_option)
                    options |= std::ios_base::app;
                else
                    options |= std::ios_base::trunc;
                if(_V_binary_option)
                    options |= std::ios_base::binary;
                _V_output_stream.open(_V_file_path.c_str(),options);
                return _V_output_stream.is_open();
            }
            else
            {
                std::ios_base::openmode options=std::ios_base::in;
                if(_V_binary_option)
                    options |= std::ios::binary;
                _V_input_stream.open(_V_file_path.c_str(),options);
                return _V_input_stream.is_open();
            }
        }
        return false;
    }
    bool FileStream::write(char* data,unsigned int bytes)
    {
        if(_V_output_stream.is_open())
        {
            _V_output_stream.write(data,bytes);
            return true;
        }
        return false;
    }
    unsigned int FileStream::read(char* data,unsigned int bytes)
    {
        if(_V_input_stream.is_open())
        {
            _V_input_stream.read(data,bytes);
            return _V_input_stream.gcount();
        }
        return 0;
    }
    bool FileStream::close()
    {
        if(_V_input_stream.is_open())
        {
            _V_input_stream.close();
            return true;
        }
        if(_V_output_stream.is_open())
        {
            _V_output_stream.close();
            return true;
        }
        return false;
    }
    bool FileStream::is_open()
    {
        return _V_input_stream.is_open() || _V_output_stream.is_open();
    }
    FileStream::~FileStream()
    {
        close();
    }

    void TextFile::set_path(std::string new_path)
    {
        _V_data.clear();
        _V_file_path=new_path;
    }
    std::string TextFile::get_path()
    {
        return _V_file_path;
    }
    bool TextFile::load()
    {
        clear();
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
    bool TextFile::save()
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
    void TextFile::clear()
    {
        _V_data.clear();
    }
    bool TextFile::insert_line(unsigned int insert_position,unsigned int total_of_new_lines)
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
    bool TextFile::remove_line(unsigned int remove_position)
    {
        if(remove_position<_V_data.size())
        {
            _V_data.erase(_V_data.begin()+remove_position);
            return true;
        }
        return false;
    }
    unsigned int TextFile::size()
    {
        return _V_data.size();
    }
    std::string& TextFile::operator [] (unsigned int line_position)
    {
        return _V_data[line_position];
    }
    TextFile::~TextFile()
    {
        clear();
    }
}
