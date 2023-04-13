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

#include "../FMC_filesystem.h"
#include "FMC_dirs.h"
#include <stdlib.h>

/* FMC_SHARED FMC_Directory* FMC_createDir(const char* restrict const path)
{

} */

FMC_SHARED int_fast64_t FMC_getDirEntryCount(const char* restrict const path)
{
    if (!path || !FMC_isDir(path)) 
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_arg, 1, "FMC_getDirEntryCount: Invalid path argument.");
            FMC_printRedError(stderr, err_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_getDirEntryCount: Invalid path argument.");
        return -1;
        FMC_UNREACHABLE;
    }
    int_fast64_t count = 0;

    #if defined(FMC_COMPILING_ON_WINDOWS)
        WIN32_FIND_DATAA ffd = {0};
        char path_with_wildcard[MAX_FEXT_SIZE + MAX_FNAME_SIZE + MAX_FPATH_SIZE] = {0};
        int ret_val = snprintf(path_with_wildcard, MAX_FEXT_SIZE + MAX_FNAME_SIZE + MAX_FPATH_SIZE, "%s\\*", path);
        if (ret_val < 0 || ret_val >= MAX_FEXT_SIZE + MAX_FNAME_SIZE + MAX_FPATH_SIZE)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_arg, 1, "FMC_getDirEntryCount: Path argument too long.");
                FMC_printRedError(stderr, err_arg);
            }
            FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_getDirEntryCount: Path argument too long.");
            return -1;
            FMC_UNREACHABLE;
        }
        HANDLE hFind = FindFirstFileA(path_with_wildcard, &ffd);
        if (hFind == INVALID_HANDLE_VALUE) 
        {
            if (GetLastError() == ERROR_FILE_NOT_FOUND)
            {
                return 0;
                FMC_UNREACHABLE;
            }
            else
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_int, 1, "FMC_getDirEntryCount: FindFirstFileA failed.");
                    FMC_printRedError(stderr, err_int);
                }
                FMC_setError(FMC_ERR_INTERNAL, "FMC_getDirEntryCount: FindFirstFileA failed.");
                return -1;
                FMC_UNREACHABLE;
            }
        }
        while (FindNextFileA(hFind, &ffd) != 0 && GetLastError() != ERROR_NO_MORE_FILES) ++count;
        FindClose(hFind);
        return count;
    #else
        struct dirent* entry = NULL;
        DIR *dir = opendir(path);
        if (!dir)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_int, 1, "FMC_getDirEntryCount: opendir failed.");
                FMC_printRedError(stderr, err_int);
            }
            FMC_setError(FMC_ERR_INTERNAL, "FMC_getDirEntryCount: opendir failed.");
            return -1;
            FMC_UNREACHABLE;
        }
        while ((entry = readdir(dir)) != NULL) ++count;
        closedir(dir);
        return count;
        FMC_UNREACHABLE;
    #endif
    FMC_UNREACHABLE;
}

// TODO: Improve this function
FMC_SHARED int FMC_mkDir(const char* restrict path, unsigned int unix_perms)
{
    /*char cmd[256] = {0};
    snprintf(cmd, 256, "mkdir %s", path);
    return system(cmd);*/
    #if defined(FMC_COMPILING_ON_WINDOWS)
        FMC_MAKE_VOID(unix_perms);
        if (!FMC_dirExists(path)) return _mkdir(path);
        else return 0;
    #else
        if (!FMC_dirExists(path)) return mkdir(path, unix_perms);
        else return 0;
    #endif
}

