#ifndef FILEMAN_H
#define FILEMAN_H 

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
#define getFileExtension(sourceFilePath, extension) char extension[MAX_FEXT_SIZE] = ""; fgetFileExtension(sourceFilePath, extension)
#endif

#ifndef getFileName
#define getFileName(sourceFilePath, name) char name[MAX_FNAME_SIZE] = ""; fgetFileName(sourceFilePath, name)
#endif

#ifndef getFilePath
#define getFilePath(sourceFilePath, path) char path[MAX_FPATH_SIZE] = ""; fgetFilePath(sourceFilePath, path)
#endif


SHARED char *copyFileWithoutTabAndLineBreak(char *sourceFilePath, char **pathToCopy); // copied file will be named like <sourceFile name>_copied
SHARED int copyFileWithoutStrings(const unsigned int argc, char *filePath, ...); // to do
SHARED void fgetFileExtension(char *sourceFileName, char *extension);
SHARED void fgetFileName(char *sourceFilePath, char *fileName);
SHARED void fgetFilePath(char *sourceFilePath, char *filePath); 


#endif