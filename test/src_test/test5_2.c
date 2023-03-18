#include "test_suite.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void test_FMC_getCurrentUserName()
{
    char buff[100];
    memset(buff, 0, 100);
    assert(FMC_getCurrentUserName(buff, 100) != NULL);
    assert(strlen(buff) > 0);
    assert(strncmp(buff, "axel", 4) == 0);
}

#if !defined(FMC_COMPILING_ON_WINDOWS)
void test_FMC_getAllUIDs()
{
    unsigned int* uids = NULL;
    unsigned int range[2] = {1000, 1100};
    uids = FMC_getAllUIDs(1, (unsigned int [2]){(unsigned int)1000U, (unsigned int)1100U});
    printf("%u uids :\n", uids[0]);
    for (unsigned int i = 1; i <= uids[0]; i++)
    {
        printf("%u\n", uids[i]);
    }
    assert(uids != NULL);
    assert(uids[0] == 1); // the number of UIDs
    assert(uids[1] == 1000);
    free(uids);
}
#endif // !defined(FMC_COMPILING_ON_WINDOWS)