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

#ifndef FMC_MACROS_H
#define FMC_MACROS_H

#include "FMC_platform.h"
#include <metalang99.h>
#include <chaos/preprocessor.h>
#include <stdint.h>
#include <stdalign.h>
#include "assert.h"
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

#if defined(FMC_1) || defined(FMC_2) || defined(FMC_3) || defined(FMC_4) || defined(FMC_5) || defined(FMC_6) || defined(FMC_7) || defined(FMC_8) || defined(FMC_9) || defined(FMC_10) || defined(FMC_11) || defined(FMC_12) || defined(FMC_13) || defined(FMC_14) || defined(FMC_15) || defined(FMC_16) || defined(FMC_17) || defined(FMC_18) || defined(FMC_19) || defined(FMC_20) || defined(FMC_21) || defined(FMC_22) || defined(FMC_23) || defined(FMC_24) || defined(FMC_25) || defined(FMC_26) || defined(FMC_27) || defined(FMC_28) || defined(FMC_29) || defined(FMC_30) || defined(FMC_31) || defined(FMC_32) || defined(FMC_33) || defined(FMC_34) || defined(FMC_35) || defined(FMC_36) || defined(FMC_37) || defined(FMC_38) || defined(FMC_39) || defined(FMC_40) || defined(FMC_41) || defined(FMC_42) || defined(FMC_43) || defined(FMC_44) || defined(FMC_45) || defined(FMC_46) || defined(FMC_47) || defined(FMC_48) || defined(FMC_49) || defined(FMC_50) || defined(FMC_51) || defined(FMC_52) || defined(FMC_53) || defined(FMC_54) || defined(FMC_55) || defined(FMC_56) || defined(FMC_57) || defined(FMC_58) || defined(FMC_59) || defined(FMC_60) || defined(FMC_61) || defined(FMC_62) || defined(FMC_63) || defined(FMC_64)
    #undef FMC_1
    #undef FMC_2
    #undef FMC_3
    #undef FMC_4
    #undef FMC_5
    #undef FMC_6
    #undef FMC_7
    #undef FMC_8
    #undef FMC_9
    #undef FMC_10
    #undef FMC_11
    #undef FMC_12
    #undef FMC_13
    #undef FMC_14
    #undef FMC_15
    #undef FMC_16
    #undef FMC_17
    #undef FMC_18
    #undef FMC_19
    #undef FMC_20
    #undef FMC_21
    #undef FMC_22
    #undef FMC_23
    #undef FMC_24
    #undef FMC_25
    #undef FMC_26
    #undef FMC_27
    #undef FMC_28
    #undef FMC_29
    #undef FMC_30
    #undef FMC_31
    #undef FMC_32
    #undef FMC_33
    #undef FMC_34
    #undef FMC_35
    #undef FMC_36
    #undef FMC_37
    #undef FMC_38
    #undef FMC_39
    #undef FMC_40
    #undef FMC_41
    #undef FMC_42
    #undef FMC_43
    #undef FMC_44
    #undef FMC_45
    #undef FMC_46
    #undef FMC_47
    #undef FMC_48
    #undef FMC_49
    #undef FMC_50
    #undef FMC_51
    #undef FMC_52
    #undef FMC_53
    #undef FMC_54
    #undef FMC_55
    #undef FMC_56
    #undef FMC_57
    #undef FMC_58
    #undef FMC_59
    #undef FMC_60
    #undef FMC_61
    #undef FMC_62
    #undef FMC_63
    #undef FMC_64
#endif
#define FMC_1 1
#define FMC_2 2
#define FMC_3 3
#define FMC_4 4
#define FMC_5 5
#define FMC_6 6
#define FMC_7 7
#define FMC_8 8
#define FMC_9 9
#define FMC_10 10
#define FMC_11 11
#define FMC_12 12
#define FMC_13 13
#define FMC_14 14
#define FMC_15 15
#define FMC_16 16
#define FMC_17 17
#define FMC_18 18
#define FMC_19 19
#define FMC_20 20
#define FMC_21 21
#define FMC_22 22
#define FMC_23 23
#define FMC_24 24
#define FMC_25 25
#define FMC_26 26
#define FMC_27 27
#define FMC_28 28
#define FMC_29 29
#define FMC_30 30
#define FMC_31 31
#define FMC_32 32
#define FMC_33 33
#define FMC_34 34
#define FMC_35 35
#define FMC_36 36
#define FMC_37 37
#define FMC_38 38
#define FMC_39 39
#define FMC_40 40
#define FMC_41 41
#define FMC_42 42
#define FMC_43 43
#define FMC_44 44
#define FMC_45 45
#define FMC_46 46
#define FMC_47 47
#define FMC_48 48
#define FMC_49 49
#define FMC_50 50
#define FMC_51 51
#define FMC_52 52
#define FMC_53 53
#define FMC_54 54
#define FMC_55 55
#define FMC_56 56
#define FMC_57 57
#define FMC_58 58
#define FMC_59 59
#define FMC_60 60
#define FMC_61 61
#define FMC_62 62
#define FMC_63 63
#define FMC_64 64

/* #if defined(FMC_GEN_ARG_LIST) || defined(FMC_GEN_ARG_LIST_HELPER_IMPL) || defined(FMC_GEN_ARG_LIST_HELPER_ARITY)
    #undef FMC_GEN_ARG_LIST
    #undef FMC_GEN_ARG_LIST_HELPER_IMPL
    #undef FMC_GEN_ARG_LIST_HELPER_ARITY
#endif
#define FMC_GEN_ARG_LIST(...) ML99_EVAL(ML99_call(ML99_variadicsForEachI, v(FMC_GEN_ARG_LIST_HELPER_IMPL), v(__VA_ARGS__)))
#define FMC_GEN_ARG_LIST_HELPER_IMPL(_arg, _i)  */


#if defined(FMC_GET_ARGC) || defined(FMC_GET_ARGC_INT) || defined(FMC_GET_ARGC_HELPER)
    #undef FMC_GET_ARGC
    #undef FMC_GET_ARGC_INT
    #undef FMC_GET_ARGC_HELPER
#endif
#define FMC_GET_ARGC(...) FMC_GET_ARGC_HELPER(__VA_ARGS__)
#define FMC_GET_ARGC_HELPER(...) FMC_ID(FMC_GET_ARGC_INT(0, ## __VA_ARGS__, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0))
#define FMC_GET_ARGC_INT(_0, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_, _17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_, _32_, _33_, _34_, _35_, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, count, ...) FMC_ID(count)

#if defined(FMC_GET_ARGN) || defined(FMC_GET_ARGN_INT)
    #undef FMC_GET_ARGN
    #undef FMC_GET_ARGN_INT
#endif
// Get the Nth argument (max 25 args)
#define FMC_GET_ARGN(_n, ...) CHAOS_PP_VARIADIC_ELEM(_n, __VA_ARGS__) // FMC_GET_ARGN_INT(_n, ## __VA_ARGS__, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0)
#define FMC_GET_ARGN_INT(_n, _0, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, ...) FMC_CONCAT(FMC_GET_ARGN_INT_, _n)(_0, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_)
#if defined(FMC_GET_ARGN_INT_0) || defined(FMC_GET_ARGN_INT_1) || defined(FMC_GET_ARGN_INT_2) || defined(FMC_GET_ARGN_INT_3) || defined(FMC_GET_ARGN_INT_4) || defined(FMC_GET_ARGN_INT_5) || defined(FMC_GET_ARGN_INT_6) || defined(FMC_GET_ARGN_INT_7) || defined(FMC_GET_ARGN_INT_8) || defined(FMC_GET_ARGN_INT_9)
    #undef FMC_GET_ARGN_INT_0
    #undef FMC_GET_ARGN_INT_1
    #undef FMC_GET_ARGN_INT_2
    #undef FMC_GET_ARGN_INT_3
    #undef FMC_GET_ARGN_INT_4
    #undef FMC_GET_ARGN_INT_5
    #undef FMC_GET_ARGN_INT_6
    #undef FMC_GET_ARGN_INT_7
    #undef FMC_GET_ARGN_INT_8
    #undef FMC_GET_ARGN_INT_9
#endif
#define FMC_GET_ARGN_INT_0(_0, ...) _0
#define FMC_GET_ARGN_INT_1(_0, _1_, ...) _1_
#define FMC_GET_ARGN_INT_2(_0, _1_, _2_, ...) _2_
#define FMC_GET_ARGN_INT_3(_0, _1_, _2_, _3_, ...) _3_
#define FMC_GET_ARGN_INT_4(_0, _1_, _2_, _3_, _4_, ...) _4_
#define FMC_GET_ARGN_INT_5(_0, _1_, _2_, _3_, _4_, _5_, ...) _5_
#define FMC_GET_ARGN_INT_6(_0, _1_, _2_, _3_, _4_, _5_, _6_, ...) _6_
#define FMC_GET_ARGN_INT_7(_0, _1_, _2_, _3_, _4_, _5_, _6_, _7_, ...) _7_
#define FMC_GET_ARGN_INT_8(_0, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, ...) _8_
#define FMC_GET_ARGN_INT_9(_0, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, ...) _9_

#if defined(FMC_GET_LAST_ARG) || defined(FMC_NFIRST_ARGS)
    #undef FMC_GET_LAST_ARG
    #undef FMC_NFIRST_ARGS
#endif
// max 25 args
#define FMC_GET_LAST_ARG(...) FMC_GET_ARGN(ML99_EVAL(ML99_call(ML99_dec, v(FMC_GET_ARGC(__VA_ARGS__)))), ## __VA_ARGS__)
#define FMC_NFIRST_ARGS(_n, ...) // TODO: finish this one

#if defined(FMC_GET_ARGN_FROM_LAST)
    #undef FMC_GET_ARGN_FROM_LAST
#endif
#define FMC_GET_ARGN_FROM_LAST(_n, ...) \
    CHAOS_PP_EXPR(\
        CHAOS_PP_VARIADIC_IF(CHAOS_PP_OR\
            (CHAOS_PP_COMPL(CHAOS_PP_BOOL(FMC_GET_ARGC(__VA_ARGS__))))\
            (FMC_GREATER(_n, FMC_DEC(FMC_GET_ARGC(__VA_ARGS__)))))\
        (static_assert(0, "FMC_GET_ARGN_FROM_LAST: Invalid index"))\
        (ML99_EVAL(ML99_listGet(v(_n), ML99_listReverse(ML99_list(v(__VA_ARGS__))))))\
    )

#if defined(FMC_CHOOSE_FUNC)
    #undef FMC_CHOOSE_FUNC
#endif
#define FMC_CHOOSE_FUNC(param_number) FMC_CHOOSE_FUNC_##param_number

#if defined(FMC_CHOOSE_FUNC_1) || defined(FMC_CHOOSE_FUNC_2) || defined(FMC_CHOOSE_FUNC_3) || defined(FMC_CHOOSE_FUNC_4) || defined(FMC_CHOOSE_FUNC_5)
    #undef FMC_CHOOSE_FUNC_1
    #undef FMC_CHOOSE_FUNC_2
    #undef FMC_CHOOSE_FUNC_3
    #undef FMC_CHOOSE_FUNC_4
    #undef FMC_CHOOSE_FUNC_5
#endif
#define FMC_CHOOSE_FUNC_1(func_without_vaargs, func_with_vaargs, param1, ...)                                                   \
ML99_EVAL(ML99_call(ML99_if, ML99_natEq(v(FMC_GET_ARGC(__VA_ARGS__)), v(0)),                                                    \
v(func_without_vaargs(param1)), v(func_with_vaargs(param1, __VA_ARGS__))))
#define FMC_CHOOSE_FUNC_2(func_without_vaargs, func_with_vaargs, param1, param2, ...)                                           \
ML99_EVAL(ML99_call(ML99_if, ML99_natEq(v(FMC_GET_ARGC(__VA_ARGS__)), v(0)),                                                    \
v(func_without_vaargs(param1, param2)), v(func_with_vaargs(param1, param2, __VA_ARGS__))))
#define FMC_CHOOSE_FUNC_3(func_without_vaargs, func_with_vaargs, param1, param2, param3, ...)                                   \
ML99_EVAL(ML99_call(ML99_if, ML99_natEq(v(FMC_GET_ARGC(__VA_ARGS__)), v(0)),                                                    \
v(func_without_vaargs(param1, param2, param3)), v(func_with_vaargs(param1, param2, param3, __VA_ARGS__))))
#define FMC_CHOOSE_FUNC_4(func_without_vaargs, func_with_vaargs, param1, param2, param3, param4, ...)                           \
ML99_EVAL(ML99_call(ML99_if, ML99_natEq(v(FMC_GET_ARGC(__VA_ARGS__)), v(0)),                                                    \
v(func_without_vaargs(param1, param2, param3, param4)), v(func_with_vaargs(param1, param2, param3, param4, __VA_ARGS__))))
#define FMC_CHOOSE_FUNC_5(func_without_vaargs, func_with_vaargs, param1, param2, param3, param4, param5, ...)                   \
ML99_EVAL(ML99_call(ML99_if, ML99_natEq(v(FMC_GET_ARGC(__VA_ARGS__)), v(0)),                                                    \
v(func_without_vaargs(param1, param2, param3, param4, param5)), v(func_with_vaargs(param1, param2, param3, param4, param5,      \
__VA_ARGS__))))


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
#define FMC_ID9(...) __VA_ARGS__
#define FMC_ID8(...) FMC_ID9(__VA_ARGS__)
#define FMC_ID7(...) FMC_ID8(__VA_ARGS__)
#define FMC_ID6(...) FMC_ID7(__VA_ARGS__)
#define FMC_ID5(...) FMC_ID6(__VA_ARGS__)
#define FMC_ID4(...) FMC_ID5(__VA_ARGS__)
#define FMC_ID3(...) FMC_ID4(__VA_ARGS__)
#define FMC_ID2(...) FMC_ID3(__VA_ARGS__)
#define FMC_ID(...) FMC_ID2(__VA_ARGS__)

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

