/* StringSplitter.h -- String Splitter Header - LexRis Logic Headers

    Copyright (c) 2016 LexRisLogic

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

#ifndef INCLUDED_LL_STRINGSPLITTER_H
#define INCLUDED_LL_STRINGSPLITTER_H

#include <string>
#include <vector>

namespace LL
{
    class StringSplitter
    {
        private:
            std::string _V_string;
            std::vector<std::string> _V_data;
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
            void clear()
            {
                _V_data.clear();
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
