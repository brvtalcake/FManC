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

#include <assert.h>
#include <stdlib.h>

#include "FMC_strings.h"

extern FMC_FUNC_INLINE FMC_FUNC_NONNULL(1) void FMC_freeChar(FMC_Char* const c);

FMC_SHARED FMC_FUNC_NONNULL(2) FMC_FUNC_MALLOC(mi_free) FMC_FUNC_WARN_UNUSED_RESULT FMC_Char* FMC_allocChar(FMC_Char* prev, const FMC_Byte* restrict const bytes, FMC_Encodings char_encoding, FMC_CharControl char_is_null, uint8_t byte_number)
{
    FMC_Char* c = mi_zalloc(sizeof(FMC_Char));
    FMC_UNREACHABLE_ASSERT(c != NULL);
    FMC_UNREACHABLE_ASSERT(c->next == NULL);
    FMC_UNREACHABLE_ASSERT(c->prev == NULL);
    c->prev = prev;
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (c == NULL)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_nullarg, 3, "ERROR : In function : ", __func__, " : the provided pointer is NULL");
            FMC_printRedError(stderr, err_nullarg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "The provided pointer is NULL");
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    switch (char_encoding)
    {
        case ascii:
            c->encoding = ascii;
            break;
        case utf8_bom:
            c->encoding = utf8_bom;
            break;
        case utf8:
            c->encoding = utf8;
            break;
        case utf16_be:
            c->encoding = utf16_be;
            break;
        case utf16_le:
            c->encoding = utf16_le;
            break;
        case utf32_be:
            c->encoding = utf32_be;
            break;
        case utf32_le:
            c->encoding = utf32_le;
            break;
        default:
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_invalidarg, 3, "ERROR : In function : ", __func__, " : the provided encoding is invalid");
                FMC_printRedError(stderr, err_invalidarg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "The provided encoding is invalid");
            mi_free(c);
            return NULL;
            FMC_UNREACHABLE;
    }
    switch (byte_number)
    {
        case 1:
            if (char_encoding != ascii || char_encoding != utf8_bom || char_encoding != utf8)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_invalidarg, 3, "ERROR : In function : ", __func__, " : the provided byte_number is invalid");
                    FMC_printRedError(stderr, err_invalidarg);
                }
                FMC_setError(FMC_ERR_INVALID_ARGUMENT, "The provided byte_number is invalid");
                mi_free(c);
                return NULL;
                FMC_UNREACHABLE;
            }
            else c->byteNumber = 1;
            break;
        case 2:
            if (char_encoding != utf16_be || char_encoding != utf16_le || char_encoding != utf8_bom || char_encoding != utf8)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_invalidarg, 3, "ERROR : In function : ", __func__, " : the provided byte_number is invalid");
                    FMC_printRedError(stderr, err_invalidarg);
                }
                FMC_setError(FMC_ERR_INVALID_ARGUMENT, "The provided byte_number is invalid");
                mi_free(c);
                return NULL;
                FMC_UNREACHABLE;
            }
            else c->byteNumber = 2;
            break;
        case 3:
            if (char_encoding != utf8_bom || char_encoding != utf8)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_invalidarg, 3, "ERROR : In function : ", __func__, " : the provided byte_number is invalid");
                    FMC_printRedError(stderr, err_invalidarg);
                }
                FMC_setError(FMC_ERR_INVALID_ARGUMENT, "The provided byte_number is invalid");
                mi_free(c);
                return NULL;
                FMC_UNREACHABLE;
            }
            else c->byteNumber = 3;
            break;
        case 4:
            if (char_encoding != utf32_be || char_encoding != utf32_le || char_encoding != utf8_bom || char_encoding != utf8 ||
                char_encoding != utf16_be || char_encoding != utf16_le)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_invalidarg, 3, "ERROR : In function : ", __func__, " : the provided byte_number is invalid");
                    FMC_printRedError(stderr, err_invalidarg);
                }
                FMC_setError(FMC_ERR_INVALID_ARGUMENT, "The provided byte_number is invalid");
                mi_free(c);
                return NULL;
                FMC_UNREACHABLE;
            }
            else c->byteNumber = 4;
            break;
        default:
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_invalidarg, 3, "ERROR : In function : ", __func__, " : the provided byte_number is invalid");
                FMC_printRedError(stderr, err_invalidarg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "The provided byte_number is invalid");
            mi_free(c);
            return NULL;
            FMC_UNREACHABLE;
    }
    c->isNull = char_is_null;
    // Assert that already is zeroed-out by mi_zalloc
    FMC_UNREACHABLE_ASSERT(c->comp.byte1 == 0);
    FMC_UNREACHABLE_ASSERT(c->comp.byte2 == 0);
    FMC_UNREACHABLE_ASSERT(c->comp.byte3 == 0);
    FMC_UNREACHABLE_ASSERT(c->comp.byte4 == 0);
    
    if (!char_is_null) 
    {
        c->comp.byte1 = bytes[0];
        if (c->byteNumber > 1) c->comp.byte2 = bytes[1];
        if (c->byteNumber > 2) c->comp.byte3 = bytes[2];
        if (c->byteNumber > 3) c->comp.byte4 = bytes[3];
    }

    return c;
}

/* FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char FMC_getChar(FMC_File *file)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (file == NULL)
    {
        FMC_makeMsg(err_nullarg, 3, "ERROR : In function : ", __func__, " : the provided file pointer is NULL");
        FMC_printRedError(stderr, err_nullarg);
    }
    #pragma GCC diagnostic pop
    if (!file->isOpened || file->name)
    {

    }

} */