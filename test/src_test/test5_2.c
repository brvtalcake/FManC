#include "test_suite.h"
#include <assert.h>
#include <string.h>

void test_FMC_getCurrentUserName()
{
    char buff[100];
    memset(buff, 0, 100);
    assert(FMC_getCurrentUserName(buff, 100) != NULL);
    assert(strlen(buff) > 0);
    assert(strncmp(buff, "axel", 4) == 0);
}