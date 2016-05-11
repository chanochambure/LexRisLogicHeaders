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
