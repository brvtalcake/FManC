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

#ifdef __CYGWIN__
    #error "Cygwin is currently not supported. Please use MinGW or MSYS2's MinGW package."
#endif

#ifndef STRINGIZE_MACROS
    #define STRINGIZE_MACROS
    #define STRINGIZE6(x) #x
    #define STRINGIZE5(x) STRINGIZE6(x)
    #define STRINGIZE4(x) STRINGIZE5(x)
    #define STRINGIZE3(x) STRINGIZE4(x)
    #define STRINGIZE2(x) STRINGIZE3(x)
    #define STRINGIZE(x) STRINGIZE2(x)
#endif


#ifndef FMC_SHARED
    #if (defined(_WIN16) || defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || defined(_WIN32_WCE)) && !defined(STATIC)
        #if defined(BUILD_DLL)
            #define FMC_SHARED __declspec(dllexport)
        #elif defined(USE_FMC_DLL)
            #define FMC_SHARED __declspec(dllimport)
        #else
            #error "You must define BUILD_DLL to build the DLL or USE_FMC_DLL to use the built DLL. To use or build the static library, please define STATIC."
        #endif
    #elif (defined(_WIN16) || defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) || defined(_WIN32_WCE)) && defined(STATIC)
    #define FMC_SHARED
    #elif defined(__linux__) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__) /*Add more platforms*/
        #if defined(STATIC) || defined(USE_FMC_DLL) || defined(BUILD_DLL)
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
    #elif defined(_MSC_VER)
        #define FMC_COMPILE_TIME_ERROR(msg) __pragma(message(__FILE__ "(" STRINGIZE(__LINE__) "): error: " STRINGIZE(msg)))
    #elif defined(__STDC_VERSION__) && __STDC_VERSION__ >= 201112L
        #define FMC_COMPILE_TIME_ERROR(msg) _Static_assert(0, STRINGIZE(msg));
    #else
        #error "Your compiler is not supported. Please use GCC, Clang, MSVC or a C11 compiler."
    #endif
#endif // FMC_COMPILE_TIME_ERROR


#ifndef FMC_PRINTF_FMT
    #if (defined(__GNUC__) && __GNUC__ >= 2) || defined(__clang__) 
        #define FMC_PRINTF_FMT(fmt_pos, args_pos) __attribute__((format(printf, fmt_pos, args_pos)))
    #else
        #define FMT_CHECK_FORMAT(...)                           \
            do {                                                \
                char const dummy = sizeof(printf(__VA_ARGS__)); \
                (void)dummy;                                    \
            } while (0)

        #define MY_FMT(...)                                    \
            do {                                               \
                CHECK_FORMAT(__VA_ARGS__);                     \
                MyFormatFunc(__FILE__, __LINE__, __VA_ARGS__); \
            } while (0)
    #endif
#endif // FMC_PRINTF_FMT



#endif // FMC_MACROS_H
