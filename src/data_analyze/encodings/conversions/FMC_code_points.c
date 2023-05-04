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
#include "../../strings/FMC_strings.h"

// TODO: Add more verifications against invalid arguments or invalid UTF-X encoded characters

/*
 * General functions
 */

FMC_FUNC_INLINE extern FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromAny(const void* const any_char, const FMC_Encodings encoding, const unsigned int arg_type_flag);

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

    if ((utf8_char->comp.byte0 == 0 && utf8_char->comp.byte1 == 0 && utf8_char->comp.byte2 == 0 && utf8_char->comp.byte3 == 0) ||
         utf8_char->byteNumber == 0) return FMC_CODE_POINT_NULL;

    FMC_CodePoint code_point = FMC_CODE_POINT_NULL;
    switch(utf8_char->byteNumber) // byte0 is the least significant byte
    {
        case 1:
            code_point = utf8_char->comp.byte0;
            break;
        case 2:
            code_point = ((utf8_char->comp.byte1 & 0x1F) << 6) | (utf8_char->comp.byte0 & 0x3F);
            break;
        case 3:
            code_point = ((utf8_char->comp.byte2 & 0x0F) << 12) | ((utf8_char->comp.byte1 & 0x3F) << 6) | (utf8_char->comp.byte0 & 0x3F);
            break;
        case 4:
            code_point = ((utf8_char->comp.byte3 & 0x07) << 18) | ((utf8_char->comp.byte2 & 0x3F) << 12) | ((utf8_char->comp.byte1 & 0x3F) << 6) | (utf8_char->comp.byte0 & 0x3F);
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
    if ((utf8_char_comp->byte0 == 0 && utf8_char_comp->byte1 == 0 && utf8_char_comp->byte2 == 0 && utf8_char_comp->byte3 == 0)) 
        return FMC_CODE_POINT_NULL;
    // Calculate the number of encoded bytes, since there is no byteNumber field in FMC_CharComp
    uint8_t byte_number = 0;
    if (utf8_char_comp->byte0 != 0)
    {
        if (utf8_char_comp->byte1 != 0)
        {
            if (utf8_char_comp->byte2 != 0)
            {
                if (utf8_char_comp->byte3 != 0) byte_number = 4;
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
            code_point = utf8_char_comp->byte0;
            break;
        case 2:
            code_point = ((utf8_char_comp->byte1 & 0x1F) << 6) | (utf8_char_comp->byte0 & 0x3F);
            break;
        case 3:
            code_point = ((utf8_char_comp->byte2 & 0x0F) << 12) | ((utf8_char_comp->byte1 & 0x3F) << 6) | (utf8_char_comp->byte0 & 0x3F);
            break;
        case 4:
            code_point = ((utf8_char_comp->byte3 & 0x07) << 18) | ((utf8_char_comp->byte2 & 0x3F) << 12) 
                       | ((utf8_char_comp->byte1 & 0x3F) << 6)  | (utf8_char_comp->byte0 & 0x3F);
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

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF8_uint32_t_ptr(const uint32_t* restrict const raw_utf8_encoded_char)
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
                if ((*raw_utf8_encoded_char & 0x00FF0000) != 0)
                {
                    if ((*raw_utf8_encoded_char & 0xFF000000) != 0) byte_number = 4;
                    else byte_number = 3;
                }
                else byte_number = 2;
            }
            else byte_number = 1;
        }
        else return FMC_CODE_POINT_NULL;
    }
    else return FMC_CODE_POINT_NULL;

    FMC_CodePoint code_point = FMC_CODE_POINT_NULL;
    switch(byte_number)
    {
        case 1:
            code_point = *raw_utf8_encoded_char & FMC_MAKE_UI32(0x7F);
            break;
        case 2:
            code_point = ((*raw_utf8_encoded_char & (FMC_MAKE_UI32(0b11111) << 8)) >> 2) 
                       |  (*raw_utf8_encoded_char & (FMC_MAKE_UI32(0b111111)));
            break;
        case 3:
            code_point = ((*raw_utf8_encoded_char & (FMC_MAKE_UI32(0b1111) << 16)) >> 4) 
                       | ((*raw_utf8_encoded_char & (FMC_MAKE_UI32(0b111111) << 8)) >> 2)
                       |  (*raw_utf8_encoded_char & (FMC_MAKE_UI32(0b111111)));
            break;
        case 4:
            code_point = ((*raw_utf8_encoded_char & (FMC_MAKE_UI32(0b111) << 24)) >> 6)
                       | ((*raw_utf8_encoded_char & (FMC_MAKE_UI32(0b111111) << 16)) >> 4)
                       | ((*raw_utf8_encoded_char & (FMC_MAKE_UI32(0b111111) << 8)) >> 2)
                       |  (*raw_utf8_encoded_char & (FMC_MAKE_UI32(0b111111)));
            break;
        default:
            FMC_UNREACHABLE;
            return FMC_CODE_POINT_NULL;
    }
    return code_point;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF8_uint32_t(const uint32_t raw_utf8_encoded_char)
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
    if ((utf16le_char->comp.byte0 == 0 && utf16le_char->comp.byte1 == 0 && utf16le_char->comp.byte2 == 0 &&
         utf16le_char->comp.byte3 == 0) || utf16le_char->byteNumber == 0 || utf16le_char->isNull) return FMC_CODE_POINT_NULL;
    if (utf16le_char->byteNumber != 2 && utf16le_char->byteNumber != 4)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Invalid UTF-16LE character");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF16LE: Invalid UTF-16LE character");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }

