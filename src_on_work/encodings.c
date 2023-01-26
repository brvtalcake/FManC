#include <stdio.h>

#define UNKWON 1
#define ASCII 2
#define UTF8 4
#define UTF8_BOM 8
#define UTF16_LE 16
#define UTF16_BE 32
#define UTF32_LE 64
#define UTF32_BE 128

typedef enum FManC_encodings
{
    utf8,
    utf8_bom,
    utf16_le,
    utf16_be,
    utf32_le,
    utf32_be,
    ascii,
    unknown,
    error
} FMC_encodings;

FMC_encodings FMC_getEncoding(FILE *file)
{
    if (file == NULL)
    {
        return unknown;
    }
    size_t sizeOfFile =0;
    fseek(file, 0, SEEK_END);
    sizeOfFile = ftell(file);
    rewind(file);
    unsigned char buff[4] = {0};
    fread(buff, 1, 4, file);
    
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
        while((currentChar = fgetc(file)) != EOF)
        {
            if (currentChar > 127)
            {
                rewind(file);
                return utf8;
            }
            else if (currentChar < 0)
            {
                rewind(file);
                return error;
            }
        }
        return ascii;
    }
}

int FMC_changeEncoding(FILE *file, FMC_encodings target_encoding, int base_encoding)
{
    if (file == NULL)
    {
        return -1;
    }
    // TODO : check the flag 'base_encoding' and change the encoding of the file
}