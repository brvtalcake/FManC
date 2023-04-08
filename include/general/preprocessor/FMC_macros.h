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
#include <stdint.h>
#include <stdalign.h>
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

#if defined(FMC_GET_ARGC) || defined(FMC_GET_ARGC_INT)
    #undef FMC_GET_ARGC
    #undef FMC_GET_ARGC_INT
#endif
#define FMC_GET_ARGC(...) FMC_GET_ARGC_INT(0, ## __VA_ARGS__, 70, 69, 68, 67, 66, 65, 64, 63, 62, 61, 60, 59, 58, 57, 56, 55, 54, 53, 52, 51, 50, 49, 48, 47, 46, 45, 44, 43, 42, 41, 40, 39, 38, 37, 36, 35, 34, 33, 32, 31, 30, 29, 28, 27, 26, 25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0)
#define FMC_GET_ARGC_INT(_0, _1_, _2_, _3_, _4_, _5_, _6_, _7_, _8_, _9_, _10_, _11_, _12_, _13_, _14_, _15_, _16_, _17_, _18_, _19_, _20_, _21_, _22_, _23_, _24_, _25_, _26_, _27_, _28_, _29_, _30_, _31_, _32_, _33_, _34_, _35_, _36, _37, _38, _39, _40, _41, _42, _43, _44, _45, _46, _47, _48, _49, _50, _51, _52, _53, _54, _55, _56, _57, _58, _59, _60, _61, _62, _63, _64, _65, _66, _67, _68, _69, _70, count, ...) count

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

