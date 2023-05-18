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

/* This file contains unfinished work */

#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include <assert.h>
#include <limits.h>
#include <stdint.h>
#include <errno.h>

#include "FMC_sys.h"
#include "../filesystem/FMC_filesystem.h"

#if !defined(FMC_COMPILING_ON_WINDOWS)
FMC_FUNC_COLD static unsigned int** FMC_parseEtcLoginDefs(unsigned int** uids_and_gids)
{
    FMC_Bool uids_and_gids_was_allocated = FMC_FALSE;
    if (!uids_and_gids)
    {
        uids_and_gids = malloc(sizeof(unsigned int*) * 2);
        if (!uids_and_gids) return NULL;
        memset(uids_and_gids, 0, sizeof(unsigned int*) * 2);
        uids_and_gids[0] = malloc(sizeof(unsigned int) * 2);
        if (!uids_and_gids[0])
        {
            free(uids_and_gids);
            return NULL;
        }
        memset(uids_and_gids[0], 0, sizeof(unsigned int) * 2);
        uids_and_gids[1] = malloc(sizeof(unsigned int) * 2);
        if (!uids_and_gids[1])
        {
            free(uids_and_gids[0]);
            free(uids_and_gids);
            return NULL;
        }
        memset(uids_and_gids[1], 0, sizeof(unsigned int) * 2);
        uids_and_gids_was_allocated = FMC_TRUE;
    }
    else
    {
        memset(uids_and_gids[0], 0, sizeof(unsigned int) * 2);
        memset(uids_and_gids[1], 0, sizeof(unsigned int) * 2);
    }
    off64_t f_len = FMC_getFileSize("/etc/login.defs");
    if (f_len <= 0) 
    {
        if (uids_and_gids_was_allocated)
        {
            free(uids_and_gids[0]);
            free(uids_and_gids[1]);
            free(uids_and_gids);
        }
        return NULL;
    }
    FILE* f = fopen("/etc/login.defs", "r");
    if (!f) 
    {
        if (uids_and_gids_was_allocated)
        {
            free(uids_and_gids[0]);
            free(uids_and_gids[1]);
            free(uids_and_gids);
        }
        return NULL;
    }
    if (f_len + 1 <= (off64_t) PTRDIFF_MAX)
    {
        char* buff = calloc((size_t) f_len + 1, sizeof(char));
        size_t ret = fread(buff, sizeof(char), (size_t) f_len, f);
        if (ret != (size_t) f_len)
        {
            fclose(f);
            if (uids_and_gids_was_allocated)
            {
                free(uids_and_gids[0]);
                free(uids_and_gids[1]);
                free(uids_and_gids);
                free(buff);
            }
            return NULL;
        }
        fclose(f);

        char* pos = strstr(buff, "UID_MIN");
        if (!pos) 
        {
            if (uids_and_gids_was_allocated)
            {
                free(uids_and_gids[0]);
                free(uids_and_gids[1]);
                free(uids_and_gids);
                free(buff);
            }
            return NULL;
        }
        pos += strlen("UID_MIN");
        while (!isdigit(*pos)) pos++;
        char* start = pos;
        while (isdigit(*pos)) pos++;
        char* end = pos;
        char tmp[end - start + 1];
        memset(tmp, 0, (size_t) (end - start) + 1);
        strncpy(tmp, start, (size_t) (end - start));
        unsigned int uid_min = (unsigned int) atoi(tmp);

        pos = strstr(buff, "UID_MAX");
        if (!pos) 
        {
            if (uids_and_gids_was_allocated)
            {
                free(uids_and_gids[0]);
                free(uids_and_gids[1]);
                free(uids_and_gids);
                free(buff);
            }
            return NULL;
        }
        pos += strlen("UID_MAX");
        while (!isdigit(*pos)) pos++;
        start = pos;
        while (isdigit(*pos)) pos++;
        end = pos;
        memset(tmp, 0, (size_t) (end - start) + 1);
        strncpy(tmp, start, (size_t) (end - start));
        unsigned int uid_max = (unsigned int) atoi(tmp);

        uids_and_gids[0][0] = uid_min;
        uids_and_gids[0][1] = uid_max;

        pos = strstr(buff, "GID_MIN");
        if (!pos) 
        {
            if (uids_and_gids_was_allocated)
            {
                free(uids_and_gids[0]);
                free(uids_and_gids[1]);
                free(uids_and_gids);
                free(buff);
            }
            return NULL;
        }
        pos += strlen("GID_MIN");
        while (!isdigit(*pos)) pos++;
        start = pos;
        while (isdigit(*pos)) pos++;
        end = pos;
        memset(tmp, 0, (size_t) (end - start) + 1);
        strncpy(tmp, start, (size_t) (end - start));
        unsigned int gid_min = (unsigned int) atoi(tmp);

        pos = strstr(buff, "GID_MAX");
        if (!pos) 
        {
            if (uids_and_gids_was_allocated)
            {
                free(uids_and_gids[0]);
                free(uids_and_gids[1]);
                free(uids_and_gids);
                free(buff);
            }
            return NULL;
        }
        pos += strlen("GID_MAX");
        while (!isdigit(*pos)) pos++;
        start = pos;
        while (isdigit(*pos)) pos++;
        end = pos;
        memset(tmp, 0, (size_t) (end - start) + 1);
        strncpy(tmp, start, (size_t) (end - start));
        unsigned int gid_max = (unsigned int) atoi(tmp);

        uids_and_gids[1][0] = gid_min;
        uids_and_gids[1][1] = gid_max;

        free(buff);
        return uids_and_gids;
        FMC_UNREACHABLE;
    }
    else
    {
        fclose(f);
        if (uids_and_gids_was_allocated)
        {
            free(uids_and_gids[0]);
            free(uids_and_gids[1]);
            free(uids_and_gids);
        }
        return NULL;
    }
}
#endif

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
        DWORD size = len >= UINT32_MAX ? (DWORD) UINT32_MAX : (DWORD) len;
        if (!GetUserNameExA(NameSamCompatible, user_name, &size))
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_get_usr_name, 1, "ERROR: FMC_getCurrentUserName: GetUserNameExA() failed.");
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

