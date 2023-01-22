/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * @defgroup fmanc_MH Main header
 * @brief This header should be included if you don't know precisely what to include.
 * @{
 */

/**
 * 
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * 
 * @file 	   fmanc.h
 *
 * 
 * @brief      This is the main header of the lib, where all of the headers are included.
 * @details	   If you don't want to have troubles, just include this one instead of including the others one by one.
 */

/**
 * @}
 */


#ifndef FMANC_H
#define FMANC_H

/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * @defgroup GEN_MACROS General macros
 * @brief These macros are intended to be defined if you need to modify the headers to be included, or to modify the expansion of the @ref SHARED_def "SHARED macro" for Windows users.
 */

/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * @def SHARED
 * @anchor SHARED_def
 * @brief Useful to choose how to use the lib on Windows systems.
 * @details If you want to use the lib with the dll, you don't need to add anything in the command line. If you want to use the static version of the lib, then put "-D STATIC" in your command line when compiling, so you let the compiler know that the keyword "SHARED" is set to nothing and the function declarations are not provided with the __declspec() attribute.
 You can also look at the full macro block below (wich is also in the source code of all of the headers) to see what I mean
 * @code{.c}
# if (defined(_WIN32) || defined(WIN32))
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
# endif // Definition of SHARED macro
 * @endcode
 *
 * @todo I should change the name of "STATIC" to something like "FMANC_STATIC" to avoid any problems in case someone wants to use two libs with the same define system
 * @ingroup GEN_MACROS
 */

# if (defined(_WIN32) || defined(WIN32))
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
# endif // Definition of SHARED macro


#include "fileMan.h"
#include "analyze.h"

/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * @def USE_CODE_UTILS
 * @brief This macro provides access to more functions.
 * @details	For example, if you want to use the functions defined in \link code_utils.h this\endlink or \link lex_yy.h this\endlink source file, then write something like @code{.c}
 * #define USE_CODE_UTILS TRUE
 * @endcode
 * or
 * @code{.sh}
 * cc -D USE_CODE_UTILS ...
 * @endcode
 * (actually, just define USE_CODE_UTILS with no value or with a certain value, no matter what it is). USE_CODE_UTILS isn't defined by default.
 * 
 * @ingroup GEN_MACROS
 */
#define USE_CODE_UTILS // just to make doxygen generate the doc
#undef USE_CODE_UTILS

#if defined(USE_CODE_UTILS)
    #include "code_utils.h"
    #include "./third_party/lex_yy.h"
#endif // USE_CODE_UTILS


#endif // fmanc.h