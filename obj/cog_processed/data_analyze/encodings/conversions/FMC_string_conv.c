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
#include "../FMC_encodings.h"

#if 0

FMC_SHARED FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_String* FMC_convertStr(FMC_String* to_convert, FMC_Encodings dest_enc)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!to_convert)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "the provided argument is NULL", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    if (dest_enc == unknown || dest_enc == error)
    {
        FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "the provided encoding is invalid", err_arg, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    if (!FMC_checkEncoding(to_convert))
    {
        FMC_HANDLE_ERR(FMC_ERR_ENC, "the provided string is not properly encoded", err_enc, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    if (to_convert->firstChar->encoding == unknown || to_convert->firstChar->encoding == error)
    {
        FMC_HANDLE_ERR(FMC_ERR_ENC, "the provided string is not properly encoded", err_enc, FMC_FALSE);
        return NULL;
        FMC_UNREACHABLE;
    }
    if (to_convert->firstChar->encoding == dest_enc) return to_convert;
    if (to_convert->firstChar->encoding == utf8 && dest_enc == utf8_bom)
    {
        for_all_char_in(to_convert, ch)
        {
            ch->encoding = utf8_bom;
        }
        return to_convert;
        FMC_UNREACHABLE;
    }
    if (to_convert->firstChar->encoding == utf8_bom && dest_enc == utf8)
    {
        for_all_char_in(to_convert, ch)
        {
            ch->encoding = utf8;
        }
        return to_convert;
        FMC_UNREACHABLE;
    }
    // TODO: implement the clonage func and uncomment this line
    // FMC_String* cloned_str = FMC_cloneStr(to_convert);
    for_all_char_in(to_convert, ch)
    {
        FMC_Char tmp = FMC_CHAR(NULL, NULL, unknown, FMC_CHARCOMP_NULL, FMC_TRUE, 0);
        switch (ch->encoding)
        {
            case utf8:
            FMC_STMT_FALLTHROUGH;
            case utf8_bom:
            {
                switch (dest_enc)
                {
                    case ascii:
                    {
                        if (FMC_codePointFromUTF8(ch) > 127)
                        {
                            FMC_HANDLE_ERR(FMC_ERR_INVALID_ARGUMENT, "the provided string contains non-ASCII characters and thus cannot be converted to ASCII", err_arg, FMC_FALSE);
                            return NULL;
                            // TODO: implement the clonage func and uncomment this line
                            // return cloned_str;
                            FMC_UNREACHABLE;
                        }
                        else
                        {
                            ch->encoding = ascii;
                            ch->byteNumber = 1;
                            ch->comp.byte1 = 0x00;
                            ch->comp.byte2 = 0x00;
                            ch->comp.byte3 = 0x00;
                        }
                    }
                    break;

                    case utf8:
                    FMC_STMT_FALLTHROUGH;
                    case utf8_bom:
                    {
                        FMC_UNREACHABLE;
                    }
                    break;

                    case utf16_le:
                    {
                        /* FMC_UTF8ToUTF16LE(ch, &tmp); */
                    }
                }
            }
        }
    }
}

#endif // UNIMPLEMENTED