FMC_SHARED int FMC_rmDir(const char* restrict path, unsigned int user_flags)
{
    if (!path) return 0;
    char cmd[256] = {0};
    check_in user_flags for_only_flags(RM_DIR_RECURSIVE, NO_CONFIRMATION) // rm everything in dir and dir itself
    {
        #if defined(FMC_COMPILING_ON_WINDOWS)
            snprintf(cmd, 256, "attrib -h %s /s && rmdir %s /s /q", path, path);
        #else
            snprintf(cmd, 256, "rm -rf %s", path);
        #endif
        return system(cmd);
    }
    else check_in user_flags for_only_flags(RM_DIR_RECURSIVE, CONFIRMATION) // same but ask for confirmation
    {
        #if defined(FMC_COMPILING_ON_WINDOWS)
            snprintf(cmd, 256, "attrib -h %s /s && rmdir %s /s", path, path);
        #else
            snprintf(cmd, 256, "rm -ri %s", path);
        #endif
        return system(cmd);
    } 
    else check_in user_flags for_only_flags(RM_DIR_ONLY_CONTENT, NO_CONFIRMATION) // rm everything in dir but not dir itself
    {
        #if defined(FMC_COMPILING_ON_WINDOWS)
            snprintf(cmd, 256, "cd %s && attrib -h .\\* /s && rmdir . /s /q", path);
        #else
            snprintf(cmd, 256, "rm -rf %s/*", path);
        #endif
        return system(cmd);
    }
    else check_in user_flags for_only_flags(RM_DIR_ONLY_CONTENT, CONFIRMATION) //...
    {
        #if defined(FMC_COMPILING_ON_WINDOWS)
            snprintf(cmd, 256, "cd %s && attrib -h .\\* /s && rmdir . /s", path);
        #else
            snprintf(cmd, 256, "rm -ri %s/*", path);
        #endif
        return system(cmd);
    }
    else check_in user_flags for_only_flags(RM_DIR_ONLY_SUBDIRS, NO_CONFIRMATION)
    {
        #if defined(FMC_COMPILING_ON_WINDOWS)
            snprintf(cmd, 256, "pwsh -c \"Get-ChildItem -Path %s -Directory -Force | Remove-Item -Recurse -Force\"", path);
        #else
            snprintf(cmd, 256, "cd %s && rm -rf */", path);
        #endif
        return system(cmd);
    }
    else check_in user_flags for_only_flags(RM_DIR_ONLY_SUBDIRS, CONFIRMATION)
    {
        #if defined(FMC_COMPILING_ON_WINDOWS)
            snprintf(cmd, 256, "pwsh -c \"Get-ChildItem -Path %s -Directory -Force | Remove-Item -Recurse -Confirm\"", path);
        #else
            snprintf(cmd, 256, "cd %s && rm -ri */", path);
        #endif
        return system(cmd);
    }
    else check_in user_flags for_only_flags(RM_DIR_ONLY_FILES, RM_DIR_RECURSIVE, NO_CONFIRMATION)
    {
        #if defined(FMC_COMPILING_ON_WINDOWS)
            snprintf(cmd, 256, "cd %s && attrib -h .\\* /s && del /s /q .\\*", path);
        #else
            snprintf(cmd, 256, "find %s -type f -mindepth 1 -exec rm -f {} \\;", path);
        #endif
        return system(cmd);
    }
    else check_in user_flags for_only_flags(RM_DIR_ONLY_FILES, RM_DIR_RECURSIVE, CONFIRMATION)
    {
        #if defined(FMC_COMPILING_ON_WINDOWS)
            snprintf(cmd, 256, "cd %s && attrib -h .\\* /s && del /s .\\*", path);
        #else
            snprintf(cmd, 256, "find %s -type f -mindepth 1 -exec rm -fi {} \\;", path);
        #endif
        return system(cmd);
    }
    else check_in user_flags for_only_flags(RM_DIR_ONLY_FILES, NO_CONFIRMATION)
    {
        #if defined(FMC_COMPILING_ON_WINDOWS)
            snprintf(cmd, 256, "cd %s && attrib -h .\\* /s && del /q .\\*", path);
        #else
            snprintf(cmd, 256, "find %s -maxdepth 1 -type f -mindepth 1 -exec rm -f {} \\;", path);
        #endif
        return system(cmd);
    }
    else check_in user_flags for_only_flags(RM_DIR_ONLY_FILES, CONFIRMATION)
    {
        #if defined(FMC_COMPILING_ON_WINDOWS)
            snprintf(cmd, 256, "cd %s && attrib -h .\\* /s && del .\\*", path);
        #else
            snprintf(cmd, 256, "find %s -maxdepth 1 -type f -mindepth 1 -exec rm -fi {} \\;", path);
        #endif
        return system(cmd);
    }
    else
    {
        FMC_setError(FMC_ERR_WRONG_FLAGS_COMBINATION, "Wrong flags combination for FMC_rmDir()");
        return -1;
    }
    FMC_UNREACHABLE;
    return 0;
}