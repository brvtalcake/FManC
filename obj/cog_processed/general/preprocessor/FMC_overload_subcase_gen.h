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

#ifndef FMC_OVERLOAD_SUBCASE_GEN_H
#define FMC_OVERLOAD_SUBCASE_GEN_H

#include <assert.h>

#if defined(FMC_OVERLOAD_GEN_SUBCASES_PRED1) || defined(FMC_OVERLOAD_GEN_SUBCASES_OP1) || defined(FMC_OVERLOAD_GEN_SUBCASES_MACRO1)
    #undef FMC_OVERLOAD_GEN_SUBCASES_PRED1
    #undef FMC_OVERLOAD_GEN_SUBCASES_OP1
    #undef FMC_OVERLOAD_GEN_SUBCASES_MACRO1
#endif
// last arg (appended to the variables to dispatch in _Generics) : current_type
// before last arg : the positionnal index to the variable being dispatched (for FMC_OVERLOAD_GEN_SUBCASES_[PRED|OP|MACRO]2 macros)
#define FMC_OVERLOAD_GEN_SUBCASES_PRED1(s, ...) FMC_GREATER(FMC_GET_ARGN(0, __VA_ARGS__), 0)

#define FMC_OVERLOAD_GEN_SUBCASES_OP1(s, ...) \
    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_REMAINING_FUNCS(0, FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(0, FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))),\
    FMC_OVERLOAD_FILTER_REMAINING_FUNCS(0, FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(0, FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
    FMC_ARGS_X_TO_Y(\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
        __VA_ARGS__\
    ),\
    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(0, FMC_GET_ARGN(1, __VA_ARGS__))

#define FMC_OVERLOAD_GEN_SUBCASES_MACRO1(s, ...)                                                                              \
    ((\
    CHAOS_PP_VARIADIC_IF(CHAOS_PP_EQUAL(\
        1,\
        FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                     0,\
                     FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(0, FMC_GET_ARGN(1, __VA_ARGS__)),\
                     FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
        ))\
    )) \
    /* When there is only one possible function */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(0, FMC_GET_ARGN(1, __VA_ARGS__)),\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC(\
            FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                0,\
                FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(0, FMC_GET_ARGN(1, __VA_ARGS__)),\
                FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
            )\
        )\
    )\
    /* When there are multiple possible functions */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(0, FMC_GET_ARGN(1, __VA_ARGS__)),\
        (FMC_OVERLOAD_DISPATCH_HELPER(\
            FMC_GET_ARGN(1, FMC_OVERLOAD_GEN_SUBCASES_ARG_LIST(FMC_GET_ARGN(0, __VA_ARGS__), FMC_ARGS_X_TO_Y(1, FMC_DEC(FMC_GET_ARGC(__VA_ARGS__)), __VA_ARGS__))),\
            FMC_ML99_SEQ_AS_ARGS(\
                CHAOS_PP_EXPR(                                                                                                              \
                    CHAOS_PP_FOR(                                                                                                           \
                    FMC_OVERLOAD_GEN_SUBCASES_PRED2, FMC_OVERLOAD_GEN_SUBCASES_OP2, FMC_OVERLOAD_GEN_SUBCASES_MACRO2,\
                    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(0, FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(0, FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))),\
                    FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(0, FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(0, FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
                    FMC_ARGS_X_TO_Y(\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
                        __VA_ARGS__\
                    ),\
                    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(0, FMC_GET_ARGN(1, __VA_ARGS__)), \
                    1\
                    )\
                )                                                                                                                       \
            )\
        ))\
    )\
    ))


#if defined(FMC_OVERLOAD_GEN_SUBCASES_PRED2) || defined(FMC_OVERLOAD_GEN_SUBCASES_OP2) || defined(FMC_OVERLOAD_GEN_SUBCASES_MACRO2)
    #undef FMC_OVERLOAD_GEN_SUBCASES_PRED2
    #undef FMC_OVERLOAD_GEN_SUBCASES_OP2
    #undef FMC_OVERLOAD_GEN_SUBCASES_MACRO2
#endif
#define FMC_OVERLOAD_GEN_SUBCASES_PRED2(s, ...) FMC_GREATER(FMC_GET_ARGN(0, __VA_ARGS__), 0)

#define FMC_OVERLOAD_GEN_SUBCASES_OP2(s, ...) \
    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))), \
    FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
    FMC_ARGS_X_TO_Y(\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
        __VA_ARGS__\
    ),\
    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
    FMC_GET_LAST_ARG(__VA_ARGS__)

