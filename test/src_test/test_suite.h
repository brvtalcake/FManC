#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include "../../include/FMC.h"

/*
void test_getFileExtension(void);
void test_getFileName(void);
void test_getFilePath(void);
void test_copyFileWithoutTabAndLineBreak(void);
void test_countCharInFile(void);
*/

void test_FMC_dirExists();
void test_FMC_isDir();
void test_FMC_isRegFile();
void test_FMC_isSymLink();
void test_FMC_getCurrentPath();
void test_FMC_getAbsolutePath();
void test_FMC_getEncoding();
void test_FMC_checkEncodingFlag();
#endif // TEST_SUITE_H
