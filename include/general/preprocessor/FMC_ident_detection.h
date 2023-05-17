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

#ifndef FMC_IDENT_DETECTION_H
#define FMC_IDENT_DETECTION_H

    #if defined(FMC_DETECTOR_ptr)
        #undef FMC_DETECTOR_ptr
    #endif
    #if defined(FMC_IDENT_EQ_ptr_ptr)
        #undef FMC_IDENT_EQ_ptr_ptr
    #endif
    #define FMC_IDENT_EQ_ptr_ptr ()
    #define FMC_DETECTOR_ptr ()

    #if defined(FMC_DETECTOR_void)
        #undef FMC_DETECTOR_void
    #endif
    #if defined(FMC_IDENT_EQ_void_void)
        #undef FMC_IDENT_EQ_void_void
    #endif
    #define FMC_IDENT_EQ_void_void ()
    #define FMC_DETECTOR_void ()

    #if defined(FMC_DETECTOR_char) || defined(FMC_DETECTOR_unsigned_char) || defined(FMC_DETECTOR_signed_char)
        #undef FMC_DETECTOR_char
        #undef FMC_DETECTOR_unsigned_char
        #undef FMC_DETECTOR_signed_char
    #endif
    #if defined(FMC_IDENT_EQ_char_char) || defined(FMC_IDENT_EQ_unsigned_char_unsigned_char) || defined(FMC_IDENT_EQ_signed_char_signed_char)
        #undef FMC_IDENT_EQ_char_char
        #undef FMC_IDENT_EQ_unsigned_char_unsigned_char
        #undef FMC_IDENT_EQ_signed_char_signed_char
    #endif
    #define FMC_IDENT_EQ_char_char ()
    #define FMC_IDENT_EQ_unsigned_char_unsigned_char ()
    #define FMC_IDENT_EQ_signed_char_signed_char () 
    #define FMC_DETECTOR_char ()
    #define FMC_DETECTOR_unsigned_char ()
    #define FMC_DETECTOR_signed_char ()

    #if defined(FMC_DETECTOR_short) || defined(FMC_DETECTOR_unsigned_short) || defined(FMC_DETECTOR_signed_short) || defined(FMC_DETECTOR_short_int) || defined(FMC_DETECTOR_unsigned_short_int) || defined(FMC_DETECTOR_signed_short_int)
        #undef FMC_DETECTOR_short
        #undef FMC_DETECTOR_unsigned_short
        #undef FMC_DETECTOR_signed_short
        #undef FMC_DETECTOR_short_int
        #undef FMC_DETECTOR_unsigned_short_int
        #undef FMC_DETECTOR_signed_short_int
    #endif
    #if defined(FMC_IDENT_EQ_short_short) || defined(FMC_IDENT_EQ_unsigned_short_unsigned_short) || defined(FMC_IDENT_EQ_signed_short_signed_short) || defined(FMC_IDENT_EQ_short_int_short_int) || defined(FMC_IDENT_EQ_unsigned_short_int_unsigned_short_int) || defined(FMC_IDENT_EQ_signed_short_int_signed_short_int)
        #undef FMC_IDENT_EQ_short_short
        #undef FMC_IDENT_EQ_unsigned_short_unsigned_short
        #undef FMC_IDENT_EQ_signed_short_signed_short
        #undef FMC_IDENT_EQ_short_int_short_int
        #undef FMC_IDENT_EQ_unsigned_short_int_unsigned_short_int
        #undef FMC_IDENT_EQ_signed_short_int_signed_short_int
    #endif
    #define FMC_IDENT_EQ_short_short ()
    #define FMC_IDENT_EQ_unsigned_short_unsigned_short ()
    #define FMC_IDENT_EQ_signed_short_signed_short ()
    #define FMC_IDENT_EQ_short_int_short_int ()
    #define FMC_IDENT_EQ_unsigned_short_int_unsigned_short_int ()
    #define FMC_IDENT_EQ_signed_short_int_signed_short_int ()
    #define FMC_DETECTOR_short ()
    #define FMC_DETECTOR_unsigned_short ()
    #define FMC_DETECTOR_signed_short ()
    #define FMC_DETECTOR_short_int ()
    #define FMC_DETECTOR_unsigned_short_int ()
    #define FMC_DETECTOR_signed_short_int ()

    #if defined(FMC_DETECTOR_int) || defined(FMC_DETECTOR_unsigned) || defined(FMC_DETECTOR_signed) || defined(FMC_DETECTOR_unsigned_int) || defined(FMC_DETECTOR_signed_int)
        #undef FMC_DETECTOR_int
        #undef FMC_DETECTOR_unsigned
        #undef FMC_DETECTOR_signed
        #undef FMC_DETECTOR_unsigned_int
        #undef FMC_DETECTOR_signed_int
    #endif
    #if defined(FMC_IDENT_EQ_int_int) || defined(FMC_IDENT_EQ_unsigned_unsigned) || defined(FMC_IDENT_EQ_signed_signed) || defined(FMC_IDENT_EQ_unsigned_int_unsigned_int) || defined(FMC_IDENT_EQ_signed_int_signed_int)
        #undef FMC_IDENT_EQ_int_int
        #undef FMC_IDENT_EQ_unsigned_unsigned
        #undef FMC_IDENT_EQ_signed_signed
        #undef FMC_IDENT_EQ_unsigned_int_unsigned_int
        #undef FMC_IDENT_EQ_signed_int_signed_int
    #endif
    #define FMC_IDENT_EQ_int_int ()
    #define FMC_IDENT_EQ_unsigned_unsigned ()
    #define FMC_IDENT_EQ_signed_signed ()
    #define FMC_IDENT_EQ_unsigned_int_unsigned_int ()
    #define FMC_IDENT_EQ_signed_int_signed_int ()
    #define FMC_DETECTOR_int ()
    #define FMC_DETECTOR_unsigned ()
    #define FMC_DETECTOR_signed ()
    #define FMC_DETECTOR_unsigned_int ()
    #define FMC_DETECTOR_signed_int ()

    #if defined(FMC_DETECTOR_long) || defined(FMC_DETECTOR_unsigned_long) || defined(FMC_DETECTOR_signed_long) || defined(FMC_DETECTOR_long_int) || defined(FMC_DETECTOR_unsigned_long_int) || defined(FMC_DETECTOR_signed_long_int)
        #undef FMC_DETECTOR_long
        #undef FMC_DETECTOR_unsigned_long
        #undef FMC_DETECTOR_signed_long
        #undef FMC_DETECTOR_long_int
        #undef FMC_DETECTOR_unsigned_long_int
        #undef FMC_DETECTOR_signed_long_int
    #endif
    #if defined(FMC_IDENT_EQ_long_long) || defined(FMC_IDENT_EQ_unsigned_long_unsigned_long) || defined(FMC_IDENT_EQ_signed_long_signed_long) || defined(FMC_IDENT_EQ_long_int_long_int) || defined(FMC_IDENT_EQ_unsigned_long_int_unsigned_long_int) || defined(FMC_IDENT_EQ_signed_long_int_signed_long_int)
        #undef FMC_IDENT_EQ_long_long
        #undef FMC_IDENT_EQ_unsigned_long_unsigned_long
        #undef FMC_IDENT_EQ_signed_long_signed_long
        #undef FMC_IDENT_EQ_long_int_long_int
        #undef FMC_IDENT_EQ_unsigned_long_int_unsigned_long_int
        #undef FMC_IDENT_EQ_signed_long_int_signed_long_int
    #endif
    #define FMC_IDENT_EQ_long_long ()
    #define FMC_IDENT_EQ_unsigned_long_unsigned_long ()
    #define FMC_IDENT_EQ_signed_long_signed_long ()
    #define FMC_IDENT_EQ_long_int_long_int ()
    #define FMC_IDENT_EQ_unsigned_long_int_unsigned_long_int ()
    #define FMC_IDENT_EQ_signed_long_int_signed_long_int ()
    #define FMC_DETECTOR_long ()
    #define FMC_DETECTOR_unsigned_long ()
    #define FMC_DETECTOR_signed_long ()
    #define FMC_DETECTOR_long_int ()
    #define FMC_DETECTOR_unsigned_long_int ()
    #define FMC_DETECTOR_signed_long_int ()

    #if defined(FMC_DETECTOR_long_long) || defined(FMC_DETECTOR_unsigned_long_long) || defined(FMC_DETECTOR_signed_long_long) || defined(FMC_DETECTOR_long_long_int) || defined(FMC_DETECTOR_unsigned_long_long_int) || defined(FMC_DETECTOR_signed_long_long_int)
        #undef FMC_DETECTOR_long_long
        #undef FMC_DETECTOR_unsigned_long_long
        #undef FMC_DETECTOR_signed_long_long
        #undef FMC_DETECTOR_long_long_int
        #undef FMC_DETECTOR_unsigned_long_long_int
        #undef FMC_DETECTOR_signed_long_long_int
    #endif
    #if defined(FMC_IDENT_EQ_long_long_long_long) || defined(FMC_IDENT_EQ_unsigned_long_long_unsigned_long_long) || defined(FMC_IDENT_EQ_signed_long_long_signed_long_long) || defined(FMC_IDENT_EQ_long_long_int_long_long_int) || defined(FMC_IDENT_EQ_unsigned_long_long_int_unsigned_long_long_int) || defined(FMC_IDENT_EQ_signed_long_long_int_signed_long_long_int)
        #undef FMC_IDENT_EQ_long_long_long_long
        #undef FMC_IDENT_EQ_unsigned_long_long_unsigned_long_long
        #undef FMC_IDENT_EQ_signed_long_long_signed_long_long
        #undef FMC_IDENT_EQ_long_long_int_long_long_int
        #undef FMC_IDENT_EQ_unsigned_long_long_int_unsigned_long_long_int
        #undef FMC_IDENT_EQ_signed_long_long_int_signed_long_long_int
    #endif
    #define FMC_IDENT_EQ_long_long_long_long ()
    #define FMC_IDENT_EQ_unsigned_long_long_unsigned_long_long ()
    #define FMC_IDENT_EQ_signed_long_long_signed_long_long ()
    #define FMC_IDENT_EQ_long_long_int_long_long_int ()
    #define FMC_IDENT_EQ_unsigned_long_long_int_unsigned_long_long_int ()
    #define FMC_IDENT_EQ_signed_long_long_int_signed_long_long_int ()
    #define FMC_DETECTOR_long_long ()
    #define FMC_DETECTOR_unsigned_long_long ()
    #define FMC_DETECTOR_signed_long_long ()
    #define FMC_DETECTOR_long_long_int ()
    #define FMC_DETECTOR_unsigned_long_long_int ()
    #define FMC_DETECTOR_signed_long_long_int ()

    #if defined(FMC_DETECTOR_float)
        #undef FMC_DETECTOR_float
    #endif
    #if defined(FMC_IDENT_EQ_float_float)
        #undef FMC_IDENT_EQ_float_float
    #endif
    #define FMC_IDENT_EQ_float_float ()
    #define FMC_DETECTOR_float ()

    #if defined(FMC_DETECTOR_double)
        #undef FMC_DETECTOR_double
    #endif
    #if defined(FMC_IDENT_EQ_double_double)
        #undef FMC_IDENT_EQ_double_double
    #endif
    #define FMC_IDENT_EQ_double_double ()
    #define FMC_DETECTOR_double ()

    #if defined(FMC_DETECTOR_long_double)
        #undef FMC_DETECTOR_long_double
    #endif
    #if defined(FMC_IDENT_EQ_long_double_long_double)
        #undef FMC_IDENT_EQ_long_double_long_double
    #endif
    #define FMC_IDENT_EQ_long_double_long_double ()
    #define FMC_DETECTOR_long_double ()

    #if defined(FMC_DETECTOR_bool)
        #undef FMC_DETECTOR_bool
    #endif
    #if defined(FMC_IDENT_EQ_bool_bool)
        #undef FMC_IDENT_EQ_bool_bool
    #endif
    #define FMC_IDENT_EQ_bool_bool ()
    #define FMC_DETECTOR_bool ()

    #if defined(FMC_DETECTOR_wchar_t)
        #undef FMC_DETECTOR_wchar_t
    #endif
    #if defined(FMC_IDENT_EQ_wchar_t_wchar_t)
        #undef FMC_IDENT_EQ_wchar_t_wchar_t
    #endif
    #define FMC_IDENT_EQ_wchar_t_wchar_t ()
    #define FMC_DETECTOR_wchar_t ()

    #if defined(FMC_DETECTOR_char8_t)
        #undef FMC_DETECTOR_char8_t
    #endif
    #if defined(FMC_IDENT_EQ_char8_t_char8_t)
        #undef FMC_IDENT_EQ_char8_t_char8_t
    #endif
    #define FMC_IDENT_EQ_char8_t_char8_t ()
    #define FMC_DETECTOR_char8_t ()

    #if defined(FMC_DETECTOR_char16_t)
        #undef FMC_DETECTOR_char16_t
    #endif
    #if defined(FMC_IDENT_EQ_char16_t_char16_t)
        #undef FMC_IDENT_EQ_char16_t_char16_t
    #endif
    #define FMC_IDENT_EQ_char16_t_char16_t ()
    #define FMC_DETECTOR_char16_t ()

    #if defined(FMC_DETECTOR_char32_t)
        #undef FMC_DETECTOR_char32_t
    #endif
    #if defined(FMC_IDENT_EQ_char32_t_char32_t)
        #undef FMC_IDENT_EQ_char32_t_char32_t
    #endif
    #define FMC_IDENT_EQ_char32_t_char32_t ()
    #define FMC_DETECTOR_char32_t ()

    #if defined(FMC_DETECTOR_int8_t) || defined(FMC_DETECTOR_uint8_t)
        #undef FMC_DETECTOR_int8_t
        #undef FMC_DETECTOR_uint8_t
    #endif
    #if defined(FMC_IDENT_EQ_int8_t_int8_t) || defined(FMC_IDENT_EQ_uint8_t_uint8_t)
        #undef FMC_IDENT_EQ_int8_t_int8_t
        #undef FMC_IDENT_EQ_uint8_t_uint8_t
    #endif
    #define FMC_IDENT_EQ_int8_t_int8_t ()
    #define FMC_IDENT_EQ_uint8_t_uint8_t ()
    #define FMC_DETECTOR_int8_t ()
    #define FMC_DETECTOR_uint8_t ()

    #if defined(FMC_DETECTOR_int16_t) || defined(FMC_DETECTOR_uint16_t)
        #undef FMC_DETECTOR_int16_t
        #undef FMC_DETECTOR_uint16_t
    #endif
    #if defined(FMC_IDENT_EQ_int16_t_int16_t) || defined(FMC_IDENT_EQ_uint16_t_uint16_t)
        #undef FMC_IDENT_EQ_int16_t_int16_t
        #undef FMC_IDENT_EQ_uint16_t_uint16_t
    #endif
    #define FMC_IDENT_EQ_int16_t_int16_t ()
    #define FMC_IDENT_EQ_uint16_t_uint16_t ()
    #define FMC_DETECTOR_int16_t ()
    #define FMC_DETECTOR_uint16_t ()

    #if defined(FMC_DETECTOR_int32_t) || defined(FMC_DETECTOR_uint32_t)
        #undef FMC_DETECTOR_int32_t
        #undef FMC_DETECTOR_uint32_t
    #endif
    #if defined(FMC_IDENT_EQ_int32_t_int32_t) || defined(FMC_IDENT_EQ_uint32_t_uint32_t)
        #undef FMC_IDENT_EQ_int32_t_int32_t
        #undef FMC_IDENT_EQ_uint32_t_uint32_t
    #endif
    #define FMC_IDENT_EQ_int32_t_int32_t ()
    #define FMC_IDENT_EQ_uint32_t_uint32_t ()
    #define FMC_DETECTOR_int32_t ()
    #define FMC_DETECTOR_uint32_t ()

    #if defined(FMC_DETECTOR_int64_t) || defined(FMC_DETECTOR_uint64_t)
        #undef FMC_DETECTOR_int64_t
        #undef FMC_DETECTOR_uint64_t
    #endif
    #if defined(FMC_IDENT_EQ_int64_t_int64_t) || defined(FMC_IDENT_EQ_uint64_t_uint64_t)
        #undef FMC_IDENT_EQ_int64_t_int64_t
        #undef FMC_IDENT_EQ_uint64_t_uint64_t
    #endif
    #define FMC_IDENT_EQ_int64_t_int64_t ()
    #define FMC_IDENT_EQ_uint64_t_uint64_t ()
    #define FMC_DETECTOR_int64_t ()
    #define FMC_DETECTOR_uint64_t ()

    #if defined(FMC_DETECTOR_int_least8_t) || defined(FMC_DETECTOR_uint_least8_t)
        #undef FMC_DETECTOR_int_least8_t
        #undef FMC_DETECTOR_uint_least8_t
    #endif
    #if defined(FMC_IDENT_EQ_int_least8_t_int_least8_t) || defined(FMC_IDENT_EQ_uint_least8_t_uint_least8_t)
        #undef FMC_IDENT_EQ_int_least8_t_int_least8_t
        #undef FMC_IDENT_EQ_uint_least8_t_uint_least8_t
    #endif
    #define FMC_IDENT_EQ_int_least8_t_int_least8_t ()
    #define FMC_IDENT_EQ_uint_least8_t_uint_least8_t ()
    #define FMC_DETECTOR_int_least8_t ()
    #define FMC_DETECTOR_uint_least8_t ()

    #if defined(FMC_DETECTOR_int_least16_t) || defined(FMC_DETECTOR_uint_least16_t)
        #undef FMC_DETECTOR_int_least16_t
        #undef FMC_DETECTOR_uint_least16_t
    #endif
    #if defined(FMC_IDENT_EQ_int_least16_t_int_least16_t) || defined(FMC_IDENT_EQ_uint_least16_t_uint_least16_t)
        #undef FMC_IDENT_EQ_int_least16_t_int_least16_t
        #undef FMC_IDENT_EQ_uint_least16_t_uint_least16_t
    #endif
    #define FMC_IDENT_EQ_int_least16_t_int_least16_t ()
    #define FMC_IDENT_EQ_uint_least16_t_uint_least16_t ()
    #define FMC_DETECTOR_int_least16_t ()
    #define FMC_DETECTOR_uint_least16_t ()

    #if defined(FMC_DETECTOR_int_least32_t) || defined(FMC_DETECTOR_uint_least32_t)
        #undef FMC_DETECTOR_int_least32_t
        #undef FMC_DETECTOR_uint_least32_t
    #endif
    #if defined(FMC_IDENT_EQ_int_least32_t_int_least32_t) || defined(FMC_IDENT_EQ_uint_least32_t_uint_least32_t)
        #undef FMC_IDENT_EQ_int_least32_t_int_least32_t
        #undef FMC_IDENT_EQ_uint_least32_t_uint_least32_t
    #endif
    #define FMC_IDENT_EQ_int_least32_t_int_least32_t ()
    #define FMC_IDENT_EQ_uint_least32_t_uint_least32_t ()
    #define FMC_DETECTOR_int_least32_t ()
    #define FMC_DETECTOR_uint_least32_t ()

    #if defined(FMC_DETECTOR_int_least64_t) || defined(FMC_DETECTOR_uint_least64_t)
        #undef FMC_DETECTOR_int_least64_t
        #undef FMC_DETECTOR_uint_least64_t
    #endif
    #if defined(FMC_IDENT_EQ_int_least64_t_int_least64_t) || defined(FMC_IDENT_EQ_uint_least64_t_uint_least64_t)
        #undef FMC_IDENT_EQ_int_least64_t_int_least64_t
        #undef FMC_IDENT_EQ_uint_least64_t_uint_least64_t
    #endif
    #define FMC_IDENT_EQ_int_least64_t_int_least64_t ()
    #define FMC_IDENT_EQ_uint_least64_t_uint_least64_t ()
    #define FMC_DETECTOR_int_least64_t ()
    #define FMC_DETECTOR_uint_least64_t ()

    #if defined(FMC_DETECTOR_int_fast8_t) || defined(FMC_DETECTOR_uint_fast8_t)
        #undef FMC_DETECTOR_int_fast8_t
        #undef FMC_DETECTOR_uint_fast8_t
    #endif
    #if defined(FMC_IDENT_EQ_int_fast8_t_int_fast8_t) || defined(FMC_IDENT_EQ_uint_fast8_t_uint_fast8_t)
        #undef FMC_IDENT_EQ_int_fast8_t_int_fast8_t
        #undef FMC_IDENT_EQ_uint_fast8_t_uint_fast8_t
    #endif
    #define FMC_IDENT_EQ_int_fast8_t_int_fast8_t ()
    #define FMC_IDENT_EQ_uint_fast8_t_uint_fast8_t ()
    #define FMC_DETECTOR_int_fast8_t ()
    #define FMC_DETECTOR_uint_fast8_t ()

    #if defined(FMC_DETECTOR_int_fast16_t) || defined(FMC_DETECTOR_uint_fast16_t)
        #undef FMC_DETECTOR_int_fast16_t
        #undef FMC_DETECTOR_uint_fast16_t
    #endif
    #if defined(FMC_IDENT_EQ_int_fast16_t_int_fast16_t) || defined(FMC_IDENT_EQ_uint_fast16_t_uint_fast16_t)
        #undef FMC_IDENT_EQ_int_fast16_t_int_fast16_t
        #undef FMC_IDENT_EQ_uint_fast16_t_uint_fast16_t
    #endif
    #define FMC_IDENT_EQ_int_fast16_t_int_fast16_t ()
    #define FMC_IDENT_EQ_uint_fast16_t_uint_fast16_t ()
    #define FMC_DETECTOR_int_fast16_t ()
    #define FMC_DETECTOR_uint_fast16_t ()

    #if defined(FMC_DETECTOR_int_fast32_t) || defined(FMC_DETECTOR_uint_fast32_t)
        #undef FMC_DETECTOR_int_fast32_t
        #undef FMC_DETECTOR_uint_fast32_t
    #endif
    #if defined(FMC_IDENT_EQ_int_fast32_t_int_fast32_t) || defined(FMC_IDENT_EQ_uint_fast32_t_uint_fast32_t)
        #undef FMC_IDENT_EQ_int_fast32_t_int_fast32_t
        #undef FMC_IDENT_EQ_uint_fast32_t_uint_fast32_t
    #endif
    #define FMC_IDENT_EQ_int_fast32_t_int_fast32_t ()
    #define FMC_IDENT_EQ_uint_fast32_t_uint_fast32_t ()
    #define FMC_DETECTOR_int_fast32_t ()
    #define FMC_DETECTOR_uint_fast32_t ()

    #if defined(FMC_DETECTOR_int_fast64_t) || defined(FMC_DETECTOR_uint_fast64_t)
        #undef FMC_DETECTOR_int_fast64_t
        #undef FMC_DETECTOR_uint_fast64_t
    #endif
    #if defined(FMC_IDENT_EQ_int_fast64_t_int_fast64_t) || defined(FMC_IDENT_EQ_uint_fast64_t_uint_fast64_t)
        #undef FMC_IDENT_EQ_int_fast64_t_int_fast64_t
        #undef FMC_IDENT_EQ_uint_fast64_t_uint_fast64_t
    #endif
    #define FMC_IDENT_EQ_int_fast64_t_int_fast64_t ()
    #define FMC_IDENT_EQ_uint_fast64_t_uint_fast64_t ()
    #define FMC_DETECTOR_int_fast64_t ()
    #define FMC_DETECTOR_uint_fast64_t ()

    #if defined(FMC_DETECTOR_intptr_t) || defined(FMC_DETECTOR_uintptr_t)
        #undef FMC_DETECTOR_intptr_t
        #undef FMC_DETECTOR_uintptr_t
    #endif
    #if defined(FMC_IDENT_EQ_intptr_t_intptr_t) || defined(FMC_IDENT_EQ_uintptr_t_uintptr_t)
        #undef FMC_IDENT_EQ_intptr_t_intptr_t
        #undef FMC_IDENT_EQ_uintptr_t_uintptr_t
    #endif
    #define FMC_IDENT_EQ_intptr_t_intptr_t ()
    #define FMC_IDENT_EQ_uintptr_t_uintptr_t ()
    #define FMC_DETECTOR_intptr_t ()
    #define FMC_DETECTOR_uintptr_t ()

    #if defined(FMC_DETECTOR_intmax_t) || defined(FMC_DETECTOR_uintmax_t)
        #undef FMC_DETECTOR_intmax_t
        #undef FMC_DETECTOR_uintmax_t
    #endif
    #if defined(FMC_IDENT_EQ_intmax_t_intmax_t) || defined(FMC_IDENT_EQ_uintmax_t_uintmax_t)
        #undef FMC_IDENT_EQ_intmax_t_intmax_t
        #undef FMC_IDENT_EQ_uintmax_t_uintmax_t
    #endif
    #define FMC_IDENT_EQ_intmax_t_intmax_t ()
    #define FMC_IDENT_EQ_uintmax_t_uintmax_t ()
    #define FMC_DETECTOR_intmax_t ()
    #define FMC_DETECTOR_uintmax_t ()

    #if defined(FMC_DETECTOR_size_t)
        #undef FMC_DETECTOR_size_t
    #endif
    #if defined(FMC_IDENT_EQ_size_t_size_t)
        #undef FMC_IDENT_EQ_size_t_size_t
    #endif
    #define FMC_IDENT_EQ_size_t_size_t ()
    #define FMC_DETECTOR_size_t ()

    #if defined(FMC_DETECTOR_ptrdiff_t)
        #undef FMC_DETECTOR_ptrdiff_t
    #endif
    #if defined(FMC_IDENT_EQ_ptrdiff_t_ptrdiff_t)
        #undef FMC_IDENT_EQ_ptrdiff_t_ptrdiff_t
    #endif
    #define FMC_IDENT_EQ_ptrdiff_t_ptrdiff_t ()
    #define FMC_DETECTOR_ptrdiff_t ()

    #if defined(FMC_DETECTOR_FILE)
        #undef FMC_DETECTOR_FILE
    #endif
    #if defined(FMC_IDENT_EQ_FILE_FILE)
        #undef FMC_IDENT_EQ_FILE_FILE
    #endif
    #define FMC_IDENT_EQ_FILE_FILE ()
    #define FMC_DETECTOR_FILE ()

    #if defined(FMC_DETECTOR_fpos_t)
        #undef FMC_DETECTOR_fpos_t
    #endif
    #if defined(FMC_IDENT_EQ_fpos_t_fpos_t)
        #undef FMC_IDENT_EQ_fpos_t_fpos_t
    #endif
    #define FMC_IDENT_EQ_fpos_t_fpos_t ()
    #define FMC_DETECTOR_fpos_t ()

    #if defined(FMC_DETECTOR_clock_t)
        #undef FMC_DETECTOR_clock_t
    #endif
    #if defined(FMC_IDENT_EQ_clock_t_clock_t)
        #undef FMC_IDENT_EQ_clock_t_clock_t
    #endif
    #define FMC_IDENT_EQ_clock_t_clock_t ()
    #define FMC_DETECTOR_clock_t ()

    #if defined(FMC_DETECTOR_time_t)
        #undef FMC_DETECTOR_time_t
    #endif
    #if defined(FMC_IDENT_EQ_time_t_time_t)
        #undef FMC_IDENT_EQ_time_t_time_t
    #endif
    #define FMC_IDENT_EQ_time_t_time_t ()
    #define FMC_DETECTOR_time_t ()

    #if defined(FMC_DETECTOR_va_list)
        #undef FMC_DETECTOR_va_list
    #endif
    #if defined(FMC_IDENT_EQ_va_list_va_list)
        #undef FMC_IDENT_EQ_va_list_va_list
    #endif
    #define FMC_IDENT_EQ_va_list_va_list ()
    #define FMC_DETECTOR_va_list ()

    #if defined(FMC_DETECTOR_wint_t)
        #undef FMC_DETECTOR_wint_t
    #endif
    #if defined(FMC_IDENT_EQ_wint_t_wint_t)
        #undef FMC_IDENT_EQ_wint_t_wint_t
    #endif
    #define FMC_IDENT_EQ_wint_t_wint_t ()
    #define FMC_DETECTOR_wint_t ()

    #if defined(FMC_DETECTOR_wctype_t)
        #undef FMC_DETECTOR_wctype_t
    #endif
    #if defined(FMC_IDENT_EQ_wctype_t_wctype_t)
        #undef FMC_IDENT_EQ_wctype_t_wctype_t
    #endif
    #define FMC_IDENT_EQ_wctype_t_wctype_t ()
    #define FMC_DETECTOR_wctype_t ()

    #if defined(FMC_DETECTOR_wctrans_t)
        #undef FMC_DETECTOR_wctrans_t
    #endif
    #if defined(FMC_IDENT_EQ_wctrans_t_wctrans_t)
        #undef FMC_IDENT_EQ_wctrans_t_wctrans_t
    #endif
    #define FMC_IDENT_EQ_wctrans_t_wctrans_t ()
    #define FMC_DETECTOR_wctrans_t ()

    #if defined(FMC_DETECTOR_sig_atomic_t)
        #undef FMC_DETECTOR_sig_atomic_t
    #endif
    #if defined(FMC_IDENT_EQ_sig_atomic_t_sig_atomic_t)
        #undef FMC_IDENT_EQ_sig_atomic_t_sig_atomic_t
    #endif
    #define FMC_IDENT_EQ_sig_atomic_t_sig_atomic_t ()
    #define FMC_DETECTOR_sig_atomic_t ()

    #if defined(FMC_DETECTOR_mbstate_t)
        #undef FMC_DETECTOR_mbstate_t
    #endif
    #if defined(FMC_IDENT_EQ_mbstate_t_mbstate_t)
        #undef FMC_IDENT_EQ_mbstate_t_mbstate_t
    #endif
    #define FMC_IDENT_EQ_mbstate_t_mbstate_t ()
    #define FMC_DETECTOR_mbstate_t ()
    
    #if !defined(FMC_CUSTOM_DETECTORS)
        #define FMC_CUSTOM_DETECTORS

        #if defined(FMC_DETECTOR_struct_FManC_Char)
            #undef FMC_DETECTOR_struct_FManC_Char
        #endif
        #if defined(FMC_IDENT_EQ_struct_FManC_Char_struct_FManC_Char)
            #undef FMC_IDENT_EQ_struct_FManC_Char_struct_FManC_Char
        #endif
        #define FMC_IDENT_EQ_struct_FManC_Char_struct_FManC_Char ()
        #define FMC_DETECTOR_struct_FManC_Char ()

        #if defined(FMC_DETECTOR_FMC_Char)
            #undef FMC_DETECTOR_FMC_Char
        #endif
        #if defined(FMC_IDENT_EQ_FMC_Char_FMC_Char)
            #undef FMC_IDENT_EQ_FMC_Char_FMC_Char
        #endif
        #define FMC_IDENT_EQ_FMC_Char_FMC_Char ()
        #define FMC_DETECTOR_FMC_Char ()

        #if defined(FMC_DETECTOR_struct_FManC_String)
            #undef FMC_DETECTOR_struct_FManC_String
        #endif
        #if defined(FMC_IDENT_EQ_struct_FManC_String_struct_FManC_String)
            #undef FMC_IDENT_EQ_struct_FManC_String_struct_FManC_String
        #endif
        #define FMC_IDENT_EQ_struct_FManC_String_struct_FManC_String ()
        #define FMC_DETECTOR_struct_FManC_String ()

        #if defined(FMC_DETECTOR_FMC_String)
            #undef FMC_DETECTOR_FMC_String
        #endif
        #if defined(FMC_IDENT_EQ_FMC_String_FMC_String)
            #undef FMC_IDENT_EQ_FMC_String_FMC_String
        #endif
        #define FMC_IDENT_EQ_FMC_String_FMC_String ()
        #define FMC_DETECTOR_FMC_String ()

        #if defined(FMC_DETECTOR_FMC_Byte)
            #undef FMC_DETECTOR_FMC_Byte
        #endif
        #if defined(FMC_IDENT_EQ_FMC_Byte_FMC_Byte)
            #undef FMC_IDENT_EQ_FMC_Byte_FMC_Byte
        #endif
        #define FMC_IDENT_EQ_FMC_Byte_FMC_Byte ()
        #define FMC_DETECTOR_FMC_Byte ()

        #if defined(FMC_DETECTOR_FMC_Bool)
            #undef FMC_DETECTOR_FMC_Bool
        #endif
        #if defined(FMC_IDENT_EQ_FMC_Bool_FMC_Bool)
            #undef FMC_IDENT_EQ_FMC_Bool_FMC_Bool
        #endif
        #define FMC_IDENT_EQ_FMC_Bool_FMC_Bool ()
        #define FMC_DETECTOR_FMC_Bool ()

        #if defined(FMC_DETECTOR_FMC_CharControl)
            #undef FMC_DETECTOR_FMC_CharControl
        #endif
        #if defined(FMC_IDENT_EQ_FMC_CharControl_FMC_CharControl)
            #undef FMC_IDENT_EQ_FMC_CharControl_FMC_CharControl
        #endif
        #define FMC_IDENT_EQ_FMC_CharControl_FMC_CharControl ()
        #define FMC_DETECTOR_FMC_CharControl ()

        #if defined(FMC_DETECTOR_FMC_FileState)
            #undef FMC_DETECTOR_FMC_FileState
        #endif
        #if defined(FMC_IDENT_EQ_FMC_FileState_FMC_FileState)
            #undef FMC_IDENT_EQ_FMC_FileState_FMC_FileState
        #endif
        #define FMC_IDENT_EQ_FMC_FileState_FMC_FileState ()
        #define FMC_DETECTOR_FMC_FileState ()

        #if defined(FMC_DETECTOR_FMC_PermsFlags)
            #undef FMC_DETECTOR_FMC_PermsFlags
        #endif
        #if defined(FMC_IDENT_EQ_FMC_PermsFlags_FMC_PermsFlags)
            #undef FMC_IDENT_EQ_FMC_PermsFlags_FMC_PermsFlags
        #endif
        #define FMC_IDENT_EQ_FMC_PermsFlags_FMC_PermsFlags ()
        #define FMC_DETECTOR_FMC_PermsFlags ()

        #if defined(FMC_DETECTOR_FMC_CodePoint)
            #undef FMC_DETECTOR_FMC_CodePoint
        #endif
        #if defined(FMC_IDENT_EQ_FMC_CodePoint_FMC_CodePoint)
            #undef FMC_IDENT_EQ_FMC_CodePoint_FMC_CodePoint
        #endif
        #define FMC_IDENT_EQ_FMC_CodePoint_FMC_CodePoint ()
        #define FMC_DETECTOR_FMC_CodePoint ()

        #if defined(FMC_DETECTOR_FMC_Mutex)
            #undef FMC_DETECTOR_FMC_Mutex
        #endif
        #if defined(FMC_IDENT_EQ_FMC_Mutex_FMC_Mutex)
            #undef FMC_IDENT_EQ_FMC_Mutex_FMC_Mutex
        #endif
        #define FMC_IDENT_EQ_FMC_Mutex_FMC_Mutex ()
        #define FMC_DETECTOR_FMC_Mutex ()

        #if defined(FMC_DETECTOR_enum_FManC_Encodings)
            #undef FMC_DETECTOR_enum_FManC_Encodings
        #endif
        #if defined(FMC_IDENT_EQ_enum_FManC_Encodings_enum_FManC_Encodings)
            #undef FMC_IDENT_EQ_enum_FManC_Encodings_enum_FManC_Encodings
        #endif
        #define FMC_IDENT_EQ_enum_FManC_Encodings_enum_FManC_Encodings ()
        #define FMC_DETECTOR_enum_FManC_Encodings ()

        #if defined(FMC_DETECTOR_FMC_Encodings)
            #undef FMC_DETECTOR_FMC_Encodings
        #endif
        #if defined(FMC_IDENT_EQ_FMC_Encodings_FMC_Encodings)
            #undef FMC_IDENT_EQ_FMC_Encodings_FMC_Encodings
        #endif
        #define FMC_IDENT_EQ_FMC_Encodings_FMC_Encodings ()
        #define FMC_DETECTOR_FMC_Encodings ()

        #if defined(FMC_DETECTOR_enum_FManC_Error)
            #undef FMC_DETECTOR_enum_FManC_Error
        #endif
        #if defined(FMC_IDENT_EQ_enum_FManC_Error_enum_FManC_Error)
            #undef FMC_IDENT_EQ_enum_FManC_Error_enum_FManC_Error
        #endif
        #define FMC_IDENT_EQ_enum_FManC_Error_enum_FManC_Error ()
        #define FMC_DETECTOR_enum_FManC_Error ()

        #if defined(FMC_DETECTOR_FMC_Error)
            #undef FMC_DETECTOR_FMC_Error
        #endif
        #if defined(FMC_IDENT_EQ_FMC_Error_FMC_Error)
            #undef FMC_IDENT_EQ_FMC_Error_FMC_Error
        #endif
        #define FMC_IDENT_EQ_FMC_Error_FMC_Error ()
        #define FMC_DETECTOR_FMC_Error ()

        #if defined(FMC_DETECTOR_struct_FManC_ErrStackElement)
            #undef FMC_DETECTOR_struct_FManC_ErrStackElement
        #endif
        #if defined(FMC_IDENT_EQ_struct_FManC_ErrStackElement_struct_FManC_ErrStackElement)
            #undef FMC_IDENT_EQ_struct_FManC_ErrStackElement_struct_FManC_ErrStackElement
        #endif
        #define FMC_IDENT_EQ_struct_FManC_ErrStackElement_struct_FManC_ErrStackElement ()
        #define FMC_DETECTOR_struct_FManC_ErrStackElement ()

        #if defined(FMC_DETECTOR_FMC_ErrStackElement)
            #undef FMC_DETECTOR_FMC_ErrStackElement
        #endif
        #if defined(FMC_IDENT_EQ_FMC_ErrStackElement_FMC_ErrStackElement)
            #undef FMC_IDENT_EQ_FMC_ErrStackElement_FMC_ErrStackElement
        #endif
        #define FMC_IDENT_EQ_FMC_ErrStackElement_FMC_ErrStackElement ()
        #define FMC_DETECTOR_FMC_ErrStackElement ()

        #if defined(FMC_DETECTOR_struct_FManC_ErrStack)
            #undef FMC_DETECTOR_struct_FManC_ErrStack
        #endif
        #if defined(FMC_IDENT_EQ_struct_FManC_ErrStack_struct_FManC_ErrStack)
            #undef FMC_IDENT_EQ_struct_FManC_ErrStack_struct_FManC_ErrStack
        #endif
        #define FMC_IDENT_EQ_struct_FManC_ErrStack_struct_FManC_ErrStack ()
        #define FMC_DETECTOR_struct_FManC_ErrStack ()

        #if defined(FMC_DETECTOR_FMC_ErrStack)
            #undef FMC_DETECTOR_FMC_ErrStack
        #endif
        #if defined(FMC_IDENT_EQ_FMC_ErrStack_FMC_ErrStack)
            #undef FMC_IDENT_EQ_FMC_ErrStack_FMC_ErrStack
        #endif
        #define FMC_IDENT_EQ_FMC_ErrStack_FMC_ErrStack ()
        #define FMC_DETECTOR_FMC_ErrStack ()

        #if defined(FMC_DETECTOR_struct_FManC_File)
            #undef FMC_DETECTOR_struct_FManC_File
        #endif
        #if defined(FMC_IDENT_EQ_struct_FManC_File_struct_FManC_File)
            #undef FMC_IDENT_EQ_struct_FManC_File_struct_FManC_File
        #endif
        #define FMC_IDENT_EQ_struct_FManC_File_struct_FManC_File ()
        #define FMC_DETECTOR_struct_FManC_File ()

        #if defined(FMC_DETECTOR_FMC_File)
            #undef FMC_DETECTOR_FMC_File
        #endif
        #if defined(FMC_IDENT_EQ_FMC_File_FMC_File)
            #undef FMC_IDENT_EQ_FMC_File_FMC_File
        #endif
        #define FMC_IDENT_EQ_FMC_File_FMC_File ()
        #define FMC_DETECTOR_FMC_File ()

        #if defined(FMC_DETECTOR_enum_FMC_File_orientation)
            #undef FMC_DETECTOR_enum_FMC_File_orientation
        #endif
        #if defined(FMC_IDENT_EQ_enum_FMC_File_orientation_enum_FMC_File_orientation)
            #undef FMC_IDENT_EQ_enum_FMC_File_orientation_enum_FMC_File_orientation
        #endif
        #define FMC_IDENT_EQ_enum_FMC_File_orientation_enum_FMC_File_orientation ()
        #define FMC_DETECTOR_enum_FMC_File_orientation ()

        #if defined(FMC_DETECTOR_enum_FMC_File_dataMode)
            #undef FMC_DETECTOR_enum_FMC_File_dataMode
        #endif
        #if defined(FMC_IDENT_EQ_enum_FMC_File_dataMode_enum_FMC_File_dataMode)
            #undef FMC_IDENT_EQ_enum_FMC_File_dataMode_enum_FMC_File_dataMode
        #endif
        #define FMC_IDENT_EQ_enum_FMC_File_dataMode_enum_FMC_File_dataMode ()
        #define FMC_DETECTOR_enum_FMC_File_dataMode ()

        #if defined(FMC_DETECTOR_struct_FManC_CharComp)
            #undef FMC_DETECTOR_struct_FManC_CharComp
        #endif
        #if defined(FMC_IDENT_EQ_struct_FManC_CharComp_struct_FManC_CharComp)
            #undef FMC_IDENT_EQ_struct_FManC_CharComp_struct_FManC_CharComp
        #endif
        #define FMC_IDENT_EQ_struct_FManC_CharComp_struct_FManC_CharComp ()
        #define FMC_DETECTOR_struct_FManC_CharComp ()

        #if defined(FMC_DETECTOR_FMC_CharComp)
            #undef FMC_DETECTOR_FMC_CharComp
        #endif
        #if defined(FMC_IDENT_EQ_FMC_CharComp_FMC_CharComp)
            #undef FMC_IDENT_EQ_FMC_CharComp_FMC_CharComp
        #endif
        #define FMC_IDENT_EQ_FMC_CharComp_FMC_CharComp ()
        #define FMC_DETECTOR_FMC_CharComp ()
        
    #endif // FMC_CUSTOM_DETECTORS
#endif // FMC_IDENT_DETECTION_H
