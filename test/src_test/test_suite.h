#ifndef TEST_SUITE_H
#define TEST_SUITE_H

#include "../../include/FMC.h"

#if defined(FMC_COMPILING_ON_WINDOWS)
    #include <windows.h>
#elif defined(FMC_COMPILING_ON_LINUX)
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <unistd.h>
#endif
#include <string.h>

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
void test_FMC_mkDir_rmDir();
void test_Error_System();
void test_FMC_getOptimalWriteBufferSize();
void test_FMC_allocStrView();
void test_FMC_getCurrentUserName();
#endif // TEST_SUITE_H
