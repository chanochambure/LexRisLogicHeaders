#ifndef LL_ENCRYPTOR_H_INCLUDED
#define LL_ENCRYPTOR_H_INCLUDED

#include <string>
#include <list>

using namespace std;

#define DEFAULT_DICTIONARY " 1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"

class Encryptor
{
    private:
        list<string> _key;
        string _dictionary;
        string _encrypt(string& key,string word);
        string _decrypt(string& key,string word);
        bool _validate_word(string word);
        int __mod__(int a,int b){return ((a%b)+b)%b;}
    public:
        Encryptor(){_dictionary=DEFAULT_DICTIONARY;}
        bool new_key(string nk){if(_validate_word(nk)){_key.push_back(nk);return 1;}return 0;}
        void clear_keys(){_key.clear();}
        void set_dictionary(string dc){_key.clear();_dictionary=dc;}
        string get_dictionary(){return _dictionary;}
        string encrypt(string word);
        string decrypt(string encrypted_word);
};

bool Encryptor::_validate_word(string word)
{
    for(unsigned int i=0;i<word.size();++i)
    {
        if(_dictionary.find(word[i])>=_dictionary.size())
            return false;
    }
    return true;
}

string Encryptor::_encrypt(string& key,string word)
{
    for(unsigned int i=0,j=0;i<word.size();++i)
    {
        if(j==key.size())
            j=0;
        int w_d_i=_dictionary.find(word[i]);
        int k_d_i=_dictionary.find(key[j]);
        word[i]=_dictionary[__mod__(w_d_i+k_d_i,(int)_dictionary.size())];
        ++j;
    }
    return word;
}

string Encryptor::_decrypt(string& key,string word)
{
    for(unsigned int i=0,j=0;i<word.size();++i)
    {
        if(j==key.size())
            j=0;
        int w_d_i=_dictionary.find(word[i]);
        int k_d_i=_dictionary.find(key[j]);
        word[i]=_dictionary[__mod__((w_d_i-k_d_i),(int)_dictionary.size())];
        ++j;
    }
    return word;
}

string Encryptor::encrypt(string word)
{
    if(_validate_word(word))
    {
        for(list<string>::iterator i=_key.begin();i!=_key.end();++i)
            word=_encrypt(*i,word);
        return word;
    }
    return string();
}

string Encryptor::decrypt(string encrypted_word)
{
    if(_validate_word(encrypted_word))
    {
        for(list<string>::reverse_iterator i=_key.rbegin();i!=_key.rend();++i)
            encrypted_word=_decrypt(*i,encrypted_word);
        return encrypted_word;
    }
    return string();
}

#endif // LL_ENCRYPTOR_H_INCLUDED
