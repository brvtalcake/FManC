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

#include "FMC_macros.h"


#ifndef FMC_FUNC_ATTRIBUTES
    #define FMC_FUNC_ATTRIBUTES 1

    #ifndef FMC_FUNC_ACCESS
        #define FMC_FUNC_ACCESS(access_type, ...) __attribute__((access(access_type, __VA_ARGS__)))
    #endif

    #ifndef FMC_FUNC_ALIAS
        #define FMC_FUNC_ALIAS(aliased) __attribute__((alias(FMC_STRINGIZE(aliased)))) 
    #endif

    #ifdef FMC_FUNC_ALLOC_SIZE
        #undef FMC_FUNC_ALLOC_SIZE
    #endif
    #define FMC_FUNC_ALLOC_SIZE(_p1, ...) __attribute__((alloc_size(_p1, __VA_ARGS__)))

    #ifndef FMC_FUNC_ALWAYS_INLINE
        #define FMC_FUNC_ALWAYS_INLINE __attribute__((always_inline))
    #endif

    #ifndef FMC_FUNC_COLD
        #define FMC_FUNC_COLD __attribute__((cold))
    #endif

    #ifndef FMC_FUNC_CONST
        #define FMC_FUNC_CONST __attribute__((const))
    #endif

    #ifndef FMC_FUNC_CONSTRUCTOR
        #define FMC_FUNC_CONSTRUCTOR(...)                                       \
            CHAOS_PP_VARIADIC_IF(CHAOS_PP_EQUAL(FMC_GET_ARGC(__VA_ARGS__), 0))  \
                (__attribute__((constructor)))                                  \
                (__attribute__((constructor(__VA_ARGS__))))
    #endif

    #ifndef FMC_FUNC_DESTRUCTOR
        #define FMC_FUNC_DESTRUCTOR(...)                                        \
            CHAOS_PP_VARIADIC_IF(CHAOS_PP_EQUAL(FMC_GET_ARGC(__VA_ARGS__), 0))  \
                (__attribute__((destructor)))                                   \
                (__attribute__((destructor(__VA_ARGS__))))
    #endif

    #ifndef FMC_FUNC_COPY
        #define FMC_FUNC_COPY(func) __attribute__((copy(func)))
    #endif

    #ifndef FMC_FUNC_DEPRECATED
        #define FMC_FUNC_DEPRECATED(msg) __attribute__((deprecated(FMC_STRINGIZE(msg))))
    #endif

    #ifndef FMC_FUNC_UNAVAILABLE
        #define FMC_FUNC_UNAVAILABLE(msg) __attribute__((unavailable(FMC_STRINGIZE(msg))))
    #endif

    #ifndef FMC_FUNC_ERROR
        #define FMC_FUNC_ERROR(msg) __attribute__((error(FMC_STRINGIZE(msg))))
    #endif

    #ifndef FMC_FUNC_WARNING
        #define FMC_FUNC_WARNING(msg) __attribute__((warning(FMC_STRINGIZE(msg))))
    #endif

    #ifndef FMC_FUNC_EXTERNALLY_VISIBLE
        #define FMC_FUNC_EXTERNALLY_VISIBLE __attribute__((externally_visible))
    #endif

    #ifndef FMC_FUNC_FLATTEN
        #define FMC_FUNC_FLATTEN __attribute__((flatten))
    #endif

    #ifndef FMC_FUNC_FORMAT
        #define FMC_FUNC_FORMAT(func_fmt, fmt_pos, args_pos) __attribute__((format(func_fmt, fmt_pos, args_pos)))
    #endif

    #ifndef FMC_FUNC_HOT
        #define FMC_FUNC_HOT __attribute__((hot))
    #endif

    #ifdef FMC_FUNC_MALLOC
        #undef FMC_FUNC_MALLOC
    #endif
    #define FMC_FUNC_MALLOC(...) FMC_FUNC_WARN_UNUSED_RESULT __attribute__((malloc(__VA_ARGS__)))
    
    #ifdef FMC_FUNC_JUST_MALLOC
        #undef FMC_FUNC_JUST_MALLOC
    #endif
    #define FMC_FUNC_JUST_MALLOC __attribute__((malloc))

    #ifndef FMC_FUNC_NONNULL
        #if !(defined(FMC_COMPILING_ON_WINDOWS) || defined(FMC_COMPILING_ON_MINGW))
            #define FMC_FUNC_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
        #else
            #define FMC_FUNC_NONNULL(...)
        #endif
    #endif

    #ifndef FMC_FUNC_NORETURN
        #define FMC_FUNC_NORETURN __attribute__((noreturn))
    #endif

    #ifndef FMC_FUNC_NOTHROW
        #define FMC_FUNC_NOTHROW __attribute__((nothrow))
    #endif

    #ifndef FMC_FUNC_OPTIMIZE
        #define FMC_FUNC_OPTIMIZE(level) __attribute__((optimize(FMC_STRINGIZE(level))))
    #endif

    #ifndef FMC_FUNC_PURE
        #define FMC_FUNC_PURE __attribute__((pure))
    #endif

    #ifndef FMC_FUNC_RETURNS_NONNULL
        #define FMC_FUNC_RETURNS_NONNULL __attribute__((returns_nonnull))
    #endif

    #ifndef FMC_FUNC_SECTION
        #define FMC_FUNC_SECTION(section_name) __attribute__((section(FMC_STRINGIZE(section_name))))
    #endif

    #ifndef FMC_FUNC_SENTINEL
        #define FMC_FUNC_SENTINEL(pos) __attribute__((sentinel(pos)))
    #endif

    #ifndef FMC_FUNC_STACK_PROTECT
        #define FMC_FUNC_STACK_PROTECT __attribute__((stack_protect))
    #endif

    #ifndef FMC_FUNC_SYMVER
        #define FMC_FUNC_SYMVER(name, ver) __attribute__((symver(FMC_STRINGIZE(name@ver))))
    #endif

    #ifndef FMC_FUNC_UNUSED
        #define FMC_FUNC_UNUSED __attribute__((unused))
    #endif

    #ifndef FMC_FUNC_USED
        #define FMC_FUNC_USED __attribute__((used))
    #endif

    #ifndef FMC_FUNC_VISIBILITY
        #define FMC_FUNC_VISIBILITY(visibility_type) __attribute__((visibility(FMC_STRINGIZE(visibility_type))))
    #endif

    #ifndef FMC_FUNC_WARN_UNUSED_RESULT
        #define FMC_FUNC_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
    #endif

    #ifndef FMC_FUNC_WEAK
        #define FMC_FUNC_WEAK __attribute__((weak))
    #endif

    #ifndef FMC_FUNC_WEAK_REF
        #define FMC_FUNC_WEAK_REF(...) __attribute__((weakref(FMC_STRINGIZE(__VA_ARGS__))))
    #endif

    #ifndef FMC_FUNC_ZERO_REGISTERS
        #define FMC_FUNC_ZERO_REGISTERS(to_zero) __attribute__((zero_call_used_regs(FMC_STRINGIZE(to_zero))))
    #endif



    #ifndef FMC_FUNC_STRONG_ALIAS
        #define FMC_FUNC_STRONG_ALIAS(func_name, aliased) FMC_FUNC_ALIAS(aliased) FMC_FUNC_COPY(aliased) __typeof__(aliased) func_name
    #endif

    #ifndef FMC_FUNC_INLINE
        #define FMC_FUNC_INLINE FMC_FUNC_ALWAYS_INLINE inline
    #endif

    #ifndef FMC_FUNC_PRINTF_FMT
        #define FMC_FUNC_PRINTF_FMT(fmt_pos, args_pos) FMC_FUNC_FORMAT(printf, fmt_pos, args_pos)
    #endif

