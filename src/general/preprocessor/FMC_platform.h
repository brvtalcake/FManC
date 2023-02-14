/*

MIT License

Copyright (c) 2022-2023 Axel PASCON

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

#ifndef FMC_PLATFORM_H
#define FMC_PLATFORM_H


#if defined(FMC_COMPILING_ON_WINDOWS)
    #undef FMC_COMPILING_ON_WINDOWS
#elif defined(FMC_COMPILING_ON_LINUX)
    #undef FMC_COMPILING_ON_LINUX
#endif // OS detection
#if defined(_WIN32) || defined(_WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__)
    #define FMC_COMPILING_ON_WINDOWS 1
#elif defined(__linux__) || defined(__linux) || defined(linux) || defined(__gnu_linux__) 
    #define FMC_COMPILING_ON_LINUX 1
#else
    #warning "This library hasn't been tested on this OS."
#endif // OS management

#if defined(FMC_COMPILING_ON_MINGW)
    #undef FMC_COMPILING_ON_MINGW
#elif defined(FMC_COMPILING_WITH_GCC)
    #undef FM_COMPILING_WITH_GCC
#endif // Compiler and environment detection
#if defined(__MINGW32__) || defined(__MINGW64__) || defined(__MINGW32) || defined(__MINGW64) || defined(__MINGW__)
    #define FMC_COMPILING_ON_MINGW 1
#elif defined(__GNUC__) || defined(__GNUG__)
    #define FMC_COMPILING_WITH_GCC 1
#else
    #warning "This library hasn't been tested on your compiler."
#endif // Compiler and environment management

// check C17 standard
#ifndef __cplusplus
    #if __STDC_VERSION__ < 201710L
        #error "FManC requires C17 standard or higher."
    #endif
#else
    #if __cplusplus < 201703L
        #error "FManC requires C++17 standard or higher."
    #endif
#endif

#endif /* FMC_PLATFORM_H */
