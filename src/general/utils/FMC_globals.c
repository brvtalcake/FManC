#include <stdatomic.h>
#include "FMC_globals.h"
#include "../preprocessor/FMC_consts.h"
#include "../types/FMC_structs.h"


#ifndef __STDC_NO_ATOMICS__
FMC_SHARED static volatile _Atomic(FMC_Bool) FMC_ENABLE_DEBUG FMC_VAR_COMMON;
#else
FMC_SHARED static volatile FMC_Bool FMC_ENABLE_DEBUG FMC_VAR_COMMON;
#endif

#ifndef __STDC_NO_ATOMICS__
FMC_SHARED static volatile _Atomic(FMC_Error) FMC_ERROR = FMC_OK;
#else
FMC_SHARED static volatile FMC_Error FMC_ERROR = FMC_OK;
#endif

#ifndef __STDC_NO_ATOMICS__
FMC_SHARED static FMC_ErrStack;
#else
FMC_SHARED static FMC_ErrStack FMC_VAR_COMMON;
#endif

FMC_SHARED static const char const FMC_ERROR_STR[FMC_ERR_STR_COUNT][FMC_ERR_STR_LEN] = 
{
    "No error occured", // FMC_OK
};

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

FMC_SHARED FMC_FUNC_COLD FMC_Error FMC_setError(FMC_Error err)
{
    #ifndef __STDC_NO_ATOMICS__
    atomic_store(&FMC_ERROR, err);
    #else
    FMC_ERROR = err;
    #endif
    return FMC_ERROR == err;
}

FMC_SHARED FMC_FUNC_HOT FMC_Error FMC_getError(void)
{
    #ifndef __STDC_NO_ATOMICS__
    return atomic_load(&FMC_ERROR);
    #else
    return FMC_ERROR;
    #endif
}