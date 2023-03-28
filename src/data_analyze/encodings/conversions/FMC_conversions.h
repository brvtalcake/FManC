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

#ifndef FMC_CONVERSIONS_H
#define FMC_CONVERSIONS_H

#include "../../../general/FMC_general.h"

FMC_BEGIN_DECLS

FMC_SHARED FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF8_FMC_Char(const FMC_Char utf8_char);
FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF8_FMC_CharComp(const FMC_CharComp utf8_char_comp);
FMC_SHARED FMC_FUNC_CONST FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF8_uint32_t(const uint32_t raw_utf8_encoded_char);
FMC_SHARED FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF8_FMC_Char_ptr(const FMC_Char* restrict const utf8_char);
FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF8_FMC_CharComp_ptr(const FMC_CharComp* restrict const utf8_char_comp);
FMC_SHARED FMC_FUNC_CONST FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF8_uint32_t_ptr(const uint32_t* restrict const raw_utf8_encoded_char);

#define FMC_codePointFromUTF8(x) _Generic((x),              \
    FMC_Char*     : FMC_codePointFromUTF8_FMC_Char_ptr,     \
    FMC_Char      : FMC_codePointFromUTF8_FMC_Char,         \
    FMC_CharComp* : FMC_codePointFromUTF8_FMC_CharComp_ptr, \
    FMC_CharComp  : FMC_codePointFromUTF8_FMC_CharComp,     \
    uint32_t*     : FMC_codePointFromUTF8_uint32_t_ptr,     \
    uint32_t      : FMC_codePointFromUTF8_uint32_t)(x)


FMC_SHARED FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF16LE_FMC_Char(const FMC_Char utf16le_char);
FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF16LE_FMC_CharComp(const FMC_CharComp utf16le_char_comp);
FMC_SHARED FMC_FUNC_CONST FMC_FUNC_HOT FMC_CodePoint FMC_codePointFromUTF16LE_uint32_t(const uint32_t raw_utf16le_char);
FMC_SHARED FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF16LE_FMC_Char_ptr(const FMC_Char* restrict const utf16le_char);
FMC_SHARED FMC_FUNC_PURE FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF16LE_FMC_CharComp_ptr(const FMC_CharComp* restrict const utf16le_char_comp);
FMC_SHARED FMC_FUNC_CONST FMC_FUNC_HOT FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF16LE_uint32_t_ptr(const uint32_t* restrict const raw_utf16le_char);

#define FMC_codePointFromUTF16LE(x) _Generic((x),          \
    FMC_Char*     : FMC_codePointFromUTF16LE_FMC_Char_ptr, \
    FMC_Char      : FMC_codePointFromUTF16LE_FMC_Char,     \
    FMC_CharComp* : FMC_codePointFromUTF16LE_FMC_Char_ptr, \
    FMC_CharComp  : FMC_codePointFromUTF16LE_FMC_Char,     \
    uint32_t*     : FMC_codePointFromUTF16LE_FMC_Char_ptr, \
    uint32_t      : FMC_codePointFromUTF16LE_FMC_Char)(x)



#define FMC_codePointFromUTF16BE(x) _Generic((x),          \
    FMC_Char*     : FMC_codePointFromUTF16BE_FMC_Char_ptr, \
    FMC_Char      : FMC_codePointFromUTF16BE_FMC_Char,     \
    FMC_CharComp* : FMC_codePointFromUTF16BE_FMC_Char_ptr, \
    FMC_CharComp  : FMC_codePointFromUTF16BE_FMC_Char,     \
    uint32_t*     : FMC_codePointFromUTF16BE_FMC_Char_ptr, \
    uint32_t      : FMC_codePointFromUTF16BE_FMC_Char)(x)

FMC_END_DECLS

#endif // FMC_CONVERSIONS_H
