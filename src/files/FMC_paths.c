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

#include <string.h>
#include <stdio.h>

#include "FMC_file_management.h"

FMC_Bool FMC_ENABLE_DEBUG FMC_VAR_COMMON; 
/* 
 * For some reasons it doesn't compile on Windows without redeclaring the above variable. The funny fact is that all the other files where
 * "FMC_ENABLE_DEBUG" appear compile well.
 * Moreover __attribute__((nonnull(...))) seems to interfere badly, optimizing away the first if of the functions below, so it must be defined to 
 * nothing.
 */

FMC_SHARED FMC_FUNC_HOT FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1, 2) char *FMC_extractFilename(const char * restrict const path, char * restrict filename, const size_t filename_size)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare" // get an error at compile time without this (because of attribute nonnull)
    if (!path || !filename)
    {
        if (FMC_ENABLE_DEBUG)
        {
            FMC_makeMsg(err_null, 4, "ERROR : ", "In function : ", __func__, ". At least one of the provided pointers is NULL.");
            FMC_printBrightRedError(stderr, err_null);
        }
        return NULL;
    }
    #pragma GCC diagnostic pop
    memset(filename, 0, filename_size);
    size_t path_len = 0;
    if ((path_len = strnlen(path, MAX_FEXT_SIZE + MAX_FNAME_SIZE + MAX_FPATH_SIZE)) >= MAX_FEXT_SIZE + MAX_FNAME_SIZE + MAX_FPATH_SIZE)
    {
        FMC_makeMsg(err_path, 4, "ERROR : ", "In function : ", __func__, ". The provided path is too long (or doesn't contain any nul-character).");
        FMC_printBrightRedError(stderr, err_path);
        return NULL;
    }
    char path_cpy[MAX_FEXT_SIZE + MAX_FNAME_SIZE + MAX_FPATH_SIZE];
    strncpy(path_cpy, path, path_len+1);
    if (strcmp(path_cpy, path) != 0)
    {
        FMC_makeMsg(err_path2, 4, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". strncpy failure.");
        FMC_printBrightRedError(stderr, err_path2);
        return NULL;
    }

    char *last_sep = NULL;
    last_sep = strrchr(path_cpy, (int)'/');
    if (!strrchr(path_cpy, (int)'/') && !strrchr(path_cpy, (int)'\\'))
    {
        filename = strncpy(filename, path_cpy, path_len+1);
        if (strcmp(filename, path_cpy) != 0)
        {
            FMC_makeMsg(err_path3, 4, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". strncpy failure.");
            FMC_printBrightRedError(stderr, err_path3);
            return NULL;
        }
        return filename;
    }
    else if (strrchr(path_cpy, (int)'\\') && strrchr(path_cpy, (int)'/'))
    {
        if (FMC_ENABLE_DEBUG)
        {
            FMC_makeMsg(err_path5, 4, "ERROR : ", "In function : ", __func__, ". The path contains both '/' and '\\'.");
            FMC_printBrightRedError(stderr, err_path5);
        }
        return NULL;
    }
    else if (last_sep)
    {
        filename = strncpy(filename, last_sep+1, path_len+1);
        if (strcmp(filename, last_sep+1) != 0)
        {
            FMC_makeMsg(err_path4, 4, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". strncpy failure.");
            FMC_printBrightRedError(stderr, err_path4);
            return NULL;
        }
        return filename;
    }
    else
    {
        last_sep = strrchr(path_cpy, (int)'\\');
        filename = strncpy(filename, last_sep+1, path_len+1);
        if (strcmp(filename, last_sep+1) != 0)
        {
            FMC_makeMsg(err_path4, 4, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". strncpy failure.");
            FMC_printBrightRedError(stderr, err_path4);
            return NULL;
        }
        return filename;
    }
}