#define FMC_OVERLOAD_GEN_SUBCASES_MACRO2(s, ...) \
    ((\
    CHAOS_PP_VARIADIC_IF(CHAOS_PP_EQUAL(\
        1,\
        FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                     FMC_GET_LAST_ARG(__VA_ARGS__),\
                     FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                     FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
        ))\
    )) \
    /* When there is only one possible function */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC(\
            FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                FMC_GET_LAST_ARG(__VA_ARGS__),\
                FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
            )\
        )\
    )\
    /* When there are multiple possible functions */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        (FMC_OVERLOAD_DISPATCH_HELPER(\
            FMC_GET_ARGN(FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__)), FMC_OVERLOAD_GEN_SUBCASES_ARG_LIST(FMC_GET_ARGN(0, __VA_ARGS__), FMC_ARGS_X_TO_Y(1, FMC_DEC(FMC_GET_ARGC(__VA_ARGS__)), __VA_ARGS__))),\
            FMC_ML99_SEQ_AS_ARGS(\
                CHAOS_PP_EXPR(                                                                                                              \
                    CHAOS_PP_FOR(                                                                                                           \
                    FMC_OVERLOAD_GEN_SUBCASES_PRED3, FMC_OVERLOAD_GEN_SUBCASES_OP3, FMC_OVERLOAD_GEN_SUBCASES_MACRO3,\
                    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))),\
                    FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
                    FMC_ARGS_X_TO_Y(\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
                        __VA_ARGS__\
                    ),\
                    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
                    FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__))\
                    )\
                )                                                                                                                       \
            )\
        ))\
    )\
    ))

#if defined(FMC_OVERLOAD_GEN_SUBCASES_PRED3) || defined(FMC_OVERLOAD_GEN_SUBCASES_OP3) || defined(FMC_OVERLOAD_GEN_SUBCASES_MACRO3)
    #undef FMC_OVERLOAD_GEN_SUBCASES_PRED3
    #undef FMC_OVERLOAD_GEN_SUBCASES_OP3
    #undef FMC_OVERLOAD_GEN_SUBCASES_MACRO3
#endif
#define FMC_OVERLOAD_GEN_SUBCASES_PRED3(s, ...) FMC_GREATER(FMC_GET_ARGN(0, __VA_ARGS__), 0)

#define FMC_OVERLOAD_GEN_SUBCASES_OP3(s, ...) \
    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))), \
    FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
    FMC_ARGS_X_TO_Y(\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
        __VA_ARGS__\
    ),\
    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
    FMC_GET_LAST_ARG(__VA_ARGS__)

#define FMC_OVERLOAD_GEN_SUBCASES_MACRO3(s, ...) \
    ((\
    CHAOS_PP_VARIADIC_IF(CHAOS_PP_EQUAL(\
        1,\
        FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                     FMC_GET_LAST_ARG(__VA_ARGS__),\
                     FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                     FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
        ))\
    )) \
    /* When there is only one possible function */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC(\
            FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                FMC_GET_LAST_ARG(__VA_ARGS__),\
                FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
            )\
        )\
    )\
    /* When there are multiple possible functions */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        (FMC_OVERLOAD_DISPATCH_HELPER(\
            FMC_GET_ARGN(FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__)), FMC_OVERLOAD_GEN_SUBCASES_ARG_LIST(FMC_GET_ARGN(0, __VA_ARGS__), FMC_ARGS_X_TO_Y(1, FMC_DEC(FMC_GET_ARGC(__VA_ARGS__)), __VA_ARGS__))),\
            FMC_ML99_SEQ_AS_ARGS(\
                CHAOS_PP_EXPR(                                                                                                              \
                    CHAOS_PP_FOR(                                                                                                           \
                    FMC_OVERLOAD_GEN_SUBCASES_PRED4, FMC_OVERLOAD_GEN_SUBCASES_OP4, FMC_OVERLOAD_GEN_SUBCASES_MACRO4,\
                    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))),\
                    FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
                    FMC_ARGS_X_TO_Y(\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
                        __VA_ARGS__\
                    ),\
                    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
                    FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__))\
                    )\
                )                                                                                                                       \
            )\
        ))\
    )\
    ))