#if defined(UNIT_1) || defined(UNIT_2)
    #undef UNIT_1
    #undef UNIT_2
#endif
#define UNIT_1 (utf16le_char->comp.byte1 | (utf16le_char->comp.byte0 << 8))
#define UNIT_2 (utf16le_char->comp.byte3 | (utf16le_char->comp.byte2 << 8))
    
    FMC_CodePoint code_point = FMC_CODE_POINT_NULL;
    switch(utf16le_char->byteNumber)
    {
        case 2:
            code_point = utf16le_char->comp.byte1 | (utf16le_char->comp.byte0 << 8);
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
            if (UNIT_2 < 0xD800 || UNIT_2 > 0xDBFF)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                    FMC_printRedError(stderr, err_inv_arg);
                }
                FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                return FMC_CODE_POINT_NULL;
                FMC_UNREACHABLE;
            }
            if (UNIT_1 < 0xDC00 || UNIT_1 > 0xDFFF)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                    FMC_printRedError(stderr, err_inv_arg);
                }
                FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                return FMC_CODE_POINT_NULL;
                FMC_UNREACHABLE;
            }
            code_point += (UNIT_2 & 0x03FF) << 10;
            code_point += UNIT_1 & 0x03FF;
            break;
        default:
            return FMC_CODE_POINT_NULL; // Wrong byte number
            FMC_UNREACHABLE;
    }
#undef UNIT_1
#undef UNIT_2
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
    if ((utf16le_char_comp->byte0 == 0 && utf16le_char_comp->byte1 == 0 && utf16le_char_comp->byte2 == 0 &&
         utf16le_char_comp->byte3 == 0)) return FMC_CODE_POINT_NULL;

#if defined(UNIT_1) || defined(UNIT_2)
    #undef UNIT_1
    #undef UNIT_2
#endif
#define UNIT_1 (utf16le_char_comp->byte1 | (utf16le_char_comp->byte0 << 8))
#define UNIT_2 (utf16le_char_comp->byte3 | (utf16le_char_comp->byte2 << 8))

    FMC_CodePoint code_point = FMC_CODE_POINT_NULL;
    if (utf16le_char_comp->byte2 == 0 && utf16le_char_comp->byte3 == 0)
    {
        code_point = utf16le_char_comp->byte1 | (utf16le_char_comp->byte0 << 8);
    }
    else
    {
        code_point = 0x10000;
        if (UNIT_2 < 0xD800 || UNIT_2 > 0xDBFF)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                FMC_printRedError(stderr, err_inv_arg);
            }
            FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
            return FMC_CODE_POINT_NULL;
            FMC_UNREACHABLE;
        }
        if (UNIT_1 < 0xDC00 || UNIT_1 > 0xDFFF)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                FMC_printRedError(stderr, err_inv_arg);
            }
            FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
            return FMC_CODE_POINT_NULL;
            FMC_UNREACHABLE;
        }
        code_point += (UNIT_2 & 0x03FF) << 10;
        code_point += UNIT_1 & 0x03FF;
    }