#endif

#ifndef FMC_VAR_ATTRIBUTES
    #define FMC_VAR_ATTRIBUTES

    #ifndef FMC_VAR_ALIAS
        #define FMC_VAR_ALIAS(aliased) __attribute__((alias(FMC_STRINGIZE(aliased))))
    #endif

    #ifndef FMC_VAR_CLEANUP
        #define FMC_VAR_CLEANUP(func_name) __attribute__((cleanup(func_name)))
    #endif
    
    #ifndef FMC_VAR_COMMON
        #define FMC_VAR_COMMON __attribute__((common))
    #endif

    #ifndef FMC_VAR_NO_COMMON
        #define FMC_VAR_NO_COMMON __attribute__((nocommon))
    #endif

    #ifndef FMC_VAR_COPY
        #define FMC_VAR_COPY(var) __attribute__((copy(var)))
    #endif

    #ifndef FMC_VAR_DEPRECATED
        #define FMC_VAR_DEPRECATED(msg) __attribute__((deprecated(FMC_STRINGIZE(msg))))
    #endif

    #ifndef FMC_VAR_UNAVAILABLE
        #define FMC_VAR_UNAVAILABLE(msg) __attribute__((unavailable(FMC_STRINGIZE(msg))))
    #endif

    #ifndef FMC_VAR_MACH_MODE
        #define FMC_VAR_MACH_MODE(_mode) __attribute__((mode(_mode)))
    #endif

    #ifndef FMC_VAR_NON_STRING
        #define FMC_VAR_NON_STRING __attribute__((nonstring))
    #endif

    #ifndef FMC_VAR_SECTION
        #define FMC_VAR_SECTION(section_name) __attribute__((section(FMC_STRINGIZE(section_name))))
    #endif

    #ifndef FMC_VAR_UNUSED
        #define FMC_VAR_UNUSED __attribute__((unused))
    #endif

    #ifndef FMC_VAR_USED
        #define FMC_VAR_USED __attribute__((used))
    #endif

    #ifndef FMC_VAR_UNINITIALIZED
        #define FMC_VAR_UNINITIALIZED __attribute__((uninitialized))
    #endif

    #ifndef FMC_VAR_VISIBILITY
        #define FMC_VAR_VISIBILITY(visibility_type) __attribute__((visibility(FMC_STRINGIZE(visibility_type))))
    #endif

    #ifndef FMC_VAR_WEAK
        #define FMC_VAR_WEAK __attribute__((weak))
    #endif