FMC_SHARED FMC_FUNC_HOT FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1, 2) char *FMC_cutFilename(const char * restrict const path, char * restrict dirs, const size_t dirs_size)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare" // get an error at compile time without this (because of attribute nonnull defined on linux)
    if (!path || !dirs)
    {
        if (FMC_ENABLE_DEBUG)
        {
            FMC_makeMsg(err_null, 4, "ERROR : ", "In function : ", __func__, ". At least one of the provided pointers is NULL.");
            FMC_printBrightRedError(stderr, err_null);
        }
        return NULL;
    }
    #pragma GCC diagnostic pop
    memset(dirs, 0, dirs_size);
    size_t path_len = 0;
    if ((path_len = strnlen(path, MAX_FEXT_SIZE + MAX_FNAME_SIZE + MAX_FPATH_SIZE)) >= MAX_FEXT_SIZE + MAX_FNAME_SIZE + MAX_FPATH_SIZE)
    {
        FMC_makeMsg(err_path, 4, "ERROR : ", "In function : ", __func__, ". The provided path is too long (or doesn't contain any nul-character).");
        FMC_printBrightRedError(stderr, err_path);
        return NULL;
    }
    char path_cpy[MAX_FEXT_SIZE + MAX_FNAME_SIZE + MAX_FPATH_SIZE];
    strncpy(path_cpy, path, path_len+1);
    if (strcmp(path_cpy, path) != 0)
    {
        FMC_makeMsg(err_path2, 4, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". strncpy failure.");
        FMC_printBrightRedError(stderr, err_path2);
        return NULL;
    }
    char *last_sep = NULL;
    if ((last_sep = strrchr(path_cpy, (int)'/')) && (last_sep = strrchr(path_cpy, (int)'\\')))
    {
        if (FMC_ENABLE_DEBUG)
        {
            FMC_makeMsg(err_path5, 4, "ERROR : ", "In function : ", __func__, ". The path contains both '/' and '\\'.");
            FMC_printBrightRedError(stderr, err_path5);
        }
        return NULL;
    }

    else if ((last_sep = strrchr(path_cpy, (int)'/')))
    {
        strncpy(dirs, path_cpy, strnlen(path_cpy, path_len) - strnlen(last_sep, path_len) + 1);
        dirs[strnlen(path_cpy, path_len) - strnlen(last_sep, path_len) + 1] = '\0';
        return dirs;
    }

    else if ((last_sep = strrchr(path_cpy, (int)'\\')))
    {
        strncpy(dirs, path_cpy, strnlen(path_cpy, path_len) - strnlen(last_sep, path_len) + 1);
        dirs[strnlen(path_cpy, path_len) - strnlen(last_sep, path_len) + 1] = '\0';
        return dirs;
    }
    else if ((last_sep = strrchr(path_cpy, (int)'~')))
    {
        strncpy(dirs, "~/", 4);
        if (strcmp(dirs, "~/") != 0)
        {
            FMC_makeMsg(err_path4, 4, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". strncpy failure.");
            FMC_printBrightRedError(stderr, err_path4);
            return NULL;
        }
        return dirs;
    }
    else
    {
        dirs = strncpy(dirs, "./", 4);
        if (strcmp(dirs, "./") != 0)
        {
            FMC_makeMsg(err_path3, 4, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". strncpy failure.");
            FMC_printBrightRedError(stderr, err_path3);
            return NULL;
        }
        return dirs;
    }
    
}

FMC_SHARED FMC_FUNC_HOT FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1, 2) char *FMC_getExtension(const char * restrict const path, char * restrict ext, const size_t ext_size)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare" // get an error at compile time without this (because of attribute nonnull)
    if (!path || !ext)
    {
        if (FMC_ENABLE_DEBUG)
        {
            FMC_makeMsg(err_null, 4, "ERROR : ", "In function : ", __func__, ". At least one of the provided pointers is NULL.");
            FMC_printBrightRedError(stderr, err_null);
        }
        return NULL;
    }
    #pragma GCC diagnostic pop
    memset(ext, 0, ext_size);
    char name[MAX_FNAME_SIZE];
    if (!FMC_extractFilename(path, name, MAX_FNAME_SIZE))
    {
        FMC_makeMsg(err_path6, 4, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". FMC_extractFilename call failed.");
        FMC_printBrightRedError(stderr, err_path6);
        return NULL;
    }

    if (!strchr(name, (int)'.')) {strncpy(ext, "", 2); return ext;} // Could be modified (?)
    else
    {
        char *last_dot = NULL;
        if ((last_dot = strrchr(name, (int)'.')))
        {
            strncpy(ext, last_dot, strnlen(last_dot+1, MAX_FEXT_SIZE)+1);
            return ext;
        }
        else
        {
            FMC_makeMsg(err_path7, 4, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". strrchr call failed.");
            FMC_printBrightRedError(stderr, err_path7);
            return NULL;
        }
    }
}