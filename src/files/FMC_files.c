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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "FMC_file_management.h"
#include "../data_analyze/encodings/FMC_encodings.h"
#include "../cpp/FMC_wrapper.h"

/* #define TO_OPEN 16U
#define GET_ENCODING 32U
#define GET_SIZE 64U
#define BYTE_ORIENTED 128U
#define WIDE_ORIENTED 256U

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

// TODO : FMC_getFileSize
// TODO : FMC_setFileOrientation



FMC_SHARED FMC_File *FMC_createFile(const unsigned int user_flags, const char* restrict const path, const char* restrict const mode)
{
    if (!path || !mode || user_flags == 0U || FMC_isRegFile(path) != 1)
    {
        return NULL;
    }

    char tmp_path[MAX_FPATH_SIZE];
    char tmp_name[MAX_FNAME_SIZE];
    char tmp_ext[MAX_FEXT_SIZE];

    if (!FMC_cutFilename(path, tmp_path, MAX_FPATH_SIZE))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_cut_name, 1, "INTERNAL ERROR: FMC_createFile: FMC_cutFilename failed.");
            FMC_printRedError(stderr, err_cut_name);
        }
        FMC_setError(FMC_INTERNAL_ERROR, "FMC_createFile: FMC_cutFilename failed.");
        return NULL;
        FMC_UNREACHABLE;
    }

    if (!FMC_extractFilename(path, tmp_path, MAX_FNAME_SIZE))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_extr_name, 1, "INTERNAL ERROR: FMC_createFile: FMC_extractFilename failed.");
            FMC_printRedError(stderr, err_extr_name);
        }
        FMC_setError(FMC_INTERNAL_ERROR, "FMC_createFile: FMC_extractFilename failed.");
        return NULL;
        FMC_UNREACHABLE;
    }

    if (!FMC_getExtension(path, tmp_ext, MAX_FEXT_SIZE))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_get_ext, 1, "INTERNAL ERROR: FMC_createFile: FMC_getExtension failed.");
            FMC_printRedError(stderr, err_get_ext);
        }
        FMC_setError(FMC_INTERNAL_ERROR, "FMC_createFile: FMC_getExtension failed.");
        return NULL;
        FMC_UNREACHABLE;
    }

    FMC_File *returned_file = malloc(sizeof(FMC_File));
    if (!returned_file)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_malloc1, 1, "INTERNAL ERROR: FMC_createFile: malloc failed to allocate memory for the file struct.");
            FMC_printRedError(stderr, err_malloc1);
        }
        FMC_setError(FMC_INTERNAL_ERROR, "FMC_createFile: malloc failed to allocate memory for the file struct.");
        return NULL;
        FMC_UNREACHABLE;
    }

    check_in user_flags if_not_set(TO_OPEN) // create the file struct but do not open the FILE
    {
        returned_file->isOpened = False;
        returned_file->file = NULL;
        returned_file->fileSize = 0ULL;
        returned_file->encoding = unknown;
        returned_file->orientation = undefined;
        strncpy(returned_file->path, tmp_path, MAX_FPATH_SIZE);
        strncpy(returned_file->name, tmp_name, MAX_FNAME_SIZE);
        strncpy(returned_file->extension, tmp_ext, MAX_FEXT_SIZE);
        memset(returned_file->mode, '\0', 10);
        return returned_file;
        FMC_UNREACHABLE;
    }
    else check_in user_flags for_at_least_flags(TO_OPEN)
    {
        check_in user_flags for_at_least_flags(BYTE_ORIENTED)
        {
            
        }
    }

    
}

/* #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!path)
    {
        return NULL;
    }
    #pragma GCC diagnostic pop // -Wnonnull-compare */

/* FMC_SHARED FMC_File *FMC_openFile();

FMC_SHARED static FMC_File *FMC_open_getEncoding();

FMC_SHARED static FMC_File *FMC_open_getSize();

FMC_SHARED static FMC_File *FMC_open_getEncoding_getSize(); */

