/*

MIT License

Copyright (c) 2022 Axel PASCON

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

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <wchar.h>
#include <locale.h>
#include "../../general/FMC_data.h"

#include "FMC_encodings.h"



SHARED FMC_Encodings FMC_getEncoding(FILE *file)
{
    if (file == NULL)
    {
        return error;
    }
    size_t sizeOfFile = 0;
    fseek(file, 0, SEEK_END);
    sizeOfFile = ftell(file);
    rewind(file);
    int buff[4] = {0};
    if (sizeOfFile < 4 && sizeOfFile > 0) fread(buff, 1, sizeOfFile, file);
    else fread(buff, 1, 4, file);
    
    if (sizeOfFile >= 3 && buff[0] == 0xEF && buff[1] == 0xBB && buff[2] == 0xBF)
    {
        rewind(file);
        return utf8_bom;
    }
    else if (sizeOfFile >= 2 && buff[0] == 0xFF && buff[1] == 0xFE)
    {
        rewind(file);
        return utf16_le;
    }
    else if (sizeOfFile >= 2 && buff[0] == 0xFE && buff[1] == 0xFF)
    {
        rewind(file);
        return utf16_be;
    }
    else if (sizeOfFile >= 4 && buff[0] == 0x00 && buff[1] == 0x00 && buff[2] == 0xFE && buff[3] == 0xFF)
    {
        rewind(file);
        return utf32_be;
    }
    else if (sizeOfFile >= 4 && buff[0] == 0xFF && buff[1] == 0xFE && buff[2] == 0x00 && buff[3] == 0x00)
    {
        rewind(file);
        return utf32_le;
    }
    else
    {
        if (sizeOfFile == 0)
        {
            rewind(file);
            return unknown;
        }
        
        int currentChar = 0;
        size_t cpt = 0;
        while((currentChar = fgetc(file)) != EOF)
        {
            if (currentChar > 127 || currentChar < 0 && currentChar != EOF)
            {
                rewind(file);
                return utf8;
            }
            cpt++;
            if (cpt >= sizeOfFile)
            {
                break;
            }
        }
        rewind(file);
        return ascii;
    }
}

SHARED FMC_Encodings FMC_checkEncodingFlag(int encoding)
{
    int value = encoding | ASCII | UTF8 | UTF8_BOM | UTF16_LE | UTF16_BE | UTF32_LE | UTF32_BE;
    switch (value)
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
        default:
            return error;
            break;
    }
}

SHARED FMC_Char FMC_getc(FMC_File file)
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
}