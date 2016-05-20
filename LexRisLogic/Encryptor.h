#ifndef INCLUDED_LL_ENCRYPTOR_H
#define INCLUDED_LL_ENCRYPTOR_H

#include <string>
#include <list>

namespace LL
{
    const char* DEFAULT_DICTIONARY=" 1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    class Encryptor
    {
        private:
            typedef std::pair<unsigned,std::string> _T_Type_last_key;
            std::string _V_pass;
            std::list<_T_Type_last_key> _V_key;
            std::string _V_dictionary=DEFAULT_DICTIONARY;
            std::string _F_encrypt(std::string& key,std::string word,unsigned int& j)
            {
                for(unsigned int i=0;i<word.size();++i)
                {
                    if(j>=key.size())
                        j=0;
                    int word_dictionary_id=_V_dictionary.find(word[i]);
                    int key_dictioonary_id=_V_dictionary.find(key[j]);
                    word[i]=_V_dictionary[_F_mod(word_dictionary_id+key_dictioonary_id,(int)_V_dictionary.size())];
                    ++j;
                }
                return word;
            }
            std::string _F_decrypt(std::string& key,std::string word)
            {
                for(unsigned int i=0,j=0;i<word.size();++i)
                {
                    if(j>=key.size())
                        j=0;
                    int word_dictionary_id=_V_dictionary.find(word[i]);
                    int key_dictioonary_id=_V_dictionary.find(key[j]);
                    word[i]=_V_dictionary[_F_mod((word_dictionary_id-key_dictioonary_id),(int)_V_dictionary.size())];
                    ++j;
                }
                return word;
            }
            void _F_add(std::string new_key)
            {
                unsigned int i=0,j=0;
                while(i<_V_pass.size())
                {
                    int word_dictionary_id=_V_dictionary.find(_V_pass[i]);
                    int key_dictioonary_id=_V_dictionary.find(new_key[j]);
                    _V_pass[i]=_V_dictionary[_F_mod(word_dictionary_id+key_dictioonary_id,(int)_V_dictionary.size())];
                    ++i;
                    ++j;
                    if(j==new_key.size())
                        j=0;
                }
                if(_V_pass.size()<new_key.size())
                {
                    std::string new_part_;
                    new_part_=new_key.substr(_V_pass.size(),new_key.size()-_V_pass.size());
                    for(std::list<_T_Type_last_key>::iterator iter=_V_key.begin();iter!=_V_key.end();++iter)
                        new_part_=_F_encrypt((*iter).second,new_part_,(*iter).first);
                    j=0;
                    _V_pass+=new_part_;
                }
                _V_key.push_back(_T_Type_last_key(j,new_key));
            }
            bool _F_validate_word(std::string word)
            {
                for(unsigned int i=0;i<word.size();++i)
                {
                    if(_V_dictionary.find(word[i])>=_V_dictionary.size())
                        return false;
                }
                return true;
            }
            int _F_mod(int dividend,int divisor)
            {
                return ((dividend%divisor)+divisor)%divisor;
            }
        public:
            bool add_new_key(std::string new_key)
            {
                if(_F_validate_word(new_key))
                {
                    _F_add(new_key);
                    return true;
                }
                return false;
            }
            void clear_keys()
            {
                _V_key.clear();
                _V_pass.clear();
            }
            void set_dictionary(std::string new_dictionary)
            {
                clear_keys();
                _V_dictionary=new_dictionary;
            }
            std::string get_dictionary()
            {
                return _V_dictionary;
            }
            std::string encrypt(std::string message)
            {
                unsigned int tempr=0;
                if(_F_validate_word(message))
                {
                    message=_F_encrypt(_V_pass,message,tempr);
                    return message;
                }
                return std::string();
            }
            std::string decrypt(std::string encrypted_message)
            {
                if(_F_validate_word(encrypted_message))
                {
                    encrypted_message=_F_decrypt(_V_pass,encrypted_message);
                    return encrypted_message;
                }
                return std::string();
            }
            ~Encryptor()
            {
                clear_keys();
            }
    };
}

#endif // INCLUDED_LL_ENCRYPTOR_H