#undef UNIT_1
#undef UNIT_2
    return code_point;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF16LE_FMC_CharComp(const FMC_CharComp utf16le_char_comp)
{
    return FMC_codePointFromUTF16LE_FMC_CharComp_ptr(&utf16le_char_comp);
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF16LE_uint32_t_ptr(const uint32_t* restrict const raw_utf16le_char)
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

#if defined(UNIT_1) || defined(UNIT_2)
    #undef UNIT_1
    #undef UNIT_2
#endif
#define UNIT_1 (((*raw_utf16le_char & 0xFF) << 8) | ((*raw_utf16le_char & 0xFF00) >> 8))
#define UNIT_2 ((((*raw_utf16le_char & 0xFF0000) << 8) | ((*raw_utf16le_char & 0xFF000000) >> 8)) >> 16)
    
    FMC_CodePoint code_point = FMC_CODE_POINT_NULL;
    if ((*raw_utf16le_char & 0xFFFF0000) == 0)
    {
        code_point = (*raw_utf16le_char & 0xFF00) >> 8 | (*raw_utf16le_char & 0x00FF) << 8;
    }
    else
    {
        code_point = 0x10000;
        if (UNIT_2 < 0xD800 || UNIT_2 > 0xDBFF)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                FMC_printRedError(stderr, err_inv_arg);
            }
            FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
            return FMC_CODE_POINT_NULL;
            FMC_UNREACHABLE;
        }
        if (UNIT_1 < 0xDC00 || UNIT_1 > 0xDFFF)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
                FMC_printRedError(stderr, err_inv_arg);
            }
            FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF16LE: Provided argument is not a valid UTF-16LE encoded character");
            return FMC_CODE_POINT_NULL;
            FMC_UNREACHABLE;
        }
        code_point += (UNIT_2 & 0x03FF) << 10;
        code_point += UNIT_1 & 0x03FF;
    }
#undef UNIT_1
#undef UNIT_2
    return code_point;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF16LE_uint32_t(const uint32_t raw_utf16le_char)
{
    return FMC_codePointFromUTF16LE_uint32_t_ptr(&raw_utf16le_char);
}

/*
 * Code point from UTF-16BE encoded character
 */

FMC_SHARED FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF16BE_FMC_Char_ptr(const FMC_Char* restrict const utf16be_char)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf16be_char || utf16be_char->byteNumber > 4 || utf16be_char->encoding != utf16_be)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16BE: Provided argument is NULL");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF16BE: Provided argument is NULL");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    if (utf16be_char->byteNumber == 0 || utf16be_char->isNull || (utf16be_char->comp.byte0 == 0 && utf16be_char->comp.byte1 == 0 &&
        utf16be_char->comp.byte2 == 0 && utf16be_char->comp.byte3 == 0)) return FMC_CODE_POINT_NULL;
    if (utf16be_char->byteNumber != 2 && utf16be_char->byteNumber != 4)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16LE: Invalid UTF-16LE character");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF16LE: Invalid UTF-16LE character");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
#if defined(UNIT_1) || defined(UNIT_2)
    #undef UNIT_1
    #undef UNIT_2
#endif
#define UNIT_1 (utf16be_char->comp.byte0 | (utf16be_char->comp.byte1 << 8))
#define UNIT_2 (utf16be_char->comp.byte2 | (utf16be_char->comp.byte3 << 8))

    FMC_CodePoint code_point = FMC_CODE_POINT_NULL;
    switch(utf16be_char->byteNumber)
    {
        case 2:
            code_point = utf16be_char->comp.byte1 << 8 | utf16be_char->comp.byte0;
            break;
        case 4:
            code_point = 0x10000;
            if (UNIT_2 < 0xD800 || UNIT_2 > 0xDBFF)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16BE: Provided argument is not a valid UTF-16BE encoded character");
                    FMC_printRedError(stderr, err_inv_arg);
                }
                FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF16BE: Provided argument is not a valid UTF-16BE encoded character");
                return FMC_CODE_POINT_NULL;
                FMC_UNREACHABLE;
            }
            if (UNIT_1 < 0xDC00 || UNIT_1 > 0xDFFF)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16BE: Provided argument is not a valid UTF-16BE encoded character");
                    FMC_printRedError(stderr, err_inv_arg);
                }
                FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF16BE: Provided argument is not a valid UTF-16BE encoded character");
                return FMC_CODE_POINT_NULL;
                FMC_UNREACHABLE;
            }
            code_point += UNIT_1 & 0x03FF;
            code_point += (UNIT_2 & 0x03FF) << 10;
            break;
    }
