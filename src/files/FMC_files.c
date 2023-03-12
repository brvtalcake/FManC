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

#if defined(FMC_COMPILING_ON_WINDOWS)
    #include <windows.h>
#else 
    #include <unistd.h>
    #include <sys/stat.h>
    #include <sys/types.h>
#endif


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

FMC_SHARED FMC_FUNC_MALLOC(FMC_freeFile, 1) FMC_File *FMC_allocFile(const char* restrict const path, const char* restrict const full_mode, const unsigned int user_flags)
{
    if (!path || !full_mode || user_flags == 0U || FMC_isRegFile(path) != 1)
    {
        return NULL;
    }

    char tmp_path[MAX_FPATH_SIZE];
    char tmp_name[MAX_FNAME_SIZE];
    char tmp_ext[MAX_FEXT_SIZE];

    memset(tmp_path, 0, MAX_FPATH_SIZE);
    memset(tmp_name, 0, MAX_FNAME_SIZE);
    memset(tmp_ext, 0, MAX_FEXT_SIZE);

    if (!FMC_cutFilename(path, tmp_path, MAX_FPATH_SIZE))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_cut_name, 1, "INTERNAL ERROR: FMC_createFile: FMC_cutFilename failed.");
            FMC_printRedError(stderr, err_cut_name);
        }
        FMC_setError(FMC_ERR_INTERNAL, "FMC_createFile: FMC_cutFilename failed.");
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
        FMC_setError(FMC_ERR_INTERNAL, "FMC_createFile: FMC_extractFilename failed.");
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
        FMC_setError(FMC_ERR_INTERNAL, "FMC_createFile: FMC_getExtension failed.");
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
        FMC_setError(FMC_ERR_INTERNAL, "FMC_createFile: malloc failed to allocate memory for the file struct.");
        return NULL;
        FMC_UNREACHABLE;
    }
    memset(returned_file, 0, sizeof(FMC_File));
    strncpy(returned_file->path, tmp_path, MAX_FPATH_SIZE);
    strncpy(returned_file->name, tmp_name, MAX_FNAME_SIZE);
    strncpy(returned_file->extension, tmp_ext, MAX_FEXT_SIZE);
    returned_file->isOpened = True;
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
            FMC_setError(FMC_ERR_INTERNAL, "FMC_createFile: fopen failed to open the file.");
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
            #if defined(FMC_COMPILING_ON_WINDOWS)
            LONGLONG file_size = 0LL;
            file_size = FMC_getFileSize(path);
            #else
            off64_t file_size = (off64_t) 0;
            file_size = FMC_getFileSize(path);
            #endif

            char tmp_err_msg[FMC_ERR_STR_LEN];
            memset(tmp_err_msg, '\0', FMC_ERR_STR_LEN);
            FMC_getLastErrorStr_noDepop(tmp_err_msg, FMC_ERR_STR_LEN);
            if (file_size <= 0 && FMC_getLastErrorNum_noDepop() == FMC_ERR_INVALID_ARGUMENT && strstr(tmp_err_msg, "In function 'FMC_getFileSize'"))
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_file_size, 1, "INTERNAL ERROR: FMC_createFile: FMC_getFileSize failed to get the file size. Maybe this is not a regular file?");
                    FMC_printRedError(stderr, err_file_size);
                }
                FMC_setError(FMC_ERR_INTERNAL, "FMC_createFile: FMC_getFileSize failed to get the file size. Maybe this is not a regular file?");
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
            FMC_setError(FMC_ERR_INTERNAL, "FMC_createFile: fopen failed to open the file.");
            free(returned_file);
            return NULL;
            FMC_UNREACHABLE;
        }
        strcpy(returned_file->fullMode, full_mode);

        check_in user_flags for_at_least_flags(WIDE_ORIENTED)
        {
            check_in user_flags if_not_set(BYTE_ORIENTED)
            {
                returned_file->orientation = (FMC_changeStreamOrientation(returned_file->file, full_mode, BYTE_ORIENTED) == BYTE_ORIENTED ? byte : failed_to_change); 
            }
            else // error, you can only provide one of both
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_arg_invalid, 1, "FMC_createFile: You can only provide one of both WIDE_ORIENTED and BYTE_ORIENTED flags.");
                    FMC_printRedError(stderr, err_arg_invalid);
                }
                FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_createFile: You can only provide one of both WIDE_ORIENTED and BYTE_ORIENTED flags.");
                fclose(returned_file->file);
                free(returned_file);
                return NULL;
                FMC_UNREACHABLE;
            }
        }

        check_in user_flags for_at_least_flags(BYTE_ORIENTED)
        {
            check_in user_flags if_not_set(WIDE_ORIENTED)
            {
                returned_file->orientation = (FMC_changeStreamOrientation(returned_file->file, full_mode, WIDE_ORIENTED) == WIDE_ORIENTED ? wide : failed_to_change);
            }
            else // error, you can only provide one of both
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_arg_invalid, 1, "FMC_createFile: You can only provide one of both WIDE_ORIENTED and BYTE_ORIENTED flags.");
                    FMC_printRedError(stderr, err_arg_invalid);
                }
                FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_createFile: You can only provide one of both WIDE_ORIENTED and BYTE_ORIENTED flags.");
                fclose(returned_file->file);
                free(returned_file);
                return NULL;
                FMC_UNREACHABLE;
            }
        }

        return returned_file;
    }
    if (returned_file->file) fclose(returned_file->file); // can't reach this since there is either "TO_OPEN" or not
    free(returned_file);
    FMC_UNREACHABLE;
    return NULL;
}


