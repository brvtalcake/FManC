/*

MIT License

Copyright (c) 2022 Axel PASCON

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

/* Compilers support macros need to be revised and reformulated */
#pragma once

#ifndef FMC_MACROS_H
#define FMC_MACROS_H

#ifndef FMC_PP_POINT
    #define FMC_PP_POINT() .
#endif

#ifndef FMC_CONCAT_MACROS
    #define FMC_CONCAT_MACROS
    #define FMC_CONCAT10(x, y) x##y
    #define FMC_CONCAT9(x, y) FMC_CONCAT10(x, y)
    #define FMC_CONCAT8(x, y) FMC_CONCAT9(x, y)
    #define FMC_CONCAT7(x, y) FMC_CONCAT8(x, y)
    #define FMC_CONCAT6(x, y) FMC_CONCAT7(x, y)
    #define FMC_CONCAT5(x, y) FMC_CONCAT6(x, y)
    #define FMC_CONCAT4(x, y) FMC_CONCAT5(x, y)
    #define FMC_CONCAT3(x, y) FMC_CONCAT4(x, y)
    #define FMC_CONCAT2(x, y) FMC_CONCAT3(x, y)
    #define FMC_CONCAT(x, y) FMC_CONCAT2(x, y)

    #define FMC_CONCAT_2(x, y) FMC_CONCAT(x, y)
    #define FMC_CONCAT_3(x, y, z) FMC_CONCAT(FMC_CONCAT(x, y), z)
    #define FMC_CONCAT_4(x, y, z, w) FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w)
    #define FMC_CONCAT_5(x, y, z, w, v) FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w), v)
    #define FMC_CONCAT_6(x, y, z, w, v, u) FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w), v), u)
    #define FMC_CONCAT_7(x, y, z, w, v, u, t) FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w), v), u), t)
    #define FMC_CONCAT_8(x, y, z, w, v, u, t, s) FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w), v), u), t), s)
    #define FMC_CONCAT_9(x, y, z, w, v, u, t, s, r) FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w), v), u), t), s), r)
#endif

#ifndef FMC_STRINGIZE_MACROS
    #define FMC_STRINGIZE_MACROS
    #define FMC_STRINGIZE10(x) #x
    #define FMC_STRINGIZE9(x) FMC_STRINGIZE10(x)
    #define FMC_STRINGIZE8(x) FMC_STRINGIZE9(x)
    #define FMC_STRINGIZE7(x) FMC_STRINGIZE8(x)
    #define FMC_STRINGIZE6(x) FMC_STRINGIZE7(x)
    #define FMC_STRINGIZE5(x) FMC_STRINGIZE6(x)
    #define FMC_STRINGIZE4(x) FMC_STRINGIZE5(x)
    #define FMC_STRINGIZE3(x) FMC_STRINGIZE4(x)
    #define FMC_STRINGIZE2(x) FMC_STRINGIZE3(x)
    #define FMC_STRINGIZE(x) FMC_STRINGIZE2(x)
#endif

#ifndef FMC_STRINGIZE_2
    #define FMC_STRINGIZE_2(x, y) FMC_STRINGIZE(FMC_CONCAT(x, y))
    #define FMC_STRINGIZE_3(x, y, z) FMC_STRINGIZE(FMC_CONCAT(FMC_CONCAT(x, y), z))
    #define FMC_STRINGIZE_4(x, y, z, w) FMC_STRINGIZE(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w))
    #define FMC_STRINGIZE_5(x, y, z, w, v) FMC_STRINGIZE(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w), v))
    #define FMC_STRINGIZE_6(x, y, z, w, v, u) FMC_STRINGIZE(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w), v), u))
    #define FMC_STRINGIZE_7(x, y, z, w, v, u, t) FMC_STRINGIZE(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w), v), u), t))
    #define FMC_STRINGIZE_8(x, y, z, w, v, u, t, s) FMC_STRINGIZE(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w), v), u), t), s))
    #define FMC_STRINGIZE_9(x, y, z, w, v, u, t, s, r) FMC_STRINGIZE(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w), v), u), t), s), r))
#endif

