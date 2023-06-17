#include <stdatomic.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "FMC_globals.h"
#include "FMC_errors.h"
#include "../preprocessor/FMC_consts.h"
#include "../preprocessor/FMC_macros.h"
#include "../preprocessor/FMC_platform.h"
#include "../types/FMC_structs.h"
#include "../types/FMC_typedefs.h"


static const char const fmc_version_string[] = "FMC v1.0.0";

FMC_SHARED const char* const FMC_version(void)
{
    return fmc_version_string;
}
// TODO: let the user choose if he wants thread local error stack or not

#if defined(FMC_COMPILING_ON_WINDOWS)
    #include <windows.h>
#else 
    #include <pthread.h>
    static pthread_mutexattr_t FMC_ERR_STACK_MUTEX_ATTR FMC_VAR_COMMON = {0};
#endif

#ifndef __STDC_NO_ATOMICS__
static _Atomic(FMC_Bool) FMC_ENABLE_DEBUG FMC_VAR_COMMON = FMC_TRUE;
#else
static FMC_Bool FMC_ENABLE_DEBUG FMC_VAR_COMMON = FMC_TRUE;
#endif

static FMC_ErrStack FMC_ERR_STACK FMC_VAR_COMMON = {0};

static FMC_Mutex FMC_ERR_STACK_MUTEX FMC_VAR_COMMON = FMC_ERR_MTX_INITIALIZER;

static const char FMC_ERROR_STR[FMC_ERR_STR_COUNT][FMC_ERR_STR_LEN / 2] = 
{
    "No error occured. "                                                    ,  // FMC_OK
    "A problem occured while trying to push an error onto the error stack. ",  // FMC_ERR_PUSH
    "Provided pointer is NULL. "                                            ,  // FMC_ERR_NULL_PTR
    "A wrong flags combination was provided. "                              ,  // FMC_ERR_WRONG_FLAGS_COMBINATION
    "An internal error occured. "                                           ,  // FMC_ERR_INTERNAL
    "Invalid argument. "                                                    ,  // FMC_ERR_INVALID_ARGUMENT
    "The provided FMC_File pointer is inconsistent. "                       ,  // FMC_ERR_FILE
    "The encoded character or string is inconsistent. "                     ,  // FMC_ERR_ENC
    "A FILE I/O error occured. "                                            ,  // FMC_ERR_IO
    "Failed to allocate memory. "                                           ,  // FMC_ERR_ALLOC_FAILED
};

#ifndef __STDC_NO_ATOMICS__
static _Atomic(FMC_Bool) FMC_ERR_STACK_MUTEX_CREATED FMC_VAR_COMMON = FMC_FALSE;
#else
static FMC_Bool FMC_ERR_STACK_MUTEX_CREATED FMC_VAR_COMMON = FMC_FALSE;
#endif

FMC_SHARED FMC_FUNC_COLD FMC_Bool FMC_setDebugState(FMC_Bool state)
{
    #ifndef __STDC_NO_ATOMICS__
    atomic_store(&FMC_ENABLE_DEBUG, state);
    #else
    FMC_ENABLE_DEBUG = state;
    #endif
    return FMC_ENABLE_DEBUG == state;
}

FMC_SHARED FMC_FUNC_HOT FMC_Bool FMC_getDebugState(void)
{
    #ifndef __STDC_NO_ATOMICS__
    return atomic_load(&FMC_ENABLE_DEBUG);
    #else
    return FMC_ENABLE_DEBUG;
    #endif
}

static void FMC_consumeOldestError(void)
{
    if (FMC_ERR_STACK.stackSize < FMC_MAX_ERR_STCK_SIZE) return;
    FMC_ErrStackElement *tmp  = FMC_ERR_STACK.lastError;
    FMC_ErrStackElement *tmp2 = NULL;
    if (!tmp) return;
    while (tmp->next)
    {
        tmp2 = tmp;
        tmp = tmp->next;
    }
    free(tmp);
    if (tmp2) tmp2->next = NULL;
    FMC_ERR_STACK.stackSize--;
}

