/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * \defgroup for_me C Headers for my personnal project
 * @{
 */

/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * \defgroup for_me_byMeAndFlex C Headers for my personnal project, made by me and flex
 * @ingroup for_me
 * @{
 */

/**
 * @file 	   lex_yy.h
 *
 * @brief      This header contains a function written by flex to delete C-style comments in a file
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


#ifndef LEX_YY_H
#define LEX_YY_H 

/**
 * @def SHARED
 * @brief Useful to choose how to use the lib on Windows systems.
 * @details If you want to use the lib with the dll, you don't need to add anything in the command line. If you want to use the static version of the lib, then put "-D STATIC" in your command line when compiling, so you let the compiler know that the keyword "SHARED" is set to nothing and the function declarations are not provided with the __declspec() attribute.
 You can also look at the full macro block below (wich is also in the source code of all of the headers) to see what I mean
 @todo       I should change the name of "STATIC" to something like "FMANC_STATIC" to avoid any problems in case someone wants to use two libs with the same define system 
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



SHARED int deleteCStyleComments(char *filePath);


#endif