#undef UNIT_1
#undef UNIT_2
    return code_point;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF16BE_FMC_Char(const FMC_Char utf16be_char)
{
    return FMC_codePointFromUTF16BE_FMC_Char_ptr(&utf16be_char);
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF16BE_FMC_CharComp_ptr(const FMC_CharComp* restrict const utf16be_char)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf16be_char)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16BE: Provided argument is NULL");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF16BE: Provided argument is NULL");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    if (utf16be_char->byte0 == 0 && utf16be_char->byte1 == 0 && utf16be_char->byte2 == 0 && utf16be_char->byte3 == 0)
        return FMC_CODE_POINT_NULL;

#if defined(UNIT_1) || defined(UNIT_2)
    #undef UNIT_1
    #undef UNIT_2
#endif
#define UNIT_1 (utf16be_char->byte0 | (utf16be_char->byte1 << 8))
#define UNIT_2 (utf16be_char->byte2 | (utf16be_char->byte3 << 8))
    
    FMC_CodePoint code_point = FMC_CODE_POINT_NULL;
    if (utf16be_char->byte2 == 0 && utf16be_char->byte3 == 0)
    {
        code_point = utf16be_char->byte1 << 8 | utf16be_char->byte0;
        return code_point;
    }
    else
    {
        code_point = 0x10000;
        if (UNIT_2 < 0xD800 || UNIT_2 > 0xDBFF)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16BE: Provided argument is not a valid UTF-16BE encoded character");
                FMC_printRedError(stderr, err_inv_arg);
            }
            FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF16BE: Provided argument is not a valid UTF-16BE encoded character");
            return FMC_CODE_POINT_NULL;
            FMC_UNREACHABLE;
        }
        if (UNIT_1 < 0xDC00 || UNIT_1 > 0xDFFF)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16BE: Provided argument is not a valid UTF-16BE encoded character");
                FMC_printRedError(stderr, err_inv_arg);
            }
            FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF16BE: Provided argument is not a valid UTF-16BE encoded character");
            return FMC_CODE_POINT_NULL;
            FMC_UNREACHABLE;
        }
        code_point += UNIT_1 & 0x03FF;
        code_point += (UNIT_2 & 0x03FF) << 10;
    }
#undef UNIT_1
#undef UNIT_2
    return code_point;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF16BE_FMC_CharComp(const FMC_CharComp utf16be_char)
{
    return FMC_codePointFromUTF16BE_FMC_CharComp_ptr(&utf16be_char);
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF16BE_uint32_t_ptr(const uint32_t* restrict const raw_utf16be_char)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!raw_utf16be_char)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16BE: Provided argument is NULL");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF16BE: Provided argument is NULL");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    if (*raw_utf16be_char == 0)
        return FMC_CODE_POINT_NULL;
    
#if defined(UNIT_1) || defined(UNIT_2)
    #undef UNIT_1
    #undef UNIT_2
#endif
#define UNIT_1 (*raw_utf16be_char & 0xFFFF)
#define UNIT_2 ((*raw_utf16be_char >> 16) & 0xFFFF)
    FMC_CodePoint code_point = FMC_CODE_POINT_NULL;
    if ((*raw_utf16be_char & 0xFFFF0000) == 0)
    {
        code_point = *raw_utf16be_char & 0xFFFF;
        return code_point;
    }
    else
    {
        code_point = 0x10000;
        if (UNIT_2 < 0xD800 || UNIT_2 > 0xDBFF)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16BE: Provided argument is not a valid UTF-16BE encoded character");
                FMC_printRedError(stderr, err_inv_arg);
            }
            FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF16BE: Provided argument is not a valid UTF-16BE encoded character");
            return FMC_CODE_POINT_NULL;
            FMC_UNREACHABLE;
        }
        if (UNIT_1 < 0xDC00 || UNIT_1 > 0xDFFF)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF16BE: Provided argument is not a valid UTF-16BE encoded character");
                FMC_printRedError(stderr, err_inv_arg);
            }
            FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF16BE: Provided argument is not a valid UTF-16BE encoded character");
            return FMC_CODE_POINT_NULL;
            FMC_UNREACHABLE;
        }
        code_point += UNIT_1 & 0x03FF;
        code_point += (UNIT_2 & 0x03FF) << 10;
    }
