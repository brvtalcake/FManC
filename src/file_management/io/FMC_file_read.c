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

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "FMC_io.h"
#include "../../cpp/FMC_wrapper.h"

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_NONNULL(1) FMC_FUNC_WARN_UNUSED_RESULT FMC_String* FMC_readFile(FMC_File* const file)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!file)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_nullarg, 3, "ERROR: In function: ", __func__, ": argument: file is null");
            FMC_printRedError(stderr, err_nullarg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "Argument: file is null");
        return NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop
    if (!file->isOpened || !*file->fullMode || !file->file || file->dataMode != binary)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_invalidarg, 3, "ERROR: In function: ", __func__, ": argument: file is not opened, or with an invalid mode");
            FMC_printRedError(stderr, err_invalidarg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "Argument: file is not opened, or with an invalid mode");
        return NULL;
        FMC_UNREACHABLE;
    }
    if (file->orientation != byte_oriented)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_invalidarg, 3, "ERROR: In function: ", __func__, ": argument: file is not byte oriented");
            FMC_printRedError(stderr, err_invalidarg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "Argument: file is not byte oriented");
        return NULL;
        FMC_UNREACHABLE;
    }
    char full_path[MAX_FNAME_SIZE + MAX_FPATH_SIZE];
    memset(full_path, 0, MAX_FNAME_SIZE + MAX_FPATH_SIZE);
    if (strcpy(full_path, file->path) != full_path)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": strcpy failed");
            FMC_printRedError(stderr, err_int);
        }
        FMC_setError(FMC_ERR_INTERNAL, "strcat failed");
        return NULL;
        FMC_UNREACHABLE;
    }
    if (strcat(full_path, file->name) != full_path)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": strcat failed");
            FMC_printRedError(stderr, err_int);
        }
        FMC_setError(FMC_ERR_INTERNAL, "strcat failed");
        return NULL;
        FMC_UNREACHABLE;
    }
    if (!FMC_isRegFile(full_path) && !FMC_isSymLink(full_path))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_invalidarg, 3, "ERROR: In function: ", __func__, ": argument: file is not a regular file or a symbolic link");
            FMC_printRedError(stderr, err_invalidarg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "Argument: file is not a regular file or a symbolic link");
        return NULL;
        FMC_UNREACHABLE;
    }
    FMC_Char* null_char = FMC_allocChar(FMC_NULL_BYTES, file->encoding, FMC_TRUE, 
                                        (file->encoding == utf8_bom || file->encoding == utf8 || file->encoding == ascii) ? 1
                                        : (file->encoding == utf16_le || file->encoding == utf16_be) ? 2
                                        : (file->encoding == utf32_le || file->encoding == utf32_be) ? 4
                                        : 0);
    if (!null_char)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": provided encoding is invalid");
            FMC_printRedError(stderr, err_int);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "Provided encoding is invalid");
        return NULL;
        FMC_UNREACHABLE;
    }
    FMC_String* str = FMC_allocStr(&null_char, 1);
    if (!str)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_allocStr failed");
            FMC_printRedError(stderr, err_int);
        }
        FMC_setError(FMC_ERR_INTERNAL, "FMC_allocStr failed");
        return NULL;
        FMC_UNREACHABLE;
    }

    // Possible encodings :
    // utf8     = 1,
	// utf8_bom = 2,
	// utf16_le = 4,
	// utf16_be = 8,
	// utf32_le = 16,
	// utf32_be = 32,
	// ascii    = 64,
	// unknown  = 128,
	// error    = 256
    rewind(file->file);
    int ch = 0;
    FMC_Char* new_char = FMC_alloca(sizeof(FMC_Char));
    switch (file->encoding)
    {
        case utf8_bom: // skip the BOM and then fallthru on utf8
        {
            if (fseek(file->file, 3, SEEK_SET))
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fseek failed");
                    FMC_printRedError(stderr, err_int);
                }
                FMC_setError(FMC_ERR_INTERNAL, "fseek failed");
                return NULL;
                FMC_UNREACHABLE;
            }
        }
        FMC_STMT_FALLTHROUGH;

        case utf8:
        {
            while ((ch = fgetc(file->file)) != EOF)
            {
                if (ch < 0 || ch > 255)
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                        FMC_printRedError(stderr, err_int);
                    }
                    FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                    return NULL;
                    FMC_UNREACHABLE;
                }
                FMC_Byte bytes[4] = {0x00, 0x00, 0x00, 0x00};
                uint8_t current_byte_count = ch < 128 ? 1 
                                           : ch >> 5 == 6 ? 2 
                                           : ch >> 4 == 14 ? 3 
                                           : ch >> 3 == 30 ? 4 
                                           : 0;

                switch (current_byte_count)
                {
                    case 1:
                    {
                        FMC_UNREACHABLE_ASSERT(ch < 128 && ch >= 0);
                        FMC_STMT_ASSUME(ch < 128 && ch >= 0);
                        bytes[0] = (FMC_Byte)ch & 0xFF;
                        /* new_char = FMC_allocChar(bytes, utf8,
                                                           ch == 0 ? FMC_TRUE : FMC_FALSE,
                                                           1); */
                        memset(new_char, 0, sizeof(FMC_Char));
                        new_char->encoding = file->encoding;
                        new_char->comp.byte0 = bytes[0];
                        new_char->comp.byte1 = 0x00;
                        new_char->comp.byte2 = 0x00;
                        new_char->comp.byte3 = 0x00;
                        new_char->isNull = (ch == 0 ? FMC_TRUE : FMC_FALSE);
                        new_char->byteNumber = 1;
                        if (!FMC_append(str, new_char))
                        {
                            if (FMC_getDebugState())
                            {
                                FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_append failed");
                                FMC_printRedError(stderr, err_int);
                            }
                            FMC_setError(FMC_ERR_INTERNAL, "FMC_append failed");
                            FMC_freeStr(str);
                            return NULL;
                            FMC_UNREACHABLE;
                        }

                        // Free the char because FMC_append makes a copy
                        /* FMC_freeChar(new_char);  */
                    }
                    break;

                    case 2:
                    {
                        FMC_UNREACHABLE_ASSERT(ch >> 5 == 6);
                        FMC_STMT_ASSUME(ch >> 5 == 6);
                        bytes[1] = (FMC_Byte)ch & 0xFF;
                        if ((ch = fgetc(file->file)) == EOF)
                        {
                            if (FMC_getDebugState())
                            {
                                FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned EOF while reading a 2-byte character");
                                FMC_printRedError(stderr, err_int);
                            }
                            FMC_setError(FMC_ERR_ENC, "fgetc returned EOF while reading a 2-byte character");
                            FMC_freeStr(str);
                            return NULL;
                            FMC_UNREACHABLE;
                        }
                        if (ch < 0 || ch > 255)
                        {
                            if (FMC_getDebugState())
                            {
                                FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                                FMC_printRedError(stderr, err_int);
                            }
                            FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                            FMC_freeStr(str);
                            return NULL;
                            FMC_UNREACHABLE;
                        }
                        FMC_UNREACHABLE_ASSERT(ch >> 6 == 2);
                        bytes[0] = (FMC_Byte)ch & 0xFF;
                        /* FMC_Char* new_char = FMC_allocChar(bytes, utf8, FMC_FALSE, 2); */
                        memset(new_char, 0, sizeof(FMC_Char));
                        new_char->encoding = file->encoding;
                        new_char->comp.byte0 = bytes[0];
                        new_char->comp.byte1 = bytes[1];
                        new_char->comp.byte2 = 0x00;
                        new_char->comp.byte3 = 0x00;
                        new_char->isNull = FMC_FALSE;
                        new_char->byteNumber = 2;
                        if (!FMC_append(str, new_char))
                        {
                            if (FMC_getDebugState())
                            {
                                FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_append failed");
                                FMC_printRedError(stderr, err_int);
                            }
                            FMC_setError(FMC_ERR_INTERNAL, "FMC_append failed");
                            FMC_freeStr(str);
                            return NULL;
                            FMC_UNREACHABLE;
                        }
                    }
                    break;

                    case 3:
                    {
                        FMC_UNREACHABLE_ASSERT(ch >> 4 == 14);
                        FMC_STMT_ASSUME(ch >> 4 == 14);
                        bytes[2] = (FMC_Byte)ch & 0xFF;
                        for (uint8_t i = 1; i < 3; i++)
                        {
                            if ((ch = fgetc(file->file)) == EOF)
                            {
                                if (FMC_getDebugState())
                                {
                                    FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned EOF while reading a 3-byte character");
                                    FMC_printRedError(stderr, err_int);
                                }
                                FMC_setError(FMC_ERR_ENC, "fgetc returned EOF while reading a 3-byte character");
                                FMC_freeStr(str);
                                return NULL;
                                FMC_UNREACHABLE;
                            }
                            if (ch < 0 || ch > 255)
                            {
                                if (FMC_getDebugState())
                                {
                                    FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                                    FMC_printRedError(stderr, err_int);
                                }
                                FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                                FMC_freeStr(str);
                                return NULL;
                                FMC_UNREACHABLE;
                            }
                            FMC_UNREACHABLE_ASSERT(ch >> 6 == 2);
                            bytes[2 - i] = (FMC_Byte)ch & 0xFF;
                        }
                        /* FMC_Char* new_char = FMC_allocChar(bytes, utf8, FMC_FALSE, 3); */
                        memset(new_char, 0, sizeof(FMC_Char));
                        new_char->encoding = file->encoding;
                        new_char->comp.byte0 = bytes[0];
                        new_char->comp.byte1 = bytes[1];
                        new_char->comp.byte2 = bytes[2];
                        new_char->comp.byte3 = 0x00;
                        new_char->isNull = FMC_FALSE;
                        new_char->byteNumber = 3;
                        if (!FMC_append(str, new_char))
                        {
                            if (FMC_getDebugState())
                            {
                                FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_append failed");
                                FMC_printRedError(stderr, err_int);
                            }
                            FMC_setError(FMC_ERR_INTERNAL, "FMC_append failed");
                            return NULL;
                            FMC_freeStr(str);
                            FMC_UNREACHABLE;
                        }
                    }
                    break;

                    case 4:
                    {
                        FMC_UNREACHABLE_ASSERT(ch >> 3 == 30);
                        FMC_STMT_ASSUME(ch >> 3 == 30);
                        bytes[3] = (FMC_Byte)ch & 0xFF;
                        for (uint8_t i = 1; i < 4; i++)
                        {
                            if ((ch = fgetc(file->file)) == EOF)
                            {
                                if (FMC_getDebugState())
                                {
                                    FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned EOF while reading a 4-byte character");
                                    FMC_printRedError(stderr, err_int);
                                }
                                FMC_setError(FMC_ERR_ENC, "fgetc returned EOF while reading a 4-byte character");
                                FMC_freeStr(str);
                                return NULL;
                                FMC_UNREACHABLE;
                            }
                            if (ch < 0 || ch > 255)
                            {
                                if (FMC_getDebugState())
                                {
                                    FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                                    FMC_printRedError(stderr, err_int);
                                }
                                FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                                FMC_freeStr(str);
                                return NULL;
                                FMC_UNREACHABLE;
                            }
                            FMC_UNREACHABLE_ASSERT(ch >> 6 == 2);
                            bytes[3 - i] = (FMC_Byte)ch & 0xFF;
                        }
                        /* FMC_Char* new_char = FMC_allocChar(bytes, utf8, FMC_FALSE, 4); */
                        memset(new_char, 0, sizeof(FMC_Char));
                        new_char->encoding = file->encoding;
                        new_char->comp.byte0 = bytes[0];
                        new_char->comp.byte1 = bytes[1];
                        new_char->comp.byte2 = bytes[2];
                        new_char->comp.byte3 = bytes[3];
                        new_char->isNull = FMC_FALSE;
                        new_char->byteNumber = 4;
                        if (!FMC_append(str, new_char))
                        {
                            if (FMC_getDebugState())
                            {
                                FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_append failed");
                                FMC_printRedError(stderr, err_int);
                            }
                            FMC_setError(FMC_ERR_INTERNAL, "FMC_append failed");
                            return NULL;
                            FMC_freeStr(str);
                            FMC_UNREACHABLE;
                        }
                    }
                    break;

                    default:
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": An invalid UTF-8 character was encountered");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_ENC, "An invalid UTF-8 character was encountered");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                }

                  
            }
        }
        break;

        case utf16_le:
        {
            // Skip the BOM
            if (fseek(file->file, 2, SEEK_SET) != 0)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fseek failed");
                    FMC_printRedError(stderr, err_int);
                }
                FMC_setError(FMC_ERR_INTERNAL, "fseek failed");
                return NULL;
                FMC_UNREACHABLE;
            }

            while ((ch = fgetc(file->file)) != EOF)
            {
                if (ch < 0 || ch > 255)
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                        FMC_printRedError(stderr, err_int);
                    }
                    FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                    FMC_freeStr(str);
                    return NULL;
                    FMC_UNREACHABLE;
                }
                // Get a second byte and see if it's a surrogate
                int ch2 = fgetc(file->file);
                if (ch2 == EOF)
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned EOF while reading a 2-byte character");
                        FMC_printRedError(stderr, err_int);
                    }
                    FMC_setError(FMC_ERR_ENC, "fgetc returned EOF while reading a 2-byte character");
                    FMC_freeStr(str);
                    return NULL;
                    FMC_UNREACHABLE;
                }
                if (ch2 < 0 || ch2 > 255)
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                        FMC_printRedError(stderr, err_int);
                    }
                    FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                    FMC_freeStr(str);
                    return NULL;
                    FMC_UNREACHABLE;
                }

                FMC_UNREACHABLE_ASSERT(ch >= 0 && ch <= 255 && ch2 >= 0 && ch2 <= 255);
                FMC_STMT_ASSUME(ch >= 0 && ch <= 255 && ch2 >= 0 && ch2 <= 255);

                FMC_Byte bytes[4] = {0};
                // These are the first two bytes of the character ("at the right" when we read them)
                uint16_t first_two_read_bytes = (uint16_t)((ch << 8) | ch2); // Little endian but with words of 16 bits, so no need to swap
                FMC_Bool is_surrogate = (first_two_read_bytes >= 0xD800 && first_two_read_bytes <= 0xDFFF);
                if (!is_surrogate)
                {
                    // It's a normal character
                    bytes[1] = (FMC_Byte)ch;
                    bytes[0] = (FMC_Byte)ch2;
                    /* FMC_Char* new_char = FMC_allocChar(bytes, utf16_le,
                                                       first_two_read_bytes == 0 ? FMC_TRUE : FMC_FALSE,
                                                       2); */
                    memset(new_char, 0, sizeof(FMC_Char));
                    new_char->comp.byte0 = bytes[0];
                    new_char->comp.byte1 = bytes[1];
                    new_char->comp.byte2 = 0x00;
                    new_char->comp.byte3 = 0x00;
                    new_char->encoding = utf16_le;
                    new_char->isNull = first_two_read_bytes == 0 ? FMC_TRUE : FMC_FALSE;
                    new_char->byteNumber = 2;
                    if (!FMC_append(str, new_char))
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_append failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "FMC_append failed");
                        return NULL;
                        FMC_freeStr(str);
                        FMC_UNREACHABLE;
                    }
                }
                else
                {
                    // It's a surrogate
                    // Get the next two bytes
                    int ch3 = fgetc(file->file);
                    if (ch3 == EOF)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned EOF while reading a 4-byte character");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_ENC, "fgetc returned EOF while reading a 4-byte character");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }
                    if (ch3 < 0 || ch3 > 255)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }
                    int ch4 = fgetc(file->file);
                    if (ch4 == EOF)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned EOF while reading a 4-byte character");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_ENC, "fgetc returned EOF while reading a 4-byte character");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }
                    if (ch4 < 0 || ch4 > 255)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }

                    FMC_UNREACHABLE_ASSERT(ch3 >= 0 && ch3 <= 255 && ch4 >= 0 && ch4 <= 255);
                    FMC_STMT_ASSUME(ch3 >= 0 && ch3 <= 255 && ch4 >= 0 && ch4 <= 255);

                    // These are the last two bytes of the character ("at the left" when we read them)
                    uint16_t last_two_read_bytes = (uint16_t)((ch3 << 8) | ch4); // Little endian but with words of 16 bits, so no need to swap
                    FMC_Bool is_valid_surrogate = (last_two_read_bytes >= 0xDC00 && last_two_read_bytes <= 0xDFFF);
                    if (!is_valid_surrogate)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_ENC, "fgetc returned a value out of range");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }

                    // We have a valid surrogate pair
                    bytes[3] = (FMC_Byte)ch;
                    bytes[2] = (FMC_Byte)ch2;
                    bytes[1] = (FMC_Byte)ch3;
                    bytes[0] = (FMC_Byte)ch4;
                    /* FMC_Char* new_char = FMC_allocChar(bytes, utf16_le, FMC_FALSE, 4); */
                    memset(new_char, 0, sizeof(FMC_Char));
                    new_char->comp.byte0 = bytes[0];
                    new_char->comp.byte1 = bytes[1];
                    new_char->comp.byte2 = bytes[2];
                    new_char->comp.byte3 = bytes[3];
                    new_char->encoding = utf16_le;
                    new_char->isNull = FMC_FALSE;
                    new_char->byteNumber = 4;
                    if (!FMC_append(str, new_char))
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_append failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "FMC_append failed");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }
                }
            }
        }
        break;

        case utf16_be:
        {
            while ((ch = fgetc(file->file)) != EOF)
            {
                if (ch < 0 || ch > 255)
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                        FMC_printRedError(stderr, err_int);
                    }
                    FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                    FMC_freeStr(str);
                    return NULL;
                    FMC_UNREACHABLE;
                }
                int ch2 = fgetc(file->file);
                if (ch2 == EOF)
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned EOF while reading the 2nd byte of a UTF-16 character");
                        FMC_printRedError(stderr, err_int);
                    }
                    FMC_setError(FMC_ERR_ENC, "fgetc returned EOF while reading the 2nd byte of a UTF-16 character");
                    FMC_freeStr(str);
                    return NULL;
                    FMC_UNREACHABLE;
                }
                if (ch2 < 0 || ch2 > 255)
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                        FMC_printRedError(stderr, err_int);
                    }
                    FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                    FMC_freeStr(str);
                    return NULL;
                    FMC_UNREACHABLE;
                }

                FMC_UNREACHABLE_ASSERT(ch >= 0 && ch <= 255 && ch2 >= 0 && ch2 <= 255);
                FMC_STMT_ASSUME(ch >= 0 && ch <= 255 && ch2 >= 0 && ch2 <= 255);

                uint16_t first_two_read_bytes = (uint16_t)((ch << 8) | ch2); 
                FMC_Bool is_surrogate = (first_two_read_bytes >= 0xD800 && first_two_read_bytes <= 0xDBFF);
                if (!is_surrogate)
                {
                    // We have a valid character
                    FMC_Byte bytes[2];
                    bytes[1] = (FMC_Byte)ch;
                    bytes[0] = (FMC_Byte)ch2;
                    /* FMC_Char* new_char = FMC_allocChar(bytes, utf16_be,
                                                       first_two_read_bytes == 0 ? FMC_TRUE : FMC_FALSE,
                                                       2); */
                    memset(new_char, 0, sizeof(FMC_Char));
                    new_char->comp.byte0 = bytes[0];
                    new_char->comp.byte1 = bytes[1];
                    new_char->comp.byte2 = 0x00;
                    new_char->comp.byte3 = 0x00;
                    new_char->encoding = utf16_be;
                    new_char->isNull = first_two_read_bytes == 0 ? FMC_TRUE : FMC_FALSE;
                    new_char->byteNumber = 2;
                    if (!FMC_append(str, new_char))
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_append failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "FMC_append failed");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }
                }
                else
                {
                    // We have a surrogate pair
                    int ch3 = fgetc(file->file);
                    if (ch3 == EOF)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned EOF while reading the 3rd byte of a UTF-16 character");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_ENC, "fgetc returned EOF while reading the 3rd byte of a UTF-16 character");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }
                    if (ch3 < 0 || ch3 > 255)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }
                    int ch4 = fgetc(file->file);
                    if (ch4 == EOF)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned EOF while reading the 4th byte of a UTF-16 character");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_ENC, "fgetc returned EOF while reading the 4th byte of a UTF-16 character");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }
                    if (ch4 < 0 || ch4 > 255)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }

                    FMC_UNREACHABLE_ASSERT(ch3 >= 0 && ch3 <= 255 && ch4 >= 0 && ch4 <= 255);
                    FMC_STMT_ASSUME(ch3 >= 0 && ch3 <= 255 && ch4 >= 0 && ch4 <= 255);

                    uint16_t second_two_read_bytes = (uint16_t)((ch3 << 8) | ch4);
                    FMC_Bool is_valid_surrogate = (second_two_read_bytes >= 0xDC00 && second_two_read_bytes <= 0xDFFF);
                    if (!is_valid_surrogate)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": Invalid surrogate pair");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_ENC, "Invalid surrogate pair");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }

                    FMC_Byte bytes[4];
                    uint32_t complete_char = (uint32_t)(((uint32_t) ch << 24) | ((uint32_t) ch2 << 16) | ((uint32_t) ch3 << 8) | (uint32_t) ch4);
                    // foreach(b, bytes, 0, LOOP_TO_THE_END)
                    // {
                    //     FMC_MAKE_VOID(b);
                    //     bytes[foreach_counter(3)] = (FMC_Byte)((complete_char >> (8 * foreach_counter(3))) & 0xFF);
                    // } 
                    // my editor crashed when expanding all foreach loops

                    for (size_t i = 0; i < 4; i++)
                    {
                        bytes[i] = (FMC_Byte)((complete_char >> (8 * i)) & 0xFF);
                    }
                    

                    /* FMC_Char *new_char = FMC_allocChar(bytes, utf16_be, FMC_FALSE, 4); */
                    memset(new_char, 0, sizeof(FMC_Char));
                    new_char->byteNumber = 4;
                    new_char->isNull = FMC_FALSE;
                    new_char->encoding = utf16_be;
                    new_char->comp.byte0 = bytes[0];
                    new_char->comp.byte1 = bytes[1];
                    new_char->comp.byte2 = bytes[2];
                    new_char->comp.byte3 = bytes[3];
                    if (!FMC_append(str, new_char))
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_append failed");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "FMC_append failed");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }
                }
            }
        }
        break;

        case utf32_le:
        {
            while ((ch = fgetc(file->file)) != EOF)
            {
                if (ch < 0 || ch > 255)
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                        FMC_printRedError(stderr, err_int);
                    }
                    FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                    FMC_freeStr(str);
                    return NULL;
                    FMC_UNREACHABLE;
                }

                int next_chs[3] = {0};

                for (uint_fast8_t i = 0; i < 3; i++)
                {
                    if ((next_chs[2 - i] = fgetc(file->file)) == EOF)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned EOF while reading the next byte of a UTF-32 character");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_ENC, "fgetc returned EOF while reading the next byte of a UTF-32 character");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }
                    if (next_chs[2 - i] < 0 || next_chs[2 - i] > 255)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }

                    FMC_UNREACHABLE_ASSERT(next_chs[2 - i] >= 0 && next_chs[2 - i] <= 255);
                    FMC_STMT_ASSUME(next_chs[2 - i] >= 0 && next_chs[2 - i] <= 255);
                }

                FMC_Byte bytes[4] = {0};
                bytes[3] = (FMC_Byte)ch;

                // foreach(b, next_chs, 0, LOOP_TO_THE_END)
                // {
                //     FMC_MAKE_VOID(b);
                //     bytes[foreach_counter(3)] = (FMC_Byte)next_chs[foreach_counter(3)];
                // }

                for (size_t i = 0; i < 3; i++)
                {
                    bytes[i] = (FMC_Byte)next_chs[i];
                }

                uint32_t complete_char = (uint32_t)(((uint32_t) bytes[3] << 24) | ((uint32_t) bytes[2] << 16) | ((uint32_t) bytes[1] << 8) | (uint32_t) bytes[0]);
                /* FMC_Char *new_char = FMC_allocChar(bytes, utf32_le,
                                                   !complete_char ? FMC_TRUE : FMC_FALSE,
                                                   4); */
                memset(new_char, 0, sizeof(FMC_Char));
                new_char->byteNumber = 4;
                new_char->isNull = !complete_char ? FMC_TRUE : FMC_FALSE;
                new_char->encoding = utf32_le;
                new_char->comp.byte0 = bytes[0];
                new_char->comp.byte1 = bytes[1];
                new_char->comp.byte2 = bytes[2];
                new_char->comp.byte3 = bytes[3];
                if (!FMC_append(str, new_char))
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_append failed");
                        FMC_printRedError(stderr, err_int);
                    }
                    FMC_setError(FMC_ERR_INTERNAL, "FMC_append failed");
                    FMC_freeStr(str);
                    return NULL;
                    FMC_UNREACHABLE;
                }
            }
        }
        break;

        case utf32_be:
        {
            while ((ch = fgetc(file->file)) != EOF)
            {
                if (ch < 0 || ch > 255)
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                        FMC_printRedError(stderr, err_int);
                    }
                    FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                    FMC_freeStr(str);
                    return NULL;
                    FMC_UNREACHABLE;
                }

                int next_chs[3] = {0};

                for (uint_fast8_t i = 0; i < 3; i++)
                {
                    if ((next_chs[2 - i] = fgetc(file->file)) == EOF)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned EOF while reading the next byte of a UTF-32 character");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_ENC, "fgetc returned EOF while reading the next byte of a UTF-32 character");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }
                    if (next_chs[2 - i] < 0 || next_chs[2 - i] > 255)
                    {
                        if (FMC_getDebugState())
                        {
                            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                            FMC_printRedError(stderr, err_int);
                        }
                        FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                        FMC_freeStr(str);
                        return NULL;
                        FMC_UNREACHABLE;
                    }

                    FMC_UNREACHABLE_ASSERT(next_chs[2 - i] >= 0 && next_chs[2 - i] <= 255);
                    FMC_STMT_ASSUME(next_chs[2 - i] >= 0 && next_chs[2 - i] <= 255);
                }

                FMC_Byte bytes[4] = {0};
                bytes[3] = (FMC_Byte)ch;

                // foreach(b, next_chs, 0, LOOP_TO_THE_END)
                // {
                //     FMC_MAKE_VOID(b);
                //     bytes[foreach_counter(3)] = (FMC_Byte)next_chs[foreach_counter(3)];
                // }

                for (size_t i = 0; i < 3; i++)
                {
                    bytes[i] = (FMC_Byte)next_chs[i];
                }

                uint32_t complete_char = (uint32_t)(((uint32_t) bytes[3] << 24) | ((uint32_t) bytes[2] << 16) | ((uint32_t) bytes[1] << 8) | (uint32_t) bytes[0]);
                /* FMC_Char *new_char = FMC_allocChar(bytes, utf32_be,
                                                   !complete_char ? FMC_TRUE : FMC_FALSE,
                                                   4); */
                memset(new_char, 0, sizeof(FMC_Char));
                new_char->byteNumber = 4;
                new_char->isNull = !complete_char ? FMC_TRUE : FMC_FALSE;
                new_char->encoding = utf32_be;
                new_char->comp.byte0 = bytes[0];
                new_char->comp.byte1 = bytes[1];
                new_char->comp.byte2 = bytes[2];
                new_char->comp.byte3 = bytes[3];
                if (!FMC_append(str, new_char))
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_append failed");
                        FMC_printRedError(stderr, err_int);
                    }
                    FMC_setError(FMC_ERR_INTERNAL, "FMC_append failed");
                    FMC_freeStr(str);
                    return NULL;
                    FMC_UNREACHABLE;
                }
            }
        }
        break;

        case ascii:
        {
            while ((ch = fgetc(file->file)) != EOF)
            {
                if (ch < 0 || ch > 255)
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned a value out of range");
                        FMC_printRedError(stderr, err_int);
                    }
                    FMC_setError(FMC_ERR_INTERNAL, "fgetc returned a value out of range");
                    FMC_freeStr(str);
                    return NULL;
                    FMC_UNREACHABLE;
                }

                FMC_Byte bytes[1] = {0};
                bytes[0] = (FMC_Byte)ch;

                uint32_t complete_char = (uint32_t)bytes[0];
                /* FMC_Char *new_char = FMC_allocChar(bytes, ascii,
                                                   !complete_char ? FMC_TRUE : FMC_FALSE,
                                                   1); */
                memset(new_char, 0, sizeof(FMC_Char));
                new_char->byteNumber = 1;
                new_char->isNull = !complete_char ? FMC_TRUE : FMC_FALSE;
                new_char->encoding = ascii;
                new_char->comp.byte0 = bytes[0];
                new_char->comp.byte1 = 0x00;
                new_char->comp.byte2 = 0x00;
                new_char->comp.byte3 = 0x00;
                if (!FMC_append(str, new_char))
                {
                    if (FMC_getDebugState())
                    {
                        FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_append failed");
                        FMC_printRedError(stderr, err_int);
                    }
                    FMC_setError(FMC_ERR_INTERNAL, "FMC_append failed");
                    FMC_freeStr(str);
                    return NULL;
                    FMC_UNREACHABLE;
                }
            }
        }
        break;

        default:
            if (FMC_getDebugState())
            {
                FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": An invalid encoding was encountered");
                FMC_printRedError(stderr, err_int);
            }
            FMC_setError(FMC_ERR_ENC, "An invalid encoding was encountered");
            return NULL;
            FMC_UNREACHABLE;
    }

    rewind(file->file);
    if (ferror(file->file) || feof(file->file))
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fgetc returned an error");
            FMC_printRedError(stderr, err_int);
        }
        FMC_setError(FMC_ERR_IO, "fgetc returned an error");
        FMC_freeStr(str);
        return NULL;
        FMC_UNREACHABLE;
    }

    return str;
    FMC_UNREACHABLE;
}