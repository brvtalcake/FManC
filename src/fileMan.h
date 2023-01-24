
/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * @defgroup fmanc_FM_UTILS File management utilities
 * @brief This module provides utilities to manage informations about files.
 * @{
 */


/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * 
 * @brief This submodule contains files related to file management utilities.
 * 
 * @defgroup fmanc_FM_UTILS_files Source files
 * @ingroup fmanc_FM_UTILS
 * @{
 */


/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * 
 * @file 	   fileMan.h
 *
 * @brief      This header contains macro definitions and function declarations that are written in \link fileMan.c this file\endlink.
 * 
 * @details    These functions are made to operate simple operation on files or file names, when there is no need to analyze something like occurrences, 
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

#ifndef FILEMAN_H
#define FILEMAN_H 

/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * 
 * @def SHARED
 * @brief Useful to choose how to use the lib on Windows systems.
 * @details For more informations, please see @ref SHARED_def "the definition of the SHARED macro" in the main header
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
# endif

/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * @brief This submodule contains constant macros used by the lib.
 * @defgroup fmanc_FM_UTILS_const_macros Constant macros
 * @ingroup fmanc_FM_UTILS
*/

/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * 
 * @def MAX_FEXT_SIZE
 * @details This the value of the maximum size of a file extension counted in characters.
 * @ingroup fmanc_FM_UTILS_const_macros
 */
#ifndef MAX_FEXT_SIZE
#define MAX_FEXT_SIZE 50
#endif

/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * @def MAX_FNAME_SIZE
 * @details This the value of the maximum size of a file name counted in characters.
 * @ingroup fmanc_FM_UTILS_const_macros
 */
#ifndef MAX_FNAME_SIZE 
#define MAX_FNAME_SIZE 256
#endif

/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * @def MAX_FPATH_SIZE
 * @details This the value of the maximum size of a file path (full (relative or not) path without name and extension) counted in characters.
 * @ingroup fmanc_FM_UTILS_const_macros
 */
#ifndef MAX_FPATH_SIZE
#define MAX_FPATH_SIZE 512
#endif


/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * @brief This submodule contains macros related to files management facilities.
 * @defgroup fmanc_FM_UTILS_macros Macros
 * @ingroup fmanc_FM_UTILS
*/

/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * @def getFileExtension(sourceFilePath, extension)
 * @brief Gives you the file extension.
 * @details It is stored in an array of char with the name you specify (extension).
 * @param[in] sourceFilePath Full path or relative path.
 * @param[out] extension The name of the array where you store the extension.
 * @return This doesn't really return anything, but displays an error message if no extension or invalid extension. Moreover, you should check the emptyness of the created variable.
 * @ingroup fmanc_FM_UTILS_macros
 */
#ifndef getFileExtension
#define getFileExtension(sourceFilePath, extension) char extension[MAX_FEXT_SIZE] = ""; fgetFileExtension(sourceFilePath, extension)
#endif


/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * @def getFileName(sourceFilePath, name)
 * @brief Gives you the file name.
 * @details It is stored in an array of char with the name you specify (name).
 * @param[in] sourceFilePath Full path or relative path.
 * @param[out] name The name of the array where you stock the name.
 * @return This doesn't really return anything, but displays an error message if no name or invalid name. Moreover, you should check the emptyness of the created variable.
 * @ingroup fmanc_FM_UTILS_macros
 */
#ifndef getFileName
#define getFileName(sourceFilePath, name) char name[MAX_FNAME_SIZE] = ""; fgetFileName(sourceFilePath, name)
#endif


/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * @def getFilePath(sourceFilePath, path)
 * @brief Gives you the file path (without name and extension).
 * @details It is stored in an array of char with the name you specify (extension).
 * @param[in] sourceFilePath Full path or relative path.
 * @param[out] path The name of the array where you stock the path.
 * @return This doesn't really return anything, but if the path is like "main.c", then the array will have '\0' as only character. Won't display any error message if no path. Here again, check the emptyness of the created variable.
 * @ingroup fmanc_FM_UTILS_macros
 */
#ifndef getFilePath
#define getFilePath(sourceFilePath, path) char path[MAX_FPATH_SIZE] = ""; fgetFilePath(sourceFilePath, path)
#endif


/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * @defgroup fmanc_FM_UTILS_func Functions
 * @ingroup fmanc_FM_UTILS
 * @brief This submodule contains the functions related to file management utilities.
**/

/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * @fn         char *copyFileWithoutTabAndLineBreak(char *sourceFilePath, char *pathToCopy);
 * @brief      Copy a file without tab and line break.
 * @details    The copied file with be renamed as <sourceFile name>_copied.<sourceFileExtension> if the param pathToCopy is set to NULL, and what you want if you specify the path with a name and extension.
 * @todo       Check if the path to copy has a name and an extension at the end.
 * @todo       Move it to code_utils.h
 *
 * @param      sourceFilePath  The source file path.
 * @param      pathToCopy      The path to copy. You can set it to NULL if you want the copied file to be in the same directory as the source file.
 *
 * @retval     sourceFileName This case is when no error has occured.
 * @retval     NULL           If an error has occured.
 * @ingroup fmanc_FM_UTILS_func
 */
SHARED char *copyFileWithoutTabAndLineBreak(char *sourceFilePath, char *pathToCopy); // copied file will be named like <sourceFile name>_copied
SHARED int copyFileWithoutStrings(const unsigned int argc, char *filePath, ...); // to do
SHARED void fgetFileExtension(const char* const sourceFileName, char *extension);
SHARED void fgetFileName(const char* const sourceFilePath, char *fileName);
SHARED void fgetFilePath(const char* const sourceFilePath, char *filePath); 


#endif