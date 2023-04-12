#include <assert.h>
#include "test_suite.h"

void test_Error_System()
{
    char err_buf[256];
    FMC_setError(FMC_ERR_INVALID_ARGUMENT, "first_test");
    assert(FMC_getLastErrorNum_noDepop() == FMC_ERR_INVALID_ARGUMENT);
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

    assert(strncmp("Invalid argument. Additional info: first_test", err_buf, 256) == 0);
    FMC_setError(FMC_ERR_INVALID_ARGUMENT, "test2");
    FMC_setError(FMC_ERR_FILE, "test3");
    FMC_setError(FMC_ERR_FILE, "test4");
    FMC_setError(FMC_ERR_NULL_PTR, "test5");
    FMC_setError(FMC_ERR_NULL_PTR, "test6");
    FMC_setError(FMC_ERR_WRONG_FLAGS_COMBINATION, "test7");
    FMC_setError(FMC_ERR_WRONG_FLAGS_COMBINATION, "test8");
    FMC_setError(FMC_ERR_INTERNAL, "test9");
    FMC_setError(FMC_ERR_PUSH, "test10");
    FMC_setError(FMC_ERR_PUSH, "test11");
    FMC_setError(FMC_ERR_PUSH, "test12");
    FMC_setError(FMC_ERR_PUSH, "test13");
    FMC_setError(FMC_ERR_PUSH, "test14");
    assert(FMC_searchError(FMC_ERR_INVALID_ARGUMENT) == FMC_FALSE); // it has been cleared because of too many errors
    assert(FMC_searchError(FMC_ERR_PUSH) == FMC_TRUE);
    assert(FMC_searchErrorMsg("test10") == FMC_TRUE);
    assert(FMC_searchErrorMsg("test11") == FMC_TRUE);
    assert(FMC_searchErrorMsg("first_test") == FMC_FALSE);
    assert(FMC_searchErrorMsg("test2") == FMC_FALSE);
    memset(err_buf, 0, 256);
    FMC_getLastErrorStr_noDepop(err_buf, 256);
    assert(strcmp("A problem occured while trying to push an error onto the error stack. Additional info: test14", err_buf) == 0);
    FMC_clearErrorStack();
    FMC_destroyErrorStack();
    assert(FMC_searchError(FMC_ERR_PUSH) == FMC_FALSE);
    assert(FMC_getDebugState() == FMC_TRUE);
    FMC_setDebugState(FMC_FALSE);
    assert(FMC_getDebugState() == FMC_FALSE);
    FMC_setDebugState(FMC_TRUE);
}

void test_FMC_allocStrView()
{
    FMC_CStrView* str_view = FMC_allocStrView("Hello World!", sizeof("Hello World!") - 1); // -1 because null terminator is not counted
    assert(str_view != NULL);
    assert(str_view->size == sizeof("Hello World!"));
    assert(strncmp(str_view->str, "Hello World!", 13) == 0);
    FMC_freeStrView(str_view);
}