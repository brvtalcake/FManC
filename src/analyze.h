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

typedef struct 
{
	size_t charCount;
	long *pos;
}stringOccurrences;

long int countCharInFile(char *filePath);
stringOccurrences *init_StringOccurences(size_t sizeOfString);
void free_stringOccurrences(stringOccurrences *toBeDeleted);
stringOccurrences *searchStringInFile(char *filePath, char *toSearch);

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
int replaceStringInFile(char *filePath, char *toReplaceString, char *toAddString);


#endif

