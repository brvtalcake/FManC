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
    #endif // FMC_FUNC_ACCESS

    #ifndef FMC_FUNC_ALIAS
        #define FMC_FUNC_ALIAS(aliased) __attribute__((alias(FMC_STRINGIZE(aliased)))) 
    #endif // FMC_FUNC_ALIAS

    #ifdef FMC_FUNC_ALLOC_SIZE
        #undef FMC_FUNC_ALLOC_SIZE
    #endif // FMC_FUNC_ALLOC_SIZE
    #define FMC_FUNC_ALLOC_SIZE(_p1, ...) __attribute__((alloc_size(_p1, __VA_ARGS__)))

    #ifndef FMC_FUNC_ALWAYS_INLINE
        #define FMC_FUNC_ALWAYS_INLINE __attribute__((always_inline))
    #endif // FMC_FUNC_ALWAYS_INLINE

    #ifndef FMC_FUNC_COLD
        #define FMC_FUNC_COLD __attribute__((cold))
    #endif // FMC_FUNC_COLD

    #ifndef FMC_FUNC_CONST
        #define FMC_FUNC_CONST __attribute__((const))
    #endif // FMC_FUNC_CONST

    #ifndef FMC_FUNC_CONSTRUCTOR
        #define FMC_FUNC_CONSTRUCTOR(priority) __attribute__((constructor(priority)))
    #endif // FMC_FUNC_CONSTRUCTOR

    #ifndef FMC_FUNC_DESTRUCTOR
        #define FMC_FUNC_DESTRUCTOR(priority) __attribute__((destructor(priority)))
    #endif // FMC_FUNC_DESTRUCTOR

    #ifndef FMC_FUNC_COPY
        #define FMC_FUNC_COPY(func) __attribute__((copy(func)))
    #endif // FMC_FUNC_COPY

    #ifndef FMC_FUNC_DEPRECATED
        #define FMC_FUNC_DEPRECATED(msg) __attribute__((deprecated(FMC_STRINGIZE(msg))))
    #endif // FMC_FUNC_DEPRECATED

    #ifndef FMC_FUNC_UNAVAILABLE
        #define FMC_FUNC_UNAVAILABLE(msg) __attribute__((unavailable(FMC_STRINGIZE(msg))))
    #endif // FMC_FUNC_UNAVAILABLE

    #ifndef FMC_FUNC_ERROR
        #define FMC_FUNC_ERROR(msg) __attribute__((error(FMC_STRINGIZE(msg))))
    #endif // FMC_FUNC_ERROR

    #ifndef FMC_FUNC_WARNING
        #define FMC_FUNC_WARNING(msg) __attribute__((warning(FMC_STRINGIZE(msg))))
    #endif // FMC_FUNC_WARNING

    #ifndef FMC_FUNC_EXTERNALLY_VISIBLE
        #define FMC_FUNC_EXTERNALLY_VISIBLE __attribute__((externally_visible))
    #endif // FMC_FUNC_EXTERNALLY_VISIBLE

    #ifndef FMC_FUNC_FLATTEN
        #define FMC_FUNC_FLATTEN __attribute__((flatten))
    #endif // FMC_FUNC_FLATTEN

    #ifndef FMC_FUNC_FORMAT
        #define FMC_FUNC_FORMAT(func_fmt, fmt_pos, args_pos) __attribute__((format(func_fmt, fmt_pos, args_pos)))
    #endif // FMC_FUNC_FORMAT

    #ifndef FMC_FUNC_HOT
        #define FMC_FUNC_HOT __attribute__((hot))
    #endif // FMC_FUNC_HOT

    #ifndef FMC_FUNC_MALLOC
        #define FMC_FUNC_MALLOC(...) FMC_FUNC_WARN_UNUSED_RESULT __attribute__((malloc(__VA_ARGS__)))
    #endif // FMC_FUNC_MALLOC

    #ifndef FMC_FUNC_NONNULL
        #if !(defined(FMC_COMPILING_ON_WINDOWS) || defined(FMC_COMPILING_ON_MINGW))
            #define FMC_FUNC_NONNULL(...) __attribute__((nonnull(__VA_ARGS__)))
        #else
            #define FMC_FUNC_NONNULL(...)
        #endif
    #endif // FMC_FUNC_NONNULL

    #ifndef FMC_FUNC_NORETURN
        #define FMC_FUNC_NORETURN __attribute__((noreturn))
    #endif // FMC_FUNC_NORETURN

    #ifndef FMC_FUNC_OPTIMIZE
        #define FMC_FUNC_OPTIMIZE(level) __attribute__((optimize(FMC_STRINGIZE(level))))
    #endif // FMC_FUNC_OPTIMIZE

    #ifndef FMC_FUNC_PURE
        #define FMC_FUNC_PURE __attribute__((pure))
    #endif // FMC_FUNC_PURE

    #ifndef FMC_FUNC_RETURNS_NONNULL
        #define FMC_FUNC_RETURNS_NONNULL __attribute__((returns_nonnull))
    #endif // FMC_FUNC_RETURNS_NONNULL

    #ifndef FMC_FUNC_SECTION
        #define FMC_FUNC_SECTION(section_name) __attribute__((section(FMC_STRINGIZE(section_name))))
    #endif // FMC_FUNC_SECTION

    #ifndef FMC_FUNC_SENTINEL
        #define FMC_FUNC_SENTINEL(pos) __attribute__((sentinel(pos)))
    #endif // FMC_FUNC_SENTINEL

    #ifndef FMC_FUNC_STACK_PROTECT
        #define FMC_FUNC_STACK_PROTECT __attribute__((stack_protect))
    #endif // FMC_FUNC_STACK_PROTECT

    #ifndef FMC_FUNC_SYMVER
        #define FMC_FUNC_SYMVER(name, major, minor, patch) __attribute__((symver(FMC_STRINGIZE(name@FMC_CONCAT_4(v,major,minor,patch)))))
    #endif // FMC_FUNC_SYMVER

    #ifndef FMC_FUNC_UNUSED
        #define FMC_FUNC_UNUSED __attribute__((unused))
    #endif // FMC_FUNC_UNUSED

    #ifndef FMC_FUNC_USED
        #define FMC_FUNC_USED __attribute__((used))
    #endif // FMC_FUNC_USED

    #ifndef FMC_FUNC_VISIBILITY
        #define FMC_FUNC_VISIBILITY(visibility_type) __attribute__((visibility(FMC_STRINGIZE(visibility_type))))
    #endif // FMC_FUNC_VISIBILITY

    #ifndef FMC_FUNC_WARN_UNUSED_RESULT
        #define FMC_FUNC_WARN_UNUSED_RESULT __attribute__((warn_unused_result))
    #endif // FMC_FUNC_WARN_UNUSED_RESULT

    #ifndef FMC_FUNC_WEAK
        #define FMC_FUNC_WEAK __attribute__((weak))
    #endif // FMC_FUNC_WEAK

    #ifndef FMC_FUNC_WEAK_REF
        #define FMC_FUNC_WEAK_REF(...) __attribute__((weakref(FMC_STRINGIZE(__VA_ARGS__))))
    #endif // FMC_FUNC_WEAK_REF

    #ifndef FMC_FUNC_ZERO_REGISTERS
        #define FMC_FUNC_ZERO_REGISTERS(to_zero) __attribute__((zero_call_used_regs(FMC_STRINGIZE(to_zero))))
    #endif // FMC_FUNC_ZERO_REGISTERS



    #ifndef FMC_FUNC_STRONG_ALIAS
        #define FMC_FUNC_STRONG_ALIAS(func_name, aliased) FMC_FUNC_ALIAS(aliased) FMC_FUNC_COPY(aliased) __typeof__(aliased) func_name
    #endif // FMC_FUNC_STRONG_ALIAS

    #ifndef FMC_FUNC_INLINE
        #define FMC_FUNC_INLINE FMC_FUNC_ALWAYS_INLINE inline
    #endif // FMC_FUNC_INLINE

    #ifndef FMC_FUNC_PRINTF_FMT
        #define FMC_FUNC_PRINTF_FMT(fmt_pos, args_pos) FMC_FUNC_FORMAT(printf, fmt_pos, args_pos)
    #endif // FMC_FUNC_PRINTF_FMT

