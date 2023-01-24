#include "../src_lib/fmanc.h"
#include <assert.h>
#include <string.h>
#include "test_suite.h"
#include <stdio.h>
#include <stdlib.h>

void test_countCharInFile(void)
{
    char *PATH_FMANC = getenv("FMANC");

    assert(countCharInFile(NULL)==0);
    
    assert(countCharInFile(strcat(PATH_FMANC,"/test/plain_text_data/rand_5040"))==5040+1);
    
    assert(countCharInFile(strcat(PATH_FMANC,"/test/plain_text_data/rand_528000"))==528000+1);

    assert(countCharInFile(strcat(PATH_FMANC,"/test/plain_text_data/rand_2716"))==2716+1);
    
    assert(countCharInFile(strcat(PATH_FMANC,"/test/plain_text_data/rand_984336"))==984336+1);

    assert(countCharInFile(strcat(PATH_FMANC,"/test/plain_text_data/empty"))==1);
}
