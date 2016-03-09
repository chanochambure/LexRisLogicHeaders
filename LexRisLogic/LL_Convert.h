#ifndef LL_CONVERT_H_INCLUDED
#define LL_CONVERT_H_INCLUDED

#include <sstream>
#include <string>
#include <stdlib.h>

namespace LL
{
    template<typename T>
    std::string to_string(T Data)
    {
        std::stringstream st;
        st<<Data;
        return st.str();
    }

    int to_int(std::string Data)
    {
        return atoi(Data.c_str());
    }

    float to_float(std::string Data)
    {
        return strtof(Data.c_str(),NULL);
    }

    double to_double(std::string Data)
    {
        return strtod(Data.c_str(),NULL);
    }
}

#endif // LL_CONVERT_H_INCLUDED
