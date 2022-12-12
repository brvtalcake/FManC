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

#ifndef MAX_FEXT_SIZE
#define MAX_FEXT_SIZE 50
#endif

#ifndef MAX_FNAME_SIZE 
#define MAX_FNAME_SIZE 256
#endif

#ifndef MAX_FPATH_SIZE
#define MAX_FPATH_SIZE 512
#endif

#ifndef getFileExtension
#define getFileExtension(sourceFileName, extension) char extension[MAX_FEXT_SIZE]; fgetFileExtension(sourceFileName, extension)
#endif

#ifndef getFileName
#define getFileName(sourceFilePath, name) char name[MAX_FNAME_SIZE]; fgetFileName(sourceFilePath, name)
#endif

#ifndef getFilePath
#define getFilePath(sourceFilePath, path) char path[MAX_FPATH_SIZE]; fgetFilePath(sourceFilePath, path)
#endif


char *copyFileWithoutTabAndLineBreak(char *sourceFilePath, char **pathToCopy); // copied file will be named like <sourceFile name>_copied
int copyFileWithoutStrings(const unsigned int argc, char *filePath, ...); // to do
void fgetFileExtension(char *sourceFileName, char *extension);
void fgetFileName(char *sourceFilePath, char *fileName);
void fgetFilePath(char *sourceFilePath, char *filePath); 


#endif