FMC_SHARED FMC_FUNC_NONNULL(1) void FMC_freeFile(FMC_File* restrict file)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!file)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg_null, 1, "Provided argument to FMC_freeFile is NULL.");
            FMC_printRedError(stderr, err_arg_null);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "Provided argument to FMC_freeFile is NULL.");
        return;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop // -Wnonnull-compare
    
    #pragma GCC diagnostic ignored "-Wanalyzer-use-after-free" // false positive
    if (file->isOpened && file->file)
    {
        fclose(file->file);
    }
    free(file);
    #pragma GCC diagnostic pop // -Wno-analyzer-use-after-free
    
    return;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1, 2) unsigned int FMC_changeStreamOrientation(FILE* restrict file, const char* restrict const mode, const unsigned int orientation_flag)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!file || !mode)
    {
    #pragma GCC diagnostic pop // -Wnonnull-compare
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg_null, 1, "Provided argument to FMC_changeStreamOrientation is NULL.");
            FMC_printRedError(stderr, err_arg_null);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "Provided argument to FMC_changeStreamOrientation is NULL.");
        return 0;
        FMC_UNREACHABLE;
    }
    check_in orientation_flag for_only_flags(WIDE_ORIENTED)
    {
        if (fwide(file, 1) <= 0)
        {
            file = freopen(NULL, mode, file);
            if (!file)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_freopen, 1, "INTERNAL ERROR: FMC_changeStreamOrientation: freopen failed.");
                    FMC_printRedError(stderr, err_freopen);
                }
                FMC_setError(FMC_ERR_INTERNAL, "FMC_changeStreamOrientation: freopen failed.");
                return 0;
                FMC_UNREACHABLE;
            }
            if (fwide(file, 1) <= 0)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_fwide, 1, "INTERNAL ERROR: FMC_changeStreamOrientation: fwide failed.");
                    FMC_printRedError(stderr, err_fwide);
                }
                FMC_setError(FMC_ERR_INTERNAL, "FMC_changeStreamOrientation: fwide failed.");
                return 0;
                FMC_UNREACHABLE;
            }
            return WIDE_ORIENTED;
        }
        else return WIDE_ORIENTED;
    }

    else check_in orientation_flag for_only_flags(BYTE_ORIENTED)
    {
        if (fwide(file, -1) >= 0)
        {
            file = freopen(NULL, mode, file);
            if (!file)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_freopen, 1, "INTERNAL ERROR: FMC_changeStreamOrientation: freopen failed.");
                    FMC_printRedError(stderr, err_freopen);
                }
                FMC_setError(FMC_ERR_INTERNAL, "FMC_changeStreamOrientation: freopen failed.");
                return 0;
                FMC_UNREACHABLE;
            }
            if (fwide(file, -1) >= 0)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_fwide, 1, "INTERNAL ERROR: FMC_changeStreamOrientation: fwide failed.");
                    FMC_printRedError(stderr, err_fwide);
                }
                FMC_setError(FMC_ERR_INTERNAL, "FMC_changeStreamOrientation: fwide failed.");
                return 0;
                FMC_UNREACHABLE;
            }
            return BYTE_ORIENTED;
        }
        else return BYTE_ORIENTED;
    }

    else check_in orientation_flag for_only_flags(NOT_SET)
    {
        if (fwide(file, 0) != 0)
        {
            file = freopen(NULL, mode, file);
            if (!file)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_freopen, 1, "INTERNAL ERROR: FMC_changeStreamOrientation: freopen failed.");
                    FMC_printRedError(stderr, err_freopen);
                }
                FMC_setError(FMC_ERR_INTERNAL, "FMC_changeStreamOrientation: freopen failed.");
                return 0;
                FMC_UNREACHABLE;
            }
            if (fwide(file, 0) != 0)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_fwide, 1, "INTERNAL ERROR: FMC_changeStreamOrientation: fwide failed.");
                    FMC_printRedError(stderr, err_fwide);
                }
                FMC_setError(FMC_ERR_INTERNAL, "FMC_changeStreamOrientation: fwide failed.");
                return 0;
                FMC_UNREACHABLE;
            }
            return NOT_SET;
        }
        else return NOT_SET;
    }
    else
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg_invalid, 1, "FMC_changeStreamOrientation: You can only provide one of BYTE_ORIENTED, WIDE_ORIENTED and NOT_SET flags.");
            FMC_printRedError(stderr, err_arg_invalid);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_changeStreamOrientation: You can only provide one of BYTE_ORIENTED, WIDE_ORIENTED and NOT_SET flags.");
        return 0;
        FMC_UNREACHABLE;
    }
    FMC_UNREACHABLE;
    return 0;
}

