#ifndef __PLATFORM_HPP__
#define __PLATFORM_HPP__

#include <inttypes.h>

#if defined(_WIN32)
#define SYSTEM_WINDOWS
#elif defined(__APPLE__)
#define SYSTEM_MACOSX
#endif

#if defined(_M_IX86) || defined(___i386__) || defined(__i386) || defined(__X86__) || defined(_X86_) || defined(__I86__)
    #define ARCHITECTURE_X86
#elif defined(_M_X64) || defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64)
    #define ARCHITECTURE_X86_64
#else
    #error supports only x86 and x64 systems.
#endif

#endif
