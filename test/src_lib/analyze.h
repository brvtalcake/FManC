#ifndef ANALYZE_H
#define ANALYZE_H 

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


#include <stddef.h>


SHARED struct FManC_StrOcc
{
	size_t charCount;
	long long int *pos;
};

SHARED typedef struct FManC_StrOcc stringOccurrences;

SHARED size_t countCharInFile(char *filePath);
SHARED stringOccurrences *init_stringOccurences(size_t sizeOfString);
SHARED void free_stringOccurrences(stringOccurrences *toBeDeleted);
SHARED stringOccurrences *searchStringInFile(char *filePath, char *toSearch);
SHARED int replaceStringInFile(char *filePath, char *toReplaceString, char *toAddString);
SHARED int copyFileWithoutStrings(const unsigned int argc, char *filePath, ...); // to do


#endif