// Generated usefull macros
#if defined(FMC_X_EXP_Y) || defined(FMC_X_EXP_Y_PRED) || defined(FMC_X_EXP_Y_OP) || defined(FMC_X_EXP_Y_MACRO)
    #undef FMC_X_EXP_Y
    #undef FMC_X_EXP_Y_PRED
    #undef FMC_X_EXP_Y_OP
    #undef FMC_X_EXP_Y_MACRO
#endif
#define FMC_X_EXP_Y_PRED(s, ...) CHAOS_PP_GREATER_EQUAL(CHAOS_PP_VARIADIC_ELEM(2, __VA_ARGS__), 1)
#define FMC_X_EXP_Y_OP(s, ...) \
    CHAOS_PP_ARBITRARY_MUL(CHAOS_PP_VARIADIC_ELEM(0, __VA_ARGS__), CHAOS_PP_VARIADIC_ELEM(1, __VA_ARGS__)),\
    CHAOS_PP_VARIADIC_ELEM(1, __VA_ARGS__),\
    CHAOS_PP_DEC(CHAOS_PP_VARIADIC_ELEM(2, __VA_ARGS__))
#define FMC_X_EXP_Y_MACRO(s, ...) CHAOS_PP_VARIADIC_IF(CHAOS_PP_EQUAL(CHAOS_PP_VARIADIC_ELEM(2, __VA_ARGS__), 1))(__VA_ARGS__)()
// TODO: Consider the case where exp = 0
// res (arbitrary), base (arbitrary), exp (regular unsigned integer)
#define FMC_X_EXP_Y(x, y) \
    CHAOS_PP_ARBITRARY_DEMOTE(FMC_GET_ARGN( \
        0, \
        CHAOS_PP_EXPR(CHAOS_PP_FOR( \
            FMC_X_EXP_Y_PRED, FMC_X_EXP_Y_OP, FMC_X_EXP_Y_MACRO, CHAOS_PP_ARBITRARY_PROMOTE(1), CHAOS_PP_ARBITRARY_PROMOTE(x), CHAOS_PP_INC(y) \
        )) \
    ))

#if defined(FMC_CHAOS_NEGATIVE)
    #undef FMC_CHAOS_NEGATIVE
#endif
#define FMC_CHAOS_NEGATIVE(x) (-)x

#if defined(FMC_DECR_BY)
    #undef FMC_DECR_BY
#endif
#define FMC_DECR_BY(x, y) ML99_EVAL(ML99_call(ML99_sub, v(x), v(y)))

#if defined(BUILDING_FMANC) || defined(EXTRA_STMTS_NEEDED)
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
    #define foreach_stop_cond(x, array) ML99_EVAL(ML99_EVAL(ML99_call(ML99_if, ML99_isNothing(x), v(ML99_id(ML99_id(v(foreach_counter(0) < sizeof(array)/sizeof(array[0]))))), v(ML99_maybeUnwrap(x)))))
    #define foreach(elem, array, start, stop_index_cond) size_t foreach_counter(0) = start; for(typeof(array[foreach_counter(0)]) elem = array[foreach_counter(0)]; foreach_stop_cond(stop_index_cond, array) ; foreach_counter(0)++, elem = array[foreach_counter(0)])
#endif // BUILDING_FMANC || EXTRA_STMTS_NEEDED

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

#if defined(FMC_CAST_TO_UI8) || defined(FMC_CAST_TO_UI16) || defined(FMC_CAST_TO_UI32) || defined(FMC_CAST_TO_UI64) || defined(FMC_CAST_TO_I8) || defined(FMC_CAST_TO_I16) || defined(FMC_CAST_TO_I32) || defined(FMC_CAST_TO_I64) 
    #undef FMC_CAST_TO_UI8
    #undef FMC_CAST_TO_UI16
    #undef FMC_CAST_TO_UI32
    #undef FMC_CAST_TO_UI64
    #undef FMC_CAST_TO_I8
    #undef FMC_CAST_TO_I16
    #undef FMC_CAST_TO_I32
    #undef FMC_CAST_TO_I64
#endif
#define FMC_CAST_TO_UI8(x) ({   \
    uint8_t __x = (x);          \
    __x;                        \
})
#define FMC_CAST_TO_UI16(x) ({  \
    uint16_t __x = (x);         \
    __x;                        \
})
#define FMC_CAST_TO_UI32(x) ({  \
    uint32_t __x = (x);         \
    __x;                        \
})
#define FMC_CAST_TO_UI64(x) ({  \
    uint64_t __x = (x);         \
    __x;                        \
})
#define FMC_CAST_TO_I8(x) ({    \
    int8_t __x = (x);           \
    __x;                        \
})
#define FMC_CAST_TO_I16(x) ({   \
    int16_t __x = (x);          \
    __x;                        \
})
#define FMC_CAST_TO_I32(x) ({   \
    int32_t __x = (x);          \
    __x;                        \
})
#define FMC_CAST_TO_I64(x) ({   \
    int64_t __x = (x);          \
    __x;                        \
})

#if defined(FMC_UINT_ARR) || defined(FMC_INT_ARR)
    #undef FMC_UINT_ARR
    #undef FMC_INT_ARR
#endif
#define FMC_UINT_ARR(...) (unsigned int[]){__VA_ARGS__}
#define FMC_INT_ARR(...) (int[]){__VA_ARGS__}

#if defined(FMC_min_2) || defined(FMC_max_2) || defined(FMC_min_3) || defined(FMC_max_3) || defined(FMC_min_4) || defined(FMC_max_4) || \
    defined(FMC_min_5) || defined(FMC_max_5) || defined(FMC_min_6) || defined(FMC_max_6) || defined(FMC_min_7) || defined(FMC_max_7) || \
    defined(FMC_min_8) || defined(FMC_max_8) || defined(FMC_min_9) || defined(FMC_max_9) || defined(FMC_min_10) || defined(FMC_max_10)
    #undef FMC_min_2
    #undef FMC_max_2
    #undef FMC_min_3
    #undef FMC_max_3
    #undef FMC_min_4
    #undef FMC_max_4
    #undef FMC_min_5
    #undef FMC_max_5
    #undef FMC_min_6
    #undef FMC_max_6
    #undef FMC_min_7
    #undef FMC_max_7
    #undef FMC_min_8
    #undef FMC_max_8
    #undef FMC_min_9
    #undef FMC_max_9
    #undef FMC_min_10
    #undef FMC_max_10
#endif
#define FMC_min_2(x, y) ({ \
    typeof(x) __x = (x);   \
    typeof(y) __y = (y);   \
    __x < __y ? __x : __y; \
})
#define FMC_max_2(x, y) ({ \
    typeof(x) __x = (x);   \
    typeof(y) __y = (y);   \
    __x > __y ? __x : __y; \
})
#define FMC_min_3(x, y, z) ({                              \
    typeof(x) __x = (x);                                   \
    typeof(y) __y = (y);                                   \
    typeof(z) __z = (z);                                   \
    __x < __y ? FMC_min_2(__x, __z) : FMC_min_2(__y, __z); \
})
#define FMC_max_3(x, y, z) ({                              \
    typeof(x) __x = (x);                                   \
    typeof(y) __y = (y);                                   \
    typeof(z) __z = (z);                                   \
    __x > __y ? FMC_max_2(__x, __z) : FMC_max_2(__y, __z); \
})
#define FMC_min_4(x, y, z, w) ({                         \
    typeof(x) __x = (x);                                 \
    typeof(y) __y = (y);                                 \
    typeof(z) __z = (z);                                 \
    typeof(w) __w = (w);                                 \
    FMC_min_2(FMC_min_2(__x, __y), FMC_min_2(__z, __w)); \
})
#define FMC_max_4(x, y, z, w) ({                         \
    typeof(x) __x = (x);                                 \
    typeof(y) __y = (y);                                 \
    typeof(z) __z = (z);                                 \
    typeof(w) __w = (w);                                 \
    FMC_max_2(FMC_max_2(__x, __y), FMC_max_2(__z, __w)); \
})
#define FMC_min_5(x, y, z, w, v) ({                           \
    typeof(x) __x = (x);                                      \
    typeof(y) __y = (y);                                      \
    typeof(z) __z = (z);                                      \
    typeof(w) __w = (w);                                      \
    typeof(v) __v = (v);                                      \
    FMC_min_2(FMC_min_2(__x, __y), FMC_min_3(__z, __w, __v)); \
})
#define FMC_max_5(x, y, z, w, v) ({                           \
    typeof(x) __x = (x);                                      \
    typeof(y) __y = (y);                                      \
    typeof(z) __z = (z);                                      \
    typeof(w) __w = (w);                                      \
    typeof(v) __v = (v);                                      \
    FMC_max_2(FMC_max_2(__x, __y), FMC_max_3(__z, __w, __v)); \
})
#define FMC_min_6(x, y, z, w, v, u) ({                             \
    typeof(x) __x = (x);                                           \
    typeof(y) __y = (y);                                           \
    typeof(z) __z = (z);                                           \
    typeof(w) __w = (w);                                           \
    typeof(v) __v = (v);                                           \
    typeof(u) __u = (u);                                           \
    FMC_min_2(FMC_min_3(__x, __y, __z), FMC_min_3(__w, __v, __u)); \
})
#define FMC_max_6(x, y, z, w, v, u) ({                             \
    typeof(x) __x = (x);                                           \
    typeof(y) __y = (y);                                           \
    typeof(z) __z = (z);                                           \
    typeof(w) __w = (w);                                           \
    typeof(v) __v = (v);                                           \
    typeof(u) __u = (u);                                           \
    FMC_max_2(FMC_max_3(__x, __y, __z), FMC_max_3(__w, __v, __u)); \
})
#define FMC_min_7(x, y, z, w, v, u, t) ({                               \
    typeof(x) __x = (x);                                                \
    typeof(y) __y = (y);                                                \
    typeof(z) __z = (z);                                                \
    typeof(w) __w = (w);                                                \
    typeof(v) __v = (v);                                                \
    typeof(u) __u = (u);                                                \
    typeof(t) __t = (t);                                                \
    FMC_min_2(FMC_min_3(__x, __y, __z), FMC_min_4(__w, __v, __u, __t)); \
})
#define FMC_max_7(x, y, z, w, v, u, t) ({                               \
    typeof(x) __x = (x);                                                \
    typeof(y) __y = (y);                                                \
    typeof(z) __z = (z);                                                \
    typeof(w) __w = (w);                                                \
    typeof(v) __v = (v);                                                \
    typeof(u) __u = (u);                                                \
    typeof(t) __t = (t);                                                \
    FMC_max_2(FMC_max_3(__x, __y, __z), FMC_max_4(__w, __v, __u, __t)); \
})
#define FMC_min_8(x, y, z, w, v, u, t, s) ({                                 \
    typeof(x) __x = (x);                                                     \
    typeof(y) __y = (y);                                                     \
    typeof(z) __z = (z);                                                     \
    typeof(w) __w = (w);                                                     \
    typeof(v) __v = (v);                                                     \
    typeof(u) __u = (u);                                                     \
    typeof(t) __t = (t);                                                     \
    typeof(s) __s = (s);                                                     \
    FMC_min_2(FMC_min_4(__x, __y, __z, __w), FMC_min_4(__v, __u, __t, __s)); \
})
#define FMC_max_8(x, y, z, w, v, u, t, s) ({                                 \
    typeof(x) __x = (x);                                                     \
    typeof(y) __y = (y);                                                     \
    typeof(z) __z = (z);                                                     \
    typeof(w) __w = (w);                                                     \
    typeof(v) __v = (v);                                                     \
    typeof(u) __u = (u);                                                     \
    typeof(t) __t = (t);                                                     \
    typeof(s) __s = (s);                                                     \
    FMC_max_2(FMC_max_4(__x, __y, __z, __w), FMC_max_4(__v, __u, __t, __s)); \
})
#define FMC_min_9(x, y, z, w, v, u, t, s, r) ({                                     \
    typeof(x) __x = (x);                                                            \
    typeof(y) __y = (y);                                                            \
    typeof(z) __z = (z);                                                            \
    typeof(w) __w = (w);                                                            \
    typeof(v) __v = (v);                                                            \
    typeof(u) __u = (u);                                                            \
    typeof(t) __t = (t);                                                            \
    typeof(s) __s = (s);                                                            \
    typeof(r) __r = (r);                                                            \
    FMC_min_2(FMC_min_4(__x, __y, __z, __w), FMC_min_5(__v, __u, __t, __s, __r));   \
})
#define FMC_max_9(x, y, z, w, v, u, t, s, r) ({                                     \
    typeof(x) __x = (x);                                                            \
    typeof(y) __y = (y);                                                            \
    typeof(z) __z = (z);                                                            \
    typeof(w) __w = (w);                                                            \
    typeof(v) __v = (v);                                                            \
    typeof(u) __u = (u);                                                            \
    typeof(t) __t = (t);                                                            \
    typeof(s) __s = (s);                                                            \
    typeof(r) __r = (r);                                                            \
    FMC_max_2(FMC_max_4(__x, __y, __z, __w), FMC_max_5(__v, __u, __t, __s, __r));   \
})
#define FMC_min_10(x, y, z, w, v, u, t, s, r, q) ({                                     \
    typeof(x) __x = (x);                                                                \
    typeof(y) __y = (y);                                                                \
    typeof(z) __z = (z);                                                                \
    typeof(w) __w = (w);                                                                \
    typeof(v) __v = (v);                                                                \
    typeof(u) __u = (u);                                                                \
    typeof(t) __t = (t);                                                                \
    typeof(s) __s = (s);                                                                \
    typeof(r) __r = (r);                                                                \
    typeof(q) __q = (q);                                                                \
    FMC_min_2(FMC_min_5(__x, __y, __z, __w, __v), FMC_min_5(__u, __t, __s, __r, __q));  \
})
#define FMC_max_10(x, y, z, w, v, u, t, s, r, q) ({                                     \
    typeof(x) __x = (x);                                                                \
    typeof(y) __y = (y);                                                                \
    typeof(z) __z = (z);                                                                \
    typeof(w) __w = (w);                                                                \
    typeof(v) __v = (v);                                                                \
    typeof(u) __u = (u);                                                                \
    typeof(t) __t = (t);                                                                \
    typeof(s) __s = (s);                                                                \
    typeof(r) __r = (r);                                                                \
    typeof(q) __q = (q);                                                                \
    FMC_max_2(FMC_max_5(__x, __y, __z, __w, __v), FMC_max_5(__u, __t, __s, __r, __q));  \
})

