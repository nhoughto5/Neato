#pragma once
#ifdef NEATO_PLATFORM_WINDOWS
    #ifdef NEATO_BUILD_DLL
        #define NEATO_API _declspec(dllexport)
    #else
        #define NEATO_API _declspec(dllimport)
    #endif //NEATO_BUILD_DLL
#else
    #error Neato Only Supports Windows!
#endif //NEATO_PLATFORM_WINDOWS
