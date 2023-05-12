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

extern FMC_FUNC_INLINE FMC_Bool FMC_checkEncoding(const FMC_String* const str);
extern FMC_FUNC_INLINE FMC_FUNC_NONNULL(1) void FMC_removeTrailNullChars(FMC_String* const str);

FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_JUST_MALLOC FMC_String* FMC_allocStr(FMC_Char* const* const chars, uint64_t size)
{
    FMC_String *str = calloc(1, sizeof(FMC_String));
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
            str->lastChar->prev = *chars;
            str->firstChar->next = *chars;
            str->size = 1;
            goto end;
            FMC_UNREACHABLE;
        default:
            str->firstChar = *chars;
            FMC_Char* tmp_ch = str->firstChar;
            FMC_Encodings enc = tmp_ch->encoding;
            for (uint64_t i = 1; i < size; i++)
            {
                FMC_Char* tmp_ch2 = *(chars + i);
                if (tmp_ch2->encoding != enc)
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_invalid_encoding, 3, "ERROR : In function : ", __func__, " : the provided string contains characters with different encodings");
                        FMC_printRedError(stderr, err_invalid_encoding);
                    }
                    FMC_freeStr(str);
                    return NULL;
                    FMC_UNREACHABLE;
                }
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

FMC_SHARED FMC_FUNC_NONNULL(1) void FMC_freeStr(FMC_String* str)
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
    FMC_Char* ch = NULL;
    goto jmp_loop; // To avoid a NULL pointer dereference
    while (ch != str->lastChar)
    {
jmp_loop:
        ch = str->firstChar;
        if (ch == NULL) goto free_str;
        str->firstChar = ch->next;
        str->size--;
        free(ch);
    }
free_str:
    free(str);
    return;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_NONNULL(1) FMC_Char* FMC_getCharAt(FMC_String* str, uint64_t index)
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
    if (str1->firstChar->encoding != str2->firstChar->encoding) 
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_encoding, 3, "ERROR : In function : ", __func__, " : the provided strings have different encodings");
            FMC_printRedError(stderr, err_encoding);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "In function : FMC_append_str : the provided strings have different encodings");
        return NULL;
        FMC_UNREACHABLE;
    }
    if (!FMC_checkEncoding(str1) || !FMC_checkEncoding(str2))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_invalid_encoding, 3, "ERROR : In function : ", __func__, " : the provided string contains characters with invalid encodings");
            FMC_printRedError(stderr, err_invalid_encoding);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "In function : FMC_append_str : the provided string contains characters with invalid encodings");
        return NULL;
        FMC_UNREACHABLE;
    }
    FMC_removeTrailNullChars(str1);
    FMC_removeTrailNullChars(str2);
    FMC_Char* last_ch = NULL;
    FMC_UNREACHABLE_ASSERT(str1->lastChar != NULL);
    if (str1->lastChar->isNull) 
    {
        last_ch = str1->lastChar->prev;
        free(str1->lastChar);
        last_ch->next = NULL;
        str1->lastChar = last_ch;
        str1->size--;
    }
    else last_ch = str1->lastChar;    
    FMC_Char* ch = NULL;
    for (uint64_t i = 0; i < str2->size; i++)
    {
        ch = FMC_getCharAt(str2, i);
        if (ch == NULL || ch->isNull) break;
        last_ch->next = calloc(1, sizeof(FMC_Char));
        FMC_UNREACHABLE_ASSERT(last_ch->next != NULL);
        last_ch->next->prev = last_ch;
        last_ch->next->next = NULL;
        last_ch->next->encoding = ch->encoding;
        last_ch->next->comp = ch->comp;
        last_ch->next->isNull = ch->isNull;
        last_ch->next->byteNumber = ch->byteNumber;

        last_ch = last_ch->next;
    }
    // Append the null character
    /* last_ch->next = calloc(1, sizeof(FMC_Char));
    FMC_UNREACHABLE_ASSERT(last_ch->next != NULL);
    last_ch->next->prev = last_ch;
    last_ch->next->next = NULL;
    last_ch->next->encoding = last_ch->encoding;
    last_ch->next->comp = FMC_CHARCOMP_NULL;
    last_ch->next->isNull = FMC_TRUE;
    last_ch->next->byteNumber = 0; */
    str1->lastChar = last_ch;
    str1->size += str2->size;
    if (!str1->lastChar->isNull)
    {
        str1->lastChar->next = calloc(1, sizeof(FMC_Char));
        FMC_UNREACHABLE_ASSERT(str1->lastChar->next != NULL);
        str1->lastChar->next->prev = str1->lastChar;
        str1->lastChar->next->next = NULL;
        str1->lastChar->next->encoding = str1->lastChar->encoding;
        str1->lastChar->next->comp = FMC_CHARCOMP_NULL;
        str1->lastChar->next->isNull = FMC_TRUE;
        str1->lastChar->next->byteNumber = 0;
        str1->size++;
        str1->lastChar = str1->lastChar->next;
    }
    return str1;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1, 2) FMC_String* FMC_append_ch(FMC_String* str, FMC_Char* ch)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!str || !ch) 
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_nullarg, 3, "ERROR : In function : ", __func__, " : the provided pointer is NULL");
            FMC_printRedError(stderr, err_nullarg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "In function : FMC_append_ch : the provided pointer is NULL");
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    if (!str->firstChar || !str->lastChar)
    {
        str->firstChar = ch;
        str->lastChar = ch;
        str->firstChar->next = ch;
        str->lastChar->prev = ch;
        str->size = 1;
        return str;
        FMC_UNREACHABLE;
    }
    if (!FMC_checkEncoding(str))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_encoding, 3, "ERROR : In function : ", __func__, " : the provided string do not have a coherent encoding");
            FMC_printRedError(stderr, err_encoding);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "In function : FMC_append_ch : the provided string do not have a coherent encoding");
        return NULL;
        FMC_UNREACHABLE;
    }
    else if (str->firstChar->encoding != ch->encoding) 
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_encoding, 3, "ERROR : In function : ", __func__, " : the provided string and the provided character have different encodings");
            FMC_printRedError(stderr, err_encoding);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "In function : FMC_append_ch : the provided string and the provided character have different encodings");
        return NULL;
        FMC_UNREACHABLE;
    }
    FMC_removeTrailNullChars(str);
    FMC_Char* last_ch = NULL;
    FMC_UNREACHABLE_ASSERT(str->lastChar != NULL);
    if (str->size == 1) goto one_ch_str;
    if (str->lastChar->isNull) 
    {
        last_ch = str->lastChar->prev;
        free(str->lastChar);
        last_ch->next = NULL;
        str->size--;
        str->lastChar = last_ch;
    }
    else last_ch = str->lastChar;
    last_ch->next = calloc(1, sizeof(FMC_Char));
    FMC_UNREACHABLE_ASSERT(last_ch->next != NULL);
    last_ch->next->prev = last_ch;
    last_ch->next->next = NULL;
    last_ch->next->encoding = ch->encoding;
    last_ch->next->comp = ch->comp;
    last_ch->next->isNull = ch->isNull;
    last_ch->next->byteNumber = ch->byteNumber;
    str->lastChar = last_ch->next;
    str->size++;
    if (!str->lastChar->isNull)
    {
        str->lastChar->next = calloc(1, sizeof(FMC_Char));
        FMC_UNREACHABLE_ASSERT(str->lastChar->next != NULL);
        str->lastChar->next->prev = str->lastChar;
        str->lastChar->next->next = NULL;
        str->lastChar->next->encoding = str->lastChar->encoding;
        str->lastChar->next->comp = FMC_CHARCOMP_NULL;
        str->lastChar->next->isNull = FMC_TRUE;
        str->lastChar->next->byteNumber = 0;
        str->size++;
        str->lastChar = str->lastChar->next;
    }
    goto end;

