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

#include <stdarg.h>
#include "FMC_file_management.h"
#include "../data_analyze/encodings/FMC_encodings.h"

/* #define TO_OPEN 16U
#define GET_ENCODING 32U
#define GET_SIZE 64U
#define BYTE_ORIENTED 128U
#define WIDE_ORIENTED 256U

#define FMC_C_STR_VIEW 1U
#define C_STR 2U
#define FMC_C_STR_VIEW_PTR 4U
#define C_STR_PTR 8U

FMC_SHARED struct FManC_File
{
    FILE *file;
    unsigned long long int fileSize;
    FMC_Encodings encoding;
    enum
    {
        wide,
        byte
    } orientation;
    FMC_FileState isOpened;
    char path[MAX_FPATH_SIZE];
    char name[MAX_FNAME_SIZE];
    char extension[MAX_FEXT_SIZE];
    char mode[10];
}; */

FMC_SHARED FMC_File *FMC_createFile(unsigned int flags, ...)
{
    va_list args;
    check_in flags for_only_flags(FMC_C_STR_VIEW, TO_OPEN)
    {

    }
    else check_in flags for_only_flags(FMC_C_STR_VIEW, GET_ENCODING)
    {

    }
    else check_in flags for_only_flags(FMC_C_STR_VIEW, GET_SIZE)
    {

    }

    FMC_UNREACHABLE;
}

/* #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!path)
    {
        return NULL;
    }
    #pragma GCC diagnostic pop // -Wnonnull-compare */

FMC_SHARED FMC_File *FMC_openFile();

FMC_SHARED static FMC_File *FMC_open_getEncoding();

FMC_SHARED static FMC_File *FMC_open_getSize();

FMC_SHARED static FMC_File *FMC_open_getEncoding_getSize();