#undef UNIT_1
#undef UNIT_2
    return code_point;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF16BE_uint32_t(const uint32_t raw_utf16be_char)
{
    return FMC_codePointFromUTF16BE_uint32_t_ptr(&raw_utf16be_char);
}

/*
 * Code point from UTF-32LE encoded character
 */

FMC_SHARED FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF32LE_FMC_Char_ptr(const FMC_Char* restrict const utf32le_char)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf32le_char)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF32LE: Provided argument is NULL");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF32LE: Provided argument is NULL");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (utf32le_char->byteNumber != 4 || utf32le_char->encoding != utf32_le)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF32LE: Provided argument is not a valid UTF-32LE encoded character");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF32LE: Provided argument is not a valid UTF-32LE encoded character");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }

    return (FMC_CodePoint)((utf32le_char->comp.byte0 << 24) | (utf32le_char->comp.byte1 << 16) | 
                           (utf32le_char->comp.byte2 << 8)  |  utf32le_char->comp.byte3);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF32LE_FMC_Char(const FMC_Char utf32le_char)
{
    if (utf32le_char.byteNumber != 4 || utf32le_char.encoding != utf32_le)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF32LE: Provided argument is not a valid UTF-32LE encoded character");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF32LE: Provided argument is not a valid UTF-32LE encoded character");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }

    return (FMC_CodePoint)((utf32le_char.comp.byte0 << 24) | (utf32le_char.comp.byte1 << 16) | 
                           (utf32le_char.comp.byte2 << 8)  |  utf32le_char.comp.byte3);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF32LE_FMC_CharComp_ptr(const FMC_CharComp* restrict const utf32le_char)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf32le_char)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF32LE: Provided argument is NULL");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF32LE: Provided argument is NULL");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    return (FMC_CodePoint)((utf32le_char->byte0 << 24) | (utf32le_char->byte1 << 16) | 
                           (utf32le_char->byte2 << 8)  |  utf32le_char->byte3);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF32LE_FMC_CharComp(const FMC_CharComp utf32le_char)
{
    return (FMC_CodePoint)((utf32le_char.byte0 << 24) | (utf32le_char.byte1 << 16) | 
                           (utf32le_char.byte2 << 8)  |  utf32le_char.byte3);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF32LE_uint32_t_ptr(const uint32_t* restrict const raw_utf32le_char)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!raw_utf32le_char)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF32LE: Provided argument is NULL");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF32LE: Provided argument is NULL");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    return (FMC_CodePoint)(FMC_bitSwap(32, *raw_utf32le_char));
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF32LE_uint32_t(const uint32_t raw_utf32le_char)
{
    return (FMC_CodePoint)(FMC_bitSwap(32, raw_utf32le_char));
    FMC_UNREACHABLE;
}

/*
 * Code point from UTF-32BE encoded character
 */

