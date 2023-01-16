
/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * \defgroup fmanc_CH Core C headers
 * @{
 */

/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * \defgroup fmanc_MH Main C header
 * @ingroup fmanc_CH
 * @{
 */

/**
 * @file 	   fmanc.h
 *
 * @brief      This is the main header of the lib, where all of the headers are included.
 * @details	   If you don't want to have troubles, just include this one instead of including the others one by one.
 * 			   If you want to use the functions defined in \link fcmx.h this\endlink or \link lex_yy.h this\endlink source files, then write something like 
 * 			   \code{.c} #define USE_FCMX TRUE\endcode (actually, just define USE_FCMX with a certain value, no matter what it is).
 *
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * 
 */

/**
 * @}
 */
/**
 * @}
 */
#ifndef FMANC_H
#define FMANC_H

/**
 * @def SHARED
 * @brief Useful to choose how to use the lib on Windows systems.
 * @details If you want to use the lib with the dll, you don't need to add anything in the command line. If you want to use the static version of the lib, then put "-D STATIC" in your command line when compiling, so you let the compiler know that the keyword "SHARED" is set to nothing and the function declarations are not provided with the __declspec() attribute.
 You can also look at the full macro block below (wich is also in the source code of all of the headers) to see what I mean
 * @code{.c}
# if defined(_WIN32)
#   if defined(STATIC)
#     define SHARED
#   else
#     if defined(BUILD_DLL)
#       define SHARED __declspec(dllexport)
#     else
#       define SHARED __declspec(dllimport)
#     endif
#   endif
# else
#   define SHARED
# endif
 * @endcode
 */

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
#include "./notByMe/lex_yy.h"
#endif







#endif