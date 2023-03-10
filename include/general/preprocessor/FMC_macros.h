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
#include <stdint.h>
#include "FMC_attributes.h"

#if defined(_FORTIFY_SOURCE) && _FORTIFY_SOURCE < 1
    #undef _FORTIFY_SOURCE
    #define _FORTIFY_SOURCE 1   
#elif !defined(_FORTIFY_SOURCE)
    #define _FORTIFY_SOURCE 1   // Enable _FORTIFY_SOURCE to this minimum value if not already enabled
#endif

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

#if defined(FMC_INT_PRINT_FMT) || defined(FMC_INT_SCANF_FMT)
    #undef FMC_INT_PRINT_FMT
    #undef FMC_INT_SCANF_FMT
#endif
#define FMC_INT_PRINT_FMT(first_str, integer, second_str) _Generic((integer), \
    signed char: first_str "%d" second_str,                                   \
    unsigned char: first_str "%u" second_str,                                 \
    signed short: first_str "%hd" second_str,                                 \
    unsigned short: first_str "%hu" second_str,                               \
    signed int: first_str "%d" second_str,                                    \
    unsigned int: first_str "%u" second_str,                                  \
    signed long: first_str "%ld" second_str,                                  \
    unsigned long: first_str "%lu" second_str,                                \
    signed long long: first_str "%lld" second_str,                            \
    unsigned long long: first_str "%llu" second_str)

#define FMC_INT_SCANF_FMT(first_str, integer, second_str) _Generic((integer), \
    signed char: first_str "%d" second_str,                                    \
    unsigned char: first_str "%u" second_str,                                  \
    signed short: first_str "%hd" second_str,                                  \
    unsigned short: first_str "%hu" second_str,                                \
    signed int: first_str "%d" second_str,                                     \
    unsigned int: first_str "%u" second_str,                                   \
    signed long: first_str "%ld" second_str,                                   \
    unsigned long: first_str "%lu" second_str,                                 \
    signed long long: first_str "%lld" second_str,                             \
    unsigned long long: first_str "%llu" second_str)

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

#if defined(FMC_MAKE_UI8) || defined(FMC_MAKE_UI16) || defined(FMC_MAKE_UI32) || defined(FMC_MAKE_UI64) || defined(FMC_MAKE_I8) || defined(FMC_MAKE_I16) || defined(FMC_MAKE_I32) || defined(FMC_MAKE_I64) 
    #undef FMC_MAKE_UI8
    #undef FMC_MAKE_UI16
    #undef FMC_MAKE_UI32
    #undef FMC_MAKE_UI64
    #undef FMC_MAKE_I8
    #undef FMC_MAKE_I16
    #undef FMC_MAKE_I32
    #undef FMC_MAKE_I64
#endif
#define FMC_MAKE_UI8(x) UINT8_C(x)
#define FMC_MAKE_UI16(x) UINT16_C(x)
#define FMC_MAKE_UI32(x) UINT32_C(x)
#define FMC_MAKE_UI64(x) UINT64_C(x)
#define FMC_MAKE_I8(x) INT8_C(x)
#define FMC_MAKE_I16(x) INT16_C(x)
#define FMC_MAKE_I32(x) INT32_C(x)
#define FMC_MAKE_I64(x) INT64_C(x)

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

#if defined(FMC_OPT)
    #undef FMC_OPT
#endif
#define FMC_OPT(...) , __VA_ARGS__

#ifndef FMC_alloca
    #define FMC_alloca(size) __builtin_alloca(size)
#endif

#if defined(FMC_objSize) || defined(FMC_dynObjSize) || defined(FMC_prefetch) || defined(FMC_arrSize)
    #undef FMC_objSize
    #undef FMC_dynObjSize
    #undef FMC_prefetch
    #undef FMC_arrSize
#endif
#define FMC_objSize(ptr, type) __builtin_object_size(ptr, type)
#define FMC_dynObjSize(ptr, type) __builtin_dynamic_object_size(ptr, type)
#define FMC_prefetch(ptr, ...) __builtin_prefetch(ptr __VA_ARGS__)
#define FMC_arrSize(arr) (sizeof(arr)/sizeof(arr[0]))

#ifndef FMC_PROB
    #define FMC_PROB(true_expr, prob) __builtin_expect_with_probability((true_expr), 1L, prob)
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
#define FMC_COMPILE_TIME_ERROR(msg) _Pragma(FMC_STRINGIZE(GCC error FMC_STRINGIZE(msg)))

#ifdef FMC_UNIMPLEMENTED
    #undef FMC_UNIMPLEMENTED
#endif
#define FMC_UNIMPLEMENTED(msg) FMC_COMPILE_TIME_ERROR(msg)


#ifdef FMC_ERROR_CHECK
    #undef FMC_ERROR_CHECK
#endif // FMC_ERROR_CHECK
// thought about this for lisibility, not sure if I'll use it though
#define FMC_ERROR_CHECK(cond, todo_stmt, enable_debug, todo_before) \
    if (cond)                                                       \
    {   if(enable_debug) todo_before                                \
        todo_stmt;                                                  \
    }

#if defined(lock_err_mtx) || defined(unlock_err_mtx) || defined(create_err_mtx) || defined(destroy_err_mtx)
    #undef lock_err_mtx
    #undef unlock_err_mtx
    #undef create_err_mtx
    #undef destroy_err_mtx
