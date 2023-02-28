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
#include <metalang99.h>
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

#if defined(FMC_ID) || defined(FMC_ID2) || defined(FMC_ID3) || defined(FMC_ID4) || defined(FMC_ID5) || defined(FMC_ID6) || defined(FMC_ID7) || defined(FMC_ID8) || defined(FMC_ID9)
    #undef FMC_ID
    #undef FMC_ID2
    #undef FMC_ID3
    #undef FMC_ID4
    #undef FMC_ID5
    #undef FMC_ID6
    #undef FMC_ID7
    #undef FMC_ID8
    #undef FMC_ID9
#endif
#define FMC_ID9(x) x
#define FMC_ID8(x) FMC_ID9(x)
#define FMC_ID7(x) FMC_ID8(x)
#define FMC_ID6(x) FMC_ID7(x)
#define FMC_ID5(x) FMC_ID6(x)
#define FMC_ID4(x) FMC_ID5(x)
#define FMC_ID3(x) FMC_ID4(x)
#define FMC_ID2(x) FMC_ID3(x)
#define FMC_ID(x) FMC_ID2(x)

#if defined(FMC_DECR_BY)
    #undef FMC_DECR_BY
#endif
#define FMC_DECR_BY(x, y) ML99_EVAL(ML99_call(ML99_sub, v(x), v(y)))

#ifdef defer
    #undef defer
#endif
#define defer(stmt, body) do body while (0); stmt

#if defined(foreach) || defined(foreach_counter) || defined(foreach_stop_cond) || defined(LOOP_TO_THE_END) || defined(LOOP_WHILE)
    #undef foreach
    #undef foreach_counter
    #undef foreach_stop_cond
    #undef LOOP_TO_THE_END
    #undef LOOP_WHILE
#endif
#define LOOP_TO_THE_END ML99_nothing()
#define LOOP_WHILE(x) ML99_just(v(x))
#define foreach_counter(lines_after_foreach) FMC_CONCAT_2(base_index, FMC_DECR_BY(__LINE__, lines_after_foreach))
#define foreach_stop_cond(x) ML99_EVAL(ML99_EVAL(ML99_call(ML99_if, ML99_isNothing(x), v(ML99_id(ML99_id(v(foreach_counter(0) < sizeof(array)/sizeof(array[0]))))), v(ML99_maybeUnwrap(x)))))
#define foreach(elem, array, start, stop_index_cond) size_t foreach_counter(0) = start; for(typeof(array[foreach_counter(0)]) elem = array[foreach_counter(0)]; foreach_stop_cond(stop_index_cond) ; foreach_counter(0)++, elem = array[foreach_counter(0)])


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
#define FMC_VERSION_NUMBER FMC_CONCAT_2(FMC_MAJOR_VERSION*10000 + FMC_MINOR_VERSION*100 + FMC_PATCH_VERSION, L)

#ifndef FMC_alloca
    #define FMC_alloca(size) __builtin_alloca(size)
#endif

#ifndef FMC_PROB
    #define FMC_PROB(true_expr, prob) __builtin_expect_with_probability(true_expr, 1, prob)
#endif

#ifndef FMC_UNREACHABLE
    #define FMC_UNREACHABLE __builtin_unreachable()
#endif

#ifndef FMC_MAKE_VOID
    #define FMC_MAKE_VOID(expr) do { (void)(expr); } while (0)
#endif

#if defined(FMC_BEGIN_DECLS) || defined(FMC_END_DECLS)
    #undef FMC_BEGIN_DECLS
    #undef FMC_END_DECLS
#endif
#ifdef __cplusplus
    #define FMC_BEGIN_DECLS extern "C" {
    #define FMC_END_DECLS }
#else
    #define FMC_BEGIN_DECLS
    #define FMC_END_DECLS
#endif

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
            #warning "You don't have to specify FMC_STATIC, USE_FMC_DLL or FMC_BUILD_DLL on Linux, Unix or Mac OS X. These are ignored on your system."
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
// thought about this for lisibility, not sure if I'll use it though
#define FMC_ERROR_CHECK(cond, todo_stmt, enable_debug, todo_before) \
    if (cond)                                                       \
    {   if(enable_debug) todo_before                                \
        todo_stmt;                                                  \
    }

#endif // FMC_MACROS_H