FMC_SHARED FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF32BE_FMC_Char_ptr(const FMC_Char* restrict const utf32be_char)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf32be_char)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF32BE: Provided argument is NULL");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF32BE: Provided argument is NULL");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (utf32be_char->byteNumber != 4 || utf32be_char->encoding != utf32_be)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF32BE: Provided argument is not a valid UTF-32BE encoded character");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF32BE: Provided argument is not a valid UTF-32BE encoded character");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }

    return (FMC_CodePoint)((utf32be_char->comp.byte3 << 24) | (utf32be_char->comp.byte2 << 16) | (utf32be_char->comp.byte1 << 8) | utf32be_char->comp.byte0);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF32BE_FMC_Char(const FMC_Char utf32be_char)
{
    if (utf32be_char.byteNumber != 4 || utf32be_char.encoding != utf32_be)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF32BE: Provided argument is not a valid UTF-32BE encoded character");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_ENC, "FMC_codePointFromUTF32BE: Provided argument is not a valid UTF-32BE encoded character");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }

    return (FMC_CodePoint)((utf32be_char.comp.byte3 << 24) | (utf32be_char.comp.byte2 << 16) | (utf32be_char.comp.byte1 << 8) | utf32be_char.comp.byte0);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF32BE_FMC_CharComp_ptr(const FMC_CharComp* restrict const utf32be_char)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf32be_char)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF32BE: Provided argument is NULL");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF32BE: Provided argument is NULL");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    return (FMC_CodePoint)((utf32be_char->byte3 << 24) | (utf32be_char->byte2 << 16) | (utf32be_char->byte1 << 8) | utf32be_char->byte0);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF32BE_FMC_CharComp(const FMC_CharComp utf32be_char)
{
    return (FMC_CodePoint)((utf32be_char.byte3 << 24) | (utf32be_char.byte2 << 16) | (utf32be_char.byte1 << 8) | utf32be_char.byte0);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF32BE_uint32_t_ptr(const uint32_t* restrict const raw_utf32be_char)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!raw_utf32be_char)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF32BE: Provided argument is NULL");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF32BE: Provided argument is NULL");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    return (FMC_CodePoint)(*raw_utf32be_char);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF32BE_uint32_t(const uint32_t raw_utf32be_char)
{
    return (FMC_CodePoint)(raw_utf32be_char);
    FMC_UNREACHABLE;
}


/*
 * UTF-X encoded characters from code points
 */

