/*

MIT License

Copyright (c) 2022-2023 Axel PASCON

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

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
void free_stringOccurrences();

FMC_FUNC_UNAVAILABLE(This function is not anymore available in the library since the version 1.0.0.)
stringOccurrences *searchStringInFile(char *filePath, char *toSearch);

FMC_FUNC_UNAVAILABLE(This function is not anymore available in the library since the version 1.0.0.)
int deleteCStyleComments(char *filePath);

#endif // BUILDING_FMANC
#endif // FMC_DEPRECATED_H