#if defined(FMC_min) || defined(FMC_max)
    #undef FMC_min
    #undef FMC_max
#endif
#define FMC_min(...) FMC_CONCAT_2(FMC_min_, FMC_ID(FMC_GET_ARGC(__VA_ARGS__)))(__VA_ARGS__)
#define FMC_max(...) FMC_CONCAT_2(FMC_max_, FMC_ID(FMC_GET_ARGC(__VA_ARGS__)))(__VA_ARGS__)

#if defined(FMC_LOCAL_LABEL)
    #undef FMC_LOCAL_LABEL
#endif
#define FMC_LOCAL_LABEL(x) __label__ x

#ifndef FMC_METHODS
    #define FMC_METHODS

    #define DECL_METHOD(name, ret, ...) \
        ret (*name)(__VA_ARGS__)

    #define INIT_STRUCT_METHOD(method, associated_function) \
        .method = associated_function

#endif // FMC_METHODS

#if defined(FMC_TUPLE_HAS_ELEMS)
    #undef FMC_TUPLE_HAS_ELEMS
#endif
#define FMC_TUPLE_HAS_ELEMS(_tuple) CHAOS_PP_BOOL(FMC_ID(FMC_INVOKE(FMC_GET_ARGC, _tuple)))

#if defined(FMC_ARGS_X_TO_Y) || defined(FMC_ARGS_X_TO_Y_)
    #undef FMC_ARGS_X_TO_Y
    #undef FMC_ARGS_X_TO_Y_
#endif
#define FMC_ARGS_X_TO_Y(x, y, ...) FMC_ID(FMC_ARGS_X_TO_Y_(FMC_ID(x), FMC_ID(y), FMC_ID(__VA_ARGS__)))
#define FMC_ARGS_X_TO_Y_(x, y, ...) \
    ML99_LIST_EVAL_COMMA_SEP(\
        ML99_listDrop(v(x), ML99_listTake(ML99_inc(v(y)), ML99_list(v(__VA_ARGS__)))) \
    )

//FMC_INVOKE(FMC_CONCAT_4(FMC_ARGS_X_TO_Y_, x, _, y), (__VA_ARGS__))

#if 0

#if defined(FMC_ARGS_X_TO_Y_0_0) || defined(FMC_ARGS_X_TO_Y_0_1) || defined(FMC_ARGS_X_TO_Y_0_2) || defined(FMC_ARGS_X_TO_Y_0_3) || defined(FMC_ARGS_X_TO_Y_0_4) || \
    defined(FMC_ARGS_X_TO_Y_0_5) || defined(FMC_ARGS_X_TO_Y_0_6) || defined(FMC_ARGS_X_TO_Y_0_7) || defined(FMC_ARGS_X_TO_Y_0_8) || \
    defined(FMC_ARGS_X_TO_Y_0_9)
    #undef FMC_ARGS_X_TO_Y_0_0
    #undef FMC_ARGS_X_TO_Y_0_1
    #undef FMC_ARGS_X_TO_Y_0_2
    #undef FMC_ARGS_X_TO_Y_0_3
    #undef FMC_ARGS_X_TO_Y_0_4
    #undef FMC_ARGS_X_TO_Y_0_5
    #undef FMC_ARGS_X_TO_Y_0_6
    #undef FMC_ARGS_X_TO_Y_0_7
    #undef FMC_ARGS_X_TO_Y_0_8
    #undef FMC_ARGS_X_TO_Y_0_9
