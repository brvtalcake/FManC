#if defined(FMC_COMPILING_ON_WINDOWS)
    #include <windows.h>
#elif defined(FMC_COMPILING_ON_LINUX)
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <unistd.h>
#endif

#include "test_suite.h"
#include <stdio.h>


int main()
{
    FMC_setDebugState(FMC_TRUE);
    
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
    
    test_Error_System();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_Error_System() passed");
    
    test_FMC_mkDir_rmDir();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_mkDir_rmDir() passed");
    
    test_FMC_getOptIOBufSize();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_getOptIOBufSize() passed");
    
    test_FMC_allocStrView();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_allocStrView() passed");
    
    test_FMC_getCurrentUserName();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_getCurrentUserName() passed");

    #if !defined(FMC_COMPILING_ON_WINDOWS)
    test_FMC_getAllUIDs();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_getAllUIDs() passed");
    #endif // !defined(FMC_COMPILING_ON_WINDOWS)

    test_FMC_extractFilename();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_extractFilename() passed");

    test_FMC_getExtension();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_getExtension() passed");

    test_FMC_cutFilename();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_cutFilename() passed");

    test_FMC_FileAPI();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_FileAPI() passed");

    test_FMC_CodePoint();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_CodePoint() passed");

    test_FMC_checkEncodingFlag2();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_checkEncodingFlag2() passed");

    test_FMC_Strings();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_Strings() passed");

    test_FMC_readFile();
    fprintf(stderr, "\x1b[32m%s\n\x1b[0m", "test_FMC_readFile() passed");

    return 0;
}