FMC_SHARED unsigned long long FMC_getOptimalWriteBufferSize(const char* restrict const path)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!path || !FMC_isRegFile(path))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg_null, 1, "ERROR: Provided argument to FMC_getOptimalWriteBufferSize is NULL or the path is not a regular file.");
            FMC_printRedError(stderr, err_arg_null);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "Provided argument to FMC_getOptimalWriteBufferSize is NULL or the path is not a regular file.");
        return 0;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop // -Wnonnull-compare

    #if defined(FMC_COMPILING_ON_WINDOWS)
        FILE_STORAGE_INFO storage_info;
        HANDLE file_handle = CreateFileA(path, FMC_mergeFlags(GENERIC_READ, GENERIC_WRITE), FMC_mergeFlags(FILE_SHARE_READ, FILE_SHARE_WRITE), NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
        if (file_handle == INVALID_HANDLE_VALUE)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_file_open, 1, "ERROR: FMC_getOptimalWriteBufferSize: CreateFileA failed.");
                FMC_printRedError(stderr, err_file_open);
            }
            FMC_setError(FMC_FILE_ERROR, "FMC_getOptimalWriteBufferSize: CreateFileA failed.");
            return 0;
            FMC_UNREACHABLE;
        }
        if (!GetFileInformationByHandleEx(file_handle, FileStorageInfo, &storage_info, sizeof(storage_info)))
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_file_open, 1, "ERROR: FMC_getOptimalWriteBufferSize: GetFileInformationByHandleEx failed.");
                FMC_printRedError(stderr, err_file_open);
            }
            FMC_setError(FMC_FILE_ERROR, "FMC_getOptimalWriteBufferSize: GetFileInformationByHandleEx failed.");
            return 0;
            FMC_UNREACHABLE;
        }
        if (!CloseHandle(file_handle))
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_file_close, 1, "ERROR: FMC_getOptimalWriteBufferSize: CloseHandle failed.");
                FMC_printRedError(stderr, err_file_close);
            }
            FMC_setError(FMC_FILE_ERROR, "FMC_getOptimalWriteBufferSize: CloseHandle failed.");
            return 0;
            FMC_UNREACHABLE;
        }
        return (unsigned long long) storage_info.PhysicalBytesPerSectorForPerformance;
        FMC_UNREACHABLE;
    #else
        struct stat file_stat;
        if (stat(path, &file_stat))
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_file_stat, 1, "ERROR: FMC_getOptimalWriteBufferSize: stat failed.");
                FMC_printRedError(stderr, err_file_stat);
            }
            FMC_setError(FMC_ERR_INTERNAL, "FMC_getOptimalWriteBufferSize: stat failed.");
            return 0;
            FMC_UNREACHABLE;
        }
        return file_stat.st_blksize < 0 ? 0 : (unsigned long long) file_stat.st_blksize;
        FMC_UNREACHABLE;
    #endif 
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_WARN_UNUSED_RESULT FMC_File* FMC_openFile_withoutFlags(FMC_File* file, const char* mode)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!file)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg_null, 1, "ERROR: Provided argument to FMC_openFile is NULL.");
            FMC_printRedError(stderr, err_arg_null);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "Provided argument to FMC_openFile is NULL.");
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop // -Wnonnull-compare
    if (file->isOpened)
    {
        if (file->file)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_file_open, 1, "WARNING: FMC_openFile: File is already opened.");
                FMC_printYellowError(stderr, err_file_open);
            }
        }
        else goto open_file_with_warning;
        return file;
        FMC_UNREACHABLE;
    }

    goto open_file;

