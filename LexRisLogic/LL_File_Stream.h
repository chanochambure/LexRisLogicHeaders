#ifndef LL_FILE_STREAM_H_INCLUDED
#define LL_FILE_STREAM_H_INCLUDED

#include <string>
#include <vector>
#include <fstream>

namespace LL
{
    class LL_FileStream
    {
        private:
            std::vector<std::string> _data;
            std::string _file_path;
            bool _loaded=0;
            bool _read_file()
            {
                _loaded=1;
                std::ifstream file(_file_path.c_str());
                if(file.is_open())
                {
                    std::string buffer;
                    while(getline(file,buffer))_data.push_back(buffer);
                    file.close();
                    return 1;
                }
                return 0;
            }
            bool _save_file()
            {
                std::ofstream file(_file_path.c_str(), std::ofstream::out | std::ofstream::trunc);
                if(file.is_open() and _data.size())
                {
                    unsigned int sizer=_data.size()-1;
                    for(unsigned int i=0;i<sizer;++i)
                        file<<_data[i]<<std::endl;
                    file<<_data[sizer];
                    return 1;
                }
                file.close();
                return 0;
            }
        public:
            void set_path(std::string new_path){_data.clear();_file_path=new_path;_loaded=0;}
            std::string get_path(){return _file_path;}
            bool load(){return ((!_loaded) and _read_file());}
            bool reload(){_data.clear();return _read_file();}
            bool save(){return _save_file();}
            void clear_file(){_data.clear();}
            bool insert_line(unsigned int pos,unsigned int n_lines){if(pos<=_data.size()){std::vector<std::string>::iterator iter=_data.begin()+pos;for(unsigned int i=0;i<n_lines;++i)iter=_data.insert(iter,std::string());return 1;}return 0;}
            bool remove_line(unsigned int line){if(line<_data.size()){_data.erase(_data.begin()+line);return 1;}return 0;}
            unsigned int size(){return _data.size();}
            std::string& operator [] (unsigned int line){return _data[line];}
            ~LL_FileStream(){clear_file();}
};
}

#endif // LL_FILE_STREAM_H_INCLUDED
