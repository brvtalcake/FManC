#include "../src_lib/fmanc.h"
#include <assert.h>
#include <string.h>
#include "test_suite.h"

void test_getFileExtension(void)
{
	getFileExtension("~/Desktop/prog/c/ext_test1.c", ext1);
	assert(strcmp(".c", ext1) == 0);

	getFileExtension("ext_test2.html", ext2);
	assert(strcmp(".html", ext2) == 0);

	getFileExtension("~ext_test3", ext3);
	assert(strcmp("", ext3) == 0);

	getFileExtension(".\\.github\\test4.loremipsum", ext4);
	assert(strcmp(".loremipsum", ext4) == 0);

	getFileExtension("FManC\\.git\\", ext5);
	assert(strcmp("", ext5) == 0);

	getFileExtension("FManC\\.git\\test6", ext6);
	assert(strcmp("", ext6) == 0);

	getFileExtension("FManC\\.git\\test7.zip", ext7);
	assert(strcmp(".zip", ext7) == 0);
}