#endif
#define FMC_ARGS_X_TO_Y_0_0(...)                                \
    FMC_GET_ARGN(0, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_0_1(...)                                \
    FMC_GET_ARGN(0, __VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_0_2(...)                                \
    FMC_GET_ARGN(0, __VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__), \
    FMC_GET_ARGN(2, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_0_3(...)                                \
    FMC_GET_ARGN(0, __VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__), \
    FMC_GET_ARGN(2, __VA_ARGS__), FMC_GET_ARGN(3, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_0_4(...)                                \
    FMC_GET_ARGN(0, __VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__), \
    FMC_GET_ARGN(2, __VA_ARGS__), FMC_GET_ARGN(3, __VA_ARGS__), \
    FMC_GET_ARGN(4, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_0_5(...)                                \
    FMC_GET_ARGN(0, __VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__), \
    FMC_GET_ARGN(2, __VA_ARGS__), FMC_GET_ARGN(3, __VA_ARGS__), \
    FMC_GET_ARGN(4, __VA_ARGS__), FMC_GET_ARGN(5, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_0_6(...)                                \
    FMC_GET_ARGN(0, __VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__), \
    FMC_GET_ARGN(2, __VA_ARGS__), FMC_GET_ARGN(3, __VA_ARGS__), \
    FMC_GET_ARGN(4, __VA_ARGS__), FMC_GET_ARGN(5, __VA_ARGS__), \
    FMC_GET_ARGN(6, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_0_7(...)                                \
    FMC_GET_ARGN(0, __VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__), \
    FMC_GET_ARGN(2, __VA_ARGS__), FMC_GET_ARGN(3, __VA_ARGS__), \
    FMC_GET_ARGN(4, __VA_ARGS__), FMC_GET_ARGN(5, __VA_ARGS__), \
    FMC_GET_ARGN(6, __VA_ARGS__), FMC_GET_ARGN(7, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_0_8(...)                                \
    FMC_GET_ARGN(0, __VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__), \
    FMC_GET_ARGN(2, __VA_ARGS__), FMC_GET_ARGN(3, __VA_ARGS__), \
    FMC_GET_ARGN(4, __VA_ARGS__), FMC_GET_ARGN(5, __VA_ARGS__), \
    FMC_GET_ARGN(6, __VA_ARGS__), FMC_GET_ARGN(7, __VA_ARGS__), \
    FMC_GET_ARGN(8, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_0_9(...)                                \
    FMC_GET_ARGN(0, __VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__), \
    FMC_GET_ARGN(2, __VA_ARGS__), FMC_GET_ARGN(3, __VA_ARGS__), \
    FMC_GET_ARGN(4, __VA_ARGS__), FMC_GET_ARGN(5, __VA_ARGS__), \
    FMC_GET_ARGN(6, __VA_ARGS__), FMC_GET_ARGN(7, __VA_ARGS__), \
    FMC_GET_ARGN(8, __VA_ARGS__), FMC_GET_ARGN(9, __VA_ARGS__)

#if defined(FMC_ARGS_X_TO_Y_1_1) || defined(FMC_ARGS_X_TO_Y_1_2) || defined(FMC_ARGS_X_TO_Y_1_3) || defined(FMC_ARGS_X_TO_Y_1_4) || defined(FMC_ARGS_X_TO_Y_1_5) || defined(FMC_ARGS_X_TO_Y_1_6) || defined(FMC_ARGS_X_TO_Y_1_7) || defined(FMC_ARGS_X_TO_Y_1_8) || defined(FMC_ARGS_X_TO_Y_1_9)
    #undef FMC_ARGS_X_TO_Y_1_1
    #undef FMC_ARGS_X_TO_Y_1_2
    #undef FMC_ARGS_X_TO_Y_1_3
    #undef FMC_ARGS_X_TO_Y_1_4
    #undef FMC_ARGS_X_TO_Y_1_5
    #undef FMC_ARGS_X_TO_Y_1_6
    #undef FMC_ARGS_X_TO_Y_1_7
    #undef FMC_ARGS_X_TO_Y_1_8
    #undef FMC_ARGS_X_TO_Y_1_9
#endif
#define FMC_ARGS_X_TO_Y_1_1(...)                                \
    FMC_GET_ARGN(1, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_1_2(...)                                \
    FMC_GET_ARGN(1, __VA_ARGS__), FMC_GET_ARGN(2, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_1_3(...)                                \
    FMC_GET_ARGN(1, __VA_ARGS__), FMC_GET_ARGN(2, __VA_ARGS__), \
    FMC_GET_ARGN(3, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_1_4(...)                                \
    FMC_GET_ARGN(1, __VA_ARGS__), FMC_GET_ARGN(2, __VA_ARGS__), \
    FMC_GET_ARGN(3, __VA_ARGS__), FMC_GET_ARGN(4, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_1_5(...)                                \
    FMC_GET_ARGN(1, __VA_ARGS__), FMC_GET_ARGN(2, __VA_ARGS__), \
    FMC_GET_ARGN(3, __VA_ARGS__), FMC_GET_ARGN(4, __VA_ARGS__), \
    FMC_GET_ARGN(5, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_1_6(...)                                \
    FMC_GET_ARGN(1, __VA_ARGS__), FMC_GET_ARGN(2, __VA_ARGS__), \
    FMC_GET_ARGN(3, __VA_ARGS__), FMC_GET_ARGN(4, __VA_ARGS__), \
    FMC_GET_ARGN(5, __VA_ARGS__), FMC_GET_ARGN(6, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_1_7(...)                                \
    FMC_GET_ARGN(1, __VA_ARGS__), FMC_GET_ARGN(2, __VA_ARGS__), \
    FMC_GET_ARGN(3, __VA_ARGS__), FMC_GET_ARGN(4, __VA_ARGS__), \
    FMC_GET_ARGN(5, __VA_ARGS__), FMC_GET_ARGN(6, __VA_ARGS__), \
    FMC_GET_ARGN(7, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_1_8(...)                                \
    FMC_GET_ARGN(1, __VA_ARGS__), FMC_GET_ARGN(2, __VA_ARGS__), \
    FMC_GET_ARGN(3, __VA_ARGS__), FMC_GET_ARGN(4, __VA_ARGS__), \
    FMC_GET_ARGN(5, __VA_ARGS__), FMC_GET_ARGN(6, __VA_ARGS__), \
    FMC_GET_ARGN(7, __VA_ARGS__), FMC_GET_ARGN(8, __VA_ARGS__)

#define FMC_ARGS_X_TO_Y_1_9(...)                                \
    FMC_GET_ARGN(1, __VA_ARGS__), FMC_GET_ARGN(2, __VA_ARGS__), \
    FMC_GET_ARGN(3, __VA_ARGS__), FMC_GET_ARGN(4, __VA_ARGS__), \
    FMC_GET_ARGN(5, __VA_ARGS__), FMC_GET_ARGN(6, __VA_ARGS__), \
    FMC_GET_ARGN(7, __VA_ARGS__), FMC_GET_ARGN(8, __VA_ARGS__), \
    FMC_GET_ARGN(9, __VA_ARGS__)

#if defined(FMC_ARGS_X_TO_Y_2_2) || defined(FMC_ARGS_X_TO_Y_2_3) || defined(FMC_ARGS_X_TO_Y_2_4) || defined(FMC_ARGS_X_TO_Y_2_5) || defined(FMC_ARGS_X_TO_Y_2_6) || defined(FMC_ARGS_X_TO_Y_2_7) || defined(FMC_ARGS_X_TO_Y_2_8) || defined(FMC_ARGS_X_TO_Y_2_9)
    #undef FMC_ARGS_X_TO_Y_2_2
    #undef FMC_ARGS_X_TO_Y_2_3
    #undef FMC_ARGS_X_TO_Y_2_4
    #undef FMC_ARGS_X_TO_Y_2_5
    #undef FMC_ARGS_X_TO_Y_2_6
    #undef FMC_ARGS_X_TO_Y_2_7
    #undef FMC_ARGS_X_TO_Y_2_8
    #undef FMC_ARGS_X_TO_Y_2_9
#endif
#define FMC_ARGS_X_TO_Y_2_2(...) FMC_ARGS_X_TO_Y_1_1(FMC_ARGS_X_TO_Y_1_2(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_2_3(...) FMC_ARGS_X_TO_Y_1_2(FMC_ARGS_X_TO_Y_1_3(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_2_4(...) FMC_ARGS_X_TO_Y_1_3(FMC_ARGS_X_TO_Y_1_4(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_2_5(...) FMC_ARGS_X_TO_Y_1_4(FMC_ARGS_X_TO_Y_1_5(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_2_6(...) FMC_ARGS_X_TO_Y_1_5(FMC_ARGS_X_TO_Y_1_6(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_2_7(...) FMC_ARGS_X_TO_Y_1_6(FMC_ARGS_X_TO_Y_1_7(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_2_8(...) FMC_ARGS_X_TO_Y_1_7(FMC_ARGS_X_TO_Y_1_8(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_2_9(...) FMC_ARGS_X_TO_Y_1_8(FMC_ARGS_X_TO_Y_1_9(__VA_ARGS__))

#if defined(FMC_ARGS_X_TO_Y_3_3) || defined(FMC_ARGS_X_TO_Y_3_4) || defined(FMC_ARGS_X_TO_Y_3_5) || defined(FMC_ARGS_X_TO_Y_3_6) || defined(FMC_ARGS_X_TO_Y_3_7) || defined(FMC_ARGS_X_TO_Y_3_8) || defined(FMC_ARGS_X_TO_Y_3_9)
    #undef FMC_ARGS_X_TO_Y_3_3
    #undef FMC_ARGS_X_TO_Y_3_4
    #undef FMC_ARGS_X_TO_Y_3_5
    #undef FMC_ARGS_X_TO_Y_3_6
    #undef FMC_ARGS_X_TO_Y_3_7
    #undef FMC_ARGS_X_TO_Y_3_8
    #undef FMC_ARGS_X_TO_Y_3_9
#endif
#define FMC_ARGS_X_TO_Y_3_3(...) FMC_ARGS_X_TO_Y_2_2(FMC_ARGS_X_TO_Y_1_3(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_3_4(...) FMC_ARGS_X_TO_Y_2_3(FMC_ARGS_X_TO_Y_1_4(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_3_5(...) FMC_ARGS_X_TO_Y_2_4(FMC_ARGS_X_TO_Y_1_5(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_3_6(...) FMC_ARGS_X_TO_Y_2_5(FMC_ARGS_X_TO_Y_1_6(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_3_7(...) FMC_ARGS_X_TO_Y_2_6(FMC_ARGS_X_TO_Y_1_7(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_3_8(...) FMC_ARGS_X_TO_Y_2_7(FMC_ARGS_X_TO_Y_1_8(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_3_9(...) FMC_ARGS_X_TO_Y_2_8(FMC_ARGS_X_TO_Y_1_9(__VA_ARGS__))

#if defined(FMC_ARGS_X_TO_Y_4_4) || defined(FMC_ARGS_X_TO_Y_4_5) || defined(FMC_ARGS_X_TO_Y_4_6) || defined(FMC_ARGS_X_TO_Y_4_7) || defined(FMC_ARGS_X_TO_Y_4_8) || defined(FMC_ARGS_X_TO_Y_4_9)
    #undef FMC_ARGS_X_TO_Y_4_4
    #undef FMC_ARGS_X_TO_Y_4_5
    #undef FMC_ARGS_X_TO_Y_4_6
    #undef FMC_ARGS_X_TO_Y_4_7
    #undef FMC_ARGS_X_TO_Y_4_8
    #undef FMC_ARGS_X_TO_Y_4_9
#endif
#define FMC_ARGS_X_TO_Y_4_4(...) FMC_ARGS_X_TO_Y_3_3(FMC_ARGS_X_TO_Y_1_4(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_4_5(...) FMC_ARGS_X_TO_Y_3_4(FMC_ARGS_X_TO_Y_1_5(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_4_6(...) FMC_ARGS_X_TO_Y_3_5(FMC_ARGS_X_TO_Y_1_6(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_4_7(...) FMC_ARGS_X_TO_Y_3_6(FMC_ARGS_X_TO_Y_1_7(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_4_8(...) FMC_ARGS_X_TO_Y_3_7(FMC_ARGS_X_TO_Y_1_8(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_4_9(...) FMC_ARGS_X_TO_Y_3_8(FMC_ARGS_X_TO_Y_1_9(__VA_ARGS__))

#if defined(FMC_ARGS_X_TO_Y_5_5) || defined(FMC_ARGS_X_TO_Y_5_6) || defined(FMC_ARGS_X_TO_Y_5_7) || defined(FMC_ARGS_X_TO_Y_5_8) || defined(FMC_ARGS_X_TO_Y_5_9)
    #undef FMC_ARGS_X_TO_Y_5_5
    #undef FMC_ARGS_X_TO_Y_5_6
    #undef FMC_ARGS_X_TO_Y_5_7
    #undef FMC_ARGS_X_TO_Y_5_8
    #undef FMC_ARGS_X_TO_Y_5_9
#endif
#define FMC_ARGS_X_TO_Y_5_5(...) FMC_ARGS_X_TO_Y_4_4(FMC_ARGS_X_TO_Y_1_5(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_5_6(...) FMC_ARGS_X_TO_Y_4_5(FMC_ARGS_X_TO_Y_1_6(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_5_7(...) FMC_ARGS_X_TO_Y_4_6(FMC_ARGS_X_TO_Y_1_7(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_5_8(...) FMC_ARGS_X_TO_Y_4_7(FMC_ARGS_X_TO_Y_1_8(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_5_9(...) FMC_ARGS_X_TO_Y_4_8(FMC_ARGS_X_TO_Y_1_9(__VA_ARGS__))

#if defined(FMC_ARGS_X_TO_Y_6_6) || defined(FMC_ARGS_X_TO_Y_6_7) || defined(FMC_ARGS_X_TO_Y_6_8) || defined(FMC_ARGS_X_TO_Y_6_9)
    #undef FMC_ARGS_X_TO_Y_6_6
    #undef FMC_ARGS_X_TO_Y_6_7
    #undef FMC_ARGS_X_TO_Y_6_8
    #undef FMC_ARGS_X_TO_Y_6_9
#endif
#define FMC_ARGS_X_TO_Y_6_6(...) FMC_ARGS_X_TO_Y_5_5(FMC_ARGS_X_TO_Y_1_6(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_6_7(...) FMC_ARGS_X_TO_Y_5_6(FMC_ARGS_X_TO_Y_1_7(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_6_8(...) FMC_ARGS_X_TO_Y_5_7(FMC_ARGS_X_TO_Y_1_8(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_6_9(...) FMC_ARGS_X_TO_Y_5_8(FMC_ARGS_X_TO_Y_1_9(__VA_ARGS__))

#if defined(FMC_ARGS_X_TO_Y_7_7) || defined(FMC_ARGS_X_TO_Y_7_8) || defined(FMC_ARGS_X_TO_Y_7_9)
    #undef FMC_ARGS_X_TO_Y_7_7
    #undef FMC_ARGS_X_TO_Y_7_8
    #undef FMC_ARGS_X_TO_Y_7_9
#endif
#define FMC_ARGS_X_TO_Y_7_7(...) FMC_ARGS_X_TO_Y_6_6(FMC_ARGS_X_TO_Y_1_7(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_7_8(...) FMC_ARGS_X_TO_Y_6_7(FMC_ARGS_X_TO_Y_1_8(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_7_9(...) FMC_ARGS_X_TO_Y_6_8(FMC_ARGS_X_TO_Y_1_9(__VA_ARGS__))

#if defined(FMC_ARGS_X_TO_Y_8_8) || defined(FMC_ARGS_X_TO_Y_8_9)
    #undef FMC_ARGS_X_TO_Y_8_8
    #undef FMC_ARGS_X_TO_Y_8_9
#endif
#define FMC_ARGS_X_TO_Y_8_8(...) FMC_ARGS_X_TO_Y_7_7(FMC_ARGS_X_TO_Y_1_8(__VA_ARGS__))
#define FMC_ARGS_X_TO_Y_8_9(...) FMC_ARGS_X_TO_Y_7_8(FMC_ARGS_X_TO_Y_1_9(__VA_ARGS__))

#if defined(FMC_ARGS_X_TO_Y_9_9)
    #undef FMC_ARGS_X_TO_Y_9_9
#endif
#define FMC_ARGS_X_TO_Y_9_9(...) FMC_ARGS_X_TO_Y_8_8(FMC_ARGS_X_TO_Y_1_9(__VA_ARGS__))

#endif

#if defined(FMC_OVERLOAD_TYPE_PTR)
    #undef FMC_OVERLOAD_TYPE_PTR
#endif
// FMC_OVERLOAD_TYPE_PTR((unsigned, char)) -> (unsigned, char, ptr)
#define FMC_OVERLOAD_TYPE_PTR(_type_tuple) (FMC_ID(FMC_INVOKE(FMC_ID, _type_tuple)), ptr)

#if !defined(FMC_IDENT_DETECTORS)
    #define FMC_IDENT_DETECTORS

    #if defined(FMC_DETECTOR_DETECTOR) || defined(FMC_IDENT_EQ_DETECTOR)
        #undef FMC_DETECTOR_DETECTOR
        #undef FMC_IDENT_EQ_DETECTOR
    #endif
    #define PREFIX_FMC_DETECTOR__FMC_DETECTOR_ ()
    #define PREFIX_FMC_IDENT_EQ__FMC_IDENT_EQ_ ()

    #include "FMC_ident_detection.h"

    #if defined(FMC_LIST_WHEN_DETECTOR) /* || defined(FMC_LIST_WHEN_IDENT_EQ) */
        #undef FMC_LIST_WHEN_DETECTOR
        /* #undef FMC_LIST_WHEN_IDENT_EQ */
    #endif
    /* #define FMC_LIST_WHEN_IDENT_EQ(_tuple) \
        ML99_LIST_EVAL_COMMA_SEP(ML99_listAppend(\
                ML99_listMap(v(FMC_MAKE_DETECTABLE_HELPER_INIT), ML99_list(v(FMC_ID _tuple))), \
                ML99_listMapInitLast(v(FMC_MAKE_DETECTABLE_HELPER_INIT), v(FMC_MAKE_DETECTABLE_HELPER_LAST), ML99_list(v(FMC_ID _tuple))))) */

    #define FMC_LIST_WHEN_DETECTOR(_tuple) \
        ML99_LIST_EVAL_COMMA_SEP(ML99_listMapInitLast(v(FMC_MAKE_DETECTABLE_HELPER_INIT), v(FMC_MAKE_DETECTABLE_HELPER_LAST), ML99_list(v(FMC_ID _tuple))))

    #if defined(FMC_MAKE_DETECTABLE) || defined(FMC_MAKE_DETECTABLE_HELPER_INIT_IMPL) || defined(FMC_MAKE_DETECTABLE_HELPER_LAST_IMPL) || defined(FMC_MAKE_DETECTABLE_HELPER_INIT_ARITY) || defined(FMC_MAKE_DETECTABLE_HELPER_LAST_ARITY) 
        #undef FMC_MAKE_DETECTABLE
        #undef FMC_MAKE_DETECTABLE_HELPER_INIT_IMPL
        #undef FMC_MAKE_DETECTABLE_HELPER_LAST_IMPL
        #undef FMC_MAKE_DETECTABLE_HELPER_INIT_ARITY
        #undef FMC_MAKE_DETECTABLE_HELPER_LAST_ARITY
    #endif
    #define FMC_MAKE_DETECTABLE_HELPER_INIT_IMPL(_type_part) v(FMC_CONCAT(_type_part, _))
    #define FMC_MAKE_DETECTABLE_HELPER_LAST_IMPL(_type_part) v(_type_part)
    #define FMC_MAKE_DETECTABLE_HELPER_INIT_ARITY 1
    #define FMC_MAKE_DETECTABLE_HELPER_LAST_ARITY 1
    // FMC_MAKE_DETECTABLE((unsigned, char)) -> unsigned_char
    // FMC_MAKE_DETECTABLE((unsigned, char, ptr)) -> unsigned_char_ptr
    // FMC_MAKE_DETECTABLE((unsigned, char, ptr, ptr)) -> unsigned_char_ptr_ptr
    /* #define FMC_MAKE_DETECTABLE(_prefix, _tuple) CHAOS_PP_VARIADIC_CAT(_prefix, \
        ML99_EVAL(ML99_if(ML99_identEq(v(PREFIX_), v(_prefix)))),\
                v(ML99_LIST_EVAL_COMMA_SEP(ML99_listMapInitLast(v(FMC_MAKE_DETECTABLE_HELPER_INIT), v(FMC_MAKE_DETECTABLE_HELPER_LAST), ML99_list(v(FMC_ID(FMC_INVOKE(FMC_ID, _tuple))))))), \
                v(ML99_LIST_EVAL_COMMA_SEP(ML99_listAppend(ML99_listMap(v(FMC_MAKE_DETECTABLE_HELPER_INIT), ML99_list(v(FMC_ID(FMC_INVOKE(FMC_ID, _tuple))))), ML99_listMapInitLast(v(FMC_MAKE_DETECTABLE_HELPER_INIT), v(FMC_MAKE_DETECTABLE_HELPER_LAST), ML99_list(v(FMC_ID(FMC_INVOKE(FMC_ID, _tuple))))))))) */

    #if defined(FMC_MAKE_DETECTABLE_EXPAND) || defined(FMC_MAKE_DETECTABLE_EXPAND_0) || defined(FMC_MAKE_DETECTABLE_EXPAND_1)
        #undef FMC_MAKE_DETECTABLE_EXPAND
        #undef FMC_MAKE_DETECTABLE_EXPAND_0
        #undef FMC_MAKE_DETECTABLE_EXPAND_1
    #endif
    #define FMC_MAKE_DETECTABLE_EXPAND_1(_tuple) FMC_LIST_WHEN_DETECTOR(_tuple)
    #define FMC_MAKE_DETECTABLE_EXPAND_0(_tuple) FMC_LIST_WHEN_DETECTOR(_tuple) // FMC_LIST_WHEN_IDENT_EQ(_tuple)
    #define FMC_MAKE_DETECTABLE_EXPAND(_prefix, _tuple) FMC_CONCAT(FMC_MAKE_DETECTABLE_EXPAND_, CHAOS_PP_BOOL(ML99_EVAL(ML99_identEq(v(PREFIX_), v(_prefix), v(FMC_DETECTOR_)))))(_tuple)

    #define FMC_MAKE_DETECTABLE(_prefix, _tuple) CHAOS_PP_VARIADIC_CAT(FMC_MAKE_DETECTABLE_EXPAND(_prefix, _tuple))

    #if defined(FMC_PRIMITIVE_IDENT_EQ) || defined(FMC_IDENT_EQ_FILTER_PTRS)
        #undef FMC_PRIMITIVE_IDENT_EQ
        #undef FMC_IDENT_EQ_FILTER_PTRS
    #endif
    #define FMC_IDENT_EQ_FILTER_PTRS(_tuple) \
        ML99_LIST_EVAL_COMMA_SEP(ML99_listFilter(ML99_compose(v(ML99_not), ML99_appl(ML99_appl(v(ML99_identEq), v(FMC_IDENT_EQ_)), v(ptr))), ML99_list(v(FMC_ID(FMC_INVOKE(FMC_ID, _tuple))))))

    #define FMC_PRIMITIVE_IDENT_EQ(_id1_tuple, _id2_tuple) \
        ML99_EVAL(ML99_identEq(v(FMC_IDENT_EQ_), v(FMC_MAKE_DETECTABLE(FMC_IDENT_EQ_, (FMC_IDENT_EQ_FILTER_PTRS(_id1_tuple)))), v(FMC_MAKE_DETECTABLE(FMC_IDENT_EQ_, (FMC_IDENT_EQ_FILTER_PTRS(_id2_tuple))))))

    #if defined(FMC_DETECT_IDENT)
        #undef FMC_DETECT_IDENT
    #endif
    #define FMC_DETECT_IDENT(_to_test_tuple) \
        ML99_EVAL(ML99_detectIdent(v(FMC_DETECTOR_), v(FMC_MAKE_DETECTABLE(FMC_DETECTOR_, (FMC_IDENT_EQ_FILTER_PTRS(_to_test_tuple))))))

    #if defined(FMC_TWO_VOID_TUPLES) || defined(FMC_ONE_VOID_TUPLE) || defined(FMC_TWO_NON_VOID_TUPLES)
        #undef FMC_TWO_VOID_TUPLES
        #undef FMC_ONE_VOID_TUPLE
        #undef FMC_TWO_NON_VOID_TUPLES
    #endif
    #define FMC_TWO_VOID_TUPLES(_t1, _t2) \
        CHAOS_PP_AND(CHAOS_PP_COMPL(FMC_TUPLE_HAS_ELEMS(_t1)))(CHAOS_PP_COMPL(FMC_TUPLE_HAS_ELEMS(_t2)))
    #define FMC_ONE_VOID_TUPLE(_t1, _t2) \
        CHAOS_PP_OR(\
            CHAOS_PP_AND(CHAOS_PP_COMPL(FMC_TUPLE_HAS_ELEMS(_t1)))(FMC_TUPLE_HAS_ELEMS(_t2))\
        )(\
            CHAOS_PP_AND(CHAOS_PP_COMPL(FMC_TUPLE_HAS_ELEMS(_t2)))(FMC_TUPLE_HAS_ELEMS(_t1))\
        )
    #define FMC_TWO_NON_VOID_TUPLES(_t1, _t2) \
        CHAOS_PP_AND(FMC_TUPLE_HAS_ELEMS(_t1))(FMC_TUPLE_HAS_ELEMS(_t2))
    #if defined(FMC_IDENT_EQ) || defined(FMC_IDENT_EQ_ptr_LIST_MAPPED) || defined(FMC_IDENT_EQ_ptr_LIST_MAPPED_HELPER_IMPL) || defined(FMC_IDENT_EQ_ptr_LIST_MAPPED_HELPER_ARITY) || defined(FMC_IDENT_EQ_SAME_PTR_POSITIONS)
        #undef FMC_IDENT_EQ
        #undef FMC_IDENT_EQ_ptr_LIST_MAPPED
        #undef FMC_IDENT_EQ_ptr_LIST_MAPPED_HELPER_IMPL
        #undef FMC_IDENT_EQ_ptr_LIST_MAPPED_HELPER_ARITY
        #undef FMC_IDENT_EQ_SAME_PTR_POSITIONS
    #endif
    #define FMC_IDENT_EQ_ptr_LIST_MAPPED_HELPER_IMPL(_type_part) ML99_if(ML99_identEq(v(FMC_IDENT_EQ_), v(ptr), v(_type_part)), v(1), v(0))
    #define FMC_IDENT_EQ_ptr_LIST_MAPPED_HELPER_ARITY 1
    #define FMC_IDENT_EQ_ptr_LIST_MAPPED(_tuple) \
        ML99_LIST_EVAL_COMMA_SEP(ML99_listMap(v(FMC_IDENT_EQ_ptr_LIST_MAPPED_HELPER), ML99_list(v(FMC_ID(FMC_INVOKE(FMC_ID, _tuple))))))
    #define FMC_IDENT_EQ_SAME_PTR_POSITIONS(_tuple_1, _tuple_2) \
        ML99_EVAL(ML99_listEq(v(ML99_natEq), ML99_list(v(FMC_IDENT_EQ_ptr_LIST_MAPPED(_tuple_1))), ML99_list(v(FMC_IDENT_EQ_ptr_LIST_MAPPED(_tuple_2)))))
    #define FMC_IDENT_EQ(_id1_tuple, _id2_tuple) \
        CHAOS_PP_VARIADIC_IF(\
            CHAOS_PP_NOT_EQUAL(\
                CHAOS_PP_VARIADIC_SIZE(FMC_ID(FMC_INVOKE(FMC_ID, _id1_tuple))),\
                CHAOS_PP_VARIADIC_SIZE(FMC_ID(FMC_INVOKE(FMC_ID, _id2_tuple))))\
        )\
        (0)\
        (\
            CHAOS_PP_VARIADIC_IF(\
                FMC_TWO_NON_VOID_TUPLES(_id1_tuple, _id2_tuple)\
            )\
            (\
                CHAOS_PP_VARIADIC_IF(\
                    FMC_IDENT_EQ_SAME_PTR_POSITIONS(_id1_tuple, _id2_tuple)\
                )\
                (FMC_PRIMITIVE_IDENT_EQ(_id1_tuple, _id2_tuple))\
                (0)\
            )\
            (\
                CHAOS_PP_VARIADIC_IF(\
                    CHAOS_PP_COMPL(FMC_ONE_VOID_TUPLE(_id1_tuple, _id2_tuple))\
                )\
                (FMC_TWO_VOID_TUPLES(_id1_tuple, _id2_tuple))\
                (0)\
            )\
        )



// CHAOS_PP_VARIADIC_IF(
// FMC_IDENT_EQ_SAME_PTR_POSITIONS(_id1_tuple, _id2_tuple)
// )
// (FMC_PRIMITIVE_IDENT_EQ(_id1_tuple, _id2_tuple))
// (0)

#endif

#if defined(FMC_EXPAND_IF_NARGS)
    #undef FMC_EXPAND_IF_NARGS
#endif
#define FMC_EXPAND_IF_NARGS(_n, _args) \
    ML99_EVAL(ML99_call(ML99_if, ML99_natEq(v(_n), v(FMC_INVOKE(FMC_GET_ARGC, FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _args)))))), v((_args)), ML99_empty()))

#if defined(FMC_INVOKE)
    #undef FMC_INVOKE
#endif
#define FMC_INVOKE(_func, _args) _func _args

#if defined(FMC_ML99_INVOKE_IMPL) || defined(FMC_ML99_INVOKE_ARITY)
    #undef FMC_ML99_INVOKE_IMPL
    #undef FMC_ML99_INVOKE_ARITY
#endif
#define FMC_ML99_INVOKE_IMPL(_func, _args) ML99_call(v(FMC_INVOKE(_func, _args)))
#define FMC_ML99_INVOKE_ARITY 2

#if defined(FMC_OVERLOAD_DISPATCH_HELPER_1) || defined(FMC_OVERLOAD_DISPATCH_HELPER_2) || defined(FMC_OVERLOAD_DISPATCH_HELPER_3) || defined(FMC_OVERLOAD_DISPATCH_HELPER_4) || defined(FMC_OVERLOAD_DISPATCH_HELPER_5) || defined(FMC_OVERLOAD_DISPATCH_HELPER_6) || defined(FMC_OVERLOAD_DISPATCH_HELPER_7) || defined(FMC_OVERLOAD_DISPATCH_HELPER_8) || defined(FMC_OVERLOAD_DISPATCH_HELPER_9) || defined(FMC_OVERLOAD_DISPATCH_HELPER_10)
    #undef FMC_OVERLOAD_DISPATCH_HELPER_1
    #undef FMC_OVERLOAD_DISPATCH_HELPER_2
    #undef FMC_OVERLOAD_DISPATCH_HELPER_3
    #undef FMC_OVERLOAD_DISPATCH_HELPER_4
    #undef FMC_OVERLOAD_DISPATCH_HELPER_5
    #undef FMC_OVERLOAD_DISPATCH_HELPER_6
    #undef FMC_OVERLOAD_DISPATCH_HELPER_7
    #undef FMC_OVERLOAD_DISPATCH_HELPER_8
    #undef FMC_OVERLOAD_DISPATCH_HELPER_9
    #undef FMC_OVERLOAD_DISPATCH_HELPER_10
#endif
#define FMC_OVERLOAD_DISPATCH_HELPER_1(_arg_to_process, _arg_1)                                                    \
    _Generic((_arg_to_process),                                                                                    \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1)))  \
        )

#define FMC_OVERLOAD_DISPATCH_HELPER_2(_arg_to_process, _arg_1, _arg_2)                                            \
    _Generic((_arg_to_process),                                                                                    \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))), \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2)))  \
        )

#define FMC_OVERLOAD_DISPATCH_HELPER_3(_arg_to_process, _arg_1, _arg_2, _arg_3)                                    \
    _Generic((_arg_to_process),                                                                                    \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))), \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))), \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3)))  \
        )