// Generated usefull macros
#if defined(FMC_2_EXP_X) || defined(FMC_2_EXP_0) || defined(FMC_2_EXP_1) || defined(FMC_2_EXP_2) || defined(FMC_2_EXP_3) || defined(FMC_2_EXP_4) || defined(FMC_2_EXP_5) || defined(FMC_2_EXP_6) || defined(FMC_2_EXP_7) || defined(FMC_2_EXP_8) || defined(FMC_2_EXP_9) || defined(FMC_2_EXP_10) || defined(FMC_2_EXP_11) || defined(FMC_2_EXP_12) || defined(FMC_2_EXP_13) || defined(FMC_2_EXP_14) || defined(FMC_2_EXP_15) || defined(FMC_2_EXP_16) || defined(FMC_2_EXP_17) || defined(FMC_2_EXP_18) || defined(FMC_2_EXP_19) || defined(FMC_2_EXP_20) || defined(FMC_2_EXP_21) || defined(FMC_2_EXP_22) || defined(FMC_2_EXP_23) || defined(FMC_2_EXP_24) || defined(FMC_2_EXP_25) || defined(FMC_2_EXP_26) || defined(FMC_2_EXP_27) || defined(FMC_2_EXP_28) || defined(FMC_2_EXP_29) || defined(FMC_2_EXP_30) || defined(FMC_2_EXP_31) || defined(FMC_2_EXP_32) || defined(FMC_2_EXP_33) || defined(FMC_2_EXP_34) || defined(FMC_2_EXP_35) || defined(FMC_2_EXP_36) || defined(FMC_2_EXP_37) || defined(FMC_2_EXP_38) || defined(FMC_2_EXP_39) || defined(FMC_2_EXP_40) || defined(FMC_2_EXP_41) || defined(FMC_2_EXP_42) || defined(FMC_2_EXP_43) || defined(FMC_2_EXP_44) || defined(FMC_2_EXP_45) || defined(FMC_2_EXP_46) || defined(FMC_2_EXP_47) || defined(FMC_2_EXP_48) || defined(FMC_2_EXP_49) || defined(FMC_2_EXP_50) || defined(FMC_2_EXP_51) || defined(FMC_2_EXP_52) || defined(FMC_2_EXP_53) || defined(FMC_2_EXP_54) || defined(FMC_2_EXP_55) || defined(FMC_2_EXP_56) || defined(FMC_2_EXP_57) || defined(FMC_2_EXP_58) || defined(FMC_2_EXP_59) || defined(FMC_2_EXP_60) || defined(FMC_2_EXP_61) || defined(FMC_2_EXP_62) || defined(FMC_2_EXP_63) || defined(FMC_2_EXP_64)
    #undef FMC_2_EXP_X
    #undef FMC_2_EXP_0
    #undef FMC_2_EXP_1
    #undef FMC_2_EXP_2
    #undef FMC_2_EXP_3
    #undef FMC_2_EXP_4
    #undef FMC_2_EXP_5
    #undef FMC_2_EXP_6
    #undef FMC_2_EXP_7
    #undef FMC_2_EXP_8
    #undef FMC_2_EXP_9
    #undef FMC_2_EXP_10
    #undef FMC_2_EXP_11
    #undef FMC_2_EXP_12
    #undef FMC_2_EXP_13
    #undef FMC_2_EXP_14
    #undef FMC_2_EXP_15
    #undef FMC_2_EXP_16
    #undef FMC_2_EXP_17
    #undef FMC_2_EXP_18
    #undef FMC_2_EXP_19
    #undef FMC_2_EXP_20
    #undef FMC_2_EXP_21
    #undef FMC_2_EXP_22
    #undef FMC_2_EXP_23
    #undef FMC_2_EXP_24
    #undef FMC_2_EXP_25
    #undef FMC_2_EXP_26
    #undef FMC_2_EXP_27
    #undef FMC_2_EXP_28
    #undef FMC_2_EXP_29
    #undef FMC_2_EXP_30
    #undef FMC_2_EXP_31
    #undef FMC_2_EXP_32
    #undef FMC_2_EXP_33
    #undef FMC_2_EXP_34
    #undef FMC_2_EXP_35
    #undef FMC_2_EXP_36
    #undef FMC_2_EXP_37
    #undef FMC_2_EXP_38
    #undef FMC_2_EXP_39
    #undef FMC_2_EXP_40
    #undef FMC_2_EXP_41
    #undef FMC_2_EXP_42
    #undef FMC_2_EXP_43
    #undef FMC_2_EXP_44
    #undef FMC_2_EXP_45
    #undef FMC_2_EXP_46
    #undef FMC_2_EXP_47
    #undef FMC_2_EXP_48
    #undef FMC_2_EXP_49
    #undef FMC_2_EXP_50
    #undef FMC_2_EXP_51
    #undef FMC_2_EXP_52
    #undef FMC_2_EXP_53
    #undef FMC_2_EXP_54
    #undef FMC_2_EXP_55
    #undef FMC_2_EXP_56
    #undef FMC_2_EXP_57
    #undef FMC_2_EXP_58
    #undef FMC_2_EXP_59
    #undef FMC_2_EXP_60
    #undef FMC_2_EXP_61
    #undef FMC_2_EXP_62
    #undef FMC_2_EXP_63
    #undef FMC_2_EXP_64
#endif