#if defined(FMC_OVERLOAD_GEN_SUBCASES_PRED4) || defined(FMC_OVERLOAD_GEN_SUBCASES_OP4) || defined(FMC_OVERLOAD_GEN_SUBCASES_MACRO4)
    #undef FMC_OVERLOAD_GEN_SUBCASES_PRED4
    #undef FMC_OVERLOAD_GEN_SUBCASES_OP4
    #undef FMC_OVERLOAD_GEN_SUBCASES_MACRO4
#endif
#define FMC_OVERLOAD_GEN_SUBCASES_PRED4(s, ...) FMC_GREATER(FMC_GET_ARGN(0, __VA_ARGS__), 0)

#define FMC_OVERLOAD_GEN_SUBCASES_OP4(s, ...) \
    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))), \
    FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
    FMC_ARGS_X_TO_Y(\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
        __VA_ARGS__\
    ),\
    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
    FMC_GET_LAST_ARG(__VA_ARGS__)

#define FMC_OVERLOAD_GEN_SUBCASES_MACRO4(s, ...) \
    ((\
    CHAOS_PP_VARIADIC_IF(CHAOS_PP_EQUAL(\
        1,\
        FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                     FMC_GET_LAST_ARG(__VA_ARGS__),\
                     FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                     FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
        ))\
    )) \
    /* When there is only one possible function */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC(\
            FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                FMC_GET_LAST_ARG(__VA_ARGS__),\
                FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
            )\
        )\
    )\
    /* When there are multiple possible functions */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        (FMC_OVERLOAD_DISPATCH_HELPER(\
            FMC_GET_ARGN(FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__)), FMC_OVERLOAD_GEN_SUBCASES_ARG_LIST(FMC_GET_ARGN(0, __VA_ARGS__), FMC_ARGS_X_TO_Y(1, FMC_DEC(FMC_GET_ARGC(__VA_ARGS__)), __VA_ARGS__))),\
            FMC_ML99_SEQ_AS_ARGS(\
                CHAOS_PP_EXPR(                                                                                                              \
                    CHAOS_PP_FOR(                                                                                                           \
                    FMC_OVERLOAD_GEN_SUBCASES_PRED5, FMC_OVERLOAD_GEN_SUBCASES_OP5, FMC_OVERLOAD_GEN_SUBCASES_MACRO5,\
                    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))),\
                    FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
                    FMC_ARGS_X_TO_Y(\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
                        __VA_ARGS__\
                    ),\
                    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
                    FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__))\
                    )\
                )                                                                                                                       \
            )\
        ))\
    )\
    ))


#if defined(FMC_OVERLOAD_GEN_SUBCASES_PRED5) || defined(FMC_OVERLOAD_GEN_SUBCASES_OP5) || defined(FMC_OVERLOAD_GEN_SUBCASES_MACRO5)
    #undef FMC_OVERLOAD_GEN_SUBCASES_PRED5
    #undef FMC_OVERLOAD_GEN_SUBCASES_OP5
    #undef FMC_OVERLOAD_GEN_SUBCASES_MACRO5
#endif
#define FMC_OVERLOAD_GEN_SUBCASES_PRED5(s, ...) FMC_GREATER(FMC_GET_ARGN(0, __VA_ARGS__), 0)

#define FMC_OVERLOAD_GEN_SUBCASES_OP5(s, ...) \
    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))), \
    FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
    FMC_ARGS_X_TO_Y(\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
        __VA_ARGS__\
    ),\
    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
    FMC_GET_LAST_ARG(__VA_ARGS__)

#define FMC_OVERLOAD_GEN_SUBCASES_MACRO5(s, ...) \
    ((\
    CHAOS_PP_VARIADIC_IF(CHAOS_PP_EQUAL(\
        1,\
        FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                     FMC_GET_LAST_ARG(__VA_ARGS__),\
                     FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                     FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
        ))\
    )) \
    /* When there is only one possible function */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC(\
            FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                FMC_GET_LAST_ARG(__VA_ARGS__),\
                FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
            )\
        )\
    )\
    /* When there are multiple possible functions */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        (FMC_OVERLOAD_DISPATCH_HELPER(\
            FMC_GET_ARGN(FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__)), FMC_OVERLOAD_GEN_SUBCASES_ARG_LIST(FMC_GET_ARGN(0, __VA_ARGS__), FMC_ARGS_X_TO_Y(1, FMC_DEC(FMC_GET_ARGC(__VA_ARGS__)), __VA_ARGS__))),\
            FMC_ML99_SEQ_AS_ARGS(\
                CHAOS_PP_EXPR(                                                                                                              \
                    CHAOS_PP_FOR(                                                                                                           \
                    FMC_OVERLOAD_GEN_SUBCASES_PRED6, FMC_OVERLOAD_GEN_SUBCASES_OP6, FMC_OVERLOAD_GEN_SUBCASES_MACRO6,\
                    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))),\
                    FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
                    FMC_ARGS_X_TO_Y(\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
                        __VA_ARGS__\
                    ),\
                    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
                    FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__))\
                    )\
                )                                                                                                                       \
            )\
        ))\
    )\
    ))


