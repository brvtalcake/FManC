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

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_COLD char* FMC_getCurrentUserName(char* const user_name, const size_t len)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!user_name)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_get_usr_name, 1, "ERROR: FMC_getCurrentUserName: user_name is NULL.");
            FMC_printRedError(stderr, err_get_usr_name);
        }
        FMC_setError(FMC_ERR_NULL_PTR, "FMC_getCurrentUserName: user_name is NULL.");
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    memset(user_name, 0, len);
    #if defined(FMC_COMPILING_ON_WINDOWS)
        DWORD size = len;
        if (!GetUserNameExA(NameSamCompatible, user_name, &size))
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_get_usr_name, 1, "ERROR: FMC_getCurrentUserName: GetUserNameExA() failed.")
                FMC_printRedError(stderr, err_get_usr_name);
            }
            FMC_setError(FMC_ERR_INTERNAL, "FMC_getCurrentUserName: GetUserNameExA() failed.");
            return NULL;
            FMC_UNREACHABLE;
        }
        return user_name;
        FMC_UNREACHABLE;
    #else
        uid_t uid = geteuid();
        struct passwd* pw = getpwuid(uid);
        if (pw)
        {
            if (strlen(pw->pw_name) > len)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_get_usr_name, 1, "ERROR: FMC_getCurrentUserName: user_name buffer is too small.");
                    FMC_printRedError(stderr, err_get_usr_name);
                }
                FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_getCurrentUserName: user_name buffer is too small.");
                return NULL;
                FMC_UNREACHABLE;
            }
            strcpy(user_name, pw->pw_name);
            return user_name;
            FMC_UNREACHABLE;
        }
        else
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_get_usr_name, 1, "ERROR: FMC_getCurrentUserName: getpwuid() failed.");
                FMC_printRedError(stderr, err_get_usr_name);
            }
            FMC_setError(FMC_ERR_INTERNAL, "FMC_getCurrentUserName: getpwuid() failed.");
            return NULL;
            FMC_UNREACHABLE;
        }
    #endif
    FMC_UNREACHABLE;
}

/* FMC_SHARED FMC_FUNC_NONNULL(2) FMC_FUNC_COLD char* FMC_getUserNameByUID(uid_t uid, char* user_name, size_t len)
{
    #if defined(FMC_COMPILING_ON_WINDOWS)

    #else
        
    #endif
} */