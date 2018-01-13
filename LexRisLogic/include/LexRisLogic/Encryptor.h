/* Encryptor.h -- Encryptor Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_ENCRYPTOR_H
#define INCLUDED_LL_ENCRYPTOR_H

#include "LL_Shared.h"

#include <string>
#include <list>

namespace LL
{
    static const char* const DEFAULT_DICTIONARY=" 1234567890ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";
    class LL_SHARED Encryptor
    {
        private:
            typedef std::pair<unsigned,std::string> _T_Type_last_key;
            std::string _V_pass;
            std::list<_T_Type_last_key> _V_key;
            std::string _V_dictionary=DEFAULT_DICTIONARY;
            std::string _F_encrypt(std::string& key,std::string word,unsigned int& j);
            std::string _F_decrypt(std::string& key,std::string word);
            void _F_add(std::string new_key);
            bool _F_validate_word(std::string word);
            int _F_mod(int dividend,int divisor);
        public:
            bool add_new_key(std::string new_key);
            void clear_keys();
            void set_dictionary(std::string new_dictionary);
            std::string get_dictionary();
            std::string encrypt(std::string message);
            std::string decrypt(std::string encrypted_message);
            ~Encryptor();
    };
}

#endif // INCLUDED_LL_ENCRYPTOR_H