#if defined(FMC_OVERLOAD_GEN_SUBCASES_PRED6) || defined(FMC_OVERLOAD_GEN_SUBCASES_OP6) || defined(FMC_OVERLOAD_GEN_SUBCASES_MACRO6)
    #undef FMC_OVERLOAD_GEN_SUBCASES_PRED6
    #undef FMC_OVERLOAD_GEN_SUBCASES_OP6
    #undef FMC_OVERLOAD_GEN_SUBCASES_MACRO6
#endif
#define FMC_OVERLOAD_GEN_SUBCASES_PRED6(s, ...) FMC_GREATER(FMC_GET_ARGN(0, __VA_ARGS__), 0)

#define FMC_OVERLOAD_GEN_SUBCASES_OP6(s, ...) \
    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))), \
    FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
    FMC_ARGS_X_TO_Y(\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
        __VA_ARGS__\
    ),\
    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
    FMC_GET_LAST_ARG(__VA_ARGS__)

#define FMC_OVERLOAD_GEN_SUBCASES_MACRO6(s, ...) \
    ((\
    CHAOS_PP_VARIADIC_IF(CHAOS_PP_EQUAL(\
        1,\
        FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                     FMC_GET_LAST_ARG(__VA_ARGS__),\
                     FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                     FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
        ))\
    )) \
    /* When there is only one possible function */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC(\
            FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                FMC_GET_LAST_ARG(__VA_ARGS__),\
                FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
            )\
        )\
    )\
    /* When there are multiple possible functions */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        (FMC_OVERLOAD_DISPATCH_HELPER(\
            FMC_GET_ARGN(FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__)), FMC_OVERLOAD_GEN_SUBCASES_ARG_LIST(FMC_GET_ARGN(0, __VA_ARGS__), FMC_ARGS_X_TO_Y(1, FMC_DEC(FMC_GET_ARGC(__VA_ARGS__)), __VA_ARGS__))),\
            FMC_ML99_SEQ_AS_ARGS(\
                CHAOS_PP_EXPR(                                                                                                              \
                    CHAOS_PP_FOR(                                                                                                           \
                    FMC_OVERLOAD_GEN_SUBCASES_PRED7, FMC_OVERLOAD_GEN_SUBCASES_OP7, FMC_OVERLOAD_GEN_SUBCASES_MACRO7,\
                    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))),\
                    FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
                    FMC_ARGS_X_TO_Y(\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
                        __VA_ARGS__\
                    ),\
                    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
                    FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__))\
                    )\
                )                                                                                                                       \
            )\
        ))\
    )\
    ))


#if defined(FMC_OVERLOAD_GEN_SUBCASES_PRED7) || defined(FMC_OVERLOAD_GEN_SUBCASES_OP7) || defined(FMC_OVERLOAD_GEN_SUBCASES_MACRO7)
    #undef FMC_OVERLOAD_GEN_SUBCASES_PRED7
    #undef FMC_OVERLOAD_GEN_SUBCASES_OP7
    #undef FMC_OVERLOAD_GEN_SUBCASES_MACRO7
#endif
#define FMC_OVERLOAD_GEN_SUBCASES_PRED7(s, ...) FMC_GREATER(FMC_GET_ARGN(0, __VA_ARGS__), 0)

#define FMC_OVERLOAD_GEN_SUBCASES_OP7(s, ...) \
    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))), \
    FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
    FMC_ARGS_X_TO_Y(\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
        __VA_ARGS__\
    ),\
    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
    FMC_GET_LAST_ARG(__VA_ARGS__)