FMC_SHARED FMC_FUNC_HOT FMC_Char* FMC_UTF8FromCodePoint(FMC_CodePoint cp, FMC_Bool has_bom)
{
    if (!FMC_isValidUnicode(cp))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_UTF8FromCodePoint: Provided argument is not a valid Unicode code point");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_ENC, "FMC_UTF8FromCodePoint: Provided argument is not a valid Unicode code point");
        return NULL;
        FMC_UNREACHABLE;
    }

    FMC_Byte bytes[4] = {0};
    if (cp <= 0x7F)
    {
        bytes[0] = (FMC_Byte)cp;
        return FMC_allocChar(bytes, has_bom ? utf8_bom : utf8, cp == 0, 1);
    }
    else if (cp <= 0x7FF)
    {
        bytes[1] = (FMC_Byte)((cp >> 6) | 0xC0);
        bytes[0] = (FMC_Byte)((cp & 0x3F) | 0x80);
        return FMC_allocChar(bytes, has_bom ? utf8_bom : utf8, FMC_FALSE, 2);
    }
    else if (cp <= 0xFFFF)
    {
        bytes[2] = (FMC_Byte)((cp >> 12) | 0xE0);
        bytes[1] = (FMC_Byte)(((cp >> 6) & 0x3F) | 0x80);
        bytes[0] = (FMC_Byte)((cp & 0x3F) | 0x80);
        return FMC_allocChar(bytes, has_bom ? utf8_bom : utf8, FMC_FALSE, 3);
    }
    else // cp <= 0x10FFFF
    {
        bytes[3] = (FMC_Byte)((cp >> 18) | 0xF0);
        bytes[2] = (FMC_Byte)(((cp >> 12) & 0x3F) | 0x80);
        bytes[1] = (FMC_Byte)(((cp >> 6) & 0x3F) | 0x80);
        bytes[0] = (FMC_Byte)((cp & 0x3F) | 0x80);
        return FMC_allocChar(bytes, has_bom ? utf8_bom : utf8, FMC_FALSE, 4);
    }
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_HOT FMC_Char* FMC_UTF16LEFromCodePoint(FMC_CodePoint cp)
{
    if (!FMC_isValidUnicode(cp))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_UTF16LEFromCodePoint: Provided argument is not a valid Unicode code point");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_ENC, "FMC_UTF16LEFromCodePoint: Provided argument is not a valid Unicode code point");
        return NULL;
        FMC_UNREACHABLE;
    }

    FMC_Byte bytes[4] = {0};
    if (cp <= 0xFFFF)
    {
        bytes[1] = (FMC_Byte)(cp & 0xFF);
        bytes[0] = (FMC_Byte)((cp >> 8) & 0xFF);
        return FMC_allocChar(bytes, utf16_le, cp == 0, 2);
    }
    else // cp <= 0x10FFFF
    {
        cp -= 0x10000;
        uint16_t high_surr = (uint16_t)((cp >> 10) + 0xD800);
        uint16_t low_surr = (uint16_t)((cp & 0x3FF) + 0xDC00);
        high_surr = FMC_bitSwap(16, high_surr);
        low_surr = FMC_bitSwap(16, low_surr);
        bytes[0] = (FMC_Byte)(low_surr & 0xFF);
        bytes[1] = (FMC_Byte)((low_surr >> 8) & 0xFF);
        bytes[2] = (FMC_Byte)(high_surr & 0xFF);
        bytes[3] = (FMC_Byte)((high_surr >> 8) & 0xFF);
        return FMC_allocChar(bytes, utf16_le, FMC_FALSE, 4);
    }
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_HOT FMC_Char* FMC_UTF16BEFromCodePoint(FMC_CodePoint cp)
{
    if (!FMC_isValidUnicode(cp))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_UTF16BEFromCodePoint: Provided argument is not a valid Unicode code point");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_ENC, "FMC_UTF16BEFromCodePoint: Provided argument is not a valid Unicode code point");
        return NULL;
        FMC_UNREACHABLE;
    }

    FMC_Byte bytes[4] = {0};
    if (cp <= 0xFFFF)
    {
        bytes[0] = (FMC_Byte)(cp & 0xFF);
        bytes[1] = (FMC_Byte)((cp >> 8) & 0xFF);
        return FMC_allocChar(bytes, utf16_be, cp == 0, 2);
    }
    else // cp <= 0x10FFFF
    {
        cp -= 0x10000;
        uint16_t high_surr = (uint16_t)((cp >> 10) + 0xD800);
        uint16_t low_surr = (uint16_t)((cp & 0x3FF) + 0xDC00);
        bytes[0] = (FMC_Byte)(high_surr & 0xFF);
        bytes[1] = (FMC_Byte)((high_surr >> 8) & 0xFF);
        bytes[2] = (FMC_Byte)(low_surr & 0xFF);
        bytes[3] = (FMC_Byte)((low_surr >> 8) & 0xFF);
        return FMC_allocChar(bytes, utf16_be, FMC_FALSE, 4);
    }
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_HOT FMC_Char* FMC_UTF32LEFromCodePoint(FMC_CodePoint cp)
{
    if (!FMC_isValidUnicode(cp))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_UTF32LEFromCodePoint: Provided argument is not a valid Unicode code point");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_ENC, "FMC_UTF32LEFromCodePoint: Provided argument is not a valid Unicode code point");
        return NULL;
        FMC_UNREACHABLE;
    }

    FMC_Byte bytes[4] = {0};
    bytes[0] = (FMC_Byte)((cp >> 24) & 0xFF);
    bytes[1] = (FMC_Byte)((cp >> 16) & 0xFF);
    bytes[2] = (FMC_Byte)((cp >> 8) & 0xFF);
    bytes[3] = (FMC_Byte)(cp & 0xFF);
    return FMC_allocChar(bytes, utf32_le, cp == 0, 4);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_HOT FMC_Char* FMC_UTF32BEFromCodePoint(FMC_CodePoint cp)
{
    if (!FMC_isValidUnicode(cp))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_UTF32BEFromCodePoint: Provided argument is not a valid Unicode code point");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_ENC, "FMC_UTF32BEFromCodePoint: Provided argument is not a valid Unicode code point");
        return NULL;
        FMC_UNREACHABLE;
    }

    FMC_Byte bytes[4] = {0};
    bytes[0] = (FMC_Byte)(cp & 0xFF);
    bytes[1] = (FMC_Byte)((cp >> 8) & 0xFF);
    bytes[2] = (FMC_Byte)((cp >> 16) & 0xFF);
    bytes[3] = (FMC_Byte)((cp >> 24) & 0xFF);
    return FMC_allocChar(bytes, utf32_be, cp == 0, 4);
    FMC_UNREACHABLE;
}