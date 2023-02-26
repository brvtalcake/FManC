#include <stdatomic.h>
#include "FMC_globals.h"

#ifndef __STDC_NO_ATOMICS__
FMC_SHARED static volatile _Atomic(FMC_Bool) FMC_ENABLE_DEBUG FMC_VAR_COMMON;
#else
FMC_SHARED static volatile FMC_Bool FMC_ENABLE_DEBUG FMC_VAR_COMMON;
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