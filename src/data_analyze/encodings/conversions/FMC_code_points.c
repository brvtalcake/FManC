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

#include "FMC_conversions.h"

// TODO: Add more verifications against invalid arguments or invalid UTF-X encoded characters

/*
 * Code points from UTF-8 encoded characters
*/

FMC_SHARED FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF8_FMC_Char_ptr(const FMC_Char* restrict const utf8_char)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf8_char || utf8_char->byteNumber > 4 || utf8_char->encoding != utf8)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF8: Provided argument is NULL or invalid");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF8: Provided argument is NULL or invalid");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if ((utf8_char->comp.byte1 == 0 && utf8_char->comp.byte2 == 0 && utf8_char->comp.byte3 == 0 && utf8_char->comp.byte4 == 0) ||
         utf8_char->byteNumber == 0) return FMC_CODE_POINT_NULL;

    FMC_CodePoint code_point = FMC_CODE_POINT_NULL;
    switch(utf8_char->byteNumber) // byte1 is the least significant byte
    {
        case 1:
            code_point = utf8_char->comp.byte1;
            break;
        case 2:
            code_point = ((utf8_char->comp.byte2 & 0x1F) << 6) | (utf8_char->comp.byte1 & 0x3F);
            break;
        case 3:
            code_point = ((utf8_char->comp.byte3 & 0x0F) << 12) | ((utf8_char->comp.byte2 & 0x3F) << 6) | (utf8_char->comp.byte1 & 0x3F);
            break;
        case 4:
            code_point = ((utf8_char->comp.byte4 & 0x07) << 18) | ((utf8_char->comp.byte3 & 0x3F) << 12) | ((utf8_char->comp.byte2 & 0x3F) << 6) | (utf8_char->comp.byte1 & 0x3F);
            break;
        default:
            FMC_UNREACHABLE;
            return FMC_CODE_POINT_NULL;
    }
    return code_point;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF8_FMC_Char(const FMC_Char utf8_char)
{
    return FMC_codePointFromUTF8_FMC_Char_ptr(&utf8_char);
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF8_FMC_CharComp_ptr(const FMC_CharComp* restrict const utf8_char_comp)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf8_char_comp)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF8: Provided argument is NULL");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF8: Provided argument is NULL");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    if ((utf8_char_comp->byte1 == 0 && utf8_char_comp->byte2 == 0 && utf8_char_comp->byte3 == 0 && utf8_char_comp->byte4 == 0)) 
        return FMC_CODE_POINT_NULL;
    // Calculate the number of encoded bytes, since there is no byteNumber field in FMC_CharComp
    uint8_t byte_number = 0;
    if (utf8_char_comp->byte1 != 0)
    {
        if (utf8_char_comp->byte2 != 0)
        {
            if (utf8_char_comp->byte3 != 0)
            {
                if (utf8_char_comp->byte4 != 0) byte_number = 4;
                else byte_number = 3;
            }
            else byte_number = 2;
        }
        else byte_number = 1;
    }
    else return FMC_CODE_POINT_NULL;

    FMC_CodePoint code_point = FMC_CODE_POINT_NULL;
    switch(byte_number)
    {
        case 1:
            code_point = utf8_char_comp->byte1;
            break;
        case 2:
            code_point = ((utf8_char_comp->byte2 & 0x1F) << 6) | (utf8_char_comp->byte1 & 0x3F);
            break;
        case 3:
            code_point = ((utf8_char_comp->byte3 & 0x0F) << 12) | ((utf8_char_comp->byte2 & 0x3F) << 6) | (utf8_char_comp->byte1 & 0x3F);
            break;
        case 4:
            code_point = ((utf8_char_comp->byte4 & 0x07) << 18) | ((utf8_char_comp->byte3 & 0x3F) << 12) 
                       | ((utf8_char_comp->byte2 & 0x3F) << 6)  | (utf8_char_comp->byte1 & 0x3F);
            break;
        default:
            FMC_UNREACHABLE;
            return FMC_CODE_POINT_NULL;
    }
    return code_point;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF8_FMC_CharComp(const FMC_CharComp utf8_char_comp)
{
    return FMC_codePointFromUTF8_FMC_CharComp_ptr(&utf8_char_comp);
}

