#ifndef LL_STRING_SPLITTER_H_INCLUDED
#define LL_STRING_SPLITTER_H_INCLUDED

#include <string>
#include <vector>

using namespace std;

class StringSplitter
{
    private:
        vector<string> _data;
        string _str;
    public:
        void set_string(string n_str){_data.clear();_str=n_str;}
        string get_string(){return _str;}
        bool split(char character='\n');
        unsigned int size(){return _data.size();}
        string operator [] (unsigned int i){return _data[i];}
        ~StringSplitter(){_data.clear();}
};

bool StringSplitter::split(char character)
{
    _data.clear();
    string data=_str;
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

#endif // LL_STRING_SPLITTER_H_INCLUDED
