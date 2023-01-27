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

#pragma once

#ifndef FMC_ERRORS_H
#define FMC_ERRORS_H

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) && !defined(STATIC)
    #if defined(BUILD_DLL)
        #define SHARED __declspec(dllexport)
    #elif defined(USE_FMC_DLL)
        #define SHARED __declspec(dllimport)
    #else
        #error "You must define BUILD_DLL to build the DLL or USE_FMC_DLL to use the built DLL. To use or build the static library, please define STATIC."
    #endif
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) && defined(STATIC)
   #define SHARED
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__) && !defined(STATIC) && !defined(USE_FMC_DLL) && !defined(BUILD_DLL) // Linux, Unix, Mac OS X

    #if defined(STATIC) || defined(USE_FMC_DLL) || defined(BUILD_DLL)
        #warning "You don't have to specify STATIC, USE_FMC_DLL or BUILD_DLL on Linux, Unix or Mac OS X."
    #endif
    #define SHARED
#else
    #error "Unsupported platform"
#endif // PLATFORMS

#ifndef FMC_STYLES
    #define FMC_STYLES

    #define RESET "\x1b[0m"

    #define FG_BLACK "\x1b[30m"
    #define FG_RED "\x1b[31m"
    #define FG_GREEN "\x1b[32m"
    #define FG_YELLOW "\x1b[33m"
    #define FG_BLUE "\x1b[34m"
    #define FG_MAGENTA "\x1b[35m"
    #define FG_CYAN "\x1b[36m"
    #define FG_WHITE "\x1b[37m"
    #define FG_BRIGHT_BLACK "\x1b[90m"
    #define FG_BRIGHT_RED "\x1b[91m"
    #define FG_BRIGHT_GREEN "\x1b[92m"
    #define FG_BRIGHT_YELLOW "\x1b[93m"
    #define FG_BRIGHT_BLUE "\x1b[94m"
    #define FG_BRIGHT_MAGENTA "\x1b[95m"
    #define FG_BRIGHT_CYAN "\x1b[96m"
    #define FG_BRIGHT_WHITE "\x1b[97m"

    #define BG_BLACK "\x1b[40m"
    #define BG_RED "\x1b[41m"
    #define BG_GREEN "\x1b[42m"
    #define BG_YELLOW "\x1b[43m"
    #define BG_BLUE "\x1b[44m"
    #define BG_MAGENTA "\x1b[45m"
    #define BG_CYAN "\x1b[46m"
    #define BG_WHITE "\x1b[47m"
    #define BG_BRIGHT_BLACK "\x1b[100m"
    #define BG_BRIGHT_RED "\x1b[101m"
    #define BG_BRIGHT_GREEN "\x1b[102m"
    #define BG_BRIGHT_YELLOW "\x1b[103m"
    #define BG_BRIGHT_BLUE "\x1b[104m"
    #define BG_BRIGHT_MAGENTA "\x1b[105m"
    #define BG_BRIGHT_CYAN "\x1b[106m"
    #define BG_BRIGHT_WHITE "\x1b[107m"

    #define TXT_BOLD "\x1b[1m"
    #define TXT_DIM "\x1b[2m"
    #define TXT_UNDERLINED "\x1b[4m"
    #define TXT_BLINK "\x1b[5m"
    #define TXT_REVERSE "\x1b[7m"
    #define TXT_HIDDEN "\x1b[8m"

#endif // FMC_STYLES

// TODO : Implement a better error system
// TODO : Add a functions to print custom errors with different styles





#endif // FMC_ERRORS_H