static FMC_Error FMC_pushError(FMC_Error err, const char* const additional_message)
{
    if (!FMC_ERR_STACK_MUTEX_CREATED)
    {
        create_err_mtx();
        atexit(FMC_destroyErrorStack);
        FMC_ERR_STACK_MUTEX_CREATED = FMC_TRUE;
    }
    lock_err_mtx();
    FMC_ErrStackElement *tmp;
    if (FMC_ERR_STACK.lastError != NULL) {tmp = FMC_ERR_STACK.lastError;}
    else tmp = NULL;

    if (FMC_ERR_STACK.stackSize >= FMC_MAX_ERR_STCK_SIZE) FMC_consumeOldestError();

    FMC_ErrStackElement *new = malloc(sizeof(FMC_ErrStackElement));
    #pragma GCC diagnostic ignored "-Wunsuffixed-float-constants"
    if (FMC_PROB(new == NULL, 0.1))
    {
        unlock_err_mtx();
        return FMC_ERR_PUSH;
    }
    #pragma GCC diagnostic pop
    if (tmp) FMC_prefetch(tmp, FMC_OPT(0, 1));

    new->errorNum = err;
    new->next = tmp;
    if (additional_message && strnlen(additional_message, FMC_ERR_STR_LEN / 2) < FMC_ERR_STR_LEN / 2) { strcpy(new->additionalInfo, additional_message); }
    else { new->additionalInfo[0] = '\0'; }
    FMC_ERR_STACK.lastError = new;    
    FMC_ERR_STACK.stackSize++;
    unlock_err_mtx();
    return FMC_OK;
}

FMC_SHARED FMC_Error FMC_setError(FMC_Error err, const char* const additional_message)
{
    return FMC_pushError(err, additional_message);
}

static FMC_Error FMC_popError(void)
{
    if (!FMC_ERR_STACK_MUTEX_CREATED)
    {
        create_err_mtx();
        atexit(FMC_destroyErrorStack);
    }
    lock_err_mtx();
    FMC_ErrStackElement *tmp = FMC_ERR_STACK.lastError;
    if (!tmp)
    {
        unlock_err_mtx();
        return FMC_OK;
    }
    FMC_Error ret = tmp->errorNum;
    FMC_ERR_STACK.lastError = tmp->next;
    free(tmp);
    FMC_ERR_STACK.stackSize--;
    unlock_err_mtx();
    return ret;
}

FMC_SHARED FMC_FUNC_HOT FMC_Error FMC_getLastErrorNum(void)
{
    return FMC_popError();
}

static char* FMC_getLastAdditionalInfo(char *str, size_t len)
{
    if (!str) return NULL;
    memset(str, '\0', len);
    if (!FMC_ERR_STACK_MUTEX_CREATED)
    {
        create_err_mtx();
        atexit(FMC_destroyErrorStack);
    }
    lock_err_mtx();
    FMC_ErrStackElement *tmp = FMC_ERR_STACK.lastError;
    if (!tmp)
    {
        unlock_err_mtx();
        return NULL;
    }
    if (len < FMC_ERR_STR_LEN / 2) return NULL;
    strncpy(str, tmp->additionalInfo, FMC_ERR_STR_LEN / 2);
    unlock_err_mtx();
    return str;
}

FMC_SHARED FMC_FUNC_HOT char* FMC_getLastErrorStr(char *str, size_t len)
{
    if (!str) return NULL;
    memset(str, '\0', len);
    if (len < FMC_ERR_STR_LEN) 
    {
        if (FMC_getDebugState()) 
        {
            char err_str_size[5] = "";
            snprintf(err_str_size, 5, "%d", FMC_ERR_STR_LEN);
            FMC_makeMsg(err_str, 7, "ERROR: ", "In func :", __func__, ":", "Provided buffer is too small to hold the error string (it needs to be at least ", err_str_size, ")");
            FMC_printRedError(stderr, err_str);
        }
        return NULL;
    }
    
    char tmp[FMC_ERR_STR_LEN / 2] = "";
    FMC_getLastAdditionalInfo(tmp, FMC_ERR_STR_LEN / 2);
    FMC_Error err = FMC_popError();
    strncpy(str, FMC_ERROR_STR[err], len);
    if (strlen(tmp) > 0)
    {
        strncat(str, "Additional info: ", len);
        strncat(str, tmp, len);
    }
    return str;
}

