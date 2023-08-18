#ifndef __KAYDEE__CORE_H__
#define __KAYDEE__CORE_H__

#ifdef KD_PLATFORM_WINDOWS
#ifdef KD_BUILD_DLL
#define KAYDEE_API __declspec(dllexport)
#else
#define KAYDEE_API __declspec(dllimport)
#endif
#endif

#ifdef KD_ENABLE_ASSERTS
#if defined(_WIN32) || defined(_WIN64)
#define KD_ASSERT(x, ...)                                                      \
    {                                                                          \
        if (!(x)) {                                                            \
            KD_ERROR("Assertion Failed: {0}", __VA_ARGS__);                    \
            __debugbreak();                                                    \
        }                                                                      \
    }
#define KD_CORE_ASSERT(x, ...)                                                 \
    {                                                                          \
        if (!(x)) {                                                            \
            KD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);               \
            __debugbreak();                                                    \
        }                                                                      \
    }
#else
#include <csignal>

#define KD_ASSERT(x, ...)                                                      \
    {                                                                          \
        if (!(x)) {                                                            \
            KD_ERROR("Assertion Failed: {0}", __VA_ARGS__);                    \
            raise(SIGTRAP);                                                    \
        }                                                                      \
    }
#define KD_CORE_ASSERT(x, ...)                                                 \
    {                                                                          \
        if (!(x)) {                                                            \
            KD_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__);               \
            raise(SIGTRAP);                                                    \
        }                                                                      \
    }
#endif
#else
#define KD_ASSERT(...)
#define KD_CORE_ASSERT(...)
#endif

#define BIT(x) (1 << x)

#endif