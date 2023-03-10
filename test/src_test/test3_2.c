#include <assert.h>
#include "test_suite.h"

void test_Error_System()
{
    char err_buf[256];
    FMC_setError(FMC_INVALID_ARGUMENT, "test1");
    assert(FMC_getLastErrorNum_noDepop() == FMC_INVALID_ARGUMENT);
    FMC_getLastErrorStr_noDepop(err_buf, 256);

    FMC_makeMsg(err_msg1, 2, "Here is the error: ", err_buf);
    FMC_printRedError(stderr, err_msg1);
    FMC_printBlueError(stderr, err_msg1);
    FMC_printGreenError(stderr, err_msg1);
    FMC_printYellowError(stderr, err_msg1);
    FMC_printMagentaError(stderr, err_msg1);
    FMC_printCyanError(stderr, err_msg1);
    FMC_printWhiteError(stderr, err_msg1);
    FMC_printBrightBlueError(stderr, err_msg1);
    FMC_printBrightGreenError(stderr, err_msg1);
    FMC_printBrightRedError(stderr, err_msg1);
    FMC_printBrightYellowError(stderr, err_msg1);
    FMC_printBrightMagentaError(stderr, err_msg1);
    FMC_printBrightCyanError(stderr, err_msg1);
    FMC_printBrightWhiteError(stderr, err_msg1);
    FMC_printWhiteText(stderr, err_msg1);
    FMC_printBrightWhiteText(stderr, err_msg1);
    FMC_printRedText(stderr, err_msg1);
    FMC_printBrightRedText(stderr, err_msg1);
    FMC_printGreenText(stderr, err_msg1);
    FMC_printBrightGreenText(stderr, err_msg1);
    FMC_printYellowText(stderr, err_msg1);
    FMC_printBrightYellowText(stderr, err_msg1);
    FMC_printBlueText(stderr, err_msg1);
    FMC_printBrightBlueText(stderr, err_msg1);
    FMC_printMagentaText(stderr, err_msg1);
    FMC_printBrightMagentaText(stderr, err_msg1);
    FMC_printCyanText(stderr, err_msg1);
    FMC_printBrightCyanText(stderr, err_msg1);    
    
    assert(strcmp("Invalid argument. Additional info: test1", err_buf) == 0);
    FMC_setError(FMC_INVALID_ARGUMENT, "test2");
}