#endif

#ifndef FMC_TYPE_ATTRIBUTES
    #define FMC_TYPE_ATTRIBUTES

    #ifndef FMC_TYPE_DEPRECATED
        #define FMC_TYPE_DEPRECATED(msg) __attribute__((deprecated(FMC_STRINGIZE(msg))))
    #endif

    #ifndef FMC_TYPE_UNAVAILABLE
        #define FMC_TYPE_UNAVAILABLE(msg) __attribute__((unavailable(FMC_STRINGIZE(msg))))
    #endif

    #ifndef FMC_TYPE_MACH_MODE
        #define FMC_TYPE_MACH_MODE(_mode) __attribute__((mode(_mode)))
    #endif

    #ifndef FMC_TYPE_UNUSED
        #define FMC_TYPE_UNUSED __attribute__((unused))
    #endif

    #ifndef FMC_TYPE_VEC_SIZE
        #define FMC_TYPE_VEC_SIZE(size) __attribute__((vector_size(size)))
    #endif

    #ifndef FMC_TYPE_VISIBILITY
        #define FMC_TYPE_VISIBILITY(visibility_type) __attribute__((visibility(FMC_STRINGIZE(visibility_type))))
    #endif

#endif

#ifndef FMC_LABEL_ATTRIBUTES
    #define FMC_LABEL_ATTRIBUTES
    
    #ifndef FMC_LABEL_UNUSED
        #define FMC_LABEL_UNUSED __attribute__((unused))
    #endif

    #ifndef FMC_LABEL_HOT
        #define FMC_LABEL_HOT __attribute__((hot))
    #endif

    #ifndef FMC_LABEL_COLD
        #define FMC_LABEL_COLD __attribute__((cold))
    #endif

#endif

#ifndef FMC_ENUM_ATTRIBUTES
    #define FMC_ENUM_ATTRIBUTES

    #ifndef FMC_ENUM_DEPRECATED
        #define FMC_ENUM_DEPRECATED(msg) __attribute__((deprecated(FMC_STRINGIZE(msg))))
    #endif

    #ifndef FMC_ENUM_UNAVAILABLE
        #define FMC_ENUM_UNAVAILABLE(msg) __attribute__((unavailable(FMC_STRINGIZE(msg))))
    #endif

#endif

#ifndef FMC_STMT_ATTRIBUTES
    #define FMC_STMT_ATTRIBUTES

    #ifndef FMC_STMT_FALLTHROUGH
        #define FMC_STMT_FALLTHROUGH __attribute__((fallthrough))
    #endif

    #ifdef FMC_STMT_ASSUME
        #undef FMC_STMT_ASSUME
    #endif
    #define FMC_STMT_ASSUME(cond) // __attribute__((assume(cond))) (apparently not supported by GCC yet)

#endif

#endif