FMC_SHARED FMC_FUNC_CONST FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF8_uint32_t_ptr(const uint32_t* restrict const raw_utf8_encoded_char)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!raw_utf8_encoded_char)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF8: Provided argument is NULL");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF8: Provided argument is NULL");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    if (*raw_utf8_encoded_char == 0) return FMC_CODE_POINT_NULL;
    // Calculate the number of encoded bytes
    uint8_t byte_number = 0;
    if (*raw_utf8_encoded_char != 0)
    {
        if ((*raw_utf8_encoded_char & 0x000000FF) != 0)
        {
            if ((*raw_utf8_encoded_char & 0x0000FF00) != 0)
            {
                if ((*raw_utf8_encoded_char & 0x00FF0000) != 0) byte_number = 4;
                else byte_number = 3;
            }
            else byte_number = 2;
        }
        else byte_number = 1;
    }
    else return FMC_CODE_POINT_NULL;

    FMC_CodePoint code_point = FMC_CODE_POINT_NULL;
    switch(byte_number)
    {
        case 1:
            code_point = *raw_utf8_encoded_char;
            break;
        case 2:
            code_point = ((*raw_utf8_encoded_char & 0x00001F00) << 6) | (*raw_utf8_encoded_char & 0x0000003F);
            break;
        case 3:
            code_point = ((*raw_utf8_encoded_char & 0x000F0000) << 12) | ((*raw_utf8_encoded_char & 0x00003F00) << 6) 
                       | (*raw_utf8_encoded_char & 0x0000003F);
            break;
        case 4:
            code_point = ((*raw_utf8_encoded_char & 0x07000000) << 18) | ((*raw_utf8_encoded_char & 0x003F0000) << 12) 
                       | ((*raw_utf8_encoded_char & 0x00003F00) << 6)  | (*raw_utf8_encoded_char & 0x0000003F);
            break;
        default:
            FMC_UNREACHABLE;
            return FMC_CODE_POINT_NULL;
    }
    return code_point;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_CONST FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF8_uint32_t(const uint32_t raw_utf8_encoded_char)
{
    return FMC_codePointFromUTF8_uint32_t_ptr(&raw_utf8_encoded_char);
}

/*
 * Code points from UTF-16LE encoded characters
*/

FMC_SHARED FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF16LE_FMC_Char_ptr(const FMC_Char* restrict const utf16le_char)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf16le_char || utf16le_char->byteNumber > 4 || utf16le_char->encoding != utf16_le)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Provided argument is NULL or invalid");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF16LE: Provided argument is NULL or invalid");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    if ((utf16le_char->comp.byte1 == 0 && utf16le_char->comp.byte2 == 0 && utf16le_char->comp.byte3 == 0 &&
         utf16le_char->comp.byte4 == 0) || utf16le_char->byteNumber == 0) return FMC_CODE_POINT_NULL;
    
    FMC_CodePoint code_point = FMC_CODE_POINT_NULL;
    switch(utf16le_char->byteNumber)
    {
        case 2:
            code_point = utf16le_char->comp.byte2 | (utf16le_char->comp.byte1 << 8);
            if (code_point >= 0xD800 && code_point <= 0xDFFF)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Invalid UTF-16LE character");
                    FMC_printRedError(stderr, err_inv_arg);
                }
                FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF16LE: Invalid UTF-16LE character");
                return FMC_CODE_POINT_NULL;
                FMC_UNREACHABLE;
            }
            break;
        case 4:
            code_point = 0x10000;
            if ((utf16le_char->comp.byte1 | (utf16le_char->comp.byte2 << 8)) < 0xD800 || 
                (utf16le_char->comp.byte1 | (utf16le_char->comp.byte2 << 8)) > 0xDBFF)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                    FMC_printRedError(stderr, err_inv_arg);
                }
                FMC_setError(FMC_ERR_UTF, "FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                return FMC_CODE_POINT_NULL;
                FMC_UNREACHABLE;
            }
            if ((utf16le_char->comp.byte3 | (utf16le_char->comp.byte4 << 8)) < 0xDC00 || 
                (utf16le_char->comp.byte3 | (utf16le_char->comp.byte4 << 8)) > 0xDFFF)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                    FMC_printRedError(stderr, err_inv_arg);
                }
                FMC_setError(FMC_ERR_UTF, "FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                return FMC_CODE_POINT_NULL;
                FMC_UNREACHABLE;
            }
            code_point += ((utf16le_char->comp.byte1 | (utf16le_char->comp.byte2 << 8)) & 0x03FF) << 10;
            code_point += (utf16le_char->comp.byte3 | (utf16le_char->comp.byte4 << 8)) & 0x03FF;
            break;
        default:
            return FMC_CODE_POINT_NULL; // Wrong byte number
            FMC_UNREACHABLE;
    }
    return code_point;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF16LE_FMC_Char(const FMC_Char utf16le_char)
{
    return FMC_codePointFromUTF16LE_FMC_Char_ptr(&utf16le_char);
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF16LE_FMC_CharComp_ptr(const FMC_CharComp* restrict const utf16le_char_comp)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf16le_char_comp)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Provided argument is NULL");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF16LE: Provided argument is NULL");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    if ((utf16le_char_comp->byte1 == 0 && utf16le_char_comp->byte2 == 0 && utf16le_char_comp->byte3 == 0 &&
         utf16le_char_comp->byte4 == 0)) return FMC_CODE_POINT_NULL;
    
    FMC_CodePoint code_point = FMC_CODE_POINT_NULL;
    if (utf16le_char_comp->byte3 == 0 && utf16le_char_comp->byte4 == 0)
    {
        code_point = utf16le_char_comp->byte2 | (utf16le_char_comp->byte1 << 8);
    }
    else
    {
        code_point = 0x10000;
        if ((utf16le_char_comp->byte1 | (utf16le_char_comp->byte2 << 8)) < 0xD800 || 
            (utf16le_char_comp->byte1 | (utf16le_char_comp->byte2 << 8)) > 0xDBFF)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                FMC_printRedError(stderr, err_inv_arg);
            }
            FMC_setError(FMC_ERR_UTF, "FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
            return FMC_CODE_POINT_NULL;
            FMC_UNREACHABLE;
        }
        if ((utf16le_char_comp->byte3 | (utf16le_char_comp->byte4 << 8)) < 0xDC00 || 
            (utf16le_char_comp->byte3 | (utf16le_char_comp->byte4 << 8)) > 0xDFFF)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                FMC_printRedError(stderr, err_inv_arg);
            }
            FMC_setError(FMC_ERR_UTF, "FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
            return FMC_CODE_POINT_NULL;
            FMC_UNREACHABLE;
        }
        code_point += ((utf16le_char_comp->byte1 | (utf16le_char_comp->byte2 << 8)) & 0x03FF) << 10;
        code_point += (utf16le_char_comp->byte3 | (utf16le_char_comp->byte4 << 8)) & 0x03FF;
    }
    return code_point;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF16LE_FMC_CharComp(const FMC_CharComp utf16le_char_comp)
{
    return FMC_codePointFromUTF16LE_FMC_CharComp_ptr(&utf16le_char_comp);
}

