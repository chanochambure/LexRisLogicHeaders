/* StringSplitter.cpp -- String Splitter Source - LexRis Logic Headers

    Copyright (c) 2017 LexRisLogic

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

#include "../include/LexRisLogic/StringSplitter.h"

namespace LL
{
    void StringSplitter::set_string(std::string new_string)
    {
        _V_data.clear();
        _V_string=new_string;
    }
    std::string StringSplitter::get_string()
    {
        return _V_string;
    }
    bool StringSplitter::split(char character)
    {
        _V_data.clear();
        if(!_V_string.size())
            return false;
        std::string data;
        for(unsigned int i=0;i<_V_string.size();++i)
        {
            if(_V_string[i]==character)
            {
                _V_data.push_back(data);
                data.clear();
            }
            else
                data+=_V_string[i];
        }
        if(data.size())
            _V_data.push_back(data);
        return true;
    }
    unsigned int StringSplitter::size()
    {
        return _V_data.size();
    }
    void StringSplitter::clear()
    {
        _V_data.clear();
    }
    const std::string StringSplitter::operator [] (unsigned int index)
    {
        return _V_data[index];
    }
    StringSplitter::~StringSplitter()
    {
        _V_data.clear();
    }
}
