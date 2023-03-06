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

#include <stdarg.h>
#include "FMC_file_management.h"
#include "../data_analyze/encodings/FMC_encodings.h"
#include "../cpp/FMC_wrapper.h"

/* #define TO_OPEN 16U
#define GET_ENCODING 32U
#define GET_SIZE 64U
#define BYTE_ORIENTED 128U
#define WIDE_ORIENTED 256U

FMC_SHARED struct FManC_File
{
    FILE *file;
    unsigned long long int fileSize;
    FMC_Encodings encoding;
    enum
    {
        wide,
        byte
    } orientation;
    FMC_FileState isOpened;
    char path[MAX_FPATH_SIZE];
    char name[MAX_FNAME_SIZE];
    char extension[MAX_FEXT_SIZE];
    char mode[10];
}; */

// TODO : FMC_getFileSize
// TODO : FMC_setFileOrientation



/* FMC_SHARED FMC_File *FMC_createFile(const unsigned int user_flags, const char* restrict const path, const char* restrict const mode)
{
    if (!path || !mode || user_flags == 0U || FMC_isRegFile(path) != 1)
    {
        return NULL;
    }

    check_in user_flags if_not_set(TO_OPEN) // create the file struct but do not open the FILE
    {
        FMC_File *returned_file = malloc(sizeof(FMC_File));
        if (!returned_file)
        {
            return NULL;
        }
        returned_file->file = NULL;
        if(!FMC_cutFilename(path, returned_file->path, MAX_FPATH_SIZE))
        {
            free(returned_file);
            return NULL;
        }
        if(!FMC_extractFilename(path, returned_file->name, MAX_FNAME_SIZE))
        {
            free(returned_file);
            return NULL;
        }
        if(!FMC_getExtension(path, returned_file->extension, MAX_FEXT_SIZE))
        {
            free(returned_file);
            return NULL;
        }
        returned_file->isOpened = False;
        FILE *feeded_file = fopen(path, "rb");
        if (!feeded_file)
        {
            free(returned_file);
            return NULL;
        }
        check_in user_flags for_at_least_flags(GET_ENCODING)
        {
            returned_file->encoding = FMC_getEncoding(feeded_file);
        }
        check_in user_flags for_at_least_flags(GET_SIZE)
        {
            
        }
    }

    
}
 */
/* #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!path)
    {
        return NULL;
    }
    #pragma GCC diagnostic pop // -Wnonnull-compare */

/* FMC_SHARED FMC_File *FMC_openFile();

FMC_SHARED static FMC_File *FMC_open_getEncoding();

FMC_SHARED static FMC_File *FMC_open_getSize();

FMC_SHARED static FMC_File *FMC_open_getEncoding_getSize(); */

