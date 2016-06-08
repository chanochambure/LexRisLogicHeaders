/* FileStream.h -- File Stream Header - LexRis Logic Headers

    Copyright (c) 2016 LexRisLogic

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

#ifndef INCLUDED_LL_FILESTREAM_H
#define INCLUDED_LL_FILESTREAM_H

#include <string>
#include <vector>
#include <fstream>

namespace LL
{
    class FileStream
    {
        private:
            bool _V_loaded=false;
            std::string _V_file_path;
            std::vector<std::string> _V_data;
            bool _F_read_file()
            {
                _V_loaded=true;
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
            bool _F_save_file()
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
        public:
            void set_path(std::string new_path)
            {
                _V_data.clear();
                _V_file_path=new_path;
                _V_loaded=false;
            }
            std::string get_path()
            {
                return _V_file_path;
            }
            bool load()
            {
                return ((!_V_loaded) and _F_read_file());
            }
            bool reload()
            {
                clear_file();
                return _F_read_file();
            }
            bool save()
            {
                return _F_save_file();
            }
            bool is_loaded()
            {
                return _V_loaded;
            }
            void clear_file()
            {
                _V_data.clear();
            }
            bool insert_line(unsigned int insert_position,unsigned int total_of_new_lines)
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
            bool remove_line(unsigned int remove_position)
            {
                if(remove_position<_V_data.size())
                {
                    _V_data.erase(_V_data.begin()+remove_position);
                    return true;
                }
                return false;
            }
            unsigned int size()
            {
                return _V_data.size();
            }
            std::string& operator [] (unsigned int line_position)
            {
                return _V_data[line_position];
            }
            ~FileStream()
            {
                clear_file();
            }
    };
}

#endif // INCLUDED_LL_FILESTREAM_H