#define FMC_OVERLOAD_DISPATCH_HELPER_4(_arg_to_process, _arg_1, _arg_2, _arg_3, _arg_4)                            \
    _Generic((_arg_to_process),                                                                                    \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))), \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))), \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3))), \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_4))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_4)))  \
        )

#define FMC_OVERLOAD_DISPATCH_HELPER_5(_arg_to_process, _arg_1, _arg_2, _arg_3, _arg_4, _arg_5)                    \
    _Generic((_arg_to_process),                                                                                    \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))), \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))), \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3))), \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_4))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_4))), \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_5))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_5)))  \
        )

#define FMC_OVERLOAD_DISPATCH_HELPER_6(_arg_to_process, _arg_1, _arg_2, _arg_3, _arg_4, _arg_5, _arg_6)                    \
    _Generic((_arg_to_process),                                                                                            \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))),         \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))),         \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3))),         \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_4))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_4))),         \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_5))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_5))),         \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_6))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_6)))          \
        )

#define FMC_OVERLOAD_DISPATCH_HELPER_7(_arg_to_process, _arg_1, _arg_2, _arg_3, _arg_4, _arg_5, _arg_6, _arg_7)                    \
    _Generic((_arg_to_process),                                                                                                    \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))),                 \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))),                 \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3))),                 \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_4))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_4))),                 \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_5))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_5))),                 \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_6))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_6))),                 \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_7))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_7)))                  \
        )

#define FMC_OVERLOAD_DISPATCH_HELPER_8(_arg_to_process, _arg_1, _arg_2, _arg_3, _arg_4, _arg_5, _arg_6, _arg_7, _arg_8)                    \
    _Generic((_arg_to_process),                                                                                                            \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))),                         \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))),                         \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3))),                         \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_4))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_4))),                         \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_5))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_5))),                         \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_6))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_6))),                         \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_7))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_7))),                         \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_8))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_8)))                          \
        )

#define FMC_OVERLOAD_DISPATCH_HELPER_9(_arg_to_process, _arg_1, _arg_2, _arg_3, _arg_4, _arg_5, _arg_6, _arg_7, _arg_8, _arg_9)                    \
    _Generic((_arg_to_process),                                                                                                                    \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))),                                 \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))),                                 \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3))),                                 \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_4))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_4))),                                 \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_5))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_5))),                                 \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_6))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_6))),                                 \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_7))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_7))),                                 \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_8))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_8))),                                 \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_9))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_9)))                                  \
        )

