#ifndef LEX_YY_H
#define LEX_YY_H 

#if defined(_WIN32)
    #if defined(BUILD_DLL)
        #define SHARED __declspec(dllexport)
    #else
        #define SHARED __declspec(dllimport)
    #endif
#endif

SHARED int deleteCStyleComments(char *filePath);


#endif