#include "../src_lib/fmanc.h"
#include <assert.h>
#include <string.h>
#include "test_suite.h"

void test_getFileName(void)
{
	getFileName("~/Desktop/prog/c/ext_test1.c", name1);
	assert(strcmp("ext_test1", name1) == 0);
    
	getFileName("ext_test2.html", name2);
	assert(strcmp("ext_test2", name2) == 0);
    
	getFileName("~ext_test3/", name3);
	assert(strcmp("", name3) == 0);

	getFileName(".\\.github\\test4.loremipsum", name4);
	assert(strcmp("test4", name4) == 0);

	getFileName("FManC\\.git\\", name5);
	assert(strcmp("", name5) == 0);

	getFileName("FManC\\.git\\test6", name6);
	assert(strcmp("test6", name6) == 0);
    
	getFileName("FManC\\.git\\test7.zip", name7);
	assert(strcmp("test7", name7) == 0);
}