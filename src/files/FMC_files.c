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
#include <wchar.h>

#include "FMC_file_management.h"
#include "../data_analyze/encodings/FMC_encodings.h"
#include "../cpp/FMC_wrapper.h"



// TODO : FMC_getFileSize
// TODO : FMC_setFileOrientation

FMC_SHARED FMC_FUNC_PURE static unsigned int FMC_getDataModeFromMode(const char* const full_mode)
{
    if (!full_mode)
    {
        return 0U;
        FMC_UNREACHABLE;
    }
    char *tmp = NULL;
    if (((tmp = strchr(full_mode, 'b')) != NULL) && tmp - full_mode < 3) return BINARY_MODE;
    else return TEXT_MODE;
    FMC_UNREACHABLE;   
}

FMC_SHARED FMC_FUNC_MALLOC(FMC_freeFile, 1) FMC_File *FMC_allocFile(const unsigned int user_flags, const char* restrict const path, const char* restrict const full_mode)
{
    if (!path || !full_mode || user_flags == 0U || FMC_isRegFile(path) != 1)
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
    FMC_prefetch(tmp_path, FMC_OPT(1, 0));
    FMC_prefetch(tmp_name, FMC_OPT(1, 0));
    FMC_prefetch(tmp_ext, FMC_OPT(1, 0));
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
    memset(returned_file, 0, sizeof(FMC_File));
    strncpy(returned_file->path, tmp_path, MAX_FPATH_SIZE);
    strncpy(returned_file->name, tmp_name, MAX_FNAME_SIZE);
    strncpy(returned_file->extension, tmp_ext, MAX_FEXT_SIZE);

    check_in user_flags if_not_set(TO_OPEN) // create the file struct but do not open the FILE
    {
        returned_file->isOpened = False;
        returned_file->file = NULL;
        returned_file->fileSize = 0ULL;
        returned_file->encoding = unknown;
        returned_file->orientation = not_set;
        returned_file->dataMode = (FMC_getDataModeFromMode(full_mode) == BINARY_MODE ? binary : text);
        strcpy(returned_file->fullMode, full_mode);
        return returned_file;
        FMC_UNREACHABLE;
    }
    else check_in user_flags for_at_least_flags(TO_OPEN)
    {
        returned_file->isOpened = True; // isOpened set
        returned_file->dataMode = (FMC_getDataModeFromMode(full_mode) == BINARY_MODE ? binary : text); // dataMode set
        
        _Bool wanted_encoding = False;
        check_in user_flags if_not_set(GET_ENCODING) returned_file->file = fopen(path, full_mode);
        else 
        {
            returned_file->file = fopen(path, "rb");
            wanted_encoding = True;
        }

        if (!returned_file->file)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_fopen, 1, "INTERNAL ERROR: FMC_createFile: fopen failed to open the file.");
                FMC_printRedError(stderr, err_fopen);
            }
            FMC_setError(FMC_INTERNAL_ERROR, "FMC_createFile: fopen failed to open the file.");
            free(returned_file);
            return NULL;
            FMC_UNREACHABLE;
        }
        
        check_in user_flags for_at_least_flags(GET_ENCODING) // encoding set
        {
            returned_file->encoding = FMC_getEncoding(returned_file->file);
        }
        else returned_file->encoding = unknown;

        if (!strcmp("rb", full_mode) && wanted_encoding) // file set
        {
            fclose(returned_file->file);
            returned_file->file = fopen(path, full_mode);
        }
        
        check_in user_flags for_at_least_flags(GET_SIZE) // size set
        {
            #if defined(_WIN32) || defined(_WIN64)
            LONGLONG file_size = 0LL;
            file_size = FMC_getFileSize(path);
            #else
            off64_t file_size = (off64_t) 0;
            file_size = FMC_getFileSize(path);
            #endif

            char tmp_err_msg[FMC_ERR_STR_LEN];
            memset(tmp_err_msg, '\0', FMC_ERR_STR_LEN);
            FMC_getLastErrorMsg_noDepop(tmp_err_msg, FMC_ERR_STR_LEN);
            if (file_size <= 0 && FMC_getLastErrorNum_noDepop() == FMC_INVALID_ARGUMENT && strstr(tmp_err_msg, "In function 'FMC_getFileSize'"))
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_file_size, 1, "INTERNAL ERROR: FMC_createFile: FMC_getFileSize failed to get the file size. Maybe this is not a regular file?");
                    FMC_printRedError(stderr, err_file_size);
                }
                FMC_setError(FMC_INTERNAL_ERROR, "FMC_createFile: FMC_getFileSize failed to get the file size. Maybe this is not a regular file?");
                free(returned_file);
                return NULL;
                FMC_UNREACHABLE;
            }
            returned_file->fileSize = (unsigned long long) file_size;            
        }
        if (!returned_file->file)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_fopen, 1, "INTERNAL ERROR: FMC_createFile: fopen failed to open the file.");
                FMC_printRedError(stderr, err_fopen);
            }
            FMC_setError(FMC_INTERNAL_ERROR, "FMC_createFile: fopen failed to open the file.");
            free(returned_file);
            return NULL;
            FMC_UNREACHABLE;
        }
        strcpy(returned_file->fullMode, full_mode);

        check_in user_flags for_at_least_flags(WIDE_ORIENTED)
        {
            check_in user_flags if_not_set(BYTE_ORIENTED)
            {
                returned_file->orientation = wide;
            }
            else // error, you can only provide one of both
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_arg_invalid, 1, "FMC_createFile: You can only provide one of both WIDE_ORIENTED and BYTE_ORIENTED flags.");
                    FMC_printRedError(stderr, err_arg_invalid);
                }
                FMC_setError(FMC_INVALID_ARGUMENT, "FMC_createFile: You can only provide one of both WIDE_ORIENTED and BYTE_ORIENTED flags.");
                free(returned_file);
                return NULL;
                FMC_UNREACHABLE;
            }
        }

        check_in user_flags for_at_least_flags(BYTE_ORIENTED)
        {
            check_in user_flags if_not_set(WIDE_ORIENTED)
            {
                returned_file->orientation = byte;
            }
            else // error, you can only provide one of both
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_arg_invalid, 1, "FMC_createFile: You can only provide one of both WIDE_ORIENTED and BYTE_ORIENTED flags.");
                    FMC_printRedError(stderr, err_arg_invalid);
                }
                FMC_setError(FMC_INVALID_ARGUMENT, "FMC_createFile: You can only provide one of both WIDE_ORIENTED and BYTE_ORIENTED flags.");
                free(returned_file);
                return NULL;
                FMC_UNREACHABLE;
            }
        }

        return returned_file;
    }
    FMC_UNREACHABLE;
}


FMC_SHARED FMC_FUNC_NONNULL(1) void FMC_freeFile(FMC_File *file)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!file)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg_null, 1, "Provided argument to FMC_freeFile is NULL.");
            FMC_printRedError(stderr, err_arg_null);
        }
        FMC_setError(FMC_INVALID_ARGUMENT, "Provided argument to FMC_freeFile is NULL.");
        return;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop // -Wnonnull-compare
    
    if (file->isOpened)
    {
        fclose(file->file);
    }
    free(file);
    
    return;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) unsigned int FMC_changeStreamOrientation(FILE* file, unsigned int orientation_flag)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!file)
    {
    #pragma GCC diagnostic pop // -Wnonnull-compare
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg_null, 1, "Provided argument to FMC_changeStreamOrientation is NULL.");
            FMC_printRedError(stderr, err_arg_null);
        }
        FMC_setError(FMC_INVALID_ARGUMENT, "Provided argument to FMC_changeStreamOrientation is NULL.");
        return 0;
        FMC_UNREACHABLE;
    }
    check_in orientation_flag for_only_flags(WIDE_ORIENTED)
    {
        if (fwide(file, 1) <= 0)
        {
            file = freopen(NULL, "w+", file);
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

