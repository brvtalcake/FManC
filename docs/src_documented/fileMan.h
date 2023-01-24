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
 * @file 	   fileMan.h
 *
 * @brief      This header contains macro definitions and function declarations that are written in \link fileMan.c this file\endlink.
 * 			   These functions are made to operate simple operation on files or file names, when there is no neee to analyze something like orccurrences, ...
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

/**
 * @def MAX_FEXT_SIZE
 * @details This the value of the maximum size of a file extension counted in characters
 */
#ifndef MAX_FEXT_SIZE
#define MAX_FEXT_SIZE 50 
#endif

/**
 * @def MAX_FNAME_SIZE
 * @details This the value of the maximum size of a file name counted in characters
 */
#ifndef MAX_FNAME_SIZE 
#define MAX_FNAME_SIZE 256
#endif

/**
 * @def MAX_FPATH_SIZE
 * @details This the value of the maximum size of a file path (full (relative or not) path without name and extension) counted in characters
 */
#ifndef MAX_FPATH_SIZE
#define MAX_FPATH_SIZE 512
#endif

/**
 * @def getFileExtension(sourceFilePath, extension)
 * @brief Gives you the file extension.
 * @details It is stored in an array of char with the name you specify (extension).
 * @param[in] sourceFilePath Full path or relative path.
 * @param[out] extension The name of the array where you stock the extension.
 * @return This doesn't really return anything, but displays an error message if no extension or invalid extension. 
 */
#ifndef getFileExtension
#define getFileExtension(sourceFilePath, extension) char extension[MAX_FEXT_SIZE] = ""; fgetFileExtension(sourceFilePath, extension)
#endif

/**
 * @def getFileName(sourceFilePath, name)
 * @brief Gives you the file name.
 * @details It is stored in an array of char with the name you specify (name).
 * @param[in] sourceFilePath Full path or relative path.
 * @param[out] name The name of the array where you stock the name.
 * @return This doesn't really return anything, but displays an error message if no name or invalid name. 
 */
#ifndef getFileName
#define getFileName(sourceFilePath, name) char name[MAX_FNAME_SIZE] = ""; fgetFileName(sourceFilePath, name)
#endif

/**
 * @def getFilePath(sourceFilePath, path)
 * @brief Gives you the file path (without name and extension).
 * @details It is stored in an array of char with the name you specify (extension).
 * @param[in] sourceFilePath Full path or relative path.
 * @param[out] path The name of the array where you stock the path.
 * @return This doesn't really return anything, but if the path is like "main.c", then the array will have '\0' as first character. Won't display any error message if no path. 
 */
#ifndef getFilePath
#define getFilePath(sourceFilePath, path) char path[MAX_FPATH_SIZE] = ""; fgetFilePath(sourceFilePath, path)
#endif

/**
 * @fn         char *copyFileWithoutTabAndLineBreak(char *sourceFilePath, char **pathToCopy);
 * @brief      Copy a file without tab and line break.
 * @details    The copied file with be renamed as <sourceFile name>_copied.<sourceFileExtension> if the param pathToCopy is set to NULL, and what you want if you specify the path with a name and extension.
 * @todo       Check if the path to copy has a name and an extension at the end.
 *
 * @param      sourceFilePath  The source file path.
 * @param      pathToCopy      The path to copy. You can set it to NULL if you want the copied file to be in the same directory as the source file.
 *
 * @retval     sourceFileName This case is when no error has occured.
 * @retval     NULL           If an error has occured.
 */
SHARED char *copyFileWithoutTabAndLineBreak(char *sourceFilePath, char **pathToCopy); // copied file will be named like <sourceFile name>_copied

/**
 * @fn         int copyFileWithoutStrings(const unsigned int argc, char *filePath, ...);
 * @brief      Function just declared and still not done.
 * @todo       Do it (lol).
 *
 * @param[in]  argc       The count of arguments
 * @param      filePath   The file path
 * @param[in]  <unnamed>  { parameter_description }
 *
 * @return     { description_of_the_return_value }
 */

SHARED int copyFileWithoutStrings(const unsigned int argc, char *filePath, ...); // to do
SHARED void fgetFileExtension(char *sourceFileName, char *extension);
SHARED void fgetFileName(char *sourceFilePath, char *fileName);
SHARED void fgetFilePath(char *sourceFilePath, char *filePath); 


#endif