#endif //FMC_FUNC_ATTRIBUTES

#ifndef FMC_VAR_ATTRIBUTES
    #define FMC_VAR_ATTRIBUTES

    #ifndef FMC_VAR_ALIAS
        #define FMC_VAR_ALIAS(aliased) __attribute__((alias(FMC_STRINGIZE(aliased))))
    #endif // FMC_VAR_ALIAS

    #ifndef FMC_VAR_CLEANUP
        #define FMC_VAR_CLEANUP(func_name) __attribute__((cleanup(func_name)))
    #endif // FMC_VAR_CLEANUP
    
    #ifndef FMC_VAR_COMMON
        #define FMC_VAR_COMMON __attribute__((common))
    #endif // FMC_VAR_COMMON

    #ifndef FMC_VAR_NO_COMMON
        #define FMC_VAR_NO_COMMON __attribute__((nocommon))
    #endif // FMC_VAR_NO_COMMON

    #ifndef FMC_VAR_COPY
        #define FMC_VAR_COPY(var) __attribute__((copy(var)))
    #endif // FMC_VAR_COPY

    #ifndef FMC_VAR_DEPRECATED
        #define FMC_VAR_DEPRECATED(msg) __attribute__((deprecated(FMC_STRINGIZE(msg))))
    #endif // FMC_VAR_DEPRECATED

    #ifndef FMC_VAR_UNAVAILABLE
        #define FMC_VAR_UNAVAILABLE(msg) __attribute__((unavailable(FMC_STRINGIZE(msg))))
    #endif // FMC_VAR_UNAVAILABLE

    #ifndef FMC_VAR_MACH_MODE
        #define FMC_VAR_MACH_MODE(_mode) __attribute__((mode(_mode)))
    #endif // FMC_VAR_MACH_MODE

    #ifndef FMC_VAR_NON_STRING
        #define FMC_VAR_NON_STRING __attribute__((nonstring))
    #endif // FMC_VAR_NON_STRING

    #ifndef FMC_VAR_SECTION
        #define FMC_VAR_SECTION(section_name) __attribute__((section(FMC_STRINGIZE(section_name))))
    #endif // FMC_VAR_SECTION

    #ifndef FMC_VAR_UNUSED
        #define FMC_VAR_UNUSED __attribute__((unused))
    #endif // FMC_VAR_UNUSED

    #ifndef FMC_VAR_USED
        #define FMC_VAR_USED __attribute__((used))
    #endif // FMC_VAR_USED

    #ifndef FMC_VAR_UNINITIALIZED
        #define FMC_VAR_UNINITIALIZED __attribute__((uninitialized))
    #endif // FMC_VAR_UNINITIALIZED

    #ifndef FMC_VAR_VISIBILITY
        #define FMC_VAR_VISIBILITY(visibility_type) __attribute__((visibility(FMC_STRINGIZE(visibility_type))))
    #endif // FMC_VAR_VISIBILITY

    #ifndef FMC_VAR_WEAK
        #define FMC_VAR_WEAK __attribute__((weak))
    #endif // FMC_VAR_WEAK

