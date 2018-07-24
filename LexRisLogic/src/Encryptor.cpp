/* Encryptor.cpp -- Encryptor Source - LexRis Logic Headers

    Copyright (c) 2017-2018 LexRisLogic

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

#include "../include/LexRisLogic/Encryptor.h"

namespace LL
{
    std::string Encryptor::_F_encrypt(std::string& key,std::string word,unsigned int& j)
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
    std::string Encryptor::_F_decrypt(std::string& key,std::string word)
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
    void Encryptor::_F_add(std::string new_key)
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
    bool Encryptor::_F_validate_word(std::string word)
    {
        for(unsigned int i=0;i<word.size();++i)
        {
            if(_V_dictionary.find(word[i])>=_V_dictionary.size())
                return false;
        }
        return true;
    }
    int Encryptor::_F_mod(int dividend,int divisor)
    {
        return ((dividend%divisor)+divisor)%divisor;
    }
    bool Encryptor::add_new_key(std::string new_key)
    {
        if(_F_validate_word(new_key))
        {
            _F_add(new_key);
            return true;
        }
        return false;
    }
    void Encryptor::clear_keys()
    {
        _V_key.clear();
        _V_pass.clear();
    }
    void Encryptor::set_dictionary(std::string new_dictionary)
    {
        clear_keys();
        _V_dictionary=new_dictionary;
    }
    std::string Encryptor::get_dictionary()
    {
        return _V_dictionary;
    }
    std::string Encryptor::encrypt(std::string message)
    {
        unsigned int tempr=0;
        if(_F_validate_word(message))
        {
            message=_F_encrypt(_V_pass,message,tempr);
            return message;
        }
        return std::string();
    }
    std::string Encryptor::decrypt(std::string encrypted_message)
    {
        if(_F_validate_word(encrypted_message))
        {
            encrypted_message=_F_decrypt(_V_pass,encrypted_message);
            return encrypted_message;
        }
        return std::string();
    }
    Encryptor::~Encryptor()
    {
        clear_keys();
    }
}
