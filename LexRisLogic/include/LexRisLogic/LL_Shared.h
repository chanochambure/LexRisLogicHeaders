#ifndef INCLUDED_LL_SHARED_H
#define INCLUDED_LL_SHARED_H

#ifdef _WIN32
    #ifdef LL_BUILD_DLL
        #define LL_SHARED __declspec(dllexport)
    #else
        #define LL_SHARED __declspec(dllimport)
    #endif
#else
    #define LL_SHARED
#endif

#endif // INCLUDED_LL_SHARED_H
