#include "../src_lib/fmanc.h"
#include <assert.h>
#include <string.h>
#include "test_suite.h"

void test_getFilePath(void)
{
	getFilePath("~/Desktop/prog/c/ext_test1.c", ext1);
	assert(strcmp("~/Desktop/prog/c/", ext1) == 0);

	getFilePath("ext_test2.html", ext2);
	assert(strcmp("", ext2) == 0);

	getFilePath("~ext_test3/", ext3);
	assert(strcmp("~ext_test3/", ext3) == 0);

	getFilePath(".\\.github\\test4.loremipsum", ext4);
	assert(strcmp(".\\.github\\", ext4) == 0);

	getFilePath("FManC\\.git\\", ext5);
	assert(strcmp("FManC\\.git\\", ext5) == 0);

	getFilePath("FManC\\.git\\test6", ext6);
	assert(strcmp("FManC\\.git\\", ext6) == 0);

	getFilePath("FManC\\.git\\test7.zip", ext7);
	assert(strcmp("FManC\\.git\\", ext7) == 0);
}