#ifndef FMANC_H
#define FMANC_H


# if defined(_WIN32)
/***************** "-D STATIC" ******************/
#   if defined(STATIC)
#     define SHARED
/**************** "-D BUILD_DLL" ****************/
#   else
#     if defined(BUILD_DLL)
#       define SHARED __declspec(dllexport)
#     else
#       define SHARED __declspec(dllimport)
#     endif
#   endif
/****************** DEFAULT *******************/
# else
#   define SHARED
# endif


#include "fileMan.h"
#include "analyze.h"

#if defined(USE_FCMX)
#include "fcmx.h"
#include "./third_party/lex_yy.h"
#endif







#endif
