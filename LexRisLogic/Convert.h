/* Convert.h -- Convert Header - LexRis Logic Headers

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

#ifndef INCLUDED_LL_CONVERT_H
#define INCLUDED_LL_CONVERT_H

#include <sstream>
#include <string>
#include <stdlib.h>

namespace LL
{
    template<typename T>
    std::string to_string(T data)
    {
        std::stringstream streamer;
        streamer<<data;
        return streamer.str();
    }

    int to_int(std::string data)
    {
        return atoi(data.c_str());
    }

    float to_float(std::string data)
    {
        return strtof(data.c_str(),NULL);
    }

    double to_double(std::string data)
    {
        return strtod(data.c_str(),NULL);
    }
}

#endif // INCLUDED_LL_CONVERT_H