#endif // FMC_VAR_ATTRIBUTES

#ifndef FMC_TYPE_ATTRIBUTES
    #define FMC_TYPE_ATTRIBUTES

    #ifndef FMC_TYPE_DEPRECATED
        #define FMC_TYPE_DEPRECATED(msg) __attribute__((deprecated(FMC_STRINGIZE(msg))))
    #endif // FMC_TYPE_DEPRECATED

    #ifndef FMC_TYPE_UNAVAILABLE
        #define FMC_TYPE_UNAVAILABLE(msg) __attribute__((unavailable(FMC_STRINGIZE(msg))))
    #endif // FMC_TYPE_UNAVAILABLE

    #ifndef FMC_TYPE_MACH_MODE
        #define FMC_TYPE_MACH_MODE(_mode) __attribute__((mode(_mode)))
    #endif // FMC_TYPE_MACH_MODE

    #ifndef FMC_TYPE_UNUSED
        #define FMC_TYPE_UNUSED __attribute__((unused))
    #endif // FMC_TYPE_UNUSED

    #ifndef FMC_TYPE_VEC_SIZE
        #define FMC_TYPE_VEC_SIZE(size) __attribute__((vector_size(size)))
    #endif // FMC_TYPE_VEC_SIZE

    #ifndef FMC_TYPE_VISIBILITY
        #define FMC_TYPE_VISIBILITY(visibility_type) __attribute__((visibility(FMC_STRINGIZE(visibility_type))))
    #endif // FMC_TYPE_VISIBILITY

#endif // FMC_TYPE_ATTRIBUTES

#ifndef FMC_LABEL_ATTRIBUTES
    #define FMC_LABEL_ATTRIBUTES
    
    #ifndef FMC_LABEL_UNUSED
        #define FMC_LABEL_UNUSED __attribute__((unused))
    #endif // FMC_LABEL_UNUSED

    #ifndef FMC_LABEL_HOT
        #define FMC_LABEL_HOT __attribute__((hot))
    #endif // FMC_LABEL_HOT

    #ifndef FMC_LABEL_COLD
        #define FMC_LABEL_COLD __attribute__((cold))
    #endif // FMC_LABEL_COLD

#endif // FMC_LABEL_ATTRIBUTES

#ifndef FMC_ENUM_ATTRIBUTES
    #define FMC_ENUM_ATTRIBUTES

    #ifndef FMC_ENUM_DEPRECATED
        #define FMC_ENUM_DEPRECATED(msg) __attribute__((deprecated(FMC_STRINGIZE(msg))))
    #endif // FMC_ENUM_DEPRECATED

    #ifndef FMC_ENUM_UNAVAILABLE
        #define FMC_ENUM_UNAVAILABLE(msg) __attribute__((unavailable(FMC_STRINGIZE(msg))))
    #endif // FMC_ENUM_UNAVAILABLE

#endif // FMC_ENUM_ATTRIBUTES

#ifndef FMC_STMT_ATTRIBUTES
    #define FMC_STMT_ATTRIBUTES

    #ifndef FMC_STMT_FALLTHROUGH
        #define FMC_STMT_FALLTHROUGH __attribute__((fallthrough))
    #endif // FM_STMT_FALLTHROUGH

#endif // FMC_STMT_ATTRIBUTES

#endif // FMC_ATTRIBUTES_H
