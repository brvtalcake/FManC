#ifndef FMANC_H
#define FMANC_H

#include "fileMan.h"
#include "analyze.h"

#if defined(USE_FCMX)
#include "fcmx.h"
#include "./notByMe/lex_yy.h"
#endif

#if defined(_WIN32)
    #if defined(BUILD_DLL)
        #define SHARED __declspec(dllexport)
    #else
        #define SHARED __declspec(dllimport)
    #endif
#endif



#endif
