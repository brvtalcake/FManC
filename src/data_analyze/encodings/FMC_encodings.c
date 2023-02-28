/*

MIT License

Copyright (c) 2023 Axel PASCON

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
#define __STDC_WANT_LIB_EXT1__ 1
#include <stdio.h>
#include <stdlib.h> 
#include <errno.h>
#include <string.h>
#include <wchar.h> // fwide
#include <stdint.h>

#include "FMC_encodings.h"

FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1) FMC_Encodings FMC_getEncoding(FILE *file)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare" // get an error at compile time without this (because of attribute nonnull)
    if (file == NULL)
    {
        if (FMC_getDebugState()) 
        {
            FMC_makeMsg(err_null, 4, "ERROR : ", "In function : ", __func__, ". The provided file must not be NULL.");
            FMC_printBrightRedError(stderr, err_null);
        }
        return error;
    }
    #pragma GCC diagnostic pop

    // check orientation
    if (fwide(file, -1) >= 0)
    {
        if (FMC_getDebugState()) 
        {
            FMC_makeMsg(err_wide, 4, "ERROR : ", "In function : ", __func__, ". The provided file must be opened with by orientation.");
            FMC_printBrightRedError(stderr, err_wide);
        }
        return error;
    }

    long long sizeOfFile = 0;
    if(fseek(file, 0, SEEK_END)) 
    {
        FMC_makeMsg(err_seek_1, 4, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". fseek failure.");
        FMC_printBrightRedError(stderr, err_seek_1);
        return error;
    }
    errno = 0;
    sizeOfFile = ftell(file);
    if (errno || sizeOfFile == -1L)
    {
        FMC_makeMsg(err_tell, 5, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". ftell failure.", strerror(errno));
        FMC_printBrightRedError(stderr, err_tell);
        return error;
    }
    
    rewind(file);
    char buff[4] = {0};
    // 1st if
    if(sizeOfFile < 0) // no error, must have overflowed
    {
        sizeOfFile = (typeof(sizeOfFile)) SIZE_MAX;
        size_t ret = fread(buff, 1, 4, file);
        if(ret != 4) goto check_error_type_1;
        else if (ret == 4) goto end_check_1;
        else return error;
    }

    // 2nd if
    else if (sizeOfFile <= 4 && sizeOfFile >= 0) 
    {
        size_t ret = fread(buff, 1, (size_t)sizeOfFile, file); // harmless cast here because 0 <= sizeOfFile <= 4
        if(ret != (size_t) sizeOfFile) goto check_error_type_1;
        else if (ret == (size_t) sizeOfFile) goto end_check_1;
        else return error;

        check_error_type_1 : 
        FMC_LABEL_COLD;
        if (feof(file))
        {
            FMC_makeMsg(err_feof, 4, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". EOF indicator set.");
            FMC_printBrightRedError(stderr, err_feof);
            return error;
        }
        else if (ferror(file))
        {
            FMC_makeMsg(err_ferror, 5, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". Error indicator set.", strerror(errno));
            FMC_printBrightRedError(stderr, err_ferror);
            return error;
        }
        else
        {
            FMC_makeMsg(err_fread, 4, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". fread failure.");
            FMC_printBrightRedError(stderr, err_fread);
            return error;
        }
        
    }

    // 3rd if
    else if(fread(buff, 1, 4, file) != 4)
    {
        if (feof(file))
        {
            FMC_makeMsg(err_feof, 4, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". EOF indicator set.");
            FMC_printBrightRedError(stderr, err_feof);
            return error;
        }
        else if (ferror(file))
        {
            FMC_makeMsg(err_ferror, 5, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". Error indicator set.", strerror(errno));
            FMC_printBrightRedError(stderr, err_ferror);
            return error;
        }
        else
        {
            FMC_makeMsg(err_fread, 4, "FMC INTERNAL ERROR : ", "In function : ", __func__, ". fread failure.");
            FMC_printBrightRedError(stderr, err_fread);
            return error;
        }
    }

    end_check_1 :
    FMC_LABEL_HOT;
    if (sizeOfFile >= 3 && (unsigned char) buff[0] == 0xEF && (unsigned char) buff[1] == 0xBB && (unsigned char) buff[2] == 0xBF)
    {
        rewind(file);
        return utf8_bom;
    }
    else if (sizeOfFile >= 2 && (unsigned char) buff[0] == 0xFF && (unsigned char) buff[1] == 0xFE)
    {
        rewind(file);
        return utf16_le;
    }
    else if (sizeOfFile >= 2 && (unsigned char) buff[0] == 0xFE && (unsigned char) buff[1] == 0xFF)
    {
        rewind(file);
        return utf16_be;
    }
    else if (sizeOfFile >= 4 && (unsigned char) buff[0] == 0x00 && (unsigned char) buff[1] == 0x00 && (unsigned char) buff[2] == 0xFE && (unsigned char) buff[3] == 0xFF)
    {
        rewind(file);
        return utf32_be;
    }
    else if (sizeOfFile >= 4 && (unsigned char) buff[0] == 0xFF && (unsigned char) buff[1] == 0xFE && (unsigned char) buff[2] == 0x00 && (unsigned char) buff[3] == 0x00)
    {
        rewind(file);
        return utf32_le;
    }
    else
    {
        rewind(file);
        if (sizeOfFile == 0)
        {
            rewind(file);
            if (FMC_getDebugState()) 
            {
                FMC_makeMsg(err_empty, 4, "WARNING : ", "In function : ", __func__, ". The provided file is empty.");
                FMC_printBrightYellowError(stderr, err_empty);
            }
            return unknown;
        }
        
        char currentChar = 0;
        size_t cpt = 0;
        while((currentChar = (char)fgetc(file)) != EOF)
        {
            if (currentChar != EOF &&  (unsigned char) currentChar > 127)
            {
                rewind(file);
                return utf8;
            }
            cpt++;
            if ((long long) cpt >= sizeOfFile)
            {
                break;
            }
        }
        rewind(file);
        return ascii;
    }
}

FMC_SHARED FMC_FUNC_CONST FMC_FUNC_ALWAYS_INLINE inline FMC_Encodings FMC_checkEncodingFlag(unsigned int encoding)
{
    switch (encoding)
    {
        case ASCII:
            return ascii;
            break;
        case UTF8:
            return utf8;
            break;
        case UTF8_BOM:
            return utf8_bom;
            break;
        case UTF16_LE:
            return utf16_le;
            break;
        case UTF16_BE:
            return utf16_be;
            break;
        case UTF32_LE:
            return utf32_le;
            break;
        case UTF32_BE:
            return utf32_be;
            break;
        default: // TODO : add error in case of unknown encoding
            return unknown;
            break;
    }
    return error;
}

/*FMC_SHARED FMC_Char FMC_getc(FMC_File file)
{
    FMC_Char c = {.encoding = file.encoding, .comp = {.mostLeft = 0, .middleLeft = 0, .middleRight = 0, .mostRight = 0}, .isNull = 0};
    if(file.file == NULL || file.encoding == error || file.encoding == unknown)
    {
        c.isNull = 1;
        return c;
    }
    else if (fwide(file.file, 0) > 0)
    {
        fprintf(stderr, "Error: file is wide oriented when trying to read with byte orientation\n");
        c.isNull = 1;
        return c;
    }
    else if (file.encoding == ascii)
    {
        if (!feof(file.file))
        {
            
        }
        
    }
}*/