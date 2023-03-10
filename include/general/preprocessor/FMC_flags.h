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

#ifndef FMC_FLAGS_H
#define FMC_FLAGS_H

#include <metalang99.h>

#if defined(check_in) || defined(for_only_flags) || defined(for_at_least_flags) || defined(if_not_set) || defined(FMC_mergeFlags)
    #undef check_in
    #undef for_only_flags
    #undef for_at_least_flags
    #undef if_not_set
    #undef FMC_mergeFlags
#endif // check_in || for_only_flags || for_at_least_flags || if_not_set || FMC_mergeFlags
#define check_in if(((
#define for_only_flags(...) ) | (ML99_LIST_EVAL(ML99_call(ML99_listIntersperse, v(|), ML99_list(v(__VA_ARGS__)))))) == (ML99_LIST_EVAL(ML99_call(ML99_listIntersperse, v(|), ML99_list(v(__VA_ARGS__))))))
#define for_at_least_flags(...) ) & (ML99_LIST_EVAL(ML99_call(ML99_listIntersperse, v(|), ML99_list(v(__VA_ARGS__)))))) == (ML99_LIST_EVAL(ML99_call(ML99_listIntersperse, v(|), ML99_list(v(__VA_ARGS__))))))
#define if_not_set(flags) ) & (flags)) == 0U)
#define FMC_mergeFlags(...) ML99_LIST_EVAL(ML99_call(ML99_listIntersperse, v(|), ML99_list(v(__VA_ARGS__))))


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

#if defined(FMC_C_STR_VIEW) || defined(C_STR) || defined(FMC_C_STR_VIEW_PTR) || defined(C_STR_PTR)
    #undef FMC_C_STR_VIEW_PTR
    #undef C_STR_PTR
    #undef C_STR
    #undef FMC_C_STR_VIEW
#endif // FMC_CSTR || C_STR || FMC_C_STR_VIEW_PTR || C_STR_PTR
#define FMC_C_STR_VIEW 1U
#define C_STR 2U
#define FMC_C_STR_VIEW_PTR 4U
#define C_STR_PTR 8U

#if defined(FMC_FILE_FLAGS) || defined(TO_OPEN) || defined(GET_ENCODING) || defined(GET_SIZE) || defined(BINARY_MODE) || defined(TEXT_MODE) || defined(BYTE_ORIENTED) || defined(WIDE_ORIENTED)
    #undef FMC_FILE_FLAGS
    #undef TO_OPEN
    #undef GET_ENCODING
    #undef GET_SIZE
    #undef BINARY_MODE
    #undef TEXT_MODE
    #undef BYTE_ORIENTED
    #undef WIDE_ORIENTED
#endif // FMC_FILE_FLAGS || TO_OPEN || GET_ENCODING || GET_SIZE || BINARY_MODE || TEXT_MODE || BYTE_ORIENTED || WIDE_ORIENTED
#define FMC_FILE_FLAGS
#define TO_OPEN 16U
#define GET_ENCODING 32U
#define GET_SIZE 64U
#define BINARY_MODE 128U
#define TEXT_MODE 256U
#define BYTE_ORIENTED 512U
#define WIDE_ORIENTED 1024U

#if defined(RM_DIR_RECURSIVE) || defined(RM_DIR_ONLY_CONTENT) || defined(RM_DIR_ONLY_SUBDIRS) || defined(RM_DIR_ONLY_FILES) || defined(CONFIRMATION) || defined(NO_CONFIRMATION)
    #undef RM_DIR_RECURSIVE
    #undef RM_DIR_ONLY_CONTENT
    #undef RM_DIR_ONLY_SUBDIRS
    #undef RM_DIR_ONLY_FILES
    #undef CONFIRMATION
    #undef NO_CONFIRMATION
#endif // RM_DIR_RECURSIVE || RM_DIR_ONLY_CONTENT || RM_DIR_ONLY_SUBDIRS || RM_DIR_ONLY_FILES || CONFIRMATION || NO_CONFIRMATION
#define RM_DIR_RECURSIVE 1U
#define RM_DIR_ONLY_CONTENT 2U
#define RM_DIR_ONLY_SUBDIRS 4U
#define RM_DIR_ONLY_FILES 8U
#define CONFIRMATION 16U
#define NO_CONFIRMATION 32U

#endif // FMC_FLAGS_H
