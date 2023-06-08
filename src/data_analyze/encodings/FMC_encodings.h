/*

MIT License

Copyright (c) 2023 Axel PASCON

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

#ifndef FMC_ENCODINGS_H
#define FMC_ENCODINGS_H

#include "../../general/FMC_general.h"
#include "conversions/FMC_conversions.h"

FMC_BEGIN_DECLS

FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1) FMC_Encodings FMC_getEncoding(FILE *file);

// TODO: add more functions to get encoding from a file path or a FMC_String, for example

/* FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1) FMC_Encodings FMC_getEncoding_FILE(FILE *file);
FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1) FMC_Encodings FMC_getEncoding_FMC_File(FMC_File* file);
FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1) FMC_Encodings FMC_getEncoding_filePath(char* path);
FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1) FMC_Encodings FMC_getEncoding_FMC_String(FMC_String* string);

#define FMC_getEncoding(x) _Generic((x), \
    FILE*: FMC_getEncoding_FILE, \
    FMC_File*: FMC_getEncoding_FMC_File, \
    char*: FMC_getEncoding_filePath, \
    FMC_String*: FMC_getEncoding_FMC_String \
)(x) */


FMC_SHARED FMC_DEF_SYM(FMC_checkEncodingFlag, 1_0_0) FMC_FUNC_CONST FMC_FUNC_ALWAYS_INLINE inline FMC_Encodings FMC_checkEncodingFlag(unsigned int encoding)
{
    switch (encoding)
    {
        case ASCII:
            return ascii;
            break;
        case UTF8:
            return utf8;
            break;
        case UTF8_BOM:
            return utf8_bom;
            break;
        case UTF16_LE:
            return utf16_le;
            break;
        case UTF16_BE:
            return utf16_be;
            break;
        case UTF32_LE:
            return utf32_le;
            break;
        case UTF32_BE:
            return utf32_be;
            break;
        default: // TODO : add error in case of unknown encoding
            return unknown;
            break;
    }
    return error;
}

FMC_END_DECLS

#endif // FMC_ENCODINGS_H