#ifndef FMC_VERSION
    #define FMC_MAJOR_VERSION 0
    #define FMC_MINOR_VERSION 1
    #define FMC_PATCH_VERSION 0
    #define FMC_VERSION FMC_CONCAT_5(FMC_MAJOR_VERSION, FMC_PP_POINT(), FMC_MINOR_VERSION, FMC_PP_POINT(), FMC_PATCH_VERSION)
    #define FMC_VERSION_STRING FMC_STRINGIZE_5(FMC_MAJOR_VERSION, FMC_PP_POINT(), FMC_MINOR_VERSION, FMC_PP_POINT(), FMC_PATCH_VERSION)
    #define FMC_VERSION_NUMBER FMC_CONCAT_4(FMC_MAJOR_VERSION, FMC_MINOR_VERSION, FMC_PATCH_VERSION, L)
#endif

#if defined(FMC_COMPILING_ON_WINDOWS)
    #undef FMC_COMPILING_ON_WINDOWS
#endif
#if defined(_WIN16) || defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || defined(MINGW32) || defined(__MINGW32__) || defined(__MINGW64__) || defined(__CYGWIN__)
    #define FMC_COMPILING_ON_WINDOWS 1
#endif

#if defined(FMC_COMPILING_ON_CYGWIN_ENVIRONMENT)
    #undef FMC_COMPILING_ON_CYGWIN_ENVIRONMENT
#endif
#if defined(__CYGWIN__)
    #define FMC_COMPILING_ON_CYGWIN_ENVIRONMENT 1
#endif

#if defined(FMC_COMPILING_ON_UNIX)
    #undef FMC_COMPILING_ON_UNIX
#endif
#if defined(__unix__) || defined(__unix) || defined(unix) || defined(__APPLE__) || defined(__MACH__) || defined(__linux__) || defined(__FreeBSD__) || defined(__NetBSD__) || defined(__OpenBSD__) || defined(__DragonFly__) || defined(__GNU__) || defined(__GLIBC__) || defined(__HAIKU__) || defined(__QNXNTO__) || defined(__QNX__) || defined(__SYLLABLE__) || defined(__ANDROID__) || defined(__EMSCRIPTEN__) || defined(__BEOS__) || defined(__HAIKU__) || defined(__INTEGRITY) || defined(__Lynx__) || defined(__MINT__) || defined(__OS400__) || defined(__OS2__) || defined(__OS9000__) || defined(__OSF__) || defined(__TOS_AIX__) || defined(__TOS_HPUX__) || defined(__TOS_LINUX__) || defined(__TOS_OS400__) || defined(__TOS_OS2__) || defined(__TOS_OS9000__) || defined(__TOS_OSF__) || defined(__TOS_SCO__) || defined(__TOS_SOLARIS__) || defined(__TOS_SUNOS__) || defined(__TOS_ULTRIX__) || defined(__TOS_UNIXWARE__) || defined(__TOS_VMS__) 
    #define FMC_COMPILING_ON_UNIX 1
#endif

#if defined(FMC_COMPILING_ON_LINUX)
    #undef FMC_COMPILING_ON_LINUX
#endif
#if defined(__linux__) || defined(__gnu_linux__) || defined(__linux) 
    #define FMC_COMPILING_ON_LINUX 1
#endif

#if defined(FMC_COMPILING_ON_MACOS)
    #undef FMC_COMPILING_ON_MACOS
#endif
#if (defined(__APPLE__) && defined(__MACH__)) || defined(__MACOSX__) || defined(__MACOS__) || defined(__TOS_MACOS__) || defined(macintosh) || defined(Macintosh)
    #define FMC_COMPILING_ON_MACOS 1
#endif

#if defined(FMC_COMPILING_WITH_GCC)
    #undef FMC_COMPILING_WITH_GCC
#endif
#if defined(__GNUC__) && !defined(__clang__)
    #if __STDC_VERSION__ >= 201112L
        #define FMC_COMPILING_WITH_GCC 1
    #else
        #error "Your GCC version is not C11 compliant."
    #endif
#endif

#if defined(FMC_COMPILING_WITH_CLANG)
    #undef FMC_COMPILING_WITH_CLANG
#endif
#if defined(__clang__)
    #if __STDC_VERSION__ >= 201112L
        #define FMC_COMPILING_WITH_CLANG 1
    #else
        #error "Your Clang version is not C11 compliant."
    #endif
#endif

