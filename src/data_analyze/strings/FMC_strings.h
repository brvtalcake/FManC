/*

MIT License

Copyright (c) 2022 Axel PASCON

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

#ifndef FMC_STRINGS_H
#define FMC_STRINGS_H

#include <stdlib.h>
#include <stdint.h>
#include <uchar.h>

#include "../../general/FMC_general.h"

FMC_BEGIN_DECLS

// TODO: FMC_isStrConsistent

#if defined(FMC_CHAR) || defined(FMC_CHARCOMP)
    #undef FMC_CHAR
    #undef FMC_CHARCOMP
#endif
#define FMC_CHAR(_next, _prev, _enc, _comp, _isnull, _bytenumber) \
    ((struct FManC_Char)                                          \
    {                                                             \
        .next = _next,                                            \
        .prev = _prev,                                            \
        .encoding = _enc,                                         \
        .comp = (struct FManC_CharComp) _comp,                    \
        .isNull = _isnull,                                        \
        .byteNumber = _bytenumber                                 \
    })

#define FMC_CHARCOMP(_byte0, _byte1, _byte2, _byte3) \
    ((struct FManC_CharComp)                         \
    {                                                \
        .byte0 = _byte0,                             \
        .byte1 = _byte1,                             \
        .byte2 = _byte2,                             \
        .byte3 = _byte3                              \
    })

#if defined(FMC_CHAR_IS_NULL) || defined(FMC_CHAR_BYTENUMBER)
    #undef FMC_CHAR_IS_NULL
    #undef FMC_CHAR_BYTENUMBER
#endif
#define FMC_CHAR_IS_NULL(_b0, _b1, _b2, _b3)               \
    ((_b0 == 0) && (_b1 == 0) && (_b2 == 0) && (_b3 == 0))

#define FMC_CHAR_BYTENUMBER(_b0, _b1, _b2, _b3)            \
    ((_b0 != 0) + (_b1 != 0) + (_b2 != 0) + (_b3 != 0))


#if defined(FMC_MAKE_CHPTR_NULL) || defined(FMC_MAKE_CH_NULL)
    #undef FMC_MAKE_CHPTR_NULL
    #undef FMC_MAKE_CH_NULL
#endif
#define FMC_MAKE_CHPTR_NULL(_ch_ptr) \
    do                               \
    {                                \
        _ch_ptr->comp.byte0 = 0;     \
        _ch_ptr->comp.byte1 = 0;     \
        _ch_ptr->comp.byte2 = 0;     \
        _ch_ptr->comp.byte3 = 0;     \
        _ch_ptr->isNull = FMC_TRUE;  \
    } while (0)

#define FMC_MAKE_CH_NULL(_ch)        \
    do                               \
    {                                \
        _ch.comp.byte0 = 0;          \
        _ch.comp.byte1 = 0;          \
        _ch.comp.byte2 = 0;          \
        _ch.comp.byte3 = 0;          \
        _ch.isNull = FMC_TRUE;       \
    } while (0)

#if defined(FMC_charCompare) || defined(FMC_charPtrCompare) || defined(FMC_charCompare_2) || defined(FMC_charCompare_3) || defined(FMC_charCompare_4)
    #undef FMC_charCompare
    #undef FMC_charPtrCompare
    #undef FMC_charCompare_2
    #undef FMC_charCompare_3
    #undef FMC_charCompare_4
#endif
#if defined(FMC_charPtrCompare_helper1) || defined(FMC_charPtrCompare_helper2) || defined(FMC_charPtrCompare_helper2_IMPL) || defined(FMC_charPtrCompare_helper1_IMPL) || defined(FMC_charPtrCompare_helper1_ARITY) || defined(FMC_charPtrCompare_helper2_ARITY)
    #undef FMC_charPtrCompare_helper1
    #undef FMC_charPtrCompare_helper2
    #undef FMC_charPtrCompare_helper2_IMPL
    #undef FMC_charPtrCompare_helper1_IMPL
    #undef FMC_charPtrCompare_helper1_ARITY
    #undef FMC_charPtrCompare_helper2_ARITY
#endif
#define FMC_charCompare_2(_ch1, _ch2) ({                        \
    FMC_Bool res = FMC_FALSE;                                   \
    if (_ch1.encoding == _ch2.encoding)                         \
    {                                                           \
        if (_ch1.byteNumber == _ch2.byteNumber)                 \
        {                                                       \
            switch (_ch1.byteNumber)                            \
            {                                                   \
                case 1:                                         \
                    res = _ch1.comp.byte0 == _ch2.comp.byte0;   \
                    break;                                      \
                case 2:                                         \
                    res = _ch1.comp.byte0 == _ch2.comp.byte0 && \
                          _ch1.comp.byte1 == _ch2.comp.byte1;   \
                    break;                                      \
                case 3:                                         \
                    res = _ch1.comp.byte0 == _ch2.comp.byte0 && \
                          _ch1.comp.byte1 == _ch2.comp.byte1 && \
                          _ch1.comp.byte2 == _ch2.comp.byte2;   \
                    break;                                      \
                case 4:                                         \
                    res = _ch1.comp.byte0 == _ch2.comp.byte0 && \
                          _ch1.comp.byte1 == _ch2.comp.byte1 && \
                          _ch1.comp.byte2 == _ch2.comp.byte2 && \
                          _ch1.comp.byte3 == _ch2.comp.byte3;   \
                    break;                                      \
                default:                                        \
                    res = FMC_FALSE;                            \
                    break;                                      \
            }                                                   \
        }                                                       \
    }                                                           \
    res;                                                        \
})

#define FMC_charCompare_3(_ch1, _ch2, _ch3) ({                  \
    FMC_Bool res = FMC_FALSE;                                   \
    if (FMC_charCompare_2(_ch1, _ch2))                          \
    {                                                           \
        res = FMC_charCompare_2(_ch1, _ch3);                    \
    }                                                           \
    res;                                                        \
})

#define FMC_charCompare_4(_ch1, _ch2, _ch3, _ch4) ({            \
    FMC_Bool res = FMC_FALSE;                                   \
    if (FMC_charCompare_2(_ch1, _ch2))                          \
    {                                                           \
        res = FMC_charCompare_3(_ch1, _ch3, _ch4);              \
    }                                                           \
    res;                                                        \
})

#define FMC_charCompare(...) FMC_CONCAT_2(FMC_charCompare_, FMC_ID(FMC_GET_ARGC(__VA_ARGS__)))(__VA_ARGS__)

#define FMC_charPtrCompare_helper1_IMPL(_val, _nb) v(FMC_Char _##_nb = *_val;)
#define FMC_charPtrCompare_helper1_ARITY 2
#define FMC_charPtrCompare_helper2_IMPL(_val, _nb) v(_##_nb,)
#define FMC_charPtrCompare_helper2_ARITY 2
#define FMC_charPtrCompare(...) ({                                                                                         \
    FMC_Bool res = FMC_FALSE;                                                                                              \
    ML99_EVAL(ML99_call(ML99_variadicsForEachI, v(FMC_charPtrCompare_helper1), v(__VA_ARGS__)));                           \
    res = FMC_charCompare(ML99_EVAL(ML99_call(ML99_variadicsForEachI, v(FMC_charPtrCompare_helper2), v(__VA_ARGS__))) _0); \
    res;                                                                                                                   \
})

#if defined(FMC_UI32_AS_BYTES) || defined(FMC_UI32_AS_FMC_BYTES)
    #undef FMC_UI32_AS_BYTES
    #undef FMC_UI32_AS_FMC_BYTES
#endif
#define FMC_UI32_AS_BYTES(_ui32) (_ui32 & 0xFF), ((_ui32 >> 8) & 0xFF), ((_ui32 >> 16) & 0xFF), ((_ui32 >> 24) & 0xFF)
#define FMC_UI32_AS_FMC_BYTES(_ui32)        \
    ((FMC_Byte[4]) {                        \
        [0] = (_ui32 & 0xFF),               \
        [1] = ((_ui32 >> 8) & 0xFF),        \
        [2] = ((_ui32 >> 16) & 0xFF),       \
        [3] = ((_ui32 >> 24) & 0xFF)        \
    })

#if defined(FMC_wrapCharComp) || defined(FMC_wrapUint32)
    #undef FMC_wrapCharComp
    #undef FMC_wrapUint32
#endif
#define FMC_wrapCharComp(_chcomp)                                                              \
    (FMC_CHAR(NULL,                                                                            \
              NULL,                                                                            \
              unknown,                                                                         \
              _chcomp,                                                                         \
              FMC_CHAR_IS_NULL(_chcomp.byte0, _chcomp.byte1, _chcomp.byte2, _chcomp.byte3),    \
              FMC_CHAR_BYTENUMBER(_chcomp.byte0, _chcomp.byte1, _chcomp.byte2, _chcomp.byte3)))

#define FMC_wrapUint32(_uint32) (FMC_wrapCharComp(FMC_CHARCOMP(FMC_UI32_AS_BYTES(_uint32))))


FMC_SHARED FMC_FUNC_NONNULL(1) void FMC_freeStr(FMC_String* str);

FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_JUST_MALLOC FMC_String* FMC_allocStr(FMC_Char* const* const chars, uint64_t size);
FMC_SHARED FMC_FUNC_PURE FMC_FUNC_NONNULL(1) FMC_Char* FMC_getCharAt(FMC_String* str, uint64_t index);
FMC_SHARED FMC_FUNC_NONNULL(1, 2) FMC_String* FMC_append_str(FMC_String* str1, FMC_String* str2);
FMC_SHARED FMC_FUNC_NONNULL(1, 2) FMC_String* FMC_append_ch(FMC_String* str, FMC_Char* ch);
FMC_SHARED FMC_FUNC_NONNULL(1) FMC_String* FMC_cloneStr(FMC_String* str);

#if defined(FMC_append)
    #undef FMC_append
#endif
#define FMC_append(_str1, _str2) _Generic((_str2), \
    FMC_String*: FMC_append_str,                   \
    FMC_Char*: FMC_append_ch,                      \
    default: FMC_append_str                        \
)(_str1, _str2)

FMC_SHARED FMC_FUNC_INLINE FMC_FUNC_NONNULL(1) FMC_Bool FMC_checkEncoding(const FMC_String* const str)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!str)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_nullarg, 3, "ERROR : In function : ", __func__, " : the provided pointer is NULL");
            FMC_printRedError(stderr, err_nullarg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "In function : FMC_checkEncoding : the provided pointer is NULL");
        return FMC_FALSE;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    if (!str->firstChar || !str->lastChar) return FMC_TRUE;
    if (str->firstChar->encoding != str->lastChar->encoding) return FMC_FALSE;
    FMC_Encodings enc = str->firstChar->encoding;
    FMC_Char* ch = str->firstChar;
    size_t count = 0;
    while (ch != str->firstChar)
    {
        if (count > str->size) return FMC_FALSE; // It should never happen
        if (ch->encoding != enc) return FMC_FALSE;
        ch = ch->next;
        count++;
    }
    return FMC_TRUE;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_INLINE FMC_FUNC_NONNULL(1) void FMC_removeTrailNullChars(FMC_String* const str)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!str)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_nullarg, 3, "ERROR : In function : ", __func__, " : the provided pointer is NULL");
            FMC_printRedError(stderr, err_nullarg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "In function : FMC_removeTrailNullChars : the provided pointer is NULL");
        return;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    if (!str->firstChar || !str->lastChar) return;
    FMC_Char* ch = str->lastChar;
    while (ch->isNull)
    {
        if (ch == str->firstChar) break;
        ch = ch->prev;
        free(ch->next);
        ch->next = NULL;
        str->lastChar = ch;
        str->size--;
    }
    return;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) void FMC_freeChar(FMC_Char* const c);

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_JUST_MALLOC FMC_FUNC_WARN_UNUSED_RESULT FMC_Char* FMC_allocChar(const FMC_Byte* restrict const bytes, FMC_Encodings char_encoding, FMC_CharControl char_is_null, uint8_t byte_number);

FMC_SHARED FMC_FUNC_NONNULL(1, 2) FMC_FUNC_COLD int64_t FMC_getLevenshtein_no_coeffs(FMC_String* str1, FMC_String* str2);
FMC_SHARED FMC_FUNC_NONNULL(1, 2, 3) FMC_FUNC_COLD int64_t FMC_getLevenshtein_coeffs(FMC_String* str1, FMC_String* str2, int64_t* coeffs);

#if defined(FMC_getLevenshtein)
    #undef FMC_getLevenshtein
#endif
#define FMC_getLevenshtein(_str1, _str2, ...) FMC_CHOOSE_FUNC(2)(FMC_getLevenshtein_no_coeffs, FMC_getLevenshtein_coeffs, _str1, _str2, __VA_ARGS__)

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_String* FMC_stringFromU8Str(unsigned char* utf8_c_str, FMC_Encodings enc);


FMC_END_DECLS

#endif // FMC_STRINGS_H