#define FMC_2_EXP_64 18446744073709551616
#define FMC_2_EXP_63 9223372036854775808
#define FMC_2_EXP_62 4611686018427387904
#define FMC_2_EXP_61 2305843009213693952
#define FMC_2_EXP_60 1152921504606846976
#define FMC_2_EXP_59 576460752303423488
#define FMC_2_EXP_58 288230376151711744
#define FMC_2_EXP_57 144115188075855872
#define FMC_2_EXP_56 72057594037927936
#define FMC_2_EXP_55 36028797018963968
#define FMC_2_EXP_54 18014398509481984
#define FMC_2_EXP_53 9007199254740992
#define FMC_2_EXP_52 4503599627370496
#define FMC_2_EXP_51 2251799813685248
#define FMC_2_EXP_50 1125899906842624
#define FMC_2_EXP_49 562949953421312
#define FMC_2_EXP_48 281474976710656
#define FMC_2_EXP_47 140737488355328
#define FMC_2_EXP_46 70368744177664
#define FMC_2_EXP_45 35184372088832
#define FMC_2_EXP_44 17592186044416
#define FMC_2_EXP_43 8796093022208
#define FMC_2_EXP_42 4398046511104
#define FMC_2_EXP_41 2199023255552
#define FMC_2_EXP_40 1099511627776
#define FMC_2_EXP_39 549755813888
#define FMC_2_EXP_38 274877906944
#define FMC_2_EXP_37 137438953472
#define FMC_2_EXP_36 68719476736
#define FMC_2_EXP_35 34359738368
#define FMC_2_EXP_34 17179869184
#define FMC_2_EXP_33 8589934592
#define FMC_2_EXP_32 4294967296
#define FMC_2_EXP_31 2147483648
#define FMC_2_EXP_30 1073741824
#define FMC_2_EXP_29 536870912
#define FMC_2_EXP_28 268435456
#define FMC_2_EXP_27 134217728
#define FMC_2_EXP_26 67108864
#define FMC_2_EXP_25 33554432
#define FMC_2_EXP_24 16777216
#define FMC_2_EXP_23 8388608
#define FMC_2_EXP_22 4194304
#define FMC_2_EXP_21 2097152
#define FMC_2_EXP_20 1048576
#define FMC_2_EXP_19 524288
#define FMC_2_EXP_18 262144
#define FMC_2_EXP_17 131072
#define FMC_2_EXP_16 65536
#define FMC_2_EXP_15 32768
#define FMC_2_EXP_14 16384
#define FMC_2_EXP_13 8192
#define FMC_2_EXP_12 4096
#define FMC_2_EXP_11 2048
#define FMC_2_EXP_10 1024
#define FMC_2_EXP_9 512
#define FMC_2_EXP_8 256
#define FMC_2_EXP_7 128
#define FMC_2_EXP_6 64
#define FMC_2_EXP_5 32
#define FMC_2_EXP_4 16
#define FMC_2_EXP_3 8
#define FMC_2_EXP_2 4
#define FMC_2_EXP_1 2
#define FMC_2_EXP_0 1
#define FMC_2_EXP_X(x) FMC_2_EXP_##x

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
#define foreach_stop_cond(x, array) ML99_EVAL(ML99_EVAL(ML99_call(ML99_if, ML99_isNothing(x), v(ML99_id(ML99_id(v(foreach_counter(0) < sizeof(array)/sizeof(array[0]))))), v(ML99_maybeUnwrap(x)))))
#define foreach(elem, array, start, stop_index_cond) size_t foreach_counter(0) = start; for(typeof(array[foreach_counter(0)]) elem = array[foreach_counter(0)]; foreach_stop_cond(stop_index_cond, array) ; foreach_counter(0)++, elem = array[foreach_counter(0)])

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

#if defined(FMC_UINT_ARR) || defined(FMC_INT_ARR)
    #undef FMC_UINT_ARR
    #undef FMC_INT_ARR
#endif
#define FMC_UINT_ARR(...) (unsigned int[]){__VA_ARGS__}
#define FMC_INT_ARR(...) (int[]){__VA_ARGS__}

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
        FMC_ERR_STACK_MUTEX = CreateMutexA(ERR_MTX_SEC_ATTR_STRUCT, FMC_FALSE, NULL);               \
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

#if defined(FMC_ADD_OVERFLOW) || defined(FMC_SUB_OVERFLOW) || defined(FMC_MUL_OVERFLOW)
    #undef FMC_ADD_OVERFLOW
    #undef FMC_SUB_OVERFLOW
    #undef FMC_MUL_OVERFLOW
#endif
#define FMC_ADD_OVERFLOW(a, b, res) __builtin_add_overflow(a, b, res)
#define FMC_SUB_OVERFLOW(a, b, res) __builtin_sub_overflow(a, b, res)
#define FMC_MUL_OVERFLOW(a, b, res) __builtin_mul_overflow(a, b, res)

#endif // ERR_STACK_MUTEX_MACROS


#endif // FMC_MACROS_H
