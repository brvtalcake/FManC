#include "../src_lib/fmanc.h"
#include <assert.h>
#include <string.h>
#include "test_suite.h"


void test_countCharInFile(void)
{
    assert(countCharInFile(NULL)==0);

    assert(countCharInFile("../../plain_text_data/rand_5040")==5040+1);

    assert(countCharInFile("../../plain_text_data/rand_528000")==528000+1);

    assert(countCharInFile("../../plain_text_data/rand_2716")==2716+1);
    
    assert(countCharInFile("../../plain_text_data/rand_984336")==984336+1);

    assert(countCharInFile("../../plain_text_data/empty")==1);
}
