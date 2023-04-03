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

#include <mimalloc.h>

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

FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_MALLOC(mi_free) FMC_String* FMC_allocStr(FMC_Char* const* chars, uint64_t size);
FMC_SHARED FMC_FUNC_NONNULL(1) FMC_Char* FMC_getCharAt(FMC_String* str, uint64_t index);

FMC_FUNC_INLINE FMC_FUNC_NONNULL(1) void FMC_freeStr(FMC_String* str)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!str)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_nullarg, 3, "ERROR : In function : ", __func__, " : the provided pointer is NULL");
            FMC_printRedError(stderr, err_nullarg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "In function : FMC_freeStr : the provided pointer is NULL");
        return;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    mi_free(str);
    return;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(2) FMC_FUNC_MALLOC(mi_free) FMC_FUNC_WARN_UNUSED_RESULT FMC_Char* FMC_allocChar(FMC_Char* prev, const FMC_Byte* restrict const bytes, FMC_Encodings char_encoding, FMC_CharControl char_is_null, uint8_t byte_number);

FMC_FUNC_INLINE FMC_FUNC_NONNULL(1) void FMC_freeChar(FMC_Char* const c)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (c == NULL)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_nullarg, 3, "ERROR : In function : ", __func__, " : the provided file pointer is NULL");
            FMC_printRedError(stderr, err_nullarg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "The provided pointer is NULL");
        return;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    mi_free(c);
    return;
    FMC_UNREACHABLE;
}

FMC_END_DECLS

#endif // FMC_STRINGS_H