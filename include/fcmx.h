#ifndef FCMX_H
#define FCMX_H 

#if defined(_WIN32)
    #if defined(BUILD_DLL)
        #define SHARED __declspec(dllexport)
    #else
        #define SHARED __declspec(dllimport)
    #endif
#endif

SHARED int copyFileWithoutStrings(const unsigned int argc, char *filePath, ...); // to do
 


#endif

