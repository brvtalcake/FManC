#include <assert.h>
#include "test_suite.h"

void test_Error_System()
{
    FMC_setError(FMC_INVALID_ARGUMENT, "test");
    assert(FMC_getLastErrorNum() == FMC_INVALID_ARGUMENT);
}