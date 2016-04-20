#ifndef LL_STRINGSPLITTER_H_INCLUDED
#define LL_STRINGSPLITTER_H_INCLUDED

#include <string>
#include <vector>

namespace LL
{
    class LL_StringSplitter
    {
        private:
            std::vector<std::string> _data;
            std::string _str;
        public:
            void set_string(std::string n_str){_data.clear();_str=n_str;}
            std::string get_string(){return _str;}
            bool split(char character='\n');
            unsigned int size(){return _data.size();}
            std::string operator [] (unsigned int i){return _data[i];}
            ~LL_StringSplitter(){_data.clear();}
    };

    bool LL_StringSplitter::split(char character)
    {
        _data.clear();
        std::string data=_str;
        if(data.size()==0)
            return 0;
        unsigned int position=data.find(character);
        while(position<data.size())
        {
            _data.push_back(data.substr(0,position));
            data=data.substr(position+1,data.size()-(position+1));
            position=data.find(character);
        }
        if(data.size())
            _data.push_back(data);
        return 1;
}
}

#endif // LL_STRINGSPLITTER_H_INCLUDED
