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

#include <assert.h>

#include "FMC_strings.h"

FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_MALLOC(mi_free) FMC_String* FMC_allocStr(FMC_Char* const* chars, uint64_t size)
{
    FMC_String *str = mi_zalloc(sizeof(FMC_String));
    FMC_UNREACHABLE_ASSERT(str != NULL);
    FMC_UNREACHABLE_ASSERT(str->firstChar == NULL);
    FMC_UNREACHABLE_ASSERT(str->lastChar == NULL);
    if (!chars || !*chars) goto end;
    switch (size)
    {
        case 0:
            str->size = 0;
            goto end;
            FMC_UNREACHABLE;
        case 1:
            str->firstChar = *chars;
            str->lastChar = *chars;
            str->size = 1;
            goto end;
            FMC_UNREACHABLE;
        default:
            str->firstChar = *chars;
            FMC_Char* tmp_ch = str->firstChar;
            for (uint64_t i = 1; i < size; i++)
            {
                FMC_Char* tmp_ch2 = *(chars + i);
                tmp_ch->next = tmp_ch2;
                tmp_ch2->prev = tmp_ch;
                tmp_ch = tmp_ch2;
            }
            str->lastChar = tmp_ch;
            str->size = size;
            goto end;
            FMC_UNREACHABLE;
    }
end:
    return str;
    FMC_UNREACHABLE;
}

extern FMC_FUNC_INLINE FMC_FUNC_NONNULL(1) void FMC_freeStr(FMC_String* str);

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_Char* FMC_getCharAt(FMC_String* str, uint64_t index)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!str) 
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_nullarg, 3, "ERROR : In function : ", __func__, " : the provided pointer is NULL");
            FMC_printRedError(stderr, err_nullarg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "In function : FMC_getCharAt : the provided pointer is NULL");
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    if (!str->firstChar || !str->lastChar) return NULL; // Empty string

    if (index == 0 || index <= str->size / 2) goto from_first;
    else goto from_last;

    FMC_Char* ch = NULL;
from_first:
    ch = str->firstChar;
    for (uint64_t i = 0; i < index; i++)
    {
        ch = ch->next;
    }
    goto end;
    FMC_UNREACHABLE;

from_last:
    ch = str->lastChar;
    for (uint64_t i = str->size - 1; i > index; i--)
    {
        ch = ch->prev;
    }
    goto end;
    FMC_UNREACHABLE;

end:
    return ch;
    FMC_UNREACHABLE;
}

// TODO: Finish this function
// TODO: Make it generic and make it accept a FMC_Char* as a parameter too
FMC_SHARED FMC_FUNC_NONNULL(1, 2) FMC_String* FMC_append_str(FMC_String* str1, FMC_String* str2) 
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!str1 || !str2) 
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_nullarg, 3, "ERROR : In function : ", __func__, " : the provided pointer is NULL");
            FMC_printRedError(stderr, err_nullarg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "In function : FMC_append_str : the provided pointer is NULL");
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    if (!str1->firstChar || !str1->lastChar) return str2;
    if (!str2->firstChar || !str2->lastChar) return str1;
    str1->lastChar->next = str2->firstChar;
    str2->firstChar->prev = str1->lastChar;
    str1->lastChar = str2->lastChar;
    str1->size += str2->size;
    return str1;
    FMC_UNREACHABLE;
}