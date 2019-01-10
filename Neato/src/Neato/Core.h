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

#ifdef NEATO_ENABLE_ASSERTS
	#define NEATO_ASSERT(x, ...) { if(!(x)) { NEATO_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define NEATO_CORE_ASSERT(x, ...) { if(!(x)) { NEATO_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define NEATO_ASSERT(x, ...)
	#define NEATO_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)
