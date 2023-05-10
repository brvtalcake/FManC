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
            utf16be_dest_ch->comp.byte0 = (FMC_Byte)((high_surr >> 8) & 0xFF);
            utf16be_dest_ch->comp.byte1 = (FMC_Byte)(high_surr & 0xFF);
            utf16be_dest_ch->comp.byte2 = (FMC_Byte)((low_surr >> 8) & 0xFF);
            utf16be_dest_ch->comp.byte3 = (FMC_Byte)(low_surr & 0xFF);
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
        utf8_src_ch->comp.byte0 = (FMC_Byte)((high_surr >> 8) & 0xFF);
        utf8_src_ch->comp.byte1 = (FMC_Byte)(high_surr & 0xFF);
        utf8_src_ch->comp.byte2 = (FMC_Byte)((low_surr >> 8) & 0xFF);
        utf8_src_ch->comp.byte3 = (FMC_Byte)(low_surr & 0xFF);
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