one_ch_str:
    if (str->firstChar->isNull)
    {
        FMC_Char* new_ch = calloc(1, sizeof(FMC_Char));
        FMC_UNREACHABLE_ASSERT(new_ch != NULL);
        new_ch->prev = NULL;
        new_ch->next = str->firstChar;
        new_ch->encoding = ch->encoding;
        new_ch->comp = ch->comp;
        new_ch->isNull = ch->isNull;
        new_ch->byteNumber = ch->byteNumber;
        str->firstChar = new_ch;
        str->lastChar = new_ch->next;
        str->lastChar->prev = new_ch;
        str->lastChar->next = NULL;
        str->size++;
        if (!str->lastChar->isNull)
        {
            str->lastChar->next = calloc(1, sizeof(FMC_Char));
            FMC_UNREACHABLE_ASSERT(str->lastChar->next != NULL);
            str->lastChar->next->prev = str->lastChar;
            str->lastChar->next->next = NULL;
            str->lastChar->next->encoding = str->lastChar->encoding;
            str->lastChar->next->comp = FMC_CHARCOMP_NULL;
            str->lastChar->next->isNull = FMC_TRUE;
            str->lastChar->next->byteNumber = 0;
            str->size++;
            str->lastChar = str->lastChar->next;
        }
    }
    else
    {
        str->firstChar->next = calloc(1, sizeof(FMC_Char));
        FMC_UNREACHABLE_ASSERT(str->firstChar->next != NULL);
        str->firstChar->next->prev = str->firstChar;
        str->firstChar->next->next = NULL;
        str->firstChar->next->encoding = ch->encoding;
        str->firstChar->next->comp = ch->comp;
        str->firstChar->next->isNull = ch->isNull;
        str->firstChar->next->byteNumber = ch->byteNumber;
        str->lastChar = str->firstChar->next;
        str->size++;
        if (!str->lastChar->isNull)
        {
            str->lastChar->next = calloc(1, sizeof(FMC_Char));
            FMC_UNREACHABLE_ASSERT(str->lastChar->next != NULL);
            str->lastChar->next->prev = str->lastChar;
            str->lastChar->next->next = NULL;
            str->lastChar->next->encoding = str->lastChar->encoding;
            str->lastChar->next->comp = FMC_CHARCOMP_NULL;
            str->lastChar->next->isNull = FMC_TRUE;
            str->lastChar->next->byteNumber = 0;
            str->size++;
            str->lastChar = str->lastChar->next;
        }
    }
    goto end;


end:
    return str;
    FMC_UNREACHABLE;
}

/* FMC_SHARED FMC_FUNC_NONNULL(1) FMC_String* FMC_cloneStr(FMC_String* str)
{
    
} */