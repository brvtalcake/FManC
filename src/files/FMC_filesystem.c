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

#include <stdint.h>
#include <stdlib.h>
#include "FMC_file_management.h"
#include "../cpp/FMC_wrapper.h"

#if defined(FMC_COMPILING_ON_WINDOWS)
    #include <windows.h>
#elif defined(FMC_COMPILING_ON_LINUX)
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <unistd.h>
#endif

// TODO: Verify if file is regular file
#if defined(FMC_COMPILING_ON_WINDOWS)
FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT LONGLONG FMC_getFileSize(const char* restrict path)
#elif defined(FMC_COMPILING_ON_LINUX) && defined(_FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS >= 64)
FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT off64_t FMC_getFileSize(const char* restrict path)
#else
FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT off_t FMC_getFileSize(const char* restrict path)
#endif
{
    #if defined(FMC_COMPILING_ON_WINDOWS) 
        if (!path || !FMC_isRegFile(path)) return -1;
        WIN32_FILE_ATTRIBUTE_DATA fad;
        if (!GetFileAttributesEx(path, GetFileExInfoStandard, &fad))
            return 0;
        LARGE_INTEGER size;
        size.HighPart = fad.nFileSizeHigh;
        size.LowPart = fad.nFileSizeLow;
        return size.QuadPart;

    #elif defined(_FILE_OFFSET_BITS) && (_FILE_OFFSET_BITS >= 64)
        if (!path || !FMC_isRegFile(path)) return ((off64_t)(-1LL) > 0 ? 0 : -1);
        struct stat64 st = {0};
        if (stat64(path, &st) == 0) return st.st_size;
        return 0;

    #else 
        if (!path || !FMC_isRegFile(path)) return ((off_t)(-1LL) > 0 ? 0 : -1);
        struct stat st = {0};
        if (stat(path, &st) == 0) return st.st_size;
        return 0;

    #endif
}

FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT int FMC_dirExists(const char* restrict path)
{
    if (!path) return 0;
    #if defined(FMC_COMPILING_ON_WINDOWS)
        DWORD dwAttrib = GetFileAttributes(path);
        return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY)) || (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
    #else
        struct stat st = {0};
        return stat(path, &st) == 0;
    #endif
}

FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT int FMC_isRegFile(const char* restrict path)
{
    if (!FMC_dirExists(path)) return 0;
    #if defined(FMC_COMPILING_ON_WINDOWS)
        DWORD dwAttrib = GetFileAttributes(path);
        return (dwAttrib != INVALID_FILE_ATTRIBUTES && !(dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
    #else
        struct stat st = {0};
        return stat(path, &st) == 0 && S_ISREG(st.st_mode);
    #endif
}

FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT int FMC_isDir(const char* restrict path)
{
    if (!FMC_dirExists(path)) return 0;
    #if defined(FMC_COMPILING_ON_WINDOWS)
        DWORD dwAttrib = GetFileAttributes(path);
        return (dwAttrib != INVALID_FILE_ATTRIBUTES && (dwAttrib & FILE_ATTRIBUTE_DIRECTORY));
    #else
        struct stat st = {0};
        return stat(path, &st) == 0 && S_ISDIR(st.st_mode);
    #endif
}

FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT int FMC_isCharDevice(const char* restrict path)
{
    if (!FMC_dirExists(path)) return 0;
    #if defined(FMC_COMPILING_ON_WINDOWS)
        HANDLE hDevice = CreateFile(path, 0, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (hDevice == INVALID_HANDLE_VALUE) return 0;
        if (GetFileType(hDevice) & FILE_TYPE_CHAR) { CloseHandle(hDevice); return 1; }
        CloseHandle(hDevice);
        return 0;
    #else
        struct stat st = {0};
        return stat(path, &st) == 0 && S_ISCHR(st.st_mode);
    #endif
}

FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT int FMC_isSocket(const char* restrict path)
{
    if (!FMC_dirExists(path)) return 0;
    #if defined(FMC_COMPILING_ON_WINDOWS)
        HANDLE hDevice = CreateFile(path, 0, 0, NULL, OPEN_EXISTING, 0, NULL);
        if (hDevice == INVALID_HANDLE_VALUE) return 0;
        if (GetFileType(hDevice) & FILE_TYPE_PIPE) { CloseHandle(hDevice); return 1; }
        CloseHandle(hDevice);
        return 0;
    #else
        struct stat st = {0};
        return stat(path, &st) == 0 && S_ISSOCK(st.st_mode);
    #endif
}

FMC_SHARED int FMC_mkDir(const char* restrict path)
{
    char cmd[256] = {0};
    snprintf(cmd, 256, "mkdir %s", path);
    return system(cmd);
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
        FMC_setError(FMC_WRONG_FLAGS_COMBINATION, "Wrong flags combination for FMC_rmDir()");
        return -1;
    }
    FMC_UNREACHABLE;
    return 0;
}