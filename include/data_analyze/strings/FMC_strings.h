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

#include "../../general/FMC_general.h"

FMC_BEGIN_DECLS

#if defined(FMC_MAKE_CHPTR_NULL) || defined(FMC_MAKE_CH_NULL)
    #undef FMC_MAKE_CHPTR_NULL
    #undef FMC_MAKE_CH_NULL
#endif
#define FMC_MAKE_CHPTR_NULL(_ch_ptr) \
    do                               \
    {                                \
        _ch_ptr->comp.byte1 = 0;     \
        _ch_ptr->comp.byte2 = 0;     \
        _ch_ptr->comp.byte3 = 0;     \
        _ch_ptr->comp.byte4 = 0;     \
        _ch_ptr->isNull = FMC_TRUE;  \
    } while (0)

#define FMC_MAKE_CH_NULL(_ch)        \
    do                               \
    {                                \
        _ch.comp.byte1 = 0;          \
        _ch.comp.byte2 = 0;          \
        _ch.comp.byte3 = 0;          \
        _ch.comp.byte4 = 0;          \
        _ch.isNull = FMC_TRUE;       \
    } while (0)

FMC_SHARED FMC_FUNC_NONNULL(1) void FMC_freeStr(FMC_String* str);

FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_MALLOC(FMC_freeStr) FMC_String* FMC_allocStr(FMC_Char* const* const chars, uint64_t size);
FMC_SHARED FMC_FUNC_NONNULL(1) FMC_Char* FMC_getCharAt(FMC_String* str, uint64_t index);
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

FMC_FUNC_INLINE FMC_FUNC_NONNULL(1) FMC_Bool FMC_checkEncoding(const FMC_String* const str)
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

FMC_FUNC_INLINE FMC_FUNC_NONNULL(1) void FMC_removeTrailNullChars(FMC_String* const str)
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

FMC_END_DECLS

#endif // FMC_STRINGS_H