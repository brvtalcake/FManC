#include "test_suite.h"
#include <stdio.h>

FMC_Bool FMC_ENABLE_DEBUG = True;

int main()
{
    test_FMC_isDir();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_isDir() passed");
    test_FMC_dirExists();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_dirExists() passed");
    test_FMC_isRegFile();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_isRegFile() passed");
    test_FMC_isSymLink();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_isSymLink() passed");
    test_FMC_getCurrentPath();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_getCurrentPath() passed");
    test_FMC_getAbsolutePath();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_getAbsolutePath() passed");
    test_FMC_getEncoding();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_getEncoding() passed");
    test_FMC_checkEncodingFlag();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_checkEncodingFlag() passed");
    
    return 0;
}