open_file_with_warning:

    if (FMC_getDebugState())
    {
        FMC_makeMsg(err_file_open, 1, "WARNING: FMC_openFile: FILE* has been closed, but FMC_File is still marked as opened. The file may also haven't been closed before, and you're trying to open it again.");
        FMC_printYellowError(stderr, err_file_open);
    }
    FMC_setError(FMC_ERR_FILE, "FMC_openFile: FILE* has been closed, but FMC_File is still marked as opened,"
                " or the file may also haven't been closed before.");
    goto open_file;

open_file:
    char full_path[MAX_FPATH_SIZE + MAX_FNAME_SIZE + MAX_FEXT_SIZE];
    memset(full_path, 0, sizeof(full_path) / sizeof(char));
    if (!*file->path || !*file->name || !*file->extension)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_file_open, 1, "ERROR: FMC_openFile: File path, name or extension is not set.");
            FMC_printRedError(stderr, err_file_open);
        }
        FMC_setError(FMC_ERR_FILE, "FMC_openFile: File path, name or extension is not set.");
        return NULL;
        FMC_UNREACHABLE;
    }
    if (strcpy(full_path, file->path) != full_path)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_file_open, 1, "ERROR: FMC_openFile: strcpy failed.");
            FMC_printRedError(stderr, err_file_open);
        }
        FMC_setError(FMC_ERR_INTERNAL, "FMC_openFile: strcpy failed.");
        return NULL;
        FMC_UNREACHABLE;
    }
    if (strcat(full_path, file->name) != full_path)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_file_open, 1, "ERROR: FMC_openFile: strcat failed.");
            FMC_printRedError(stderr, err_file_open);
        }
        FMC_setError(FMC_ERR_INTERNAL, "FMC_openFile: strcat failed.");
        return NULL;
        FMC_UNREACHABLE;
    }
    if (strcat(full_path, file->extension) != full_path)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_file_open, 1, "ERROR: FMC_openFile: strcat failed.");
            FMC_printRedError(stderr, err_file_open);
        }
        FMC_setError(FMC_ERR_INTERNAL, "FMC_openFile: strcat failed.");
        return NULL;
        FMC_UNREACHABLE;
    }
    if (!FMC_isRegFile(full_path))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_file_open, 1, "ERROR: FMC_openFile: File does not exist or is not a regular file.");
            FMC_printRedError(stderr, err_file_open);
        }
        FMC_setError(FMC_ERR_FILE, "FMC_openFile: File does not exist or is not a regular file.");
        return NULL;
        FMC_UNREACHABLE;
    }
    if (strnlen(mode, MAX_MODE_SIZE) >= MAX_MODE_SIZE)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_file_open, 1, "ERROR: FMC_openFile: Mode is too long.");
            FMC_printRedError(stderr, err_file_open);
        }
        FMC_setError(FMC_ERR_FILE, "FMC_openFile: Mode is too long.");
        return NULL;
        FMC_UNREACHABLE;
    }
    if (mode)
    {
        if (strncpy(file->fullMode, mode, MAX_MODE_SIZE - 1) != file->fullMode) // -1 to be sure that the string is null-terminated
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_file_open, 1, "ERROR: FMC_openFile: strncpy failed.");
                FMC_printRedError(stderr, err_file_open);
            }
            FMC_setError(FMC_ERR_INTERNAL, "FMC_openFile: strncpy failed.");
            return NULL;
            FMC_UNREACHABLE;
        }
    }
    else if ((!mode || !*mode) && !*file->fullMode)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_file_open, 1, "ERROR: FMC_openFile: Mode is not set nor provided.");
            FMC_printRedError(stderr, err_file_open);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_openFile: Mode is not set nor provided.");
        return NULL;
        FMC_UNREACHABLE;
    }
    else file->file = fopen(full_path, file->fullMode);
    if (!file->file)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_file_open, 1, "ERROR: FMC_openFile: fopen failed. errno may contain more information.");
            FMC_printRedError(stderr, err_file_open);
        }
        FMC_setError(FMC_ERR_INTERNAL, "FMC_openFile: fopen failed. errno may contain more information.");
        return NULL;
        FMC_UNREACHABLE;
    }

    file->dataMode = FMC_getDataModeFromMode(file->fullMode);

    file->isOpened = True;
    return file;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_WARN_UNUSED_RESULT FMC_File* FMC_openFile_withFlags(FMC_File* file, const char* const mode, const unsigned int user_flags)
{
    if(!FMC_openFile_withoutFlags(file, mode)) return NULL;

    check_in user_flags for_at_least_flags(GET_ENCODING)
    {
        if (FMC_changeStreamOrientation(file->file, "rb", BYTE_ORIENTED) != BYTE_ORIENTED)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_file_open, 1, "ERROR: FMC_openFile: Cannot get encoding. Your file has been freed");
                FMC_printRedError(stderr, err_file_open);
            }
            FMC_setError(FMC_ERR_INTERNAL, "FMC_openFile: Cannot get encoding. Your file has been freed");
            FMC_freeFile(file);
            return NULL;
            FMC_UNREACHABLE;
        }
        file->encoding = FMC_getEncoding(file->file);
        if (FMC_changeStreamOrientation(file->file, file->fullMode, NOT_SET) != NOT_SET)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_file_open, 1, "ERROR: FMC_openFile: Cannot get encoding. Your file has been freed");
                FMC_printRedError(stderr, err_file_open);
            }
            FMC_setError(FMC_ERR_INTERNAL, "FMC_openFile: Cannot get encoding. Your file has been freed");
            FMC_freeFile(file);
            return NULL;
            FMC_UNREACHABLE;
        }
    }

    check_in user_flags for_at_least_flags(WIDE_ORIENTED)
    {
        check_in user_flags if_not_set(BYTE_ORIENTED)
        {
            check_in user_flags if_not_set(NOT_SET)
            {
                file->orientation = (FMC_changeStreamOrientation(file->file, file->fullMode, WIDE_ORIENTED) == WIDE_ORIENTED ? wide : failed_to_change); 
            }
            else goto error_orientation_arg1;
        }
        else
        {
error_orientation_arg1:
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_file_open, 1, "ERROR: FMC_openFile: Cannot set both BYTE_ORIENTED and WIDE_ORIENTED flags. Your file has been freed");
                FMC_printRedError(stderr, err_file_open);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_openFile: Cannot set both BYTE_ORIENTED and WIDE_ORIENTED flags. Your file has been freed");
            FMC_freeFile(file);
            return NULL;
            FMC_UNREACHABLE;
        }
    }

    check_in user_flags for_at_least_flags(BYTE_ORIENTED)
    {
        check_in user_flags if_not_set(WIDE_ORIENTED)
        {
            check_in user_flags if_not_set(NOT_SET)
            {
                file->orientation = (FMC_changeStreamOrientation(file->file, file->fullMode, BYTE_ORIENTED) == BYTE_ORIENTED ? byte : failed_to_change);
            }
            else goto error_orientation_arg2;
        }
        else
        {
error_orientation_arg2:
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_file_open, 1, "ERROR: FMC_openFile: Cannot set both BYTE_ORIENTED and WIDE_ORIENTED flags. Your file has been freed");
                FMC_printRedError(stderr, err_file_open);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_openFile: Cannot set both BYTE_ORIENTED and WIDE_ORIENTED flags. Your file has been freed");
            FMC_freeFile(file);
            return NULL;
            FMC_UNREACHABLE;
        }
    }

    return file;
    FMC_UNREACHABLE;
}