#if defined(FMC_COMPILING_WITH_MINGW)
    #undef FMC_COMPILING_WITH_MINGW
#endif
#if defined(__MINGW32__) || defined(__MINGW64__)
    #if __STDC_VERSION__ >= 201112L
        #define FMC_COMPILING_WITH_MINGW 1
    #else
        #error "Your MinGW version is not C11 compliant."
    #endif
#endif

#if defined(FMC_COMPILING_WITH_CYGWIN)
    #undef FMC_COMPILING_WITH_CYGWIN
#endif
#if defined(__CYGWIN__)
    #if __STDC_VERSION__ >= 201112L
        #define FMC_COMPILING_WITH_CYGWIN 1
    #else
        #error "Your Cygwin's GCC version is not C11 compliant."
    #endif
#endif

#if !defined(FMC_COMPILING_WITH_GCC) && !defined(FMC_COMPILING_WITH_CLANG) && !defined(FMC_COMPILING_WITH_MINGW) && !defined(FMC_COMPILING_WITH_CYGWIN)
    #error "Your compiler is not yet supported."
#endif

#if FMC_COMPILING_ON_CYGWIN_ENVIRONMENT
    #error "Cygwin is not yet supported."
#endif

#if FMC_COMPILING_ON_UNIX && !(FMC_COMPILING_ON_LINUX || FMC_COMPILING_ON_MACOS)
    #error "Your Unix environment is not yet supported."
#endif

#ifndef FMC_SHARED
    #if FMC_COMPILING_ON_WINDOWS && !defined(FMC_STATIC)
        #if defined(FMC_BUILD_DLL)
            #define FMC_SHARED __declspec(dllexport)
        #elif defined(USE_FMC_DLL)
            #define FMC_SHARED __declspec(dllimport)
        #else
            #error "You must define FMC_BUILD_DLL to build the DLL or USE_FMC_DLL to use the built DLL. To use or build the static library, please define FMC_STATIC."
        #endif
    #elif FMC_COMPILING_ON_WINDOWS && defined(FMC_STATIC)
        #define FMC_SHARED
    #elif FMC_COMPILING_ON_UNIX && (FMC_COMPILING_ON_LINUX || FMC_COMPILING_ON_MACOS) /*Add more platforms*/
        #if defined(FMC_STATIC) || defined(USE_FMC_DLL) || defined(FMC_BUILD_DLL)
            #warning "You don't have to specify STATIC, USE_FMC_DLL or BUILD_DLL on Linux, Unix or Mac OS X. These are ignored on your system."
        #endif
        #define FMC_SHARED
    #else
        #error "Unsupported OS"
    #endif // PLATFORMS
#endif // FMC_SHARED

#ifndef FMC_COMPILE_TIME_ERROR
    #if defined(__GNUC__) || defined(__clang__)
        #define FMC_COMPILE_TIME_ERROR(msg) _Pragma(STRINGIZE(GCC error STRINGIZE(msg)))
    #elif defined(_MSC_VER) && _MSC_VER >= 1600
        #define FMC_COMPILE_TIME_ERROR(msg) __pragma(message(__FILE__ "(" STRINGIZE(__LINE__) "): error: " STRINGIZE(msg)))
    #elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        #define FMC_COMPILE_TIME_ERROR(msg) _Static_assert(0, STRINGIZE(msg));
    #else
        #error "Your compiler is not supported. Please use GCC, Clang, MSVC, on a C11 compliant version."
    #endif
#endif // FMC_COMPILE_TIME_ERROR


#ifndef FMC_PRINTF_FMT
    #if (defined(__GNUC__) && __GNUC__ >= 2) || defined(__clang__) 
        #define FMC_PRINTF_FMT(fmt_pos, args_pos) __attribute__((format(printf, fmt_pos, args_pos)))
    #else
        #define FMC_PRINTF_FMT(fmt_pos, args_pos) /* Just ignore this, there will be an error anyway */
    #endif
#endif // FMC_PRINTF_FMT

#ifndef FMC_INLINE
    #if defined(__GNUC__) || defined(__clang__)
        #define FMC_INLINE inline __attribute__((always_inline))
    #else
        #define FMC_INLINE inline
    #endif
#endif // FMC_INLINE

#endif // FMC_MACROS_H
