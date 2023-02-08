/*

MIT License

Copyright (c) 2023 Axel PASCON

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

#ifndef FMC_ATTRIBUTES_H
#define FMC_ATTRIBUTES_H

#include "FMC_platform.h"
#include "FMC_macros.h"

#if defined(__has_attribute)
    #define FMC_HAS_ATTRIBUTE(to_test) __has_attribute(to_test)
#else
    #define FMC_HAS_ATTRIBUTE(to_test) 0
#endif // __has_attribute

#ifndef FMC_FUNC_ATTRIBUTES
    #define FMC_FUNC_ATTRIBUTES 1

    #ifndef FMC_ACCESS
        #define FMC_ACCESS(access_type, position) __attribute__((access(access_type, position)))
    #endif // FMC_ACCESS
    
    #ifndef FMC_ALWAYS_INLINE
        #define FMC_ALWAYS_INLINE __attribute__((always_inline))
    #endif // FMC_ALWAYS_INLINE

    #ifndef FMC_COLD
        #define FMC_COLD __attribute__((cold))
    #endif // FMC_COLD

    #ifndef FMC_CONST
        #define FMC_CONST __attribute__((const))
    #endif // FMC_CONST

    #ifndef FMC_CONSTRUCTOR
        #define FMC_CONSTRUCTOR(priority) __attribute__((constructor(priority)))
    #endif // FMC_CONSTRUCTOR

    #ifndef FMC_DESTRUCTOR
        #define FMC_DESTRUCTOR(priority) __attribute__((destructor(priority)))
    #endif // FMC_DESTRUCTOR



    #ifndef FMC_INLINE
        #define FMC_INLINE inline FMC_ALWAYS_INLINE
    #endif // FMC_INLINE

    #ifndef FMC_PRINTF_FMT
        #define FMC_PRINTF_FMT(fmt_pos, args_pos) __attribute__((format(printf, fmt_pos, args_pos)))
    #endif // FMC_PRINTF_FMT

#endif //FMC_FUNC_ATTRIBUTES


#endif // FMC_ATTRIBUTES_H

/*
#ifndef FMC_ALIAS_FUNC
        #define FMC_ALIAS_FUNC(func_name, aliased) __attribute__((alias(FMC_STRINGIZE(aliased)))) __attribute__((copy(aliased))) __typeof__(aliased) func_name
    #endif // FMC_ALIAS_FUNC

*/