#define FMC_OVERLOAD_DISPATCH_HELPER_10(_arg_to_process, _arg_1, _arg_2, _arg_3, _arg_4, _arg_5, _arg_6, _arg_7, _arg_8, _arg_9, _arg_10)                \
    _Generic((_arg_to_process),                                                                                                                          \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_1))),                                       \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_2))),                                       \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_3))),                                       \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_4))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_4))),                                       \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_5))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_5))),                                       \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_6))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_6))),                                       \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_7))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_7))),                                       \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_8))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_8))),                                       \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_9))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_9))),                                       \
        FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _arg_10))) : FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _arg_10)))                                      \
        )

#if defined(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS) || defined(FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC) || defined(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_HELPER1_IMPL) || defined(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_HELPER1_ARITY) || defined(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_EXPANDED) || defined(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_HELPER2_IMPL) || defined(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_HELPER2_ARITY)
    #undef FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS
    #undef FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC
    #undef FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_HELPER1_IMPL
    #undef FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_HELPER1_ARITY
    #undef FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_EXPANDED
    #undef FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_HELPER2_IMPL
    #undef FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_HELPER2_ARITY
#endif
#define FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_HELPER1_IMPL(_arg) ML99_if(ML99_identEq(v(FMC_IDENT_EQ_), v(ptr), v(_arg)), v(*), v(_arg))
#define FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_HELPER1_ARITY 1

#define FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_HELPER2_IMPL(_tuple) ML99_tupleForEach(v(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_HELPER1), v(_tuple))
#define FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_HELPER2_ARITY 1

// FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_EXPANDED((f1, ((unsigned, int, ptr), (int)))) -> unsigned int*, int
// FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS((f1, ((unsigned, int, ptr), (int)))) -> (unsigned, int, ptr) , (int)
// FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC((f1, ((unsigned, int, ptr), (int)))) -> f1

// FMC_ID(FMC_INVOKE(FMC_ID, FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _tuple)))))
#define FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS(_tuple) ML99_LIST_EVAL_COMMA_SEP(ML99_list(v(FMC_ID(FMC_INVOKE(FMC_ID, FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _tuple))))))))
#define FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC(_tuple) FMC_GET_ARGN(0, FMC_ID(FMC_INVOKE(FMC_ID, _tuple)))
#define FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_EXPANDED(_tuple) \
    ML99_LIST_EVAL_COMMA_SEP(ML99_listMap(v(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_HELPER2), ML99_list(v(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS(_tuple)))))

#if defined(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N) || defined(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED)
    #undef FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N
    #undef FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED
#endif
#define FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(_n, _tuple) FMC_GET_ARGN(_n, FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS(_tuple))
#define FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(_n, _tuple) FMC_GET_ARGN(_n, FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_EXPANDED(_tuple))

#if defined(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_EXPANDED_META_IMPL) || defined(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_EXPANDED_META_ARITY)
    #undef FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_EXPANDED_META_IMPL
    #undef FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_EXPANDED_META_ARITY
#endif
#define FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_EXPANDED_META_IMPL(_arg_no_wanted, _tuple) \
    ML99_listGet(v(_arg_no_wanted), ML99_listMap(v(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_HELPER2), ML99_list(v(FMC_ID(FMC_INVOKE(FMC_ID, FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _tuple)))))))))
#define FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_EXPANDED_META_ARITY 2

/* ML99_EVAL(ML99_appl(ML99_appl(v(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_EXPANDED_META), v(0)), v((f1, ((FMC_Char, ptr), (int)))))) */

#if defined(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_META_IMPL) || defined(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_META_ARITY)
    #undef FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_META_IMPL
    #undef FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_META_ARITY
#endif
#define FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_META_IMPL(_arg_no_wanted, _tuple) \
    ML99_listGet(v(_arg_no_wanted), ML99_list(v(FMC_ID(FMC_INVOKE(FMC_ID, FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _tuple))))))))
#define FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_META_ARITY 2

/* ML99_EVAL(ML99_appl(ML99_appl(v(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_META), v(0)), v((f1, ((FMC_Char, ptr), (int)))))) */

#if defined(FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC_META_IMPL) || defined(FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC_META_ARITY)
    #undef FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC_META_IMPL
    #undef FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC_META_ARITY
#endif
#define FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC_META_IMPL(_tuple) v(FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC(_tuple))
#define FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC_META_ARITY 1

#if defined(FMC_OVERLOAD_DISPATCH_1) || defined(FMC_OVERLOAD_DISPATCH_2) || defined(FMC_OVERLOAD_DISPATCH_3) || defined(FMC_OVERLOAD_DISPATCH_4) || defined(FMC_OVERLOAD_DISPATCH_5) || defined(FMC_OVERLOAD_DISPATCH_6) || defined(FMC_OVERLOAD_DISPATCH_7) || defined(FMC_OVERLOAD_DISPATCH_8) || defined(FMC_OVERLOAD_DISPATCH_9) || defined(FMC_OVERLOAD_DISPATCH_10) || defined(FMC_OVERLOAD_DISPATCH_0)
    #undef FMC_OVERLOAD_DISPATCH_1
    #undef FMC_OVERLOAD_DISPATCH_2
    #undef FMC_OVERLOAD_DISPATCH_3
    #undef FMC_OVERLOAD_DISPATCH_4
    #undef FMC_OVERLOAD_DISPATCH_5
    #undef FMC_OVERLOAD_DISPATCH_6
    #undef FMC_OVERLOAD_DISPATCH_7
    #undef FMC_OVERLOAD_DISPATCH_8
    #undef FMC_OVERLOAD_DISPATCH_9
    #undef FMC_OVERLOAD_DISPATCH_10
    #undef FMC_OVERLOAD_DISPATCH_0
#endif
#if defined(FMC_DUPLICATE_10) || defined(FMC_DUPLICATE_9) || defined(FMC_DUPLICATE_8) || defined(FMC_DUPLICATE_7) || defined(FMC_DUPLICATE_6) || defined(FMC_DUPLICATE_5) || defined(FMC_DUPLICATE_4) || defined(FMC_DUPLICATE_3) || defined(FMC_DUPLICATE_2) || defined(FMC_DUPLICATE_1) || defined(FMC_DUPLICATE_0)
    #undef FMC_DUPLICATE_10
    #undef FMC_DUPLICATE_9
    #undef FMC_DUPLICATE_8
    #undef FMC_DUPLICATE_7
    #undef FMC_DUPLICATE_6
    #undef FMC_DUPLICATE_5
    #undef FMC_DUPLICATE_4
    #undef FMC_DUPLICATE_3
    #undef FMC_DUPLICATE_2
    #undef FMC_DUPLICATE_1
    #undef FMC_DUPLICATE_0
#endif
#define FMC_DUPLICATE_0(...) 
#define FMC_DUPLICATE_1(...) __VA_ARGS__
#define FMC_DUPLICATE_2(...) __VA_ARGS__, __VA_ARGS__
#define FMC_DUPLICATE_3(...) __VA_ARGS__, __VA_ARGS__, __VA_ARGS__
#define FMC_DUPLICATE_4(...) __VA_ARGS__, __VA_ARGS__, __VA_ARGS__, __VA_ARGS__
#define FMC_DUPLICATE_5(...) __VA_ARGS__, __VA_ARGS__, __VA_ARGS__, __VA_ARGS__, __VA_ARGS__
#define FMC_DUPLICATE_6(...) __VA_ARGS__, __VA_ARGS__, __VA_ARGS__, __VA_ARGS__, __VA_ARGS__, __VA_ARGS__
#define FMC_DUPLICATE_7(...) __VA_ARGS__, __VA_ARGS__, __VA_ARGS__, __VA_ARGS__, __VA_ARGS__, __VA_ARGS__, __VA_ARGS__
#define FMC_DUPLICATE_8(...) __VA_ARGS__, __VA_ARGS__, __VA_ARGS__, __VA_ARGS__, __VA_ARGS__, __VA_ARGS__, __VA_ARGS__, __VA_ARGS__
#define FMC_DUPLICATE_9(...) FMC_DUPLICATE_5(__VA_ARGS__), FMC_DUPLICATE_4(__VA_ARGS__)

#if defined(FMC_DUPLICATE)
    #undef FMC_DUPLICATE
#endif
#define FMC_DUPLICATE(_n, ...) FMC_CONCAT(FMC_DUPLICATE_, _n)(__VA_ARGS__)

#if defined(FMC_ADD) || defined(FMC_INC) || defined(FMC_DEC) || defined(FMC_SUB)
    #undef FMC_ADD
    #undef FMC_INC
    #undef FMC_DEC
    #undef FMC_SUB
#endif
#define FMC_ADD(_x, _y) ML99_EVAL(ML99_add(v(_x), v(_y)))
#define FMC_INC(_x) ML99_EVAL(ML99_inc(v(_x)))
#define FMC_DEC(_x) ML99_EVAL(ML99_dec(v(_x)))
#define FMC_SUB(_x, _y) ML99_EVAL(ML99_sub(v(_x), v(_y)))

#if defined(FMC_GREATER) || defined(FMC_LESS) || defined(FMC_GREATER_EQUAL) || defined(FMC_LESS_EQUAL)
    #undef FMC_GREATER
    #undef FMC_LESS
    #undef FMC_GREATER_EQUAL
    #undef FMC_LESS_EQUAL
#endif
#define FMC_GREATER(_x, _y) ML99_EVAL(ML99_greater(v(_x), v(_y)))
#define FMC_LESS(_x, _y) ML99_EVAL(ML99_lesser(v(_x), v(_y)))
#define FMC_GREATER_EQUAL(_x, _y) ML99_EVAL(ML99_greaterEq(v(_x), v(_y)))
#define FMC_LESS_EQUAL(_x, _y) ML99_EVAL(ML99_lesserEq(v(_x), v(_y)))

#if defined(FMC_FORMAT_FOR_OVERLOAD_DISPATCH)
    #undef FMC_FORMAT_FOR_OVERLOAD_DISPATCH
#endif

#define FMC_FORMAT_FOR_OVERLOAD_DISPATCH_TO_ZIP_WITH(_arg_no, _func_count, ...) \
    ML99_list(\
        v(FMC_ARGS_X_TO_Y(_func_count, FMC_DEC(FMC_ADD(_func_count, _func_count)), __VA_ARGS__)) \
    )

#define FMC_FORMAT_FOR_OVERLOAD_DISPATCH(_arg_no, _func_count, ...) \
    ML99_LIST_EVAL_COMMA_SEP(\
        ML99_listZip(\
            ML99_listMap(ML99_appl(v(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_EXPANDED_META), v(_arg_no)), ML99_list(v(FMC_ARGS_X_TO_Y(0, FMC_DEC(_func_count), __VA_ARGS__)))),\
            FMC_FORMAT_FOR_OVERLOAD_DISPATCH_TO_ZIP_WITH(_arg_no, _func_count, __VA_ARGS__)\
        )\
    )
/* 
FMC_FORMAT_FOR_OVERLOAD_DISPATCH(0, 2, (f1, ((unsigned, int, ptr), (int))), (f2, ((unsigned, int, ptr), (int))), _Generic(0, int : 0, char : 1, default : 2), f1) // (unsigned int *, _Generic(0, int : 0, char : 1, default : 2)) , (unsigned int *, f1)
 */
#if defined(FMC_OVERLOAD_NESTED_GENERICS)
    #undef FMC_OVERLOAD_NESTED_GENERICS
#endif
#define FMC_OVERLOAD_NESTED_GENERICS(_arg_no, _tupled_expr_to_nest, ...) \
    ML99_LIST_EVAL_COMMA_SEP(\
        ML99_listZip(\
            ML99_listMap(ML99_appl(v(FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS_EXPANDED_META), v(_arg_no)), ML99_list(v(__VA_ARGS__))),\
            ML99_list(v(FMC_DUPLICATE(FMC_GET_ARGC(__VA_ARGS__), FMC_ID(FMC_INVOKE(FMC_ID, _tupled_expr_to_nest)))))\
        )\
    )

#if defined(FMC_ARGS_TO_SEQ) || defined(FMC_ARGS_TO_SEQ_HELPER_IMPL) || defined(FMC_ARGS_TO_SEQ_HELPER_ARITY)
    #undef FMC_ARGS_TO_SEQ
    #undef FMC_ARGS_TO_SEQ_HELPER_IMPL
    #undef FMC_ARGS_TO_SEQ_HELPER_ARITY
#endif
#define FMC_ARGS_TO_SEQ_HELPER_IMPL(_arg) v((_arg))
#define FMC_ARGS_TO_SEQ_HELPER_ARITY 1
#define FMC_ARGS_TO_SEQ(...) ML99_EVAL(ML99_variadicsForEach(v(FMC_ARGS_TO_SEQ_HELPER), v(__VA_ARGS__)))

#if defined(FMC_IDENT_EQ_META_IMPL) || defined(FMC_IDENT_EQ_META_ARITY)
    #undef FMC_IDENT_EQ_META_IMPL
    #undef FMC_IDENT_EQ_META_ARITY
#endif
#define FMC_IDENT_EQ_META_IMPL(_x, _y) v(FMC_IDENT_EQ(_x, _y))
#define FMC_IDENT_EQ_META_ARITY 2

#if defined(FMC_OVERLOAD_COMPARE_TUPLED_TYPES) || defined(FMC_OVERLOAD_COMPARE_TUPLED_TYPES_COMPL)
    #undef FMC_OVERLOAD_COMPARE_TUPLED_TYPES
    #undef FMC_OVERLOAD_COMPARE_TUPLED_TYPES_COMPL