#define FMC_OVERLOAD_GEN_SUBCASES_MACRO7(s, ...) \
    ((\
    CHAOS_PP_VARIADIC_IF(CHAOS_PP_EQUAL(\
        1,\
        FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                     FMC_GET_LAST_ARG(__VA_ARGS__),\
                     FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                     FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
        ))\
    )) \
    /* When there is only one possible function */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC(\
            FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                FMC_GET_LAST_ARG(__VA_ARGS__),\
                FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
            )\
        )\
    )\
    /* When there are multiple possible functions */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        (FMC_OVERLOAD_DISPATCH_HELPER(\
            FMC_GET_ARGN(FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__)), FMC_OVERLOAD_GEN_SUBCASES_ARG_LIST(FMC_GET_ARGN(0, __VA_ARGS__), FMC_ARGS_X_TO_Y(1, FMC_DEC(FMC_GET_ARGC(__VA_ARGS__)), __VA_ARGS__))),\
            FMC_ML99_SEQ_AS_ARGS(\
                CHAOS_PP_EXPR(                                                                                                              \
                    CHAOS_PP_FOR(                                                                                                           \
                    FMC_OVERLOAD_GEN_SUBCASES_PRED8, FMC_OVERLOAD_GEN_SUBCASES_OP8, FMC_OVERLOAD_GEN_SUBCASES_MACRO8,\
                    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))),\
                    FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
                    FMC_ARGS_X_TO_Y(\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
                        __VA_ARGS__\
                    ),\
                    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
                    FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__))\
                    )\
                )                                                                                                                       \
            )\
        ))\
    )\
    ))


#if defined(FMC_OVERLOAD_GEN_SUBCASES_PRED8) || defined(FMC_OVERLOAD_GEN_SUBCASES_OP8) || defined(FMC_OVERLOAD_GEN_SUBCASES_MACRO8)
    #undef FMC_OVERLOAD_GEN_SUBCASES_PRED8
    #undef FMC_OVERLOAD_GEN_SUBCASES_OP8
    #undef FMC_OVERLOAD_GEN_SUBCASES_MACRO8
#endif
#define FMC_OVERLOAD_GEN_SUBCASES_PRED8(s, ...) FMC_GREATER(FMC_GET_ARGN(0, __VA_ARGS__), 0)

#define FMC_OVERLOAD_GEN_SUBCASES_OP8(s, ...) \
    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))), \
    FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
    FMC_ARGS_X_TO_Y(\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
        __VA_ARGS__\
    ),\
    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
    FMC_GET_LAST_ARG(__VA_ARGS__)

#define FMC_OVERLOAD_GEN_SUBCASES_MACRO8(s, ...) \
    ((\
    CHAOS_PP_VARIADIC_IF(CHAOS_PP_EQUAL(\
        1,\
        FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                     FMC_GET_LAST_ARG(__VA_ARGS__),\
                     FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                     FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
        ))\
    )) \
    /* When there is only one possible function */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC(\
            FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                FMC_GET_LAST_ARG(__VA_ARGS__),\
                FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
            )\
        )\
    )\
    /* When there are multiple possible functions */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        (FMC_OVERLOAD_DISPATCH_HELPER(\
            FMC_GET_ARGN(FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__)), FMC_OVERLOAD_GEN_SUBCASES_ARG_LIST(FMC_GET_ARGN(0, __VA_ARGS__), FMC_ARGS_X_TO_Y(1, FMC_DEC(FMC_GET_ARGC(__VA_ARGS__)), __VA_ARGS__))),\
            FMC_ML99_SEQ_AS_ARGS(\
                CHAOS_PP_EXPR(                                                                                                              \
                    CHAOS_PP_FOR(                                                                                                           \
                    FMC_OVERLOAD_GEN_SUBCASES_PRED9, FMC_OVERLOAD_GEN_SUBCASES_OP9, FMC_OVERLOAD_GEN_SUBCASES_MACRO9,\
                    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))),\
                    FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
                    FMC_ARGS_X_TO_Y(\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
                        __VA_ARGS__\
                    ),\
                    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
                    FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__))\
                    )\
                )                                                                                                                       \
            )\
        ))\
    )\
    ))


#if defined(FMC_OVERLOAD_GEN_SUBCASES_PRED9) || defined(FMC_OVERLOAD_GEN_SUBCASES_OP9) || defined(FMC_OVERLOAD_GEN_SUBCASES_MACRO9)
    #undef FMC_OVERLOAD_GEN_SUBCASES_PRED9
    #undef FMC_OVERLOAD_GEN_SUBCASES_OP9
    #undef FMC_OVERLOAD_GEN_SUBCASES_MACRO9
#endif
#define FMC_OVERLOAD_GEN_SUBCASES_PRED9(s, ...) FMC_GREATER(FMC_GET_ARGN(0, __VA_ARGS__), 0)