#if !defined(FMC_COMPILING_ON_WINDOWS)
#pragma GCC diagnostic ignored "-Wstack-protector" 
FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_JUST_MALLOC unsigned int* FMC_getAllUIDs(unsigned int range_number, ...)
{
    #pragma GCC diagnostic pop
    // this function gets all the UIDs in the system between the specified ranges (wich are variable)
    if (range_number == 0)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_get_all_uids, 1, "ERROR: FMC_getAllUIDs: range_number is 0.");
            FMC_printRedError(stderr, err_get_all_uids);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_getAllUIDs: range_number is 0.");
        return NULL;
        FMC_UNREACHABLE;
    }
    if (range_number >= 10)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_get_all_uids, 1, "ERROR: FMC_getAllUIDs: range_number is too big.");
            FMC_printRedError(stderr, err_get_all_uids);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_getAllUIDs: range_number is too big.");
        return NULL;
        FMC_UNREACHABLE;
    }
    FMC_UNREACHABLE_ASSERT(range_number < 10);
    va_list args;
    va_start(args, range_number);
    unsigned int ranges[range_number][2];
    memset(ranges, 0, sizeof(unsigned int) * 2 * range_number);
    unsigned int *tmp = NULL;

    for (size_t i = 0; i < range_number; i++)
    {
        tmp = (unsigned int*) va_arg(args, void*);
        // copy the first elem of tmp range to the ranges array, then the second, in two different instructions
        ranges[i][0] = tmp[0];
        ranges[i][1] = tmp[1];
    }
    va_end(args);
    
    unsigned int* uids = malloc(2*sizeof(unsigned int));
    if (!uids)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_get_all_uids, 1, "ERROR: FMC_getAllUIDs: malloc() failed.");
            FMC_printRedError(stderr, err_get_all_uids);
        }
        FMC_setError(FMC_ERR_INTERNAL, "FMC_getAllUIDs: malloc() failed.");
        return NULL;
        FMC_UNREACHABLE;
    }
    memset(uids + 1, 0, sizeof(unsigned int));
    struct passwd* pw = NULL;
    size_t i = 1;
    while ((pw = getpwent()))
    {
        if (i > UINT_MAX)
        {
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_get_all_uids, 1, "ERROR: FMC_getAllUIDs: too many UIDs.");
                FMC_printRedError(stderr, err_get_all_uids);
            }
            FMC_setError(FMC_ERR_INTERNAL, "FMC_getAllUIDs: too many UIDs.");
            free(uids);
            return NULL;
            FMC_UNREACHABLE;
        }
        unsigned int* old_uids = NULL;
        for (size_t j = 0; j < range_number; j++)
        {
            if (pw->pw_uid >= ranges[j][0] && pw->pw_uid <= ranges[j][1])
            {
                uids = realloc((old_uids = uids), sizeof(unsigned int) * (i + 1));
                if (!uids)
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_get_all_uids, 1, "ERROR: FMC_getAllUIDs: realloc() failed.");
                        FMC_printRedError(stderr, err_get_all_uids);
                    }
                    FMC_setError(FMC_ERR_INTERNAL, "FMC_getAllUIDs: realloc() failed.");
                    free(old_uids);
                    return NULL;
                    FMC_UNREACHABLE;
                }
                uids[i] = pw->pw_uid;
                i++;
            }
        }
    }
    endpwent();

    // store the number of UIDs in the first position of the array
    FMC_UNREACHABLE_ASSERT(i < UINT_MAX);
    uids[0] = (unsigned int) (i - 1);
    return uids;
    FMC_UNREACHABLE;
}
#endif

/* FMC_SHARED FMC_FUNC_NONNULL(2) FMC_FUNC_COLD char* FMC_getUserNameByUID(uid_t uid, char* user_name, size_t len)
{
    #if defined(FMC_COMPILING_ON_WINDOWS)

    #else
        
    #endif
} */

/*
 * TODO: FMC_getNativeUIDRanges() (only POSIX)
 * TODO: FMC_getNativeGIDRanges() (only POSIX)
 * TODO: FMC_getUserNameByUID() (only POSIX)
 * TODO: FMC_getGroupNameByGID() (only POSIX)
 * TODO: FMC_getAllGIDs() (only POSIX)
 * TODO: FMC_getAllGroupNames() (only POSIX)
 * TODO: FMC_getAllUserNames() (only POSIX)
 * TODO: FMC_parseEtcLoginDefs() (only POSIX, static)
 * TODO: FMC_parseEtcPasswd() (only POSIX, static)
*/