FMC_SHARED FMC_FUNC_CONST FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF16LE_uint32_t_ptr(const uint32_t* restrict const raw_utf16le_char)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!raw_utf16le_char)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Provided argument is NULL");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF16LE: Provided argument is NULL");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    if (*raw_utf16le_char == 0) return FMC_CODE_POINT_NULL;
    
    FMC_CodePoint code_point = FMC_CODE_POINT_NULL;
    if ((*raw_utf16le_char & 0xFFFF0000) == 0)
    {
        code_point = (*raw_utf16le_char & 0xFF00) >> 8 | (*raw_utf16le_char & 0x00FF) << 8;
    }
    else
    {
        code_point = 0x10000;
        if ((*raw_utf16le_char & 0xFFFF) < 0xD800 || 
            (*raw_utf16le_char & 0xFFFF) > 0xDBFF)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                FMC_printRedError(stderr, err_inv_arg);
            }
            FMC_setError(FMC_ERR_UTF, "FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
            return FMC_CODE_POINT_NULL;
            FMC_UNREACHABLE;
        }
        if ((*raw_utf16le_char & 0xFFFF0000) < 0xDC000000 || 
            (*raw_utf16le_char & 0xFFFF0000) > 0xDFFF0000)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                FMC_printRedError(stderr, err_inv_arg);
            }
            FMC_setError(FMC_ERR_UTF, "FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
            return FMC_CODE_POINT_NULL;
            FMC_UNREACHABLE;
        }
        code_point += ((*raw_utf16le_char & 0xFFFF) & 0x03FF) << 10;
        code_point += ((*raw_utf16le_char & 0xFFFF0000) & 0x03FF0000) >> 16;
    }
    return code_point;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_CONST FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF16LE_uint32_t(const uint32_t raw_utf16le_char)
{
    return FMC_codePointFromUTF16LE_uint32_t_ptr(&raw_utf16le_char);
}

/*
 * Code point from UTF-16BE encoded character
*/

/* FMC_SHARED FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF16BE */