#endif
#define FMC_OVERLOAD_COMPARE_TUPLED_TYPES(_s, _func, ...) \
    CHAOS_PP_BOOL(FMC_IDENT_EQ(FMC_ID(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ID(FMC_GET_ARGN(FMC_ID(FMC_GET_ARGN(1, __VA_ARGS__)), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARGS(FMC_ID(FMC_INVOKE(FMC_ID, _func)))))))

#define FMC_OVERLOAD_COMPARE_TUPLED_TYPES_COMPL(_s, _func, ...) CHAOS_PP_COMPL(FMC_OVERLOAD_COMPARE_TUPLED_TYPES(_s, _func, __VA_ARGS__))

#if defined(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC)
    #undef FMC_OVERLOAD_FILTER_POTENTIAL_FUNC
#endif
// Filter out the potential functions that will figure in the next nested generic
#define FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(_arg_no, _tupled_type_to_compare_to, ...) \
    FMC_ML99_SEQ_AS_ARGS(\
        CHAOS_PP_EXPR(\
            CHAOS_PP_VARIADIC_SEQ_FILTER(\
                FMC_OVERLOAD_COMPARE_TUPLED_TYPES, FMC_ARGS_TO_SEQ(__VA_ARGS__), _tupled_type_to_compare_to, _arg_no \
            )\
        )\
    )

#if defined(FMC_OVERLOAD_FILTER_REMAINING_FUNCS)
    #undef FMC_OVERLOAD_FILTER_REMAINING_FUNCS
#endif
#define FMC_OVERLOAD_FILTER_REMAINING_FUNCS(_arg_no, _tupled_type_to_compare_to, ...) \
    FMC_ML99_SEQ_AS_ARGS(\
        CHAOS_PP_EXPR(\
            CHAOS_PP_VARIADIC_SEQ_FILTER(\
                FMC_OVERLOAD_COMPARE_TUPLED_TYPES_COMPL, FMC_ARGS_TO_SEQ(__VA_ARGS__), _tupled_type_to_compare_to, _arg_no \
            )\
        )\
    )

#if defined(FMC_OVERLOAD_GEN_SUBCASES)
    #undef FMC_OVERLOAD_GEN_SUBCASES
#endif

#if defined(FMC_OVERLOAD_GEN_SUBCASES_FUNC_LIST)
    #undef FMC_OVERLOAD_GEN_SUBCASES_FUNC_LIST
#endif
#define FMC_OVERLOAD_GEN_SUBCASES_FUNC_LIST(_possible_func_count, ...)        \
    ML99_LIST_EVAL_COMMA_SEP(                                                 \
        ML99_list(                                                            \
            v(FMC_ARGS_X_TO_Y(0, FMC_DEC(_possible_func_count), __VA_ARGS__)) \
        )                                                                     \
    )

#if defined(FMC_OVERLOAD_GEN_SUBCASES_ARG_LIST)
    #undef FMC_OVERLOAD_GEN_SUBCASES_ARG_LIST
#endif
#define FMC_OVERLOAD_GEN_SUBCASES_ARG_LIST(_possible_func_count, ...) \
    ML99_LIST_EVAL_COMMA_SEP(                                          \
        ML99_list(                                                     \
            v(FMC_ARGS_X_TO_Y(                                          \
                FMC_INC(_possible_func_count),\
                FMC_ADD(FMC_GET_ARGN(_possible_func_count, __VA_ARGS__), _possible_func_count), __VA_ARGS__)) \
        )                                                                     \
    )

#if defined(FMC_APPEND_ARG)
    #undef FMC_APPEND_ARG
#endif
#define FMC_APPEND_ARG(_a, ...) __VA_ARGS__, _a

/* 
// TESTS 
#define PRED2(s, ...) CHAOS_PP_NOT_EQUAL(FMC_GET_ARGN(0, __VA_ARGS__), 0)
#define OP2(s, ...) CHAOS_PP_DEC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_GET_ARGN(1, __VA_ARGS__)
#define MACRO2(s, ...) FMC_GET_ARGN(0, __VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)

#define PRED(s, ...) CHAOS_PP_NOT_EQUAL(FMC_GET_ARGN(0, __VA_ARGS__), 0)
#define OP(s, ...) CHAOS_PP_DEC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_GET_ARGN(1, __VA_ARGS__)
#define MACRO(s, ...) { CHAOS_PP_EXPR(CHAOS_PP_FOR(PRED2, OP2, MACRO2, __VA_ARGS__)) }

CHAOS_PP_EXPR(CHAOS_PP_FOR(
    PRED, OP, MACRO, 3, 100
)) */
// { 3, 100 2, 100 1, 100 } { 2, 100 1, 100 } { 1, 100 }

#include "FMC_overload_subcase_gen.h"


#define FMC_OVERLOAD_GEN_SUBCASES(_possible_func_count, ...) \
    CHAOS_PP_EXPR(CHAOS_PP_FOR(\
        FMC_OVERLOAD_GEN_SUBCASES_PRED1, FMC_OVERLOAD_GEN_SUBCASES_OP1, FMC_OVERLOAD_GEN_SUBCASES_MACRO1, _possible_func_count, __VA_ARGS__, ()\
    ))

#if defined(FMC_OVERLOAD_SUBCASES)
    #undef FMC_OVERLOAD_SUBCASES
#endif
#define FMC_OVERLOAD_SUBCASES(_possible_func_count, ...) \
    FMC_ML99_SEQ_AS_ARGS(\
        FMC_OVERLOAD_GEN_SUBCASES(_possible_func_count, __VA_ARGS__) \
    )

// No args to process, there must have only one possible function
#define FMC_OVERLOAD_DISPATCH_0(_possible_func_count, ...) FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC(FMC_GET_ARGN(0, __VA_ARGS__))
    
// One arg to process
#define FMC_OVERLOAD_DISPATCH_1(_possible_func_count, ...) \
    FMC_OVERLOAD_DISPATCH_2(_possible_func_count, __VA_ARGS__)

// Two args to process
#define FMC_OVERLOAD_DISPATCH_2(_possible_func_count, ...) \
    FMC_OVERLOAD_DISPATCH_HELPER(\
        FMC_GET_ARGN(0, FMC_OVERLOAD_GEN_SUBCASES_ARG_LIST(_possible_func_count, __VA_ARGS__)),\
        FMC_OVERLOAD_SUBCASES(_possible_func_count, __VA_ARGS__)\
    )
// Three args to process
#define FMC_OVERLOAD_DISPATCH_3(_possible_func_count, ...) \
    FMC_OVERLOAD_DISPATCH_2(_possible_func_count, __VA_ARGS__)

// ...
#define FMC_OVERLOAD_DISPATCH_4(_possible_func_count, ...) \
    FMC_OVERLOAD_DISPATCH_2(_possible_func_count, __VA_ARGS__)

#define FMC_OVERLOAD_DISPATCH_5(_possible_func_count, ...) \
    FMC_OVERLOAD_DISPATCH_2(_possible_func_count, __VA_ARGS__)

#define FMC_OVERLOAD_DISPATCH_6(_possible_func_count, ...) \
    FMC_OVERLOAD_DISPATCH_2(_possible_func_count, __VA_ARGS__)

#define FMC_OVERLOAD_DISPATCH_7(_possible_func_count, ...) \
    FMC_OVERLOAD_DISPATCH_2(_possible_func_count, __VA_ARGS__)

#define FMC_OVERLOAD_DISPATCH_8(_possible_func_count, ...) \
    FMC_OVERLOAD_DISPATCH_2(_possible_func_count, __VA_ARGS__)

#define FMC_OVERLOAD_DISPATCH_9(_possible_func_count, ...) \
    FMC_OVERLOAD_DISPATCH_2(_possible_func_count, __VA_ARGS__)

#define FMC_OVERLOAD_DISPATCH_10(_possible_func_count, ...) \
    FMC_OVERLOAD_DISPATCH_2(_possible_func_count, __VA_ARGS__)

#if defined(FMC_OVERLOAD_DISPATCH) || defined(FMC_OVERLOAD_DISPATCH_HELPER) 
    #undef FMC_OVERLOAD_DISPATCH
    #undef FMC_OVERLOAD_DISPATCH_HELPER
#endif
#define FMC_OVERLOAD_DISPATCH_HELPER(_arg_to_process, ...) FMC_CONCAT(FMC_OVERLOAD_DISPATCH_HELPER_, FMC_GET_ARGC(__VA_ARGS__))(_arg_to_process, __VA_ARGS__)
#define FMC_OVERLOAD_DISPATCH(_possible_func_count, ...) \
    CHAOS_PP_VARIADIC_IF(FMC_GREATER(FMC_GET_ARGN(_possible_func_count, __VA_ARGS__), 10))\
        (static_assert(0, "ERROR: FMC_OVERLOAD: You can not overload functions with more than 10 args if they have at least 9 args with same respective types")) \
        (FMC_CONCAT(FMC_OVERLOAD_DISPATCH_, FMC_GET_ARGN(_possible_func_count, __VA_ARGS__))(_possible_func_count, __VA_ARGS__))

/* FMC_OVERLOAD_DISPATCH_3(2, (f1, ((unsigned, int, ptr), (FMC_Char, ptr), (int))), (f2, ((float), (double), (int))), 3, a, b, c) */

/* FMC_OVERLOAD_DISPATCH_2(2, (f1, ((unsigned, int, ptr), (FMC_Char, ptr))), (f2, ((float), (double))), 2, a, b) */
/*
 * FMC_OVERLOAD_DISPATCH_2(2, (f1, ((unsigned, int, ptr), (FMC_Char, ptr))), (f2, ((float), (double))), 2, a, b) ->
 * _Generic((a),         \
 *    unsigned int*: f1, \
 *    FMC_Char*: f1,     \
 * )
 * 
*/
// FMC_OVERLOAD(4, (f_two_int, ((int), (int))), (f_one_float, ((float))), (f_one_int, ((int))), (f_no_args, ()), FMC_GET_ARGC(a, b), a, b) 
// 1, (f_two_int, ((int), (int))), 2, a, b    are passed to FMC_OVERLOAD_DISPATCH

/* #if defined(FMC_MAYBE)
    #undef FMC_MAYBE
#endif
#define FMC_MAYBE(...) ML99_EVAL(ML99_if(ML99_natEq(v(FMC_GET_ARGC(__VA_ARGS__)), v(0)), v(), v(ML99_QUOTE(, __VA_ARGS__))))

FMC_MAYBE()
FMC_MAYBE(1)
 */

#if defined(FMC_OVERLOAD_EXPAND_IF_NARGS_IMPL) || defined(FMC_OVERLOAD_EXPAND_IF_NARGS_ARITY)
    #undef FMC_OVERLOAD_EXPAND_IF_NARGS_IMPL
    #undef FMC_OVERLOAD_EXPAND_IF_NARGS_ARITY
#endif
#define FMC_OVERLOAD_EXPAND_IF_NARGS_IMPL(_n, _args) \
    ML99_call(ML99_if, ML99_natEq(v(_n), v(FMC_INVOKE(FMC_GET_ARGC, FMC_GET_ARGN(1, FMC_ID(FMC_INVOKE(FMC_ID, _args)))))), v((_args)), ML99_empty())
#define FMC_OVERLOAD_EXPAND_IF_NARGS_ARITY 2

#if defined(FMC_ML99_SEQ_AS_ARGS)
    #undef FMC_ML99_SEQ_AS_ARGS
#endif
#define FMC_ML99_SEQ_AS_ARGS(_seq) FMC_INVOKE(FMC_ID, CHAOS_PP_SEQ_TO_TUPLE(_seq))
/*
 * For instance: 
 *   ML99_SEQ_AS_ARGS(((+, -, *, /))((123))((~))) -> (+, -, *, /), (123), (~)
 * Note that you must extra-parenthise the sequence elements.
*/

#if defined(FMC_OVERLOAD_FILTER_ARGC)
    #undef FMC_OVERLOAD_FILTER_ARGC
#endif
#define FMC_OVERLOAD_FILTER_ARGC(_n, ...) \
    FMC_ML99_SEQ_AS_ARGS(ML99_EVAL(ML99_variadicsForEach(ML99_appl(v(FMC_OVERLOAD_EXPAND_IF_NARGS), v(_n)), v(__VA_ARGS__))))

#if defined(FMC_OVERLOAD_GET_ARGC)
    #undef FMC_OVERLOAD_GET_ARGC
#endif
#define FMC_OVERLOAD_GET_ARGC(...) ML99_EVAL(ML99_if(ML99_natEq(v(FMC_GET_ARGC(__VA_ARGS__)), v(0)), v(0), v(CHAOS_PP_VARIADIC_SIZE(__VA_ARGS__))))

#if defined(FMC_OVERLOAD) || defined(FMC_OVERLOAD_)
    #undef FMC_OVERLOAD
    #undef FMC_OVERLOAD_
#endif
/*
 * This is a macro that allows you to overload functions on the number of arguments and their types.
 * Example: 
 *    #define f(...) \
 *      FMC_OVERLOAD(4, (f_two_int, ((int), (int))), (f_one_float, ((float))), (f_one_int, ((int))), (f_no_args, ()), FMC_GET_ARGC(__VA_ARGS__), __VA_ARGS__)
*/
#define FMC_OVERLOAD(_overloaded_func_count, ...) FMC_OVERLOAD_(_overloaded_func_count, __VA_ARGS__)
#define FMC_OVERLOAD_(_overloaded_func_count, ...) \
    FMC_OVERLOAD_DISPATCH(\
        FMC_OVERLOAD_GET_ARGC(FMC_OVERLOAD_FILTER_ARGC(FMC_GET_ARGN(_overloaded_func_count, __VA_ARGS__), FMC_ARGS_X_TO_Y(0, ML99_EVAL(ML99_dec(v(_overloaded_func_count))), __VA_ARGS__))),\
        FMC_OVERLOAD_FILTER_ARGC(FMC_GET_ARGN(_overloaded_func_count, __VA_ARGS__), FMC_ARGS_X_TO_Y(0, ML99_EVAL(ML99_dec(v(_overloaded_func_count))), __VA_ARGS__)),\
        FMC_ARGS_X_TO_Y(_overloaded_func_count, ML99_EVAL(ML99_add(v(_overloaded_func_count), v(FMC_GET_ARGN(_overloaded_func_count, __VA_ARGS__)))), __VA_ARGS__)\
    )(FMC_ARGS_X_TO_Y(FMC_INC(_overloaded_func_count), FMC_ADD(FMC_INC(_overloaded_func_count), FMC_GET_ARGN(_overloaded_func_count, __VA_ARGS__)), __VA_ARGS__))

#if defined(FMC_OVERLOADED) || defined(FMC_ARGS) || defined(FMC_OVERLOADED_)
    #undef FMC_OVERLOADED
    #undef FMC_OVERLOADED_
    #undef FMC_ARGS
#endif
#define FMC_OVERLOADED(...) FMC_OVERLOADED_(__VA_ARGS__)
#define FMC_OVERLOADED_(...) FMC_GET_ARGC(__VA_ARGS__), __VA_ARGS__
#define FMC_ARGS(...) FMC_OVERLOADED(__VA_ARGS__)

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

#if defined(FMC_alloca) || defined(FMC_alignedAlloca)
    #undef FMC_alloca
    #undef FMC_alignedAlloca
#endif
#define FMC_alloca(size) __builtin_alloca(size)
#define FMC_alignedAlloca(size, type_name) __builtin_alloca_with_align(size, alignof(type_name))


#ifdef FMC_bitSwap
    #undef FMC_bitSwap
#endif
#define FMC_bitSwap(width, to_swap) FMC_CONCAT(__builtin_bswap, width)(to_swap)

#if defined(FMC_Byte_leadingZeros) || defined(FMC_Byte_trailingZeros) || defined(FMC_Byte_popCount)
    #undef FMC_Byte_leadingZeros
    #undef FMC_Byte_trailingZeros
    #undef FMC_Byte_popCount
#endif
#define FMC_Byte_leadingZeros(x) (__builtin_clz((unsigned int) x) - 24) // because FMC_Byte is 8 bits
#define FMC_Byte_trailingZeros(x) (__builtin_ctz((unsigned int) x) - 24) // because FMC_Byte is 8 bits
#define FMC_Byte_popCount(x) (__builtin_popcount((unsigned int) x) - 24) // because FMC_Byte is 8 bits

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

#if defined(FMC_UNREACHABLE_ASSERT)
    #undef FMC_UNREACHABLE_ASSERT
#endif
#define FMC_UNREACHABLE_ASSERT(expr) assert(expr)

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
    #define _Bool bool
#else
    #define FMC_BEGIN_DECLS
    #define FMC_END_DECLS
#endif

// @ macro to cat a token with '@'
#if defined(FMC_PP_AT)
    #undef FMC_PP_AT
#endif
#define FMC_PP_AT(...) __VA_ARGS__@

#if defined(__INTELLISENSE__) && !defined(FMC_COMPILING_ON_WINDOWS)
    #define FMC_BUILD_SO
#endif
/* Maybe I'll have to modify this, even though it sounds fine to me now. */
#if defined(FMC_SHARED) || defined(FMC_SYM) || defined(FMC_DEF_SYM)
    #undef FMC_SHARED
    #undef FMC_SYM
    #undef FMC_DEF_SYM
#endif
#if FMC_COMPILING_ON_WINDOWS && defined(FMC_BUILD_SO)
    #warning "You must define FMC_BUILD_DLL to build the DLL or FMC_USE_DLL to use the built DLL. To use or build the static library, please define FMC_STATIC."
    #define FMC_BUILD_DLL 1
#endif
#if FMC_COMPILING_ON_WINDOWS && !defined(FMC_STATIC)
    #if defined(FMC_BUILD_DLL)
        #define FMC_SHARED __attribute__ ((dllexport))
        #define FMC_SYM(_name, _ver)
        #define FMC_DEF_SYM(_name, _ver)
    #elif defined(FMC_USE_DLL)
        #define FMC_SHARED __attribute__ ((dllimport))
        #define FMC_SYM(_name, _ver)
        #define FMC_DEF_SYM(_name, _ver)
    #else
        #error "You must define FMC_BUILD_DLL to build the DLL or FMC_USE_DLL to use the built DLL. To use or build the static library, please define FMC_STATIC."
    #endif
#elif FMC_COMPILING_ON_WINDOWS && defined(FMC_STATIC)
    #define FMC_SHARED
    #define FMC_SYM(_name, _ver)
    #define FMC_DEF_SYM(_name, _ver)
#elif FMC_COMPILING_ON_LINUX || FMC_COMPILING_ON_MACOS
    #if defined(FMC_STATIC) || defined(FMC_USE_DLL) || defined(FMC_BUILD_DLL)
        #warning "You don't have to specify FMC_STATIC, FMC_USE_DLL or FMC_BUILD_DLL on Linux, Unix or Mac OS X. These are ignored on your system."
    #endif
    #if defined(FMC_BUILD_SO)
        #define FMC_SHARED __attribute__((visibility("default")))
        #define FMC_SYM(_name, _ver) __attribute__((symver(FMC_STRINGIZE(FMC_CONCAT(_name@FMC_VER_, _ver)))))
        #define FMC_DEF_SYM(_name, _ver) __attribute__((symver(FMC_STRINGIZE(FMC_CONCAT(_name@@FMC_VER_, _ver)))))
    #else
        #define FMC_SHARED
        #define FMC_SYM(_name, _ver)
        #define FMC_DEF_SYM(_name, _ver)
    #endif
#else
    #error "Unsupported OS"
#endif // PLATFORMS

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

#if defined(BUILDING_FMANC)
    #if defined(lock_err_mtx) || defined(unlock_err_mtx) || defined(create_err_mtx) || defined(destroy_err_mtx)
        #undef lock_err_mtx
        #undef unlock_err_mtx
        #undef create_err_mtx
        #undef destroy_err_mtx
    #endif
    #if defined(FMC_COMPILING_ON_WINDOWS)
        #if defined(ERR_MTX_SEC_ATTR_STRUCT)
            #undef ERR_MTX_SEC_ATTR_STRUCT
        #endif
        #define ERR_MTX_SEC_ATTR_STRUCT \
           (&(SECURITY_ATTRIBUTES){.nLength = sizeof(SECURITY_ATTRIBUTES), .lpSecurityDescriptor = NULL, .bInheritHandle = FMC_TRUE})

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
            FMC_ERR_STACK_MUTEX = CreateMutexA(ERR_MTX_SEC_ATTR_STRUCT, FMC_FALSE, NULL);           \
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

#endif // BUILDING_FMANC

#if defined(FMC_ADD_OVERFLOW) || defined(FMC_SUB_OVERFLOW) || defined(FMC_MUL_OVERFLOW)
    #undef FMC_ADD_OVERFLOW
    #undef FMC_SUB_OVERFLOW
    #undef FMC_MUL_OVERFLOW
#endif
#define FMC_ADD_OVERFLOW(_a, _b, _res) __builtin_add_overflow(_a, _b, _res)
#define FMC_SUB_OVERFLOW(_a, _b, _res) __builtin_sub_overflow(_a, _b, _res)
#define FMC_MUL_OVERFLOW(_a, _b, _res) __builtin_mul_overflow(_a, _b, _res)

#if defined(FMC_HANDLE_ERR) || defined(FMC_HANDLE_WARN)
    #undef FMC_HANDLE_ERR
    #undef FMC_HANDLE_WARN
#endif
#define FMC_HANDLE_ERR(_err, _msg, _msg_var, _is_int)                       \
    FMC_makeMsg(_msg_var, 4, (_is_int ?                                     \
                             "INTERNAL ERROR: In function: " :              \
                             "ERROR: In function: ")                        \
                             , __func__, ": ", _msg);                       \
    if (FMC_getDebugState())                                                \
        {                                                                   \
            FMC_printRedError(stderr, _msg_var);                            \
        }                                                                   \
    FMC_setError(_err, _msg_var);

#define FMC_HANDLE_WARN(_err, _msg, _msg_var)                               \
    FMC_makeMsg(_msg_var, 4, "ERROR: In function: ", __func__, ": ", _msg); \
    if (FMC_getDebugState())                                                \
        {                                                                   \
            FMC_printYellowError(stderr, _msg_var);                         \
        }                                                                   \
    FMC_setError(_err, _msg_var);


#if defined(for_all_char_in)
    #undef for_all_char_in
#endif
#define for_all_char_in(_str, _char_var) \
    uint64_t FMC_CONCAT(counter, __LINE__) = 0; for (FMC_Char* _char_var = (_str)->firstChar; _char_var != (_str)->lastChar && FMC_CONCAT(counter, __LINE__) != (_str)->size; _char_var = _char_var->next)

#endif // FMC_MACROS_H

#if 0 // Little playground to test macro expansion

#define f(...) FMC_OVERLOAD(FMC_OVERLOADED((f_two_int, ((int), (int))), (f_one_float, ((float))), (f_one_int, ((int))), (f_no_args, ())), FMC_ARGS(__VA_ARGS__))

f()
f(a)
f(x, y)

FMC_ARGS_X_TO_Y(0, 1, (1)(2)0, azefazef, ((f, ((aoiezfugazef)))))

FMC_OVERLOAD_GEN_SUBCASES_MACRO1(s, 3, (f1, ((unsigned, int), (FMC_Char), (ptrdiff_t))), (f2, ((unsigned, int), (FMC_Char), (float))), (f3, ((unsigned, int), (signed, char), (double))), 3, x, y, z, (signed, int))

FMC_OVERLOAD_GEN_SUBCASES(3, (f1, ((unsigned, int), (FMC_Char))), (f2, ((char), (int))), (f3, ((size_t, ptr), (signed, char))), 2, x, y)

FMC_OVERLOAD_DISPATCH_2(3, (f1, ((unsigned, int), (FMC_Char), (ptrdiff_t))), (f2, ((unsigned, int), (FMC_Char), (float))), (f3, ((unsigned, int), (signed, char), (double))), 3, x, y, z, (signed, int))

#define TEST_FUNC1 (f1, ((unsigned, int), (size_t, ptr)))
#define TEST_FUNC2 (f2, ((unsigned, int), (size_t)))
#define TEST_FUNC3 (f3, ((char), (size_t, ptr)))

#define TEST_ARGS 3, TEST_FUNC1, TEST_FUNC2, TEST_FUNC3, 3, a, b, c, (FMC_Char, ptr)

#define TEST_MAC1(_s, ...) \
            FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(0, FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(0, FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))),\
            FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(0, FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(0, FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
            FMC_ARGS_X_TO_Y(\
                FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
                FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
                __VA_ARGS__\
            ),\
            FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(0, FMC_GET_ARGN(1, __VA_ARGS__)), \
            1

#if 0
// TESTS 
#define PRED2(s, ...) CHAOS_PP_NOT_EQUAL(FMC_GET_ARGN(0, __VA_ARGS__), 0)
#define OP2(s, ...) CHAOS_PP_DEC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_GET_ARGN(1, __VA_ARGS__)
#define MACRO2(s, ...) FMC_GET_ARGN(0, __VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)

#define PRED(s, ...) PRED2(s, __VA_ARGS__)// CHAOS_PP_NOT_EQUAL(FMC_GET_ARGN(0, __VA_ARGS__), 0)
#define OP(s, ...) CHAOS_PP_DEC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_GET_ARGN(1, __VA_ARGS__)
#define MACRO(s, ...) { CHAOS_PP_EXPR(CHAOS_PP_FOR(PRED2, OP2, MACRO2, __VA_ARGS__)) }

CHAOS_PP_EXPR(CHAOS_PP_FOR(
    PRED, OP, MACRO, 3, 100
)) 
// { 3, 100 2, 100 1, 100 } { 2, 100 1, 100 } { 1, 100 }

#if 0

#define REC_PRED(s, ...) FMC_GREATER(FMC_GET_LAST_ARG(__VA_ARGS__), 0)
#define REC_OP(s, ...) FMC_ARGS_X_TO_Y(1, FMC_DEC(FMC_DEC(FMC_GET_ARGC(__VA_ARGS__))), __VA_ARGS__), FMC_DEC(FMC_GET_LAST_ARG(__VA_ARGS__))
#define REC_MAC(s, ...) { CHAOS_PP_EXPR(CHAOS_PP_FOR( \
    REC_PRED, REC_OP, REC_MAC2, 3, 2, 1, 0, 4 \
))  }

#define REC_MAC2(s, ...) { FMC_ARGS_X_TO_Y(0, FMC_DEC(FMC_DEC(FMC_GET_ARGC(__VA_ARGS__))), __VA_ARGS__) }

CHAOS_PP_EXPR(CHAOS_PP_FOR(
    REC_PRED, REC_OP, REC_MAC, 3, 2, 1, 0, 4
)) 

#endif

#endif

#endif