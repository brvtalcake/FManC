/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * \defgroup fmanc_CH Core C headers
 * @{
 */

/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * \defgroup fmanc_CLH Core lib C headers
 * @ingroup fmanc_CH
 * @{
 */

/**
 * @file 	   analyze.h
 *
 * @brief      This header contains type definitions and function declarations that are written in \link analyze.c this file \endlink.
 * @details	   These functions are made to analyze files content and make operations on it.
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

#ifndef ANALYZE_H
#define ANALYZE_H 

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


#include <stddef.h>


SHARED struct FMANC_SO
{
    size_t charCount;
    long long int *pos;
};

SHARED typedef struct FMANC_SO stringOccurrences;

SHARED size_t countCharInFile(char *filePath);
SHARED stringOccurrences *init_StringOccurences(size_t sizeOfString);
SHARED void free_stringOccurrences(stringOccurrences *toBeDeleted);
SHARED stringOccurrences *searchStringInFile(char *filePath, char *toSearch);

/**
 * @fn         int replaceStringInFile(char *filePath, char *toReplaceString, char *toAddString);
 * @brief      This function replace a wide-character string by another one 
 * @details    If there is a problem during the call of the function, it will print strerr(errno) on stderr, and/or return an appropriate value 
 * @param      filePath         The file path of the document (for example : "./src/example.txt", or "exemple.txt" if the program is called from the same folder). For paths with backslashes, you will need to double it ("\\"), but no need to do this if you use a path that comes from argv arg of your main func.
 * @param      toReplaceString  The string to replace
 * @param      toAddString      The string to add
 *
 * @return     Returns 0 if all good.
 * @retval     -4 Problem when converting the char string to wide char string
 * @retval     -3 Problem when calling setlocale() 
 * @retval     -2 Problem when trying to get the ext, name or path of the file
 * @retval     -1 Problem when opening files
 * @retval      1 Problem when writing into the new file
 * @retval      2 Problem when renaming or removing files
 * @retval      3 The string to replace isn't in the file 
 */
SHARED int replaceStringInFile(char *filePath, char *toReplaceString, char *toAddString);


#endif

