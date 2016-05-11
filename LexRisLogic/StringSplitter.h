#ifndef INCLUDED_LL_STRINGSPLITTER_H
#define INCLUDED_LL_STRINGSPLITTER_H

#include <string>
#include <vector>

namespace LL
{
    class StringSplitter
    {
        private:
            std::vector<std::string> _V_data;
            std::string _V_string;
        public:
            void set_string(std::string new_string)
            {
                _V_data.clear();
                _V_string=new_string;
            }
            std::string get_string()
            {
                return _V_string;
            }
            bool split(char character='\n')
            {
                _V_data.clear();
                std::string data=_V_string;
                if(!data.size())
                    return false;
                for(unsigned int position=data.find(character);position<data.size();position=data.find(character))
                {
                    _V_data.push_back(data.substr(0,position));
                    data=data.substr(position+1,data.size()-(position+1));
                }
                if(data.size())
                    _V_data.push_back(data);
                return true;
            }
            unsigned int size()
            {
                return _V_data.size();
            }
            std::string operator [] (unsigned int index)
            {
                return _V_data[index];
            }
            ~StringSplitter()
            {
                _V_data.clear();
            }
    };
}

#endif // INCLUDED_LL_STRINGSPLITTER_H
