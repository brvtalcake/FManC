#ifndef FMC_DEPRECATED_H
#define FMC_DEPRECATED_H

#include "../preprocessor/FMC_attributes.h"
#include <stddef.h>

#if !defined(BUILDING_FMANC)
FMC_TYPE_UNAVAILABLE(This type is not anymore available in the library since the version 1.0.0.)
struct FMANC_SO
{
    size_t charCount;
    long long int *pos;
};

FMC_TYPE_UNAVAILABLE(This type is not anymore available in the library since the version 1.0.0.)
typedef struct FMANC_SO stringOccurrences;

FMC_FUNC_UNAVAILABLE(This function is not anymore available in the library since the version 1.0.0.)
char *copyFileWithoutTabAndLineBreak(char *sourceFilePath, char **pathToCopy);

FMC_FUNC_UNAVAILABLE(This function is not anymore available in the library since the version 1.0.0. Use FMC_extractFilename instead)
void fgetFileName(char *sourceFilePath, char *fileName);

FMC_FUNC_UNAVAILABLE(This function is not anymore available in the library since the version 1.0.0. Use FMC_cutFilename instead)
void fgetFilePath(char *sourceFilePath, char *filePath);

FMC_FUNC_UNAVAILABLE(This function is not anymore available in the library since the version 1.0.0. Use FMC_getExtension instead)
void fgetFileExtension(char *sourceFilePath, char *extension);

FMC_FUNC_UNAVAILABLE(This function is not anymore available in the library since the version 1.0.0.)
size_t countCharInFile(char *filePath);

FMC_FUNC_UNAVAILABLE(This function is not anymore available in the library since the version 1.0.0.)
stringOccurrences *init_StringOccurences(size_t sizeOfString);

FMC_FUNC_UNAVAILABLE(This function is not anymore available in the library since the version 1.0.0.)
void free_stringOccurrences(stringOccurrences *toBeDeleted);

FMC_FUNC_UNAVAILABLE(This function is not anymore available in the library since the version 1.0.0.)
stringOccurrences *searchStringInFile(char *filePath, char *toSearch);

FMC_FUNC_UNAVAILABLE(This function is not anymore available in the library since the version 1.0.0.)
int deleteCStyleComments(char *filePath);

#endif // BUILDING_FMANC
#endif // FMC_DEPRECATED_H
