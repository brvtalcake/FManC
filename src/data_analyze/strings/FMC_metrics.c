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

#include <limits.h>
#include <string.h>

#include "../encodings/conversions/FMC_conversions.h"
#include "FMC_strings.h"

static FMC_FUNC_COLD void FMC_swapPtrs(int64_t** ptr1, int64_t** ptr2)
{
    int64_t* tmp = *ptr1;
    *ptr1 = *ptr2;
    *ptr2 = tmp;
}

FMC_SHARED FMC_FUNC_COLD int64_t FMC_getLevenshtein_coeffs(FMC_String* str1, FMC_String* str2, int64_t* coeffs)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!str1 || !str2)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_nullarg, 3, "ERROR: In function: ", __func__, ": one or both of arguments is (or are) null");
            FMC_printRedError(stderr, err_nullarg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_getLevenshtein: one or both of arguments is (or are) null");
        return -1;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    // if (!FMC_isStrConsistent(str1) || ...) ... 
    if (!str1->firstChar || !str1->lastChar)
    {
        return ((!str2->firstChar && !str2->lastChar) || str2->firstChar->isNull || !str2->size) ? 0 : ((str2->size > INT64_MAX) ? FMC_MAKE_I64(-2) : (int64_t)str2->size);
        FMC_UNREACHABLE;
    }
    if (!str2->firstChar || !str2->lastChar)
    {
        return ((!str1->firstChar && !str1->lastChar) || str1->firstChar->isNull || !str1->size) ? 0 : ((str1->size > INT64_MAX) ? FMC_MAKE_I64(-2) : (int64_t)str1->size);
        FMC_UNREACHABLE;
    }
    FMC_removeTrailNullChars(str1);
    FMC_removeTrailNullChars(str2);
    if (!FMC_checkEncoding(str1) || !FMC_checkEncoding(str2))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_utf, 3, "ERROR: In function: ", __func__, ": one or both of the provided string are not consistent");
            FMC_printRedError(stderr, err_utf);
        }
        FMC_setError(FMC_ERR_ENC, "ERROR: In function: FMC_getLevenshtein: one or both of the provided string are not consistent");
        return -1;
        FMC_UNREACHABLE;
    }

    int64_t result = 0;
    if (!(str1->firstChar->encoding == str2->firstChar->encoding))
    {
        FMC_CodePoint str1_code_points[str1->size], str2_code_points[str2->size];
        memset(str1_code_points, 0, FMC_arrSize(str1_code_points));
        memset(str2_code_points, 0, FMC_arrSize(str2_code_points));
        uint64_t measured_size1 = 0, measured_size2 = 0;
        for (uint64_t i = 0; i < str1->size; ++i)
        {
            FMC_UNREACHABLE_ASSERT(i < str1->size);
            FMC_Bool is_end_of_str = FMC_FALSE;
            switch (str1->firstChar->encoding)
            {
                case ascii:
                {
                    FMC_Char* current_char = FMC_getCharAt(str1, i);
                    if (current_char == NULL)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_getCharAt failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_getCharAt failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char->byteNumber != 1)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_utf, 3, "ERROR: In function: ", __func__, ": str1 is not consistent");
                            FMC_printRedError(stderr, err_utf);
                        }
                        FMC_setError(FMC_ERR_ENC, "ERROR: In function: FMC_getLevenshtein: str1 is not consistent");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    str1_code_points[i] = current_char->comp.byte0;
                    if (current_char == str1->lastChar) is_end_of_str = FMC_TRUE;
                    break;
                }

                case utf8_bom:
                    FMC_STMT_FALLTHROUGH;
                case utf8:
                {
                    FMC_Char* current_char = FMC_getCharAt(str1, i);
                    if (current_char == NULL)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_getCharAt failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_getCharAt failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    str1_code_points[i] = FMC_codePointFromUTF8(current_char);
                    if (str1_code_points[i] == FMC_CODE_POINT_NULL && !current_char->isNull)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_codePointFromUTF8 failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_codePointFromUTF8 failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char == str1->lastChar) is_end_of_str = FMC_TRUE;
                    break;
                }

                case utf16_le:
                {
                    FMC_Char* current_char = FMC_getCharAt(str1, i);
                    if (current_char == NULL)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_getCharAt failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_getCharAt failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char->byteNumber != 2 && current_char->byteNumber != 4)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_utf, 3, "ERROR: In function: ", __func__, ": str1 is not consistent");
                            FMC_printRedError(stderr, err_utf);
                        }
                        FMC_setError(FMC_ERR_ENC, "ERROR: In function: FMC_getLevenshtein: str1 is not consistent");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    str1_code_points[i] = FMC_codePointFromUTF16LE(current_char);
                    if (str1_code_points[i] == FMC_CODE_POINT_NULL && !current_char->isNull)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_codePointFromUTF8 failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_codePointFromUTF8 failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char == str1->lastChar) is_end_of_str = FMC_TRUE;
                    break;
                }

                case utf16_be:
                {
                    FMC_Char* current_char = FMC_getCharAt(str1, i);
                    if (current_char == NULL)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_getCharAt failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_getCharAt failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char->byteNumber != 2 && current_char->byteNumber != 4)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_utf, 3, "ERROR: In function: ", __func__, ": str1 is not consistent");
                            FMC_printRedError(stderr, err_utf);
                        }
                        FMC_setError(FMC_ERR_ENC, "ERROR: In function: FMC_getLevenshtein: str1 is not consistent");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    str1_code_points[i] = FMC_codePointFromUTF16BE(current_char);
                    if (str1_code_points[i] == FMC_CODE_POINT_NULL && !current_char->isNull)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_codePointFromUTF8 failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_codePointFromUTF8 failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char == str1->lastChar) is_end_of_str = FMC_TRUE;
                    break;
                }

                case utf32_le:
                {
                    FMC_Char* current_char = FMC_getCharAt(str1, i);
                    if (current_char == NULL)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_getCharAt failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_getCharAt failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char->byteNumber != 4)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_utf, 3, "ERROR: In function: ", __func__, ": str1 is not consistent");
                            FMC_printRedError(stderr, err_utf);
                        }
                        FMC_setError(FMC_ERR_ENC, "ERROR: In function: FMC_getLevenshtein: str1 is not consistent");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    str1_code_points[i] = FMC_codePointFromUTF32LE(current_char);
                    if (str1_code_points[i] == FMC_CODE_POINT_NULL && !current_char->isNull)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_codePointFromUTF8 failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_codePointFromUTF8 failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char == str1->lastChar) is_end_of_str = FMC_TRUE;
                    break;
                }

                case utf32_be:
                {
                    FMC_Char* current_char = FMC_getCharAt(str1, i);
                    if (current_char == NULL)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_getCharAt failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_getCharAt failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char->byteNumber != 4)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_utf, 3, "ERROR: In function: ", __func__, ": str1 is not consistent");
                            FMC_printRedError(stderr, err_utf);
                        }
                        FMC_setError(FMC_ERR_ENC, "ERROR: In function: FMC_getLevenshtein: str1 is not consistent");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    str1_code_points[i] = FMC_codePointFromUTF32BE(current_char);
                    if (str1_code_points[i] == FMC_CODE_POINT_NULL && !current_char->isNull)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_codePointFromUTF8 failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_codePointFromUTF8 failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char == str1->lastChar) is_end_of_str = FMC_TRUE;
                    break;
                }
                default:
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_int, 3, "ERROR: In function: ", __func__, ": str1 encoding value is not supported");
                        FMC_printRedError(stderr, err_int);
                    }
                    FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_getLevenshtein: str1 encoding value is not supported");
                    return -1;
                    FMC_UNREACHABLE;
                }
            }
            measured_size1++;
            if (is_end_of_str) break;
        }

        // Do the same for str2
        for (uint64_t i = 0; i < str2->size; ++i)
        {
            FMC_UNREACHABLE_ASSERT(i < str2->size);
            FMC_Bool is_end_of_str = FMC_FALSE;
            switch (str2->firstChar->encoding)
            {
                case ascii:
                {
                    FMC_Char* current_char = FMC_getCharAt(str2, i);
                    if (current_char == NULL)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_getCharAt failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_getCharAt failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char->byteNumber != 1)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_utf, 3, "ERROR: In function: ", __func__, ": str2 is not consistent");
                            FMC_printRedError(stderr, err_utf);
                        }
                        FMC_setError(FMC_ERR_ENC, "ERROR: In function: FMC_getLevenshtein: str2 is not consistent");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    str2_code_points[i] = current_char->comp.byte0;
                    if (current_char == str2->lastChar) is_end_of_str = FMC_TRUE;
                    break;
                }
                
                case utf8_bom:
                    FMC_STMT_FALLTHROUGH;
                case utf8:
                {
                    FMC_Char* current_char = FMC_getCharAt(str2, i);
                    if (current_char == NULL)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_getCharAt failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_getCharAt failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    str2_code_points[i] = FMC_codePointFromUTF8(current_char);
                    if (str2_code_points[i] == FMC_CODE_POINT_NULL && !current_char->isNull)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_codePointFromUTF8 failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_codePointFromUTF8 failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char == str2->lastChar) is_end_of_str = FMC_TRUE;
                    break;
                }

                case utf16_le:
                {
                    FMC_Char* current_char = FMC_getCharAt(str2, i);
                    if (current_char == NULL)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_getCharAt failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_getCharAt failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char->byteNumber != 2 && current_char->byteNumber != 4)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_utf, 3, "ERROR: In function: ", __func__, ": str2 is not consistent");
                            FMC_printRedError(stderr, err_utf);
                        }
                        FMC_setError(FMC_ERR_ENC, "ERROR: In function: FMC_getLevenshtein: str2 is not consistent");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    str2_code_points[i] = FMC_codePointFromUTF16LE(current_char);
                    if (str2_code_points[i] == FMC_CODE_POINT_NULL && !current_char->isNull)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_codePointFromUTF8 failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_codePointFromUTF8 failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char == str2->lastChar) is_end_of_str = FMC_TRUE;
                    break;
                }

                case utf16_be:
                {
                    FMC_Char* current_char = FMC_getCharAt(str2, i);
                    if (current_char == NULL)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_getCharAt failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_getCharAt failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char->byteNumber != 2 && current_char->byteNumber != 4)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_utf, 3, "ERROR: In function: ", __func__, ": str2 is not consistent");
                            FMC_printRedError(stderr, err_utf);
                        }
                        FMC_setError(FMC_ERR_ENC, "ERROR: In function: FMC_getLevenshtein: str2 is not consistent");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    str2_code_points[i] = FMC_codePointFromUTF16BE(current_char);
                    if (str2_code_points[i] == FMC_CODE_POINT_NULL && !current_char->isNull)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_codePointFromUTF8 failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_codePointFromUTF8 failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char == str2->lastChar) is_end_of_str = FMC_TRUE;
                    break;
                }
                
                case utf32_le:
                {
                    FMC_Char* current_char = FMC_getCharAt(str2, i);
                    if (current_char == NULL)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_getCharAt failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_getCharAt failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char->byteNumber != 4)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_utf, 3, "ERROR: In function: ", __func__, ": str2 is not consistent");
                            FMC_printRedError(stderr, err_utf);
                        }
                        FMC_setError(FMC_ERR_ENC, "ERROR: In function: FMC_getLevenshtein: str2 is not consistent");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    str2_code_points[i] = FMC_codePointFromUTF32LE(current_char);
                    if (str2_code_points[i] == FMC_CODE_POINT_NULL && !current_char->isNull)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_codePointFromUTF8 failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_codePointFromUTF8 failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char == str2->lastChar) is_end_of_str = FMC_TRUE;
                    break;
                }
                
                case utf32_be:
                {
                    FMC_Char* current_char = FMC_getCharAt(str2, i);
                    if (current_char == NULL)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_getCharAt failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_getCharAt failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char->byteNumber != 4)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_utf, 3, "ERROR: In function: ", __func__, ": str2 is not consistent");
                            FMC_printRedError(stderr, err_utf);
                        }
                        FMC_setError(FMC_ERR_ENC, "ERROR: In function: FMC_getLevenshtein: str2 is not consistent");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    str2_code_points[i] = FMC_codePointFromUTF32BE(current_char);
                    if (str2_code_points[i] == FMC_CODE_POINT_NULL && !current_char->isNull)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_codePointFromUTF8 failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "INTERNAL ERROR: In function: FMC_getLevenshtein: FMC_codePointFromUTF8 failed");
                        return -1;
                        FMC_UNREACHABLE;
                    }
                    if (current_char == str2->lastChar) is_end_of_str = FMC_TRUE;
                    break;
                }

                default:
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_enc, 3, "ERROR: In function: ", __func__, ": str2's encoding is not supported");
                        FMC_printRedError(stderr, err_enc);
                    }
                    FMC_setError(FMC_ERR_ENC, "ERROR: In function: FMC_getLevenshtein: str2's encoding is not supported");
                    return -1;
                    FMC_UNREACHABLE;
                }
            }
            measured_size2++;
            if (is_end_of_str) break;
        }

        if (measured_size1 != str1->size)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_str1, 3, "ERROR: In function: ", __func__, ": str1's size does not match its effective size");
                FMC_printRedError(stderr, err_str1);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_getLevenshtein: str1's size does not match its effective size");
            return -1;
            FMC_UNREACHABLE;
        }
        if (measured_size2 != str2->size)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_str2, 3, "ERROR: In function: ", __func__, ": str2's size does not match its effective size");
                FMC_printRedError(stderr, err_str2);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_getLevenshtein: str2's size does not match its effective size");
            return -1;
            FMC_UNREACHABLE;
        }

        int64_t* vect1 = malloc((measured_size2 + 1) * sizeof(int64_t));
        int64_t* vect2 = malloc((measured_size2 + 1) * sizeof(int64_t));
        memset(vect1, 0, measured_size2 + 1);
        memset(vect2, 0, measured_size2 + 1);
        int64_t delete_cost = 0, insert_cost = 0, subst_cost = 0;

        for (uint64_t i = 0; i <= measured_size2; i++)
        {
            FMC_UNREACHABLE_ASSERT(i <= (uint64_t) INT64_MAX);
            vect1[i] = (int64_t) i;
        }

        for (uint64_t i = 0; i < measured_size1; i++)
        {
            FMC_UNREACHABLE_ASSERT(i <= (uint64_t) INT64_MAX);
            vect2[0] = (int64_t) (i + 1);
            for (uint64_t j = 0; j < measured_size2; j++)
            {
                FMC_UNREACHABLE_ASSERT(j <= (uint64_t) INT64_MAX);
                delete_cost = (vect1[j + 1] + 1) * coeffs[0];
                insert_cost = (vect2[j] + 1) * coeffs[1];
                subst_cost = (vect1[j] + (str1_code_points[i] == str2_code_points[j] ? 0 : 1)) * coeffs[2];
                vect2[j + 1] = FMC_min(delete_cost, insert_cost, subst_cost);
            }
            FMC_swapPtrs(&vect1, &vect2);
        }
        result = vect1[measured_size2];
        free(vect1);
        free(vect2);
    }
    else // str1 and str2 have the same encoding, no need to convert to codepoints
    {
        int64_t* vect1 = malloc((str2->size + 1) * sizeof(int64_t));
        int64_t* vect2 = malloc((str2->size + 1) * sizeof(int64_t));
        memset(vect1, 0, str2->size + 1);
        memset(vect2, 0, str2->size + 1);
        int64_t delete_cost = 0, insert_cost = 0, subst_cost = 0;

        for (uint64_t i = 0; i <= str2->size; i++)
        {
            FMC_UNREACHABLE_ASSERT(i <= (uint64_t) INT64_MAX);
            vect1[i] = (int64_t) i;
        }

        for (uint64_t i = 0; i < str1->size; i++)
        {
            FMC_UNREACHABLE_ASSERT(i <= (uint64_t) INT64_MAX);
            vect2[0] = (int64_t) (i + 1);
            for (uint64_t j = 0; j < str2->size; j++)
            {
                FMC_UNREACHABLE_ASSERT(j <= (uint64_t) INT64_MAX);
                delete_cost = (vect1[j + 1] + 1) * coeffs[0];
                insert_cost = (vect2[j] + 1) * coeffs[1];
                FMC_Char* curr_char_str1 = FMC_getCharAt(str1, i);
                FMC_Char* curr_char_str2 = FMC_getCharAt(str2, j);
                subst_cost = (vect1[j] + (FMC_charPtrCompare(curr_char_str1, curr_char_str2) ? 0 : 1)) * coeffs[2];
                vect2[j + 1] = FMC_min(delete_cost, insert_cost, subst_cost);
            }
            FMC_swapPtrs(&vect1, &vect2);
        }
        result = vect1[str2->size];
        free(vect1);
        free(vect2);
    }
    return result;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_COLD int64_t FMC_getLevenshtein_no_coeffs(FMC_String* str1, FMC_String* str2)
{
    int64_t coeffs[3] = {1, 1, 1};
    return FMC_getLevenshtein(str1, str2, coeffs);
}
