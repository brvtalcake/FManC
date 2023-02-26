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

#pragma once

#ifndef FMC_FLAGS
#define FMC_FLAGS

#if defined(check_in) || defined(for_flags)
    #undef check_in
    #undef for_flags
#endif // check_in || for_flags
#define check_in if(( 
#define for_flags(...) ) &


#if defined(FMC_ENCODING_FLAGS) || defined(UTF8) || defined(UTF8_BOM) || defined(UTF16_LE) || defined(UTF16_BE) || defined(UTF32_LE) || defined(UTF32_BE) || defined(ASCII) || defined(UNKNOWN)
    #undef FMC_ENCODING_FLAGS
    #undef UTF8
    #undef UTF8_BOM
    #undef UTF16_LE
    #undef UTF16_BE
    #undef UTF32_LE
    #undef UTF32_BE
    #undef ASCII
    #undef UNKNOWN
#endif
#define FMC_ENCODING_FLAGS
#define UTF8 1U
#define UTF8_BOM 2U
#define UTF16_LE 4U
#define UTF16_BE 8U
#define UTF32_LE 16U
#define UTF32_BE 32U
#define ASCII 64U
#define UNKNOWN 128U

#if defined(FMC_C_STR_VIEW) || defined(C_STR) || defined(FMC_C_STR_VIEW_PTR) || defined(C_STR_PTR) || defined(TO_OPEN) || defined(GET_ENCODING)
    #undef FMC_C_STR_VIEW_PTR
    #undef C_STR_PTR
    #undef TO_OPEN
    #undef GET_ENCODING
    #undef C_STR
    #undef FMC_C_STR_VIEW
#endif // FMC_CSTR || C_STR || FMC_C_STR_VIEW_PTR || C_STR_PTR || TO_OPEN || GET_ENCODING
#define FMC_C_STR_VIEW 1U
#define C_STR 2U
#define FMC_C_STR_VIEW_PTR 4U
#define C_STR_PTR 8U
#define TO_OPEN 16U
#define GET_ENCODING 32U

#endif // FMC_FLAGS
