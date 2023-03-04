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

#if defined(FMC_COMPILING_ON_WINDOWS)
    #include <windows.h>
#else 
    #include <pthread.h>
    FMC_SHARED static pthread_mutexattr_t FMC_ERR_STACK_MUTEX_ATTR FMC_VAR_COMMON = {0};
#endif

#ifndef __STDC_NO_ATOMICS__
FMC_SHARED static volatile _Atomic(FMC_Bool) FMC_ENABLE_DEBUG FMC_VAR_COMMON = True;
#else
FMC_SHARED static volatile FMC_Bool FMC_ENABLE_DEBUG FMC_VAR_COMMON = True;
#endif

FMC_SHARED static FMC_ErrStack FMC_ERR_STACK FMC_VAR_COMMON = {0};

FMC_SHARED static FMC_Mutex FMC_ERR_STACK_MUTEX FMC_VAR_COMMON = FMC_ERR_MTX_INITIALIZER;

FMC_SHARED static const char const FMC_ERROR_STR[FMC_ERR_STR_COUNT][FMC_ERR_STR_LEN / 2] = 
{
    "No error occured", // FMC_OK
    "A problem occured while trying to push an error onto the error stack", // FMC_ERR_PUSH
    "Provided pointer is NULL", // FMC_ERR_NULL_PTR
};

#ifndef __STDC_NO_ATOMICS__
FMC_SHARED static volatile _Atomic(FMC_Bool) FMC_ERR_STACK_MUTEX_CREATED FMC_VAR_COMMON = False;
#else
FMC_SHARED static volatile FMC_Bool FMC_ERR_STACK_MUTEX_CREATED FMC_VAR_COMMON = False;
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

FMC_SHARED static FMC_Error FMC_pushError(FMC_Error err, const char* const additionnal_message)
{
    if (!FMC_ERR_STACK_MUTEX_CREATED)
    {
        create_err_mtx();
        atexit(FMC_destroyErrorStack);
    }
    lock_err_mtx();
    FMC_ErrStackElement *tmp = FMC_ERR_STACK.lastError;

    if (FMC_ERR_STACK.stackSize == FMC_MAX_ERR_STCK_SIZE) FMC_consumeOldestError();

    FMC_ErrStackElement *new = malloc(sizeof(FMC_ErrStackElement));
    if (FMC_PROB(!new, 0.1))
    {
        unlock_err_mtx();
        return FMC_ERR_PUSH;
    }
    FMC_prefetch(tmp, FMC_OPT(0, 1));

    new->errorNum = err;
    new->next = tmp;
    if (additionnal_message && strlen(additionnal_message) < FMC_ERR_STR_LEN / 2) { strcpy(new->additionalInfo, additionnal_message); }
    else { new->additionalInfo[0] = '\0'; }
    FMC_ERR_STACK.lastError = new;    
    FMC_ERR_STACK.stackSize++;
    unlock_err_mtx();
    return FMC_OK;
}

FMC_SHARED FMC_Error FMC_setError(FMC_Error err, const char* const additionnal_message)
{
    return FMC_pushError(err, additionnal_message);
}

FMC_SHARED static FMC_Error FMC_popError(void)
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

FMC_SHARED static char* FMC_getLastAdditionalInfo(char *str, size_t len)
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
        strncat(str, "Addtional info: (", len);
        strncat(str, tmp, len);
        strncat(str, ")", len);
    }
    return str;
}

FMC_SHARED FMC_FUNC_HOT FMC_Error FMC_getLastErrorNum_noDepop(void)
{
    return FMC_ERR_STACK.lastError->errorNum;
}

FMC_SHARED static void FMC_consumeOldestError(void)
{
    if (FMC_ERR_STACK.stackSize < FMC_MAX_ERR_STCK_SIZE) return;
    FMC_ErrStackElement *tmp = FMC_ERR_STACK.lastError;
    while (tmp->next)
    {
        tmp = tmp->next;
    }
    free(tmp);
    FMC_ERR_STACK.stackSize--;
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
    destroy_err_mtx();
    FMC_ERR_STACK_MUTEX_CREATED = False;
}
