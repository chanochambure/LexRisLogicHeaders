#ifndef LL_ENCRYPTOR_H_INCLUDED
#define LL_ENCRYPTOR_H_INCLUDED

#include <string>
#include <list>

namespace LL
{
    #define LL_DEFAULT_DICTIONARY " 1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz"
    class LL_Encryptor
    {
        private:
            typedef std::pair<unsigned,std::string> _last_key;
            std::string _pass_;
            std::list<_last_key> _key;
            std::string _dictionary=LL_DEFAULT_DICTIONARY;
            std::string _encrypt(std::string& key,std::string word,unsigned int& j);
            std::string _decrypt(std::string& key,std::string word);
            void _add_(std::string nk);
            bool _validate_word(std::string word);
            int __mod__(int a,int b){return ((a%b)+b)%b;}
        public:
            bool add_new_key(std::string nk){if(_validate_word(nk)){_add_(nk);return 1;}return 0;}
            void clear_keys(){_key.clear();_pass_.clear();}
            void set_dictionary(std::string dc){clear_keys();_dictionary=dc;}
            std::string get_dictionary(){return _dictionary;}
            std::string encrypt(std::string word);
            std::string decrypt(std::string encrypted_word);
            ~LL_Encryptor(){clear_keys();}
    };

    bool LL_Encryptor::_validate_word(std::string word)
    {
        for(unsigned int i=0;i<word.size();++i)
        {
            if(_dictionary.find(word[i])>=_dictionary.size())
                return false;
        }
        return true;
    }

    void LL_Encryptor::_add_(std::string nk)
    {
        unsigned int i=0,j=0;
        while(i<_pass_.size())
        {
            int w_d_i=_dictionary.find(_pass_[i]);
            int k_d_i=_dictionary.find(nk[j]);
            _pass_[i]=_dictionary[__mod__(w_d_i+k_d_i,(int)_dictionary.size())];
            ++i;
            ++j;
            if(j==nk.size())
                j=0;
        }
        if(_pass_.size()<nk.size())
        {
            std::string new_part_;
            new_part_=nk.substr(_pass_.size(),nk.size()-_pass_.size());
            for(std::list<_last_key>::iterator iter=_key.begin();iter!=_key.end();++iter)
                new_part_=_encrypt((*iter).second,new_part_,(*iter).first);
            j=0;
            _pass_+=new_part_;
        }
        _key.push_back(_last_key(j,nk));
    }

    std::string LL_Encryptor::_encrypt(std::string& key,std::string word,unsigned int& j)
    {
        for(unsigned int i=0;i<word.size();++i)
        {
            if(j>=key.size())
                j=0;
            int w_d_i=_dictionary.find(word[i]);
            int k_d_i=_dictionary.find(key[j]);
            word[i]=_dictionary[__mod__(w_d_i+k_d_i,(int)_dictionary.size())];
            ++j;
        }
        return word;
    }

    std::string LL_Encryptor::_decrypt(std::string& key,std::string word)
    {
        for(unsigned int i=0,j=0;i<word.size();++i)
        {
            int w_d_i=_dictionary.find(word[i]);
            int k_d_i=_dictionary.find(key[j]);
            word[i]=_dictionary[__mod__((w_d_i-k_d_i),(int)_dictionary.size())];
            ++j;
            if(j>=key.size())
                j=0;
        }
        return word;
    }

    std::string LL_Encryptor::encrypt(std::string word)
    {
        unsigned int tempr=0;
        if(_validate_word(word))
        {
            word=_encrypt(_pass_,word,tempr);
            return word;
        }
        return std::string();
    }

    std::string LL_Encryptor::decrypt(std::string encrypted_word)
    {
        if(_validate_word(encrypted_word))
        {
            encrypted_word=_decrypt(_pass_,encrypted_word);
            return encrypted_word;
        }
        return std::string();
    }
}

#endif // LL_ENCRYPTOR_H_INCLUDED
