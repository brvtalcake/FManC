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
#include <tgmath.h>
#include "FMC_filesystem.h"


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


/*
 * TODO: Verify the returned values for the FMC_is* functions and set more error codes when an error occurs
 *
 * TODO: FMC_getPathPerms
 * TODO: FMC_setPathPerms
 * TODO: FMC_getPathOwner
 * TODO: FMC_setPathOwner
 * TODO: FMC_getPathGroup
 * TODO: FMC_setPathGroup
 * TODO: FMC_getPathSize
 * TODO: FMC_getPathTimestamp
*/