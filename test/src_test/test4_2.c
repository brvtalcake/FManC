#include "test_suite.h"
#include <assert.h>
#include <string.h>

void test_FMC_getOptimalWriteBufferSize()
{
    char opt_buf_size_res[10];
    snprintf(opt_buf_size_res, 10, "%lld", FMC_getOptimalWriteBufferSize("test.txt"));
    FMC_makeMsg(msg_opt_buf_size, 2, "Optimal write buffer size: ", opt_buf_size_res);
    FMC_printBlueText(stderr, msg_opt_buf_size);
    assert(FMC_getOptimalWriteBufferSize("test.txt") > 0);
    assert(FMC_getOptimalWriteBufferSize(NULL) == 0); 
    assert(FMC_getOptimalWriteBufferSize("file_that_doesnt_exist.ext") == 0);
}