FMC_SHARED FMC_FUNC_HOT FMC_Error FMC_getLastErrorNum_noDepop(void)
{
    return FMC_ERR_STACK.lastError->errorNum;
}

FMC_SHARED void FMC_clearErrorStack(void)
{
    FMC_ErrStackElement *tmp = FMC_ERR_STACK.lastError;
    while (tmp)
    {
        FMC_ErrStackElement *tmp2 = tmp;
        tmp = tmp->next;
        free(tmp2);
    }
    FMC_ERR_STACK.lastError = NULL;
    FMC_ERR_STACK.stackSize = 0;
}

FMC_SHARED void FMC_destroyErrorStack(void)
{
    FMC_clearErrorStack();
    if (!FMC_ERR_STACK_MUTEX_CREATED) return;
    destroy_err_mtx();
    FMC_ERR_STACK_MUTEX_CREATED = FMC_FALSE;
}

FMC_SHARED FMC_Bool FMC_searchError(FMC_Error err)
{
    FMC_ErrStackElement *tmp = FMC_ERR_STACK.lastError;
    while (tmp)
    {
        if (tmp->errorNum == err) return 1;
        tmp = tmp->next;
    }
    return 0;
}

FMC_SHARED FMC_FUNC_NONNULL(1) char* FMC_getLastErrorStr_noDepop(char* to_fill, size_t len)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!to_fill) return NULL;
    #pragma GCC diagnostic pop
    memset(to_fill, '\0', len);
    if (len < FMC_ERR_STR_LEN) 
    {
        if (FMC_getDebugState()) 
        {
            char err_str_size[5] = "";
            snprintf(err_str_size, 5, "%d", FMC_ERR_STR_LEN);
            FMC_makeMsg(err_str, 7, "ERROR: ", "In func :", __func__, ":", "Provided buffer is too small to hold the error string (it needs to be at least ", err_str_size, ")");
            FMC_printRedError(stderr, err_str);
        }
        return NULL;
        FMC_UNREACHABLE;
    }
    
    char tmp[FMC_ERR_STR_LEN / 2] = "";
    FMC_getLastAdditionalInfo(tmp, FMC_ERR_STR_LEN / 2);
    if (!FMC_ERR_STACK.lastError)
    {
        strncpy(to_fill, "No error", len);
        goto func_end;
    }
    FMC_Error err = FMC_ERR_STACK.lastError->errorNum;
    strncpy(to_fill, FMC_ERROR_STR[err], len);
    if (strlen(tmp) > 0)
    {
        strncat(to_fill, "Additional info: ", len);
        strncat(to_fill, tmp, len);
    }
    func_end:
    return to_fill;
    FMC_UNREACHABLE;
}

FMC_SHARED FMC_Bool FMC_FUNC_NONNULL(1) FMC_searchErrorMsg(const char* restrict const msg)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!msg) return 0;
    #pragma GCC diagnostic pop
    FMC_ErrStackElement *tmp = FMC_ERR_STACK.lastError;
    char tmp_err_msg[FMC_ERR_STR_LEN] = "";
    while (tmp)
    {
        memset(tmp_err_msg, '\0', FMC_ERR_STR_LEN);
        strcpy(tmp_err_msg, FMC_ERROR_STR[tmp->errorNum]);
        strcat(tmp_err_msg, tmp->additionalInfo);
        if (strstr(tmp_err_msg, msg)) return 1;
        tmp = tmp->next;
    }
    return 0;
    FMC_UNREACHABLE;
}