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

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF8ToUTF16LE(FMC_Char* restrict utf8_src_ch, FMC_Char* restrict utf16le_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf8_src_ch)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf8_src_ch) is NULL");
            FMC_printRedError(stderr, err_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF16LE: argument 1 (utf8_src_ch) is NULL");
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf16le_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 2 (utf16le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF16LE: argument 2 (utf16le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set");
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else // both are provided
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 2 (utf16le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF16LE: argument 2 (utf16le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set");
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else // utf16le_dest_ch non NULL
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF8(utf8_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf8_src_ch) is not a valid unicode code point");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF16LE: argument 1 (utf8_src_ch) is not a valid unicode code point");
            return NULL;
            FMC_UNREACHABLE;
        }
        if (ch_cp <= 0xFFFF)
        {
            utf16le_dest_ch->comp.byte0 = (FMC_Byte)((ch_cp >> 8) & 0xFF);
            utf16le_dest_ch->comp.byte1 = (FMC_Byte)(ch_cp & 0xFF);
            utf16le_dest_ch->comp.byte2 = 0;
            utf16le_dest_ch->comp.byte3 = 0;
            utf16le_dest_ch->encoding = utf16_le;
            utf16le_dest_ch->byteNumber = 2;
            utf16le_dest_ch->isNull = ch_cp == 0;
        }
        else // ch_cp <= 0x10FFFF
        {
            ch_cp -= 0x10000;
            uint16_t high_surr = (uint16_t)((ch_cp >> 10) + 0xD800);
            uint16_t low_surr = (uint16_t)((ch_cp & 0x3FF) + 0xDC00);
            high_surr = FMC_bitSwap(16, high_surr);
            low_surr = FMC_bitSwap(16, low_surr);
            utf16le_dest_ch->comp.byte0 = (FMC_Byte)(low_surr & 0xFF);
            utf16le_dest_ch->comp.byte1 = (FMC_Byte)((low_surr >> 8) & 0xFF);
            utf16le_dest_ch->comp.byte2 = (FMC_Byte)(high_surr & 0xFF);
            utf16le_dest_ch->comp.byte3 = (FMC_Byte)((high_surr >> 8) & 0xFF);
            utf16le_dest_ch->encoding = utf16_le;
            utf16le_dest_ch->byteNumber = 4;
            utf16le_dest_ch->isNull = FMC_FALSE;
        }
        return utf16le_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf8_src_ch to make it UTF16LE
    FMC_CodePoint ch_cp1 = FMC_codePointFromUTF8(utf8_src_ch);
    if (!FMC_isValidUnicode(ch_cp1))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf8_src_ch) is not a valid unicode code point");
            FMC_printRedError(stderr, err_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF16LE: argument 1 (utf8_src_ch) is not a valid unicode code point");
        return NULL;
        FMC_UNREACHABLE;
    }
    if (ch_cp1 <= 0xFFFF)
    {
        utf8_src_ch->comp.byte0 = (FMC_Byte)((ch_cp1 >> 8) & 0xFF);
        utf8_src_ch->comp.byte1 = (FMC_Byte)(ch_cp1 & 0xFF);
        utf8_src_ch->comp.byte2 = 0;
        utf8_src_ch->comp.byte3 = 0;
        utf8_src_ch->encoding = utf16_le;
        utf8_src_ch->byteNumber = 2;
        utf8_src_ch->isNull = ch_cp1 == 0;
    }
    else // ch_cp <= 0x10FFFF
    {
        ch_cp1 -= 0x10000;
        uint16_t high_surr = (uint16_t)((ch_cp1 >> 10) + 0xD800);
        uint16_t low_surr = (uint16_t)((ch_cp1 & 0x3FF) + 0xDC00);
        high_surr = FMC_bitSwap(16, high_surr);
        low_surr = FMC_bitSwap(16, low_surr);
        utf8_src_ch->comp.byte0 = (FMC_Byte)(low_surr & 0xFF);
        utf8_src_ch->comp.byte1 = (FMC_Byte)((low_surr >> 8) & 0xFF);
        utf8_src_ch->comp.byte2 = (FMC_Byte)(high_surr & 0xFF);
        utf8_src_ch->comp.byte3 = (FMC_Byte)((high_surr >> 8) & 0xFF);
        utf8_src_ch->encoding = utf16_le;
        utf8_src_ch->byteNumber = 4;
        utf8_src_ch->isNull = FMC_FALSE;
    }
    return utf8_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf16le_dest_ch
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF8(utf8_src_ch);
    return FMC_UTF16LEFromCodePoint(ch_cp2);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF8ToUTF16BE(FMC_Char* restrict utf8_src_ch, FMC_Char* restrict utf16be_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf8_src_ch)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf8_src_ch) is NULL");
            FMC_printRedError(stderr, err_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF16BE: argument 1 (utf8_src_ch) is NULL");
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf16be_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 2 (utf16be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF16BE: argument 2 (utf16be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set");
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else // both are provided
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 2 (utf16be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF16BE: argument 2 (utf16be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set");
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else // utf16be_dest_ch non NULL
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF8(utf8_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf8_src_ch) is not a valid unicode code point");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF16BE: argument 1 (utf8_src_ch) is not a valid unicode code point");
            return NULL;
            FMC_UNREACHABLE;
        }
        if (ch_cp <= 0xFFFF)
        {
            utf16be_dest_ch->comp.byte0 = (FMC_Byte)(ch_cp & 0xFF);
            utf16be_dest_ch->comp.byte1 = (FMC_Byte)((ch_cp >> 8) & 0xFF);
            utf16be_dest_ch->comp.byte2 = 0;
            utf16be_dest_ch->comp.byte3 = 0;
            utf16be_dest_ch->encoding = utf16_be;
            utf16be_dest_ch->byteNumber = 2;
            utf16be_dest_ch->isNull = ch_cp == 0;
        }
        else // ch_cp <= 0x10FFFF
        {
            ch_cp -= 0x10000;
            uint16_t high_surr = (uint16_t)((ch_cp >> 10) + 0xD800);
            uint16_t low_surr = (uint16_t)((ch_cp & 0x3FF) + 0xDC00);
            utf16be_dest_ch->comp.byte0 = (FMC_Byte)(low_surr & 0xFF);
            utf16be_dest_ch->comp.byte1 = (FMC_Byte)((low_surr >> 8) & 0xFF);
            utf16be_dest_ch->comp.byte2 = (FMC_Byte)(high_surr & 0xFF);
            utf16be_dest_ch->comp.byte3 = (FMC_Byte)((high_surr >> 8) & 0xFF);
            utf16be_dest_ch->encoding = utf16_be;
            utf16be_dest_ch->byteNumber = 4;
            utf16be_dest_ch->isNull = FMC_FALSE;
        }
        return utf16be_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf8_src_ch to make it UTF16BE
    FMC_CodePoint ch_cp1 = FMC_codePointFromUTF8(utf8_src_ch);
    if (!FMC_isValidUnicode(ch_cp1))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf8_src_ch) is not a valid unicode code point");
            FMC_printRedError(stderr, err_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF16BE: argument 1 (utf8_src_ch) is not a valid unicode code point");
        return NULL;
        FMC_UNREACHABLE;
    }
    if (ch_cp1 <= 0xFFFF)
    {
        utf8_src_ch->comp.byte0 = (FMC_Byte)(ch_cp1 & 0xFF);
        utf8_src_ch->comp.byte1 = (FMC_Byte)((ch_cp1 >> 8) & 0xFF);
        utf8_src_ch->comp.byte2 = 0;
        utf8_src_ch->comp.byte3 = 0;
        utf8_src_ch->encoding = utf16_be;
        utf8_src_ch->byteNumber = 2;
        utf8_src_ch->isNull = ch_cp1 == 0;
    }
    else // ch_cp <= 0x10FFFF
    {
        ch_cp1 -= 0x10000;
        uint16_t high_surr = (uint16_t)((ch_cp1 >> 10) + 0xD800);
        uint16_t low_surr = (uint16_t)((ch_cp1 & 0x3FF) + 0xDC00);
        utf8_src_ch->comp.byte0 = (FMC_Byte)(low_surr & 0xFF);
        utf8_src_ch->comp.byte1 = (FMC_Byte)((low_surr >> 8) & 0xFF);
        utf8_src_ch->comp.byte2 = (FMC_Byte)(high_surr & 0xFF);
        utf8_src_ch->comp.byte3 = (FMC_Byte)((high_surr >> 8) & 0xFF);
        utf8_src_ch->encoding = utf16_be;
        utf8_src_ch->byteNumber = 4;
        utf8_src_ch->isNull = FMC_FALSE;
    }
    return utf8_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf16be_dest_ch
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF8(utf8_src_ch);
    return FMC_UTF16BEFromCodePoint(ch_cp2);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF8ToUTF32LE(FMC_Char* restrict utf8_src_ch, FMC_Char* restrict utf32le_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf8_src_ch)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf8_src_ch) is NULL");
            FMC_printRedError(stderr, err_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF32LE: argument 1 (utf8_src_ch) is NULL");
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf32le_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 2 (utf32le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF32LE: argument 2 (utf32le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set");
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else // both are provided
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 2 (utf32le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF32LE: argument 2 (utf32le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set");
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else // utf32le_dest_ch non NULL
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF8(utf8_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf8_src_ch) is not a valid unicode code point");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF32LE: argument 1 (utf8_src_ch) is not a valid unicode code point");
            return NULL;
            FMC_UNREACHABLE;
        }
        ch_cp = FMC_bitSwap(32, ch_cp);
        utf32le_dest_ch->comp.byte0 = (FMC_Byte)(ch_cp & 0xFF);
        utf32le_dest_ch->comp.byte1 = (FMC_Byte)((ch_cp >> 8) & 0xFF);
        utf32le_dest_ch->comp.byte2 = (FMC_Byte)((ch_cp >> 16) & 0xFF);
        utf32le_dest_ch->comp.byte3 = (FMC_Byte)((ch_cp >> 24) & 0xFF);
        utf32le_dest_ch->encoding = utf32_le;
        utf32le_dest_ch->byteNumber = 4;
        utf32le_dest_ch->isNull = ch_cp == 0;
        return utf32le_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf8_src_ch to make it UTF32LE
    FMC_CodePoint ch_cp1 = FMC_codePointFromUTF8(utf8_src_ch);
    if (!FMC_isValidUnicode(ch_cp1))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf8_src_ch) is not a valid unicode code point");
            FMC_printRedError(stderr, err_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF32LE: argument 1 (utf8_src_ch) is not a valid unicode code point");
        return NULL;
        FMC_UNREACHABLE;
    }
    ch_cp1 = FMC_bitSwap(32, ch_cp1);
    utf8_src_ch->comp.byte0 = (FMC_Byte)(ch_cp1 & 0xFF);
    utf8_src_ch->comp.byte1 = (FMC_Byte)((ch_cp1 >> 8) & 0xFF);
    utf8_src_ch->comp.byte2 = (FMC_Byte)((ch_cp1 >> 16) & 0xFF);
    utf8_src_ch->comp.byte3 = (FMC_Byte)((ch_cp1 >> 24) & 0xFF);
    utf8_src_ch->encoding = utf32_le;
    utf8_src_ch->byteNumber = 4;
    utf8_src_ch->isNull = ch_cp1 == 0;
    return utf8_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf32le_dest_ch
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF8(utf8_src_ch);
    return FMC_UTF32LEFromCodePoint(ch_cp2);
    FMC_UNREACHABLE;
}


FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF8ToUTF32BE(FMC_Char* restrict utf8_src_ch, FMC_Char* restrict utf32be_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf8_src_ch)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf8_src_ch) is NULL");
            FMC_printRedError(stderr, err_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF32BE: argument 1 (utf8_src_ch) is NULL");
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf32be_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 2 (utf32be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF32BE: argument 2 (utf32be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set");
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else // both are provided
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 2 (utf32be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF32BE: argument 2 (utf32be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set");
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else // utf32be_dest_ch non NULL
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF8(utf8_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf8_src_ch) is not a valid unicode code point");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF32BE: argument 1 (utf8_src_ch) is not a valid unicode code point");
            return NULL;
            FMC_UNREACHABLE;
        }
        utf32be_dest_ch->comp.byte0 = (FMC_Byte)(ch_cp & 0xFF);
        utf32be_dest_ch->comp.byte1 = (FMC_Byte)((ch_cp >> 8) & 0xFF);
        utf32be_dest_ch->comp.byte2 = (FMC_Byte)((ch_cp >> 16) & 0xFF);
        utf32be_dest_ch->comp.byte3 = (FMC_Byte)((ch_cp >> 24) & 0xFF);
        utf32be_dest_ch->encoding = utf32_be;
        utf32be_dest_ch->byteNumber = 4;
        utf32be_dest_ch->isNull = ch_cp == 0;
        return utf32be_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf8_src_ch to make it UTF32BE
    FMC_CodePoint ch_cp1 = FMC_codePointFromUTF8(utf8_src_ch);
    if (!FMC_isValidUnicode(ch_cp1))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf8_src_ch) is not a valid unicode code point");
            FMC_printRedError(stderr, err_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_UTF8ToUTF32BE: argument 1 (utf8_src_ch) is not a valid unicode code point");
        return NULL;
        FMC_UNREACHABLE;
    }
    utf8_src_ch->comp.byte0 = (FMC_Byte)(ch_cp1 & 0xFF);
    utf8_src_ch->comp.byte1 = (FMC_Byte)((ch_cp1 >> 8) & 0xFF);
    utf8_src_ch->comp.byte2 = (FMC_Byte)((ch_cp1 >> 16) & 0xFF);
    utf8_src_ch->comp.byte3 = (FMC_Byte)((ch_cp1 >> 24) & 0xFF);
    utf8_src_ch->encoding = utf32_be;
    utf8_src_ch->byteNumber = 4;
    utf8_src_ch->isNull = ch_cp1 == 0;
    return utf8_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf32be_dest_ch
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF8(utf8_src_ch);
    return FMC_UTF32BEFromCodePoint(ch_cp2);
    FMC_UNREACHABLE;
}


FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF16LEToUTF8(FMC_Char* restrict utf16le_src_ch, FMC_Char* restrict utf8_dest_ch, unsigned int flags, FMC_Bool put_bom)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf16le_src_ch)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf16le_src_ch) is NULL");
            FMC_printRedError(stderr, err_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function FMC_UTF16LEToUTF8: argument 1 (utf16le_src_ch) is NULL");
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf8_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 2 (utf8_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function FMC_UTF16LEToUTF8: argument 2 (utf8_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set");
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else // both are provided
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 2 (utf8_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function FMC_UTF16LEToUTF8: argument 2 (utf8_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set");
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else // utf8_dest_ch non NULL
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF16LE(utf16le_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf16le_src_ch) is not a valid unicode code point");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function FMC_UTF16LEToUTF8: argument 1 (utf16le_src_ch) is not a valid unicode code point");
            return NULL;
            FMC_UNREACHABLE;
        }
        if (ch_cp <= 0x7F)
        {
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(ch_cp & 0xFF);
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 1;
            utf8_dest_ch->isNull = ch_cp == 0;
        }
        else if (ch_cp <= 0x7FF)
        {
            utf8_dest_ch->comp.byte1 = (FMC_Byte)(0xC0 | ((ch_cp >> 6) & 0x1F));
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp & 0x3F));
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 2;
            utf8_dest_ch->isNull = FMC_FALSE;
        }
        else if (ch_cp <= 0xFFFF)
        {
            utf8_dest_ch->comp.byte2 = (FMC_Byte)(0xE0 | ((ch_cp >> 12) & 0x0F));
            utf8_dest_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp >> 6) & 0x3F));
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp & 0x3F));
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 3;
            utf8_dest_ch->isNull = FMC_FALSE;
        }
        else // ch_cp <= 0x10FFFF
        {
            utf8_dest_ch->comp.byte3 = (FMC_Byte)(0xF0 | ((ch_cp >> 18) & 0x07));
            utf8_dest_ch->comp.byte2 = (FMC_Byte)(0x80 | ((ch_cp >> 12) & 0x3F));
            utf8_dest_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp >> 6) & 0x3F));
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp & 0x3F));
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 4;
            utf8_dest_ch->isNull = FMC_FALSE;
        }
        if (put_bom) utf8_dest_ch->encoding = utf8_bom;
        return utf8_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf16le_src_ch to make it UTF8
    FMC_CodePoint ch_cp1 = FMC_codePointFromUTF16LE(utf16le_src_ch);
    if (!FMC_isValidUnicode(ch_cp1))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf16le_src_ch) is not a valid unicode code point");
            FMC_printRedError(stderr, err_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function FMC_UTF16LEToUTF8: argument 1 (utf16le_src_ch) is not a valid unicode code point");
        return NULL;
        FMC_UNREACHABLE;
    }
    if (ch_cp1 <= 0x7F)
    {
        utf16le_src_ch->comp.byte0 = (FMC_Byte)(ch_cp1 & 0xFF);
        utf16le_src_ch->encoding = utf8;
        utf16le_src_ch->byteNumber = 1;
        utf16le_src_ch->isNull = ch_cp1 == 0;
    }
    else if (ch_cp1 <= 0x7FF)
    {
        utf16le_src_ch->comp.byte1 = (FMC_Byte)(0xC0 | ((ch_cp1 >> 6) & 0x1F));
        utf16le_src_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp1 & 0x3F));
        utf16le_src_ch->encoding = utf8;
        utf16le_src_ch->byteNumber = 2;
        utf16le_src_ch->isNull = FMC_FALSE;
    }
    else if (ch_cp1 <= 0xFFFF)
    {
        utf16le_src_ch->comp.byte2 = (FMC_Byte)(0xE0 | ((ch_cp1 >> 12) & 0x0F));
        utf16le_src_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp1 >> 6) & 0x3F));
        utf16le_src_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp1 & 0x3F));
        utf16le_src_ch->encoding = utf8;
        utf16le_src_ch->byteNumber = 3;
        utf16le_src_ch->isNull = FMC_FALSE;
    }
    else // ch_cp <= 0x10FFFF
    {
        utf16le_src_ch->comp.byte3 = (FMC_Byte)(0xF0 | ((ch_cp1 >> 18) & 0x07));
        utf16le_src_ch->comp.byte2 = (FMC_Byte)(0x80 | ((ch_cp1 >> 12) & 0x3F));
        utf16le_src_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp1 >> 6) & 0x3F));
        utf16le_src_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp1 & 0x3F));
        utf16le_src_ch->encoding = utf8;
        utf16le_src_ch->byteNumber = 4;
        utf16le_src_ch->isNull = FMC_FALSE;
    }
    if (put_bom) utf16le_src_ch->encoding = utf8_bom;
    return utf16le_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf8_dest_ch
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF16LE(utf16le_src_ch);
    return FMC_UTF8FromCodePoint(ch_cp2, put_bom);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF16LEToUTF16BE(FMC_Char* restrict utf16le_src_ch, FMC_Char* restrict utf16be_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf16le_src_ch)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 1 (utf16le_src_ch) is NULL");
            FMC_printRedError(stderr, err_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function FMC_UTF16LEToUTF16BE: argument 1 (utf16le_src_ch) is NULL");
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf16be_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 2 (utf16be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function FMC_UTF16LEToUTF16BE: argument 2 (utf16be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set");
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else // both are provided
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 3, "ERROR: In function: ", __func__, ": argument 2 (utf16be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function FMC_UTF16LEToUTF16BE: argument 2 (utf16be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set");
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else // utf16be_dest_ch non NULL
    {
        utf16be_dest_ch->comp.byte0 = utf16le_src_ch->comp.byte1;
        utf16be_dest_ch->comp.byte1 = utf16le_src_ch->comp.byte0;
        utf16be_dest_ch->comp.byte2 = utf16le_src_ch->comp.byte3;
        utf16be_dest_ch->comp.byte3 = utf16le_src_ch->comp.byte2;
        utf16be_dest_ch->encoding = utf16_be;
        utf16be_dest_ch->byteNumber = utf16le_src_ch->byteNumber;
        utf16be_dest_ch->isNull = utf16le_src_ch->isNull;
        return utf16be_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf16le_src_ch to make it UTF16BE
    FMC_Char tmp = *utf16le_src_ch;
    utf16le_src_ch->comp.byte0 = tmp.comp.byte1;
    utf16le_src_ch->comp.byte1 = tmp.comp.byte0;
    utf16le_src_ch->comp.byte2 = tmp.comp.byte3;
    utf16le_src_ch->comp.byte3 = tmp.comp.byte2;
    utf16le_src_ch->encoding = utf16_be;
    return utf16le_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf16be_dest_ch
    FMC_Char* ret = FMC_allocChar((FMC_Byte[4]){[0] = utf16le_src_ch->comp.byte1, [1] = utf16le_src_ch->comp.byte0, [2] = utf16le_src_ch->comp.byte3, [3] = utf16le_src_ch->comp.byte2}, utf16_be, utf16le_src_ch->isNull, utf16le_src_ch->byteNumber);
    if (!ret)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_alloc, 3, "ERROR: In function: ", __func__, ": failed to allocate memory for new FMC_Char");
            FMC_printRedError(stderr, err_alloc);
        }
        FMC_setError(FMC_ERR_ALLOC_FAILED, "ERROR: In function FMC_UTF16LEToUTF16BE: failed to allocate memory for new FMC_Char");
        return NULL;
        FMC_UNREACHABLE;
    }
    return ret;
    FMC_UNREACHABLE;        
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF16LEToUTF32LE(FMC_Char* restrict utf16le_src_ch, FMC_Char* restrict utf32le_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf16le_src_ch)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16le_src_ch) is NULL", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    
    if (!utf32le_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf32le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf32le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF16LE(utf16le_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16le_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        ch_cp = FMC_bitSwap(32, ch_cp);
        utf32le_dest_ch->comp.byte0 = (FMC_Byte)(ch_cp & 0xFF);
        utf32le_dest_ch->comp.byte1 = (FMC_Byte)((ch_cp >> 8) & 0xFF);
        utf32le_dest_ch->comp.byte2 = (FMC_Byte)((ch_cp >> 16) & 0xFF);
        utf32le_dest_ch->comp.byte3 = (FMC_Byte)((ch_cp >> 24) & 0xFF);
        utf32le_dest_ch->encoding = utf32_le;
        utf32le_dest_ch->byteNumber = 4;
        utf32le_dest_ch->isNull = ch_cp == 0;
        return utf32le_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf16le_src_ch to make it UTF32LE
    FMC_CodePoint ch_cp1 = FMC_codePointFromUTF16LE(utf16le_src_ch);
    if (!FMC_isValidUnicode(ch_cp1))
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16le_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    ch_cp1 = FMC_bitSwap(32, ch_cp1);
    utf16le_src_ch->comp.byte0 = (FMC_Byte)(ch_cp1 & 0xFF);
    utf16le_src_ch->comp.byte1 = (FMC_Byte)((ch_cp1 >> 8) & 0xFF);
    utf16le_src_ch->comp.byte2 = (FMC_Byte)((ch_cp1 >> 16) & 0xFF);
    utf16le_src_ch->comp.byte3 = (FMC_Byte)((ch_cp1 >> 24) & 0xFF);
    utf16le_src_ch->encoding = utf32_le;
    utf16le_src_ch->byteNumber = 4;
    utf16le_src_ch->isNull = ch_cp1 == 0;
    return utf16le_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf32le_dest_ch
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF16LE(utf16le_src_ch);
    return FMC_UTF32LEFromCodePoint(ch_cp2);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF16LEToUTF32BE(FMC_Char* restrict utf16le_src_ch, FMC_Char* restrict utf32be_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf16le_src_ch)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16le_src_ch) is NULL", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    
    if (!utf32be_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf32be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf32be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF16LE(utf16le_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16le_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        utf32be_dest_ch->comp.byte0 = (FMC_Byte)(ch_cp & 0xFF);
        utf32be_dest_ch->comp.byte1 = (FMC_Byte)((ch_cp >> 8) & 0xFF);
        utf32be_dest_ch->comp.byte2 = (FMC_Byte)((ch_cp >> 16) & 0xFF);
        utf32be_dest_ch->comp.byte3 = (FMC_Byte)((ch_cp >> 24) & 0xFF);
        utf32be_dest_ch->encoding = utf32_be;
        utf32be_dest_ch->byteNumber = 4;
        utf32be_dest_ch->isNull = ch_cp == 0;
        return utf32be_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf16le_src_ch to make it UTF32BE
    FMC_CodePoint ch_cp1 = FMC_codePointFromUTF16LE(utf16le_src_ch);
    if (!FMC_isValidUnicode(ch_cp1))
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16le_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    utf16le_src_ch->comp.byte0 = (FMC_Byte)(ch_cp1 & 0xFF);
    utf16le_src_ch->comp.byte1 = (FMC_Byte)((ch_cp1 >> 8) & 0xFF);
    utf16le_src_ch->comp.byte2 = (FMC_Byte)((ch_cp1 >> 16) & 0xFF);
    utf16le_src_ch->comp.byte3 = (FMC_Byte)((ch_cp1 >> 24) & 0xFF);
    utf16le_src_ch->encoding = utf32_be;
    utf16le_src_ch->byteNumber = 4;
    utf16le_src_ch->isNull = ch_cp1 == 0;
    return utf16le_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf32be_dest_ch
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF16LE(utf16le_src_ch);
    return FMC_UTF32BEFromCodePoint(ch_cp2);
    FMC_UNREACHABLE;
}


FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF16BEToUTF8(FMC_Char* restrict utf16be_src_ch, FMC_Char* restrict utf8_dest_ch, unsigned int flags, FMC_Bool put_bom)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf16be_src_ch)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16be_src_ch) is NULL", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf8_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf8_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf8_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF16BE(utf16be_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16be_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }

        if (ch_cp <= 0x7F)
        {
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(ch_cp & 0xFF);
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 1;
            utf8_dest_ch->isNull = ch_cp == 0;
        }
        else if (ch_cp <= 0x7FF)
        {
            utf8_dest_ch->comp.byte1 = (FMC_Byte)(0xC0 | ((ch_cp >> 6) & 0x1F));
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp & 0x3F));
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 2;
            utf8_dest_ch->isNull = FMC_FALSE;
        }
        else if (ch_cp <= 0xFFFF)
        {
            utf8_dest_ch->comp.byte2 = (FMC_Byte)(0xE0 | ((ch_cp >> 12) & 0x0F));
            utf8_dest_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp >> 6) & 0x3F));
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp & 0x3F));
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 3;
            utf8_dest_ch->isNull = FMC_FALSE;
        }
        else // ch_cp <= 0x10FFFF
        {
            utf8_dest_ch->comp.byte3 = (FMC_Byte)(0xF0 | ((ch_cp >> 18) & 0x07));
            utf8_dest_ch->comp.byte2 = (FMC_Byte)(0x80 | ((ch_cp >> 12) & 0x3F));
            utf8_dest_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp >> 6) & 0x3F));
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp & 0x3F));
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 4;
            utf8_dest_ch->isNull = FMC_FALSE;
        }
        if (put_bom) utf8_dest_ch->encoding = utf8_bom;
        return utf8_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf16be_src_ch to make it UTF8
    FMC_CodePoint ch_cp1 = FMC_codePointFromUTF16BE(utf16be_src_ch);
    if (!FMC_isValidUnicode(ch_cp1))
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16be_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }

    if (ch_cp1 <= 0x7F)
    {
        utf16be_src_ch->comp.byte0 = (FMC_Byte)(ch_cp1 & 0xFF);
        utf16be_src_ch->encoding = utf8;
        utf16be_src_ch->byteNumber = 1;
        utf16be_src_ch->isNull = ch_cp1 == 0;
    }
    else if (ch_cp1 <= 0x7FF)
    {
        utf16be_src_ch->comp.byte1 = (FMC_Byte)(0xC0 | ((ch_cp1 >> 6) & 0x1F));
        utf16be_src_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp1 & 0x3F));
        utf16be_src_ch->encoding = utf8;
        utf16be_src_ch->byteNumber = 2;
        utf16be_src_ch->isNull = FMC_FALSE;
    }
    else if (ch_cp1 <= 0xFFFF)
    {
        utf16be_src_ch->comp.byte2 = (FMC_Byte)(0xE0 | ((ch_cp1 >> 12) & 0x0F));
        utf16be_src_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp1 >> 6) & 0x3F));
        utf16be_src_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp1 & 0x3F));
        utf16be_src_ch->encoding = utf8;
        utf16be_src_ch->byteNumber = 3;
        utf16be_src_ch->isNull = FMC_FALSE;
    }
    else
    {
        utf16be_src_ch->comp.byte3 = (FMC_Byte)(0xF0 | ((ch_cp1 >> 18) & 0x07));
        utf16be_src_ch->comp.byte2 = (FMC_Byte)(0x80 | ((ch_cp1 >> 12) & 0x3F));
        utf16be_src_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp1 >> 6) & 0x3F));
        utf16be_src_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp1 & 0x3F));
        utf16be_src_ch->encoding = utf8;
        utf16be_src_ch->byteNumber = 4;
        utf16be_src_ch->isNull = FMC_FALSE;
    }
    if (put_bom) utf16be_src_ch->encoding = utf8_bom;
    return utf16be_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf8_dest_ch
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF16BE(utf16be_src_ch);
    return FMC_UTF8FromCodePoint(ch_cp2, put_bom);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF16BEToUTF16LE(FMC_Char* restrict utf16be_src_ch, FMC_Char* restrict utf16le_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf16be_src_ch)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16be_src_ch) is NULL", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf16le_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf16le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf16le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else
    {
        utf16le_dest_ch->comp.byte0 = utf16be_src_ch->comp.byte1;
        utf16le_dest_ch->comp.byte1 = utf16be_src_ch->comp.byte0;
        utf16le_dest_ch->comp.byte2 = utf16be_src_ch->comp.byte3;
        utf16le_dest_ch->comp.byte3 = utf16be_src_ch->comp.byte2;
        utf16le_dest_ch->encoding = utf16_le;
        utf16le_dest_ch->byteNumber = utf16be_src_ch->byteNumber;
        utf16le_dest_ch->isNull = utf16be_src_ch->isNull;
        return utf16le_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf16be_src_ch to make it UTF16LE
    FMC_Char tmp = *utf16be_src_ch;
    utf16be_src_ch->comp.byte0 = tmp.comp.byte1;
    utf16be_src_ch->comp.byte1 = tmp.comp.byte0;
    utf16be_src_ch->comp.byte2 = tmp.comp.byte3;
    utf16be_src_ch->comp.byte3 = tmp.comp.byte2;
    utf16be_src_ch->encoding = utf16_le;
    return utf16be_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf16le_dest_ch
    FMC_Char* ret = FMC_allocChar((FMC_Byte[4]){[0] = utf16be_src_ch->comp.byte1, [1] = utf16be_src_ch->comp.byte0, [2] = utf16be_src_ch->comp.byte3, [3] = utf16be_src_ch->comp.byte2}, utf16_le, utf16be_src_ch->isNull, utf16be_src_ch->byteNumber);
    if (!ret)
    {
        FMC_HANDLE_ERR(FMC_ERR_ALLOC_FAILED, "failed to allocate memory for new FMC_Char", err_alloc, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    return ret;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF16BEToUTF32LE(FMC_Char* restrict utf16be_src_ch, FMC_Char* restrict utf32le_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf16be_src_ch)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16be_src_ch) is NULL", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf32le_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf32le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf32le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF16BE(utf16be_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16be_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        ch_cp = FMC_bitSwap(32, ch_cp);
        utf32le_dest_ch->comp.byte0 = (FMC_Byte)(ch_cp & 0xFF);
        utf32le_dest_ch->comp.byte1 = (FMC_Byte)((ch_cp >> 8) & 0xFF);
        utf32le_dest_ch->comp.byte2 = (FMC_Byte)((ch_cp >> 16) & 0xFF);
        utf32le_dest_ch->comp.byte3 = (FMC_Byte)((ch_cp >> 24) & 0xFF);
        utf32le_dest_ch->encoding = utf32_le;
        utf32le_dest_ch->byteNumber = 4;
        utf32le_dest_ch->isNull = ch_cp == 0;
        return utf32le_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf16be_src_ch to make it UTF32LE
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF16BE(utf16be_src_ch);
    if (!FMC_isValidUnicode(ch_cp2))
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16be_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    ch_cp2 = FMC_bitSwap(32, ch_cp2);
    utf16be_src_ch->comp.byte0 = (FMC_Byte)(ch_cp2 & 0xFF);
    utf16be_src_ch->comp.byte1 = (FMC_Byte)((ch_cp2 >> 8) & 0xFF);
    utf16be_src_ch->comp.byte2 = (FMC_Byte)((ch_cp2 >> 16) & 0xFF);
    utf16be_src_ch->comp.byte3 = (FMC_Byte)((ch_cp2 >> 24) & 0xFF);
    utf16be_src_ch->encoding = utf32_le;
    utf16be_src_ch->byteNumber = 4;
    utf16be_src_ch->isNull = ch_cp2 == 0;
    return utf16be_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf32le_dest_ch
    FMC_CodePoint ch_cp3 = FMC_codePointFromUTF16BE(utf16be_src_ch);
    return FMC_UTF32LEFromCodePoint(ch_cp3);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF16BEToUTF32BE(FMC_Char* restrict utf16be_src_ch, FMC_Char* restrict utf32be_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf16be_src_ch)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16be_src_ch) is NULL", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf32be_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf32be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf32be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF16BE(utf16be_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16be_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        utf32be_dest_ch->comp.byte0 = (FMC_Byte)(ch_cp & 0xFF);
        utf32be_dest_ch->comp.byte1 = (FMC_Byte)((ch_cp >> 8) & 0xFF);
        utf32be_dest_ch->comp.byte2 = (FMC_Byte)((ch_cp >> 16) & 0xFF);
        utf32be_dest_ch->comp.byte3 = (FMC_Byte)((ch_cp >> 24) & 0xFF);
        utf32be_dest_ch->encoding = utf32_be;
        utf32be_dest_ch->byteNumber = 4;
        utf32be_dest_ch->isNull = ch_cp == 0;
        return utf32be_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf16be_src_ch to make it UTF32BE
    FMC_CodePoint ch_cp1 = FMC_codePointFromUTF16BE(utf16be_src_ch);
    if (!FMC_isValidUnicode(ch_cp1))
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf16be_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    utf16be_src_ch->comp.byte0 = (FMC_Byte)(ch_cp1 & 0xFF);
    utf16be_src_ch->comp.byte1 = (FMC_Byte)((ch_cp1 >> 8) & 0xFF);
    utf16be_src_ch->comp.byte2 = (FMC_Byte)((ch_cp1 >> 16) & 0xFF);
    utf16be_src_ch->comp.byte3 = (FMC_Byte)((ch_cp1 >> 24) & 0xFF);
    utf16be_src_ch->encoding = utf32_be;
    utf16be_src_ch->byteNumber = 4;
    utf16be_src_ch->isNull = ch_cp1 == 0;
    return utf16be_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf32be_dest_ch
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF16BE(utf16be_src_ch);
    return FMC_UTF32BEFromCodePoint(ch_cp2);
    FMC_UNREACHABLE;
}


FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF32LEToUTF8(FMC_Char* restrict utf32le_src_ch, FMC_Char* restrict utf8_dest_ch, unsigned int flags, FMC_Bool put_bom)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf32le_src_ch)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32le_src_ch) is NULL", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf8_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf8_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf8_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF32LE(utf32le_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32le_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }

        if (ch_cp <= 0x7F)
        {
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(ch_cp & 0xFF);
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 1;
            utf8_dest_ch->isNull = ch_cp == 0;
        }
        else if (ch_cp <= 0x7FF)
        {
            utf8_dest_ch->comp.byte1 = (FMC_Byte)(0xC0 | ((ch_cp >> 6) & 0x1F));
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp & 0x3F));
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 2;
            utf8_dest_ch->isNull = FMC_FALSE;
        }
        else if (ch_cp <= 0xFFFF)
        {
            utf8_dest_ch->comp.byte2 = (FMC_Byte)(0xE0 | ((ch_cp >> 12) & 0x0F));
            utf8_dest_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp >> 6) & 0x3F));
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp & 0x3F));
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 3;
            utf8_dest_ch->isNull = FMC_FALSE;
        }
        else // ch_cp <= 0x10FFFF
        {
            utf8_dest_ch->comp.byte3 = (FMC_Byte)(0xF0 | ((ch_cp >> 18) & 0x07));
            utf8_dest_ch->comp.byte2 = (FMC_Byte)(0x80 | ((ch_cp >> 12) & 0x3F));
            utf8_dest_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp >> 6) & 0x3F));
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp & 0x3F));
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 4;
            utf8_dest_ch->isNull = FMC_FALSE;
        }
        if (put_bom) utf8_dest_ch->encoding = utf8_bom;
        return utf8_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf32le_src_ch to make it UTF8
    FMC_CodePoint ch_cp1 = FMC_codePointFromUTF32LE(utf32le_src_ch);
    if (!FMC_isValidUnicode(ch_cp1))
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32le_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }

    if (ch_cp1 <= 0x7F)
    {
        utf32le_src_ch->comp.byte0 = (FMC_Byte)(ch_cp1 & 0xFF);
        utf32le_src_ch->encoding = utf8;
        utf32le_src_ch->byteNumber = 1;
        utf32le_src_ch->isNull = ch_cp1 == 0;
    }
    else if (ch_cp1 <= 0x7FF)
    {
        utf32le_src_ch->comp.byte1 = (FMC_Byte)(0xC0 | ((ch_cp1 >> 6) & 0x1F));
        utf32le_src_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp1 & 0x3F));
        utf32le_src_ch->encoding = utf8;
        utf32le_src_ch->byteNumber = 2;
        utf32le_src_ch->isNull = FMC_FALSE;
    }
    else if (ch_cp1 <= 0xFFFF)
    {
        utf32le_src_ch->comp.byte2 = (FMC_Byte)(0xE0 | ((ch_cp1 >> 12) & 0x0F));
        utf32le_src_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp1 >> 6) & 0x3F));
        utf32le_src_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp1 & 0x3F));
        utf32le_src_ch->encoding = utf8;
        utf32le_src_ch->byteNumber = 3;
        utf32le_src_ch->isNull = FMC_FALSE;
    }
    else
    {
        utf32le_src_ch->comp.byte3 = (FMC_Byte)(0xF0 | ((ch_cp1 >> 18) & 0x07));
        utf32le_src_ch->comp.byte2 = (FMC_Byte)(0x80 | ((ch_cp1 >> 12) & 0x3F));
        utf32le_src_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp1 >> 6) & 0x3F));
        utf32le_src_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp1 & 0x3F));
        utf32le_src_ch->encoding = utf8;
        utf32le_src_ch->byteNumber = 4;
        utf32le_src_ch->isNull = FMC_FALSE;
    }
    if (put_bom) utf32le_src_ch->encoding = utf8_bom;
    return utf32le_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf8_dest_ch
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF32LE(utf32le_src_ch);
    return FMC_UTF8FromCodePoint(ch_cp2, put_bom);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF32LEToUTF16LE(FMC_Char* restrict utf32le_src_ch, FMC_Char* restrict utf16le_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf32le_src_ch)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32le_src_ch) is NULL", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf16le_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf16le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf16le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF32LE(utf32le_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32le_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }

        if (ch_cp <= 0xFFFF)
        {
            utf16le_dest_ch->comp.byte0 = (FMC_Byte)((ch_cp >> 8) & 0xFF);
            utf16le_dest_ch->comp.byte1 = (FMC_Byte)(ch_cp & 0xFF);
            utf16le_dest_ch->encoding = utf16_le;
            utf16le_dest_ch->byteNumber = 2;
            utf16le_dest_ch->isNull = ch_cp == 0;
        }
        else // ch_cp <= 0x10FFFF
        {
            ch_cp -= 0x10000;
            uint16_t low_surr = (uint16_t)((ch_cp >> 10) + 0xDC00);
            uint16_t high_surr = (uint16_t)((ch_cp & 0x3FF) + 0xD800);
            low_surr = FMC_bitSwap(16, low_surr);
            high_surr = FMC_bitSwap(16, high_surr);
            utf16le_dest_ch->comp.byte0 = (FMC_Byte)(low_surr & 0xFF);
            utf16le_dest_ch->comp.byte1 = (FMC_Byte)((low_surr >> 8) & 0xFF);
            utf16le_dest_ch->comp.byte2 = (FMC_Byte)(high_surr & 0xFF);
            utf16le_dest_ch->comp.byte3 = (FMC_Byte)((high_surr >> 8) & 0xFF);
            utf16le_dest_ch->encoding = utf16_le;
            utf16le_dest_ch->byteNumber = 4;
            utf16le_dest_ch->isNull = FMC_FALSE;
        }
        return utf16le_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf32le_src_ch to make it UTF16LE
    FMC_CodePoint ch_cp1 = FMC_codePointFromUTF32LE(utf32le_src_ch);
    if (!FMC_isValidUnicode(ch_cp1))
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32le_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }

    if (ch_cp1 <= 0xFFFF)
    {
        utf32le_src_ch->comp.byte0 = (FMC_Byte)((ch_cp1 >> 8) & 0xFF);
        utf32le_src_ch->comp.byte1 = (FMC_Byte)(ch_cp1 & 0xFF);
        utf32le_src_ch->encoding = utf16_le;
        utf32le_src_ch->byteNumber = 2;
        utf32le_src_ch->isNull = ch_cp1 == 0;
    }
    else // ch_cp <= 0x10FFFF
    {
        ch_cp1 -= 0x10000;
        uint16_t low_surr = (uint16_t)((ch_cp1 >> 10) + 0xDC00);
        uint16_t high_surr = (uint16_t)((ch_cp1 & 0x3FF) + 0xD800);
        low_surr = FMC_bitSwap(16, low_surr);
        high_surr = FMC_bitSwap(16, high_surr);
        utf32le_src_ch->comp.byte0 = (FMC_Byte)(low_surr & 0xFF);
        utf32le_src_ch->comp.byte1 = (FMC_Byte)((low_surr >> 8) & 0xFF);
        utf32le_src_ch->comp.byte2 = (FMC_Byte)(high_surr & 0xFF);
        utf32le_src_ch->comp.byte3 = (FMC_Byte)((high_surr >> 8) & 0xFF);
        utf32le_src_ch->encoding = utf16_le;
        utf32le_src_ch->byteNumber = 4;
        utf32le_src_ch->isNull = FMC_FALSE;
    }
    return utf32le_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf16le_dest_ch
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF32LE(utf32le_src_ch);
    return FMC_UTF16LEFromCodePoint(ch_cp2);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF32LEToUTF16BE(FMC_Char* restrict utf32le_src_ch, FMC_Char* restrict utf16be_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf32le_src_ch)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32le_src_ch) is NULL", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf16be_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf16be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf16be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF32LE(utf32le_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32le_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }

        if (ch_cp <= 0xFFFF)
        {
            utf16be_dest_ch->comp.byte0 = (FMC_Byte)(ch_cp & 0xFF);
            utf16be_dest_ch->comp.byte1 = (FMC_Byte)((ch_cp >> 8) & 0xFF);
            utf16be_dest_ch->encoding = utf16_be;
            utf16be_dest_ch->byteNumber = 2;
            utf16be_dest_ch->isNull = ch_cp == 0;
        }
        else // ch_cp <= 0x10FFFF
        {
            ch_cp -= 0x10000;
            uint16_t low_surr = (uint16_t)(0xDC00 | (ch_cp & 0x3FF));
            uint16_t high_surr = (uint16_t)(0xD800 | ((ch_cp >> 10) & 0x3FF));
            utf16be_dest_ch->comp.byte0 = (FMC_Byte)(low_surr & 0xFF);
            utf16be_dest_ch->comp.byte1 = (FMC_Byte)((low_surr >> 8) & 0xFF);
            utf16be_dest_ch->comp.byte2 = (FMC_Byte)(high_surr & 0xFF);
            utf16be_dest_ch->comp.byte3 = (FMC_Byte)((high_surr >> 8) & 0xFF);
            utf16be_dest_ch->encoding = utf16_be;
            utf16be_dest_ch->byteNumber = 4;
            utf16be_dest_ch->isNull = FMC_FALSE;
        }
        return utf16be_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf32le_src_ch to make it UTF16BE
    FMC_CodePoint ch_cp1 = FMC_codePointFromUTF32LE(utf32le_src_ch);
    if (!FMC_isValidUnicode(ch_cp1))
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32le_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }

    if (ch_cp1 <= 0xFFFF)
    {
        utf32le_src_ch->comp.byte0 = (FMC_Byte)(ch_cp1 & 0xFF);
        utf32le_src_ch->comp.byte1 = (FMC_Byte)((ch_cp1 >> 8) & 0xFF);
        utf32le_src_ch->encoding = utf16_be;
        utf32le_src_ch->byteNumber = 2;
        utf32le_src_ch->isNull = ch_cp1 == 0;
    }
    else // ch_cp <= 0x10FFFF
    {
        ch_cp1 -= 0x10000;
        uint16_t low_surr = (uint16_t)(0xDC00 | (ch_cp1 & 0x3FF));
        uint16_t high_surr = (uint16_t)(0xD800 | ((ch_cp1 >> 10) & 0x3FF));
        utf32le_src_ch->comp.byte0 = (FMC_Byte)(low_surr & 0xFF);
        utf32le_src_ch->comp.byte1 = (FMC_Byte)((low_surr >> 8) & 0xFF);
        utf32le_src_ch->comp.byte2 = (FMC_Byte)(high_surr & 0xFF);
        utf32le_src_ch->comp.byte3 = (FMC_Byte)((high_surr >> 8) & 0xFF);
        utf32le_src_ch->encoding = utf16_be;
        utf32le_src_ch->byteNumber = 4;
        utf32le_src_ch->isNull = FMC_FALSE;
    }
    return utf32le_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf16be_dest_ch
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF32LE(utf32le_src_ch);
    return FMC_UTF16BEFromCodePoint(ch_cp2);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF32LEToUTF32BE(FMC_Char* restrict utf32le_src_ch, FMC_Char* restrict utf32be_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf32le_src_ch)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32le_src_ch) is NULL", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf32be_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf32be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf32be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else
    {
        utf32be_dest_ch->comp.byte0 = utf32le_src_ch->comp.byte3;
        utf32be_dest_ch->comp.byte1 = utf32le_src_ch->comp.byte2;
        utf32be_dest_ch->comp.byte2 = utf32le_src_ch->comp.byte1;
        utf32be_dest_ch->comp.byte3 = utf32le_src_ch->comp.byte0;
        utf32be_dest_ch->encoding = utf32_be;
        utf32be_dest_ch->byteNumber = 4;
        utf32be_dest_ch->isNull = utf32le_src_ch->isNull;
        return utf32be_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf32le_src_ch to make it UTF32BE
    FMC_Char tmp = *utf32le_src_ch;
    utf32le_src_ch->comp.byte0 = tmp.comp.byte3;
    utf32le_src_ch->comp.byte1 = tmp.comp.byte2;
    utf32le_src_ch->comp.byte2 = tmp.comp.byte1;
    utf32le_src_ch->comp.byte3 = tmp.comp.byte0;
    utf32le_src_ch->encoding = utf32_be;
    utf32le_src_ch->byteNumber = 4;
    utf32le_src_ch->isNull = tmp.isNull;
    return utf32le_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf32be_dest_ch
    FMC_Char* ret = FMC_allocChar((FMC_Byte[4]){[0] = utf32le_src_ch->comp.byte3, [1] = utf32le_src_ch->comp.byte2, [2] = utf32le_src_ch->comp.byte1, [3] = utf32le_src_ch->comp.byte0}, utf32_be, utf32le_src_ch->isNull, utf32le_src_ch->byteNumber);
    if (!ret)
    {
        FMC_HANDLE_ERR(FMC_ERR_ALLOC_FAILED, "failed to allocate memory for ret", err_alloc, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    return ret;
    FMC_UNREACHABLE;
}


FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF32BEToUTF8(FMC_Char* restrict utf32be_src_ch, FMC_Char* restrict utf8_dest_ch, unsigned int flags, FMC_Bool put_bom)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf32be_src_ch)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32be_src_ch) is NULL", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf8_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf8_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf8_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF32BE(utf32be_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32be_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }

        if (ch_cp <= 0x7F)
        {
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(ch_cp & 0xFF);
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 1;
            utf8_dest_ch->isNull = ch_cp == 0;
        }
        else if (ch_cp <= 0x7FF)
        {
            utf8_dest_ch->comp.byte1 = (FMC_Byte)(0xC0 | ((ch_cp >> 6) & 0x1F));
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp & 0x3F));
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 2;
            utf8_dest_ch->isNull = FMC_FALSE;
        }
        else if (ch_cp <= 0xFFFF)
        {
            utf8_dest_ch->comp.byte2 = (FMC_Byte)(0xE0 | ((ch_cp >> 12) & 0x0F));
            utf8_dest_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp >> 6) & 0x3F));
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp & 0x3F));
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 3;
            utf8_dest_ch->isNull = FMC_FALSE;
        }
        else // ch_cp <= 0x10FFFF
        {
            utf8_dest_ch->comp.byte3 = (FMC_Byte)(0xF0 | ((ch_cp >> 18) & 0x07));
            utf8_dest_ch->comp.byte2 = (FMC_Byte)(0x80 | ((ch_cp >> 12) & 0x3F));
            utf8_dest_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp >> 6) & 0x3F));
            utf8_dest_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp & 0x3F));
            utf8_dest_ch->encoding = utf8;
            utf8_dest_ch->byteNumber = 4;
            utf8_dest_ch->isNull = FMC_FALSE;
        }
        if (put_bom) utf8_dest_ch->encoding = utf8_bom;
        return utf8_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf32be_src_ch to make it UTF8
    FMC_CodePoint ch_cp1 = FMC_codePointFromUTF32BE(utf32be_src_ch);
    if (!FMC_isValidUnicode(ch_cp1))
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32be_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }

    if (ch_cp1 <= 0x7F)
    {
        utf32be_src_ch->comp.byte0 = (FMC_Byte)(ch_cp1 & 0xFF);
        utf32be_src_ch->encoding = utf8;
        utf32be_src_ch->byteNumber = 1;
        utf32be_src_ch->isNull = ch_cp1 == 0;
    }
    else if (ch_cp1 <= 0x7FF)
    {
        utf32be_src_ch->comp.byte1 = (FMC_Byte)(0xC0 | ((ch_cp1 >> 6) & 0x1F));
        utf32be_src_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp1 & 0x3F));
        utf32be_src_ch->encoding = utf8;
        utf32be_src_ch->byteNumber = 2;
        utf32be_src_ch->isNull = FMC_FALSE;
    }
    else if (ch_cp1 <= 0xFFFF)
    {
        utf32be_src_ch->comp.byte2 = (FMC_Byte)(0xE0 | ((ch_cp1 >> 12) & 0x0F));
        utf32be_src_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp1 >> 6) & 0x3F));
        utf32be_src_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp1 & 0x3F));
        utf32be_src_ch->encoding = utf8;
        utf32be_src_ch->byteNumber = 3;
        utf32be_src_ch->isNull = FMC_FALSE;
    }
    else // ch_cp <= 0x10FFFF
    {
        utf32be_src_ch->comp.byte3 = (FMC_Byte)(0xF0 | ((ch_cp1 >> 18) & 0x07));
        utf32be_src_ch->comp.byte2 = (FMC_Byte)(0x80 | ((ch_cp1 >> 12) & 0x3F));
        utf32be_src_ch->comp.byte1 = (FMC_Byte)(0x80 | ((ch_cp1 >> 6) & 0x3F));
        utf32be_src_ch->comp.byte0 = (FMC_Byte)(0x80 | (ch_cp1 & 0x3F));
        utf32be_src_ch->encoding = utf8;
        utf32be_src_ch->byteNumber = 4;
        utf32be_src_ch->isNull = FMC_FALSE;
    }
    if (put_bom) utf32be_src_ch->encoding = utf8_bom;
    return utf32be_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf8_dest_ch
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF32BE(utf32be_src_ch);
    return FMC_UTF8FromCodePoint(ch_cp2, put_bom);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF32BEToUTF16LE(FMC_Char* restrict utf32be_src_ch, FMC_Char* restrict utf16le_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf32be_src_ch)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32be_src_ch) is NULL", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf16le_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf16le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf16le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF32BE(utf32be_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32be_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }

        if (ch_cp <= 0xFFFF)
        {
            utf16le_dest_ch->comp.byte0 = (FMC_Byte)((ch_cp >> 8) & 0xFF);
            utf16le_dest_ch->comp.byte1 = (FMC_Byte)(ch_cp & 0xFF);
            utf16le_dest_ch->encoding = utf16_le;
            utf16le_dest_ch->byteNumber = 2;
            utf16le_dest_ch->isNull = ch_cp == 0;
        }
        else // ch_cp <= 0x10FFFF
        {
            ch_cp -= 0x10000;
            uint16_t low_surr = (uint16_t)((ch_cp >> 10) + 0xDC00);
            uint16_t high_surr = (uint16_t)((ch_cp & 0x3FF) + 0xD800);
            low_surr = FMC_bitSwap(16, low_surr);
            high_surr = FMC_bitSwap(16, high_surr);
            utf16le_dest_ch->comp.byte0 = (FMC_Byte)(low_surr & 0xFF);
            utf16le_dest_ch->comp.byte1 = (FMC_Byte)((low_surr >> 8) & 0xFF);
            utf16le_dest_ch->comp.byte2 = (FMC_Byte)(high_surr & 0xFF);
            utf16le_dest_ch->comp.byte3 = (FMC_Byte)((high_surr >> 8) & 0xFF);
            utf16le_dest_ch->encoding = utf16_le;
            utf16le_dest_ch->byteNumber = 4;
            utf16le_dest_ch->isNull = FMC_FALSE;
        }
        return utf16le_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf32be_src_ch to make it UTF16LE
    FMC_CodePoint ch_cp1 = FMC_codePointFromUTF32BE(utf32be_src_ch);
    if (!FMC_isValidUnicode(ch_cp1))
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32be_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }

    if (ch_cp1 <= 0xFFFF)
    {
        utf32be_src_ch->comp.byte0 = (FMC_Byte)((ch_cp1 >> 8) & 0xFF);
        utf32be_src_ch->comp.byte1 = (FMC_Byte)(ch_cp1 & 0xFF);
        utf32be_src_ch->encoding = utf16_le;
        utf32be_src_ch->byteNumber = 2;
        utf32be_src_ch->isNull = ch_cp1 == 0;
    }
    else // ch_cp <= 0x10FFFF
    {
        ch_cp1 -= 0x10000;
        uint16_t low_surr = (uint16_t)((ch_cp1 >> 10) + 0xDC00);
        uint16_t high_surr = (uint16_t)((ch_cp1 & 0x3FF) + 0xD800);
        low_surr = FMC_bitSwap(16, low_surr);
        high_surr = FMC_bitSwap(16, high_surr);
        utf32be_src_ch->comp.byte0 = (FMC_Byte)(low_surr & 0xFF);
        utf32be_src_ch->comp.byte1 = (FMC_Byte)((low_surr >> 8) & 0xFF);
        utf32be_src_ch->comp.byte2 = (FMC_Byte)(high_surr & 0xFF);
        utf32be_src_ch->comp.byte3 = (FMC_Byte)((high_surr >> 8) & 0xFF);
        utf32be_src_ch->encoding = utf16_le;
        utf32be_src_ch->byteNumber = 4;
        utf32be_src_ch->isNull = FMC_FALSE;
    }
    return utf32be_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf16le_dest_ch
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF32BE(utf32be_src_ch);
    return FMC_UTF16LEFromCodePoint(ch_cp2);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF32BEToUTF16BE(FMC_Char* restrict utf32be_src_ch, FMC_Char* restrict utf16be_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf32be_src_ch)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32be_src_ch) is NULL", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf16be_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf16be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf16be_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else
    {
        FMC_CodePoint ch_cp = FMC_codePointFromUTF32BE(utf32be_src_ch);
        if (!FMC_isValidUnicode(ch_cp))
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32be_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }

        if (ch_cp <= 0xFFFF)
        {
            utf16be_dest_ch->comp.byte0 = (FMC_Byte)(ch_cp & 0xFF);
            utf16be_dest_ch->comp.byte1 = (FMC_Byte)((ch_cp >> 8) & 0xFF);
            utf16be_dest_ch->encoding = utf16_be;
            utf16be_dest_ch->byteNumber = 2;
            utf16be_dest_ch->isNull = ch_cp == 0;
        }
        else // ch_cp <= 0x10FFFF
        {
            ch_cp -= 0x10000;
            uint16_t low_surr = (uint16_t)(0xDC00 | (ch_cp & 0x3FF));
            uint16_t high_surr = (uint16_t)(0xD800 | ((ch_cp >> 10) & 0x3FF));
            utf16be_dest_ch->comp.byte0 = (FMC_Byte)(low_surr & 0xFF);
            utf16be_dest_ch->comp.byte1 = (FMC_Byte)((low_surr >> 8) & 0xFF);
            utf16be_dest_ch->comp.byte2 = (FMC_Byte)(high_surr & 0xFF);
            utf16be_dest_ch->comp.byte3 = (FMC_Byte)((high_surr >> 8) & 0xFF);
            utf16be_dest_ch->encoding = utf16_be;
            utf16be_dest_ch->byteNumber = 4;
            utf16be_dest_ch->isNull = FMC_FALSE;
        }
        return utf16be_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf32be_src_ch to make it UTF16BE
    FMC_CodePoint ch_cp1 = FMC_codePointFromUTF32BE(utf32be_src_ch);
    if (!FMC_isValidUnicode(ch_cp1))
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32be_src_ch) is not a valid unicode code point", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }

    if (ch_cp1 <= 0xFFFF)
    {
        utf32be_src_ch->comp.byte0 = (FMC_Byte)(ch_cp1 & 0xFF);
        utf32be_src_ch->comp.byte1 = (FMC_Byte)((ch_cp1 >> 8) & 0xFF);
        utf32be_src_ch->encoding = utf16_be;
        utf32be_src_ch->byteNumber = 2;
        utf32be_src_ch->isNull = ch_cp1 == 0;
    }
    else // ch_cp <= 0x10FFFF
    {
        ch_cp1 -= 0x10000;
        uint16_t low_surr = (uint16_t)(0xDC00 | (ch_cp1 & 0x3FF));
        uint16_t high_surr = (uint16_t)(0xD800 | ((ch_cp1 >> 10) & 0x3FF));
        utf32be_src_ch->comp.byte0 = (FMC_Byte)(low_surr & 0xFF);
        utf32be_src_ch->comp.byte1 = (FMC_Byte)((low_surr >> 8) & 0xFF);
        utf32be_src_ch->comp.byte2 = (FMC_Byte)(high_surr & 0xFF);
        utf32be_src_ch->comp.byte3 = (FMC_Byte)((high_surr >> 8) & 0xFF);
        utf32be_src_ch->encoding = utf16_be;
        utf32be_src_ch->byteNumber = 4;
        utf32be_src_ch->isNull = FMC_FALSE;
    }
    return utf32be_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf16be_dest_ch
    FMC_CodePoint ch_cp2 = FMC_codePointFromUTF32BE(utf32be_src_ch);
    return FMC_UTF16BEFromCodePoint(ch_cp2);
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char* FMC_UTF32BEToUTF32LE(FMC_Char* restrict utf32be_src_ch, FMC_Char* restrict utf32le_dest_ch, unsigned int flags)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf32be_src_ch)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 1 (utf32be_src_ch) is NULL", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (!utf32le_dest_ch)
    {
        check_in flags if_not_set(MODIFY, ALLOC_NEW)
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf32le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are not set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
        else check_in flags for_only_flags(MODIFY) goto modify;
        else check_in flags for_only_flags(ALLOC_NEW) goto alloc_new;
        else
        {
            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "argument 2 (utf32le_dest_ch) is NULL and MODIFY and ALLOC_NEW flags are both set", err_arg, FMC_FALSE);
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else
    {
        utf32le_dest_ch->comp.byte0 = utf32be_src_ch->comp.byte3;
        utf32le_dest_ch->comp.byte1 = utf32be_src_ch->comp.byte2;
        utf32le_dest_ch->comp.byte2 = utf32be_src_ch->comp.byte1;
        utf32le_dest_ch->comp.byte3 = utf32be_src_ch->comp.byte0;
        utf32le_dest_ch->encoding = utf32_le;
        utf32le_dest_ch->byteNumber = 4;
        utf32le_dest_ch->isNull = utf32be_src_ch->isNull;
        return utf32le_dest_ch;
        FMC_UNREACHABLE;
    }

modify: // modify utf32be_src_ch to make it UTF32LE
    FMC_Char tmp = *utf32be_src_ch;
    utf32be_src_ch->comp.byte0 = tmp.comp.byte3;
    utf32be_src_ch->comp.byte1 = tmp.comp.byte2;
    utf32be_src_ch->comp.byte2 = tmp.comp.byte1;
    utf32be_src_ch->comp.byte3 = tmp.comp.byte0;
    utf32be_src_ch->encoding = utf32_le;
    utf32be_src_ch->byteNumber = 4;
    utf32be_src_ch->isNull = tmp.isNull;
    return utf32be_src_ch;
    FMC_UNREACHABLE;

alloc_new: // allocate new utf32le_dest_ch
    FMC_Char* ret = FMC_allocChar((FMC_Byte[4]){[0] = utf32be_src_ch->comp.byte3, [1] = utf32be_src_ch->comp.byte2, [2] = utf32be_src_ch->comp.byte1, [3] = utf32be_src_ch->comp.byte0}, utf32_le, utf32be_src_ch->isNull, utf32be_src_ch->byteNumber);
    if (!ret)
    {
        FMC_HANDLE_ERR(FMC_ERR_ALLOC_FAILED, "failed to allocate memory for utf32le_dest_ch", err_alloc, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    return ret;
    FMC_UNREACHABLE;
}
