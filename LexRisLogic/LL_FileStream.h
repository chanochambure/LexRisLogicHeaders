#ifndef LL_FILESTREAM_H_INCLUDED
#define LL_FILESTREAM_H_INCLUDED

#include <string>
#include <vector>
#include <fstream>

using namespace std;

class FileStream
{
    private:
        vector<string> _data;
        string _file_path;
        bool _loaded=0;
        bool _read_file()
        {
            _loaded=1;
            ifstream file(_file_path.c_str());
            if(file.is_open())
            {
                string buffer;
                while(getline(file,buffer))_data.push_back(buffer);
                file.close();
                return 1;
            }
            return 0;
        }
        bool _save_file()
        {
            ofstream file(_file_path.c_str(), ofstream::out | ofstream::trunc);
            if(file.is_open() and _data.size())
            {
                unsigned int sizer=_data.size()-1;
                for(unsigned int i=0;i<sizer;++i)
                    file<<_data[i]<<endl;
                file<<_data[sizer];
                return 1;
            }
            file.close();
            return 0;
        }
    public:
        void set_path(string new_path){_file_path=new_path;}
        string get_path(){return _file_path;}
        bool load(){if(!_loaded)return _read_file();return 0;}
        void reload(){_data.clear();_read_file();}
        bool save(){return _save_file();}
        void clear_file(){_data.clear();}
        bool insert_line(unsigned int pos,unsigned int n_lines){if(pos<=_data.size()){vector<string>::iterator iter=_data.begin()+pos;for(unsigned int i=0;i<n_lines;++i)iter=_data.insert(iter,string());return 1;}return 0;}
        bool remove_line(unsigned int line){if(line<_data.size()){_data.erase(_data.begin()+line);return 1;}return 0;}
        unsigned int size(){return _data.size();}
        string& operator [] (unsigned int line){return _data[line];}
        ~FileStream(){clear_file();}
};

#endif // LL_FILESTREAM_H_INCLUDED
