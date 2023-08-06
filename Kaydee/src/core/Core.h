#ifndef __KAYDEE__CORE_H__
#define __KAYDEE__CORE_H__

#ifdef KD_PLATFORM_WINDOWS
    #ifdef KD_BUILD_DLL
        #define KAYDEE_API __declspec(dllexport)
    #else
        #define KAYDEE_API __declspec(dllimport)
    #endif
#endif

#endif