#define FMC_OVERLOAD_GEN_SUBCASES_OP9(s, ...) \
    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))), \
    FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
    FMC_ARGS_X_TO_Y(\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
        __VA_ARGS__\
    ),\
    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
    FMC_GET_LAST_ARG(__VA_ARGS__)

#define FMC_OVERLOAD_GEN_SUBCASES_MACRO9(s, ...) \
    ((\
    CHAOS_PP_VARIADIC_IF(CHAOS_PP_EQUAL(\
        1,\
        FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                     FMC_GET_LAST_ARG(__VA_ARGS__),\
                     FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                     FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
        ))\
    )) \
    /* When there is only one possible function */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC(\
            FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                FMC_GET_LAST_ARG(__VA_ARGS__),\
                FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
            )\
        )\
    )\
    /* When there are multiple possible functions */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        (FMC_OVERLOAD_DISPATCH_HELPER(\
            FMC_GET_ARGN(FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__)), FMC_OVERLOAD_GEN_SUBCASES_ARG_LIST(FMC_GET_ARGN(0, __VA_ARGS__), FMC_ARGS_X_TO_Y(1, FMC_DEC(FMC_GET_ARGC(__VA_ARGS__)), __VA_ARGS__))),\
            FMC_ML99_SEQ_AS_ARGS(\
                CHAOS_PP_EXPR(                                                                                                              \
                    CHAOS_PP_FOR(                                                                                                           \
                    FMC_OVERLOAD_GEN_SUBCASES_PRED10, FMC_OVERLOAD_GEN_SUBCASES_OP10, FMC_OVERLOAD_GEN_SUBCASES_MACRO10,\
                    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))),\
                    FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
                    FMC_ARGS_X_TO_Y(\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
                        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
                        __VA_ARGS__\
                    ),\
                    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
                    FMC_INC(FMC_GET_LAST_ARG(__VA_ARGS__))\
                    )\
                )                                                                                                                       \
            )\
        ))\
    )\
    ))


#if defined(FMC_OVERLOAD_GEN_SUBCASES_PRED10) || defined(FMC_OVERLOAD_GEN_SUBCASES_OP10) || defined(FMC_OVERLOAD_GEN_SUBCASES_MACRO10)
    #undef FMC_OVERLOAD_GEN_SUBCASES_PRED10
    #undef FMC_OVERLOAD_GEN_SUBCASES_OP10
    #undef FMC_OVERLOAD_GEN_SUBCASES_MACRO10
#endif
#define FMC_OVERLOAD_GEN_SUBCASES_PRED10(s, ...) FMC_GREATER(FMC_GET_ARGN(0, __VA_ARGS__), 0)

#define FMC_OVERLOAD_GEN_SUBCASES_OP10(s, ...) \
    FMC_GET_ARGC(FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__))), \
    FMC_OVERLOAD_FILTER_REMAINING_FUNCS(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)), \
    FMC_ARGS_X_TO_Y(\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), FMC_ADD(FMC_GET_ARGN(FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__)), __VA_ARGS__),\
        FMC_INC(FMC_GET_ARGN(0, __VA_ARGS__))),\
        __VA_ARGS__\
    ),\
    FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)), \
    FMC_GET_LAST_ARG(__VA_ARGS__)

#define FMC_OVERLOAD_GEN_SUBCASES_MACRO10(s, ...) \
    ((\
    CHAOS_PP_VARIADIC_IF(CHAOS_PP_EQUAL(\
        1,\
        FMC_GET_ARGC(FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                     FMC_GET_LAST_ARG(__VA_ARGS__),\
                     FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                     FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
        ))\
    )) \
    /* When there is only one possible function */ \
    (\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N_EXPANDED(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
        FMC_OVERLOAD_FUNC_SIG_EXTRACT_FUNC(\
            FMC_OVERLOAD_FILTER_POTENTIAL_FUNC(\
                FMC_GET_LAST_ARG(__VA_ARGS__),\
                FMC_OVERLOAD_FUNC_SIG_EXTRACT_ARG_N(FMC_GET_LAST_ARG(__VA_ARGS__), FMC_GET_ARGN(1, __VA_ARGS__)),\
                FMC_ARGS_X_TO_Y(1, FMC_GET_ARGN(0, __VA_ARGS__), __VA_ARGS__)\
            )\
        )\
    )\
    /* When there are multiple possible functions */ \
    (\
        non_existent_t : static_assert(0, "FMC_OVERLOAD: ERROR: You can not overload functions that have more than 10 args") \
    )\
    ))

#endif