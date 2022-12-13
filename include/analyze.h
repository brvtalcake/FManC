#ifndef ANALYZE_H
#define ANALYZE_H 

#if defined(_WIN32)
    #if defined(BUILD_DLL)
        #define SHARED __declspec(dllexport)
    #else
        #define SHARED __declspec(dllimport)
    #endif
#endif

SHARED struct FMANC_SO
{
	size_t charCount;
	long *pos;
};

SHARED typedef struct FMANC_SO stringOccurrences;

SHARED long int countCharInFile(char *filePath);
SHARED stringOccurrences *init_StringOccurences(size_t sizeOfString);
SHARED void free_stringOccurrences(stringOccurrences *toBeDeleted);
SHARED stringOccurrences *searchStringInFile(char *filePath, char *toSearch);
SHARED int replaceStringInFile(char *filePath, char *toReplaceString, char *toAddString);


#endif

