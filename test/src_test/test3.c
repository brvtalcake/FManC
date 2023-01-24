#include "../src_lib/fmanc.h"
#include <assert.h>
#include <string.h>
#include "test_suite.h"
#include <stdio.h>
void test_getFilePath(void)
{
	getFilePath("~/Desktop/prog/c/ext_test1.c", path1);
	assert(strcmp("~/Desktop/prog/c/", path1) == 0);

	getFilePath("ext_test2.html", path2);
	assert(strcmp("", path2) == 0);

	getFilePath("~ext_test3/", path3);
	printf("%s\n", path3);
	assert(strcmp("~ext_test3/", path3) == 0);

	getFilePath(".\\.github\\test4.loremipsum", path4);
	assert(strcmp(".\\.github\\", path4) == 0);

	getFilePath("FManC\\.git\\", path5);
	assert(strcmp("FManC\\.git\\", path5) == 0);

	getFilePath("FManC\\.git\\test6", path6);
	assert(strcmp("FManC\\.git\\", path6) == 0);

	getFilePath("FManC\\.git\\test7.zip", path7);
	assert(strcmp("FManC\\.git\\", path7) == 0);
}