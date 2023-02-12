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


#pragma once

#ifndef FMC_MACROS_H
#define FMC_MACROS_H

#include "FMC_platform.h"
#include "FMC_attributes.h"

/* Used to avoid false warnings (for example "attribute destructor/constructor does not take argument", when it actually can) */
#if defined(__INTELLISENSE__ )
    #pragma diag_suppress 1094
#endif

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

#ifndef FMC_STRINGIZE_X
    #define FMC_STRINGIZE_X
    #define FMC_STRINGIZE_2(x, y) FMC_STRINGIZE(FMC_CONCAT(x, y))
    #define FMC_STRINGIZE_3(x, y, z) FMC_STRINGIZE(FMC_CONCAT(FMC_CONCAT(x, y), z))
    #define FMC_STRINGIZE_4(x, y, z, w) FMC_STRINGIZE(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w))
    #define FMC_STRINGIZE_5(x, y, z, w, v) FMC_STRINGIZE(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w), v))
    #define FMC_STRINGIZE_6(x, y, z, w, v, u) FMC_STRINGIZE(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w), v), u))
    #define FMC_STRINGIZE_7(x, y, z, w, v, u, t) FMC_STRINGIZE(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w), v), u), t))
    #define FMC_STRINGIZE_8(x, y, z, w, v, u, t, s) FMC_STRINGIZE(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w), v), u), t), s))
    #define FMC_STRINGIZE_9(x, y, z, w, v, u, t, s, r) FMC_STRINGIZE(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(FMC_CONCAT(x, y), z), w), v), u), t), s), r))
#endif

#ifdef FMC_DEFER
    #undef FMC_DEFER
#endif
#define FMC_DEFER(stmt, body) do body while (0); stmt


#ifndef FMC_METHODS
    #define FMC_METHODS

    #define DECL_METHOD(name, ret, ...) \
        ret (*name)(__VA_ARGS__)

    #define INIT_STRUCT_METHOD(method, associated_function) \
        .method = associated_function

#endif // FMC_METHODS

/*#ifndef FMC_OVERLOAD
    #define FMC_OVERLOAD(func)
*/

#ifdef FMC_VERSION
    #undef FMC_VERSION
    #undef FMC_VERSION_STRING
    #undef FMC_VERSION_NUMBER
    #undef FMC_MAJOR_VERSION
    #undef FMC_MINOR_VERSION
    #undef FMC_PATCH_VERSION
#endif // FMC_VERSION

#define FMC_MAJOR_VERSION 1
#define FMC_MINOR_VERSION 0
#define FMC_PATCH_VERSION 0
#define FMC_VERSION FMC_CONCAT_5(FMC_MAJOR_VERSION, FMC_PP_POINT(), FMC_MINOR_VERSION, FMC_PP_POINT(), FMC_PATCH_VERSION)
#define FMC_VERSION_STRING FMC_STRINGIZE_5(FMC_MAJOR_VERSION, FMC_PP_POINT(), FMC_MINOR_VERSION, FMC_PP_POINT(), FMC_PATCH_VERSION)
#define FMC_VERSION_NUMBER FMC_CONCAT_4(FMC_MAJOR_VERSION, FMC_MINOR_VERSION, FMC_PATCH_VERSION, L)


/* Maybe I'll have to modify this, even though it sounds fine to me now. */
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
    #elif FMC_COMPILING_ON_LINUX || FMC_COMPILING_ON_MACOS
        #if defined(FMC_STATIC) || defined(USE_FMC_DLL) || defined(FMC_BUILD_DLL)
            #warning "You don't have to specify STATIC, USE_FMC_DLL or BUILD_DLL on Linux, Unix or Mac OS X. These are ignored on your system."
        #endif
        #define FMC_SHARED
    #else
        #error "Unsupported OS"
    #endif // PLATFORMS
#endif // FMC_SHARED

#ifdef FMC_COMPILE_TIME_ERROR
    #undef FMC_COMPILE_TIME_ERROR
#endif // FMC_COMPILE_TIME_ERROR
#define FMC_COMPILE_TIME_ERROR(msg) _Pragma(STRINGIZE(GCC error STRINGIZE(msg)))


#ifdef FMC_ERROR_CHECK
    #undef FMC_ERROR_CHECK
#endif // FMC_ERROR_CHECK
#define FMC_ERROR_CHECK(cond) \
    if (cond) 




#endif // FMC_MACROS_H
