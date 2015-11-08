#ifndef LL_CONVERT_H_INCLUDED
#define LL_CONVERT_H_INCLUDED

#include <sstream>
#include <string>
#include <stdlib.h>

using namespace std;

template<typename T>
string to_string(T Data)
{
    stringstream st;
    st<<Data;
    return st.str();
}

int to_int(string Data)
{
    return atoi(Data.c_str());
}

float to_float(string Data)
{
    return strtof(Data.c_str(),NULL);
}

double to_double(string Data)
{
    return strtod(Data.c_str(),NULL);
}

#endif // LL_CONVERT_H_INCLUDED