FMC_SHARED void FMC_closeFile(FMC_File* restrict file)
{
    if (!file) 
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_file_close, 1, "ERROR: FMC_closeFile: file is NULL");
            FMC_printRedError(stderr, err_file_close);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_closeFile: file is NULL");
        return;
        FMC_UNREACHABLE;
    }
    if (file->isOpened)
    {
        fclose(file->file);
        file->isOpened = False;
        return;
        FMC_UNREACHABLE;
    }
    else
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_file_close, 1, "ERROR: FMC_closeFile: file is already closed");
            FMC_printRedError(stderr, err_file_close);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_closeFile: file is already closed");
        return;
        FMC_UNREACHABLE;
    }
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_FUNC_NONNULL(1, 2, 3) FMC_File* FMC_reopenFile(FMC_File* restrict file, const char* restrict const new_path, const char* restrict const full_mode, const unsigned int user_flags) // new_path is restrict because we copy a part of it in tmp_[name | path | ext], so there's no aliasing
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!new_path || !*new_path || !file || !full_mode || !*full_mode)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_file_reopen, 1, "ERROR: FMC_reopenFile: new_path or file or full_mode is NULL or empty, your file will be freed");
            FMC_printRedError(stderr, err_file_reopen);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_reopenFile: new_path or file or full_mode is NULL or empty, your file will be freed");
        FMC_freeFile(file);
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    FMC_closeFile(file);
    memset(file->path, 0, (MAX_FPATH_SIZE + MAX_FEXT_SIZE + MAX_FNAME_SIZE + MAX_MODE_SIZE) * sizeof(char));
    char tmp_path[MAX_FPATH_SIZE];
    memset(tmp_path, 0, MAX_FPATH_SIZE * sizeof(char));
    char tmp_name[MAX_FNAME_SIZE];
    memset(tmp_name, 0, MAX_FNAME_SIZE * sizeof(char));
    char tmp_ext[MAX_FEXT_SIZE];
    memset(tmp_ext, 0, MAX_FEXT_SIZE * sizeof(char));
    if (!FMC_cutFilename(new_path, tmp_path, MAX_FPATH_SIZE))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_file_reopen, 1, "ERROR: FMC_reopenFile: new_path is invalid, your file will be freed");
            FMC_printRedError(stderr, err_file_reopen);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_reopenFile: new_path is invalid, your file will be freed");
        FMC_freeFile(file);
        return NULL;
        FMC_UNREACHABLE;
    }
    if (!FMC_getExtension(new_path, tmp_ext, MAX_FEXT_SIZE))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_file_reopen, 1, "ERROR: FMC_reopenFile: new_path is invalid, your file will be freed");
            FMC_printRedError(stderr, err_file_reopen);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_reopenFile: new_path is invalid, your file will be freed");
        FMC_freeFile(file);
        return NULL;
        FMC_UNREACHABLE;
    }
    if (!FMC_extractFilename(new_path, tmp_name, MAX_FNAME_SIZE))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_file_reopen, 1, "ERROR: FMC_reopenFile: new_path is invalid, your file will be freed");
            FMC_printRedError(stderr, err_file_reopen);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_reopenFile: new_path is invalid, your file will be freed");
        FMC_freeFile(file);
        return NULL;
        FMC_UNREACHABLE;
    }
    if (strnlen(full_mode, MAX_MODE_SIZE) >= MAX_MODE_SIZE)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_file_reopen, 1, "ERROR: FMC_reopenFile: full_mode is too long, your file will be freed");
            FMC_printRedError(stderr, err_file_reopen);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_reopenFile: full_mode is too long, your file will be freed");
        FMC_freeFile(file);
        return NULL;
        FMC_UNREACHABLE;
    }
    strncpy(file->path, tmp_path, MAX_FPATH_SIZE); 
    strncpy(file->name, tmp_name, MAX_FNAME_SIZE); 
    strncpy(file->extension, tmp_ext, MAX_FEXT_SIZE); 
    strncpy(file->fullMode, full_mode, MAX_MODE_SIZE - 1); // -1 to be sure that the string is null-terminated
    return FMC_openFile(file, full_mode, user_flags);
}

/*
 * TODO: finish FMC_openFile : DONE
 * TODO: FMC_closeFile : DONE
 * TODO: FMC_reopenFile : DONE
 * TODO: FMC_readFile
 * TODO: FMC_writeFile
 * TODO: FMC_changeMode
 * TODO: FMC_changeFileOrientation
 * TODO: FMC_saveFileWithEncoding
 * 
 * TODO: FMC_getFilePosition
 * TODO: FMC_setFilePosition
 * TODO: FMC_getFileSize
 * TODO: FMC_getFileMode
 * 
 * TODO: FMC_lockFile
 * TODO: FMC_unlockFile
 * TODO: FMC_lockFileRegion
 * TODO: FMC_unlockFileRegion
 * TODO: FMC_tryLockFile
 * TODO: FMC_tryLockFileRegion
 * TODO: FMC_getFileLockState
*/