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

#if defined(_WIN32)
    #if defined(BUILD_DLL)
        #define SHARED __declspec(dllexport)
    #else
        #define SHARED __declspec(dllimport)
    #endif
#endif

SHARED int deleteCStyleComments(char *filePath);


#endif