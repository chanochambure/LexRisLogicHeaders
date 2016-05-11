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
            std::vector<std::string> _V_data;
            std::string _V_file_path;
            bool _V_loaded=false;
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