#endif
#if defined(FMC_COMPILING_ON_WINDOWS)
    #if defined(SEC_ATTR_STRUCT)
        #undef SEC_ATTR_STRUCT
    #endif
    #define SEC_ATTR_STRUCT {sizeof(SECURITY_ATTRIBUTES), NULL, TRUE}
    #define lock_err_mtx()                                                                      \
        if (WaitForSingleObject(FMC_ERR_STACK_MUTEX, 20000) != WAIT_OBJECT_0)                   \
        {                                                                                       \
            FMC_printBrightRedError(stderr,                                                     \
                "FATAL ERROR : could not update error stack due to blocking mutex.");           \
            exit(EXIT_FAILURE);                                                                 \
        }
    
    #define unlock_err_mtx()                                                                    \
        if (!ReleaseMutex(FMC_ERR_STACK_MUTEX))                                                 \
        {                                                                                       \
            FMC_printBrightRedError(stderr,                                                     \
                "FATAL ERROR : could not update error stack due to mutex release failure.");    \
            exit(EXIT_FAILURE);                                                                 \
        }

    #define create_err_mtx()                                                                    \
        FMC_ERR_STACK_MUTEX = CreateMutexA(SEC_ATTR_STRUCT, FALSE, NULL);                       \
        if (FMC_ERR_STACK_MUTEX == INVALID_HANDLE_VALUE)                                        \
        {                                                                                       \
            FMC_printBrightRedError(stderr,                                                     \
                "FATAL ERROR : could not create mutex for error stack.");                       \
            exit(EXIT_FAILURE);                                                                 \
        }
    
    #define destroy_err_mtx()                                                                   \
        if (!CloseHandle(FMC_ERR_STACK_MUTEX))                                                  \
        {                                                                                       \
            FMC_printBrightRedError(stderr,                                                     \
                "FATAL ERROR : could not close mutex for error stack.");                        \
            exit(EXIT_FAILURE);                                                                 \
        }
#else
    #define lock_err_mtx()                                                                      \
        struct timespec ts;                                                                     \
        clock_gettime(CLOCK_REALTIME, &ts);                                                     \
        ts.tv_sec += 20;                                                                        \
        if (pthread_mutex_timedlock(&FMC_ERR_STACK_MUTEX, &ts) != 0)                            \
        {                                                                                       \
            FMC_printBrightRedError(stderr,                                                     \
                "FATAL ERROR : could not update error stack due to blocking mutex.");           \
            exit(EXIT_FAILURE);                                                                 \
        }
        
    #define unlock_err_mtx()                                                                    \
        if (pthread_mutex_unlock(&FMC_ERR_STACK_MUTEX) != 0)                                    \
        {                                                                                       \
            FMC_printBrightRedError(stderr,                                                     \
                "FATAL ERROR : could not update error stack due to mutex release failure.");    \
            exit(EXIT_FAILURE);                                                                 \
        }
    // mutex must be recursive, must be sharaable between threads and processes and we must set his robustness to PTHREAD_MUTEX_ROBUST_NP
    #define create_err_mtx()                                                                    \
        if (pthread_mutexattr_init(&FMC_ERR_STACK_MUTEX_ATTR) != 0)                             \
        {                                                                                       \
            FMC_printBrightRedError(stderr,                                                     \
                "FATAL ERROR : could not initialize mutex attribute for error stack.");         \
            exit(EXIT_FAILURE);                                                                 \
        }                                                                                       \
        if (pthread_mutexattr_settype(&FMC_ERR_STACK_MUTEX_ATTR,                                \
            PTHREAD_MUTEX_RECURSIVE) != 0)                                                      \
        {                                                                                       \
            FMC_printBrightRedError(stderr,                                                     \
                "FATAL ERROR : could not set mutex attribute type for error stack.");           \
            exit(EXIT_FAILURE);                                                                 \
        }                                                                                       \
        if (pthread_mutexattr_setpshared(&FMC_ERR_STACK_MUTEX_ATTR,                             \
            PTHREAD_PROCESS_SHARED) != 0)                                                       \
        {                                                                                       \
            FMC_printBrightRedError(stderr,                                                     \
                "FATAL ERROR : could not set mutex attribute process sharing for error stack.");\
            exit(EXIT_FAILURE);                                                                 \
        }                                                                                       \
        if (pthread_mutexattr_setrobust(&FMC_ERR_STACK_MUTEX_ATTR,                              \
            PTHREAD_MUTEX_ROBUST) != 0)                                                         \
        {                                                                                       \
            FMC_printBrightRedError(stderr,                                                     \
                "FATAL ERROR : could not set mutex attribute robustness for error stack.");     \
            exit(EXIT_FAILURE);                                                                 \
        }                                                                                       \
        if (pthread_mutex_init(&FMC_ERR_STACK_MUTEX, &FMC_ERR_STACK_MUTEX_ATTR) != 0)           \
        {                                                                                       \
            FMC_printBrightRedError(stderr,                                                     \
                "FATAL ERROR : could not create mutex for error stack.");                       \
            exit(EXIT_FAILURE);                                                                 \
        }

    #define destroy_err_mtx()                                                                   \
        if (pthread_mutex_destroy(&FMC_ERR_STACK_MUTEX) != 0)                                   \
        {                                                                                       \
            FMC_printBrightRedError(stderr,                                                     \
                "FATAL ERROR : could not destroy mutex for error stack.");                      \
            exit(EXIT_FAILURE);                                                                 \
        }                                                                                       \
        if (pthread_mutexattr_destroy(&FMC_ERR_STACK_MUTEX_ATTR) != 0)                          \
        {                                                                                       \
            FMC_printBrightRedError(stderr,                                                     \
                "FATAL ERROR : could not destroy mutex attribute for error stack.");            \
            exit(EXIT_FAILURE);                                                                 \
        }

#endif // ERR_STACK_MUTEX_MACROS


#endif // FMC_MACROS_H
