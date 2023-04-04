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

#include <mimalloc.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>

#include "FMC_io.h"
#include "../../cpp/FMC_wrapper.h"

// TODO: finish
FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_WARN_UNUSED_RESULT FMC_String* FMC_slurpFile(FMC_File* const file)
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
    char full_path[MAX_FEXT_SIZE + MAX_FNAME_SIZE + MAX_FPATH_SIZE];
    memset(full_path, 0, MAX_FEXT_SIZE + MAX_FNAME_SIZE + MAX_FPATH_SIZE);
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
    if (strcat(full_path, file->extension) != full_path)
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
    if (!FMC_isRegFile(full_path) || !FMC_isSymLink(full_path))
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
    FMC_Bool enc_has_bom = (file->encoding == utf8_bom || file->encoding == utf16_le || file->encoding == utf16_be || file->encoding == utf32_le || file->encoding == utf32_be);
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
                        FMC_Char* new_char = FMC_allocChar(bytes, utf8,
                                                           ch == 0 ? FMC_TRUE : FMC_FALSE,
                                                           1);
                        if (!new_char)
                        {
                            if (FMC_getDebugState())
                            {
                                FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_allocChar failed");
                                FMC_printRedError(stderr, err_int);
                            }
                            FMC_setError(FMC_ERR_INTERNAL, "FMC_allocChar failed");
                            FMC_freeStr(str);
                            return NULL;
                            FMC_UNREACHABLE;
                        }
                        if (!(str = FMC_append(str, new_char)))
                        {
                            if (FMC_getDebugState())
                            {
                                FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_append failed");
                                FMC_printRedError(stderr, err_int);
                            }
                            FMC_setError(FMC_ERR_INTERNAL, "FMC_append failed");
                            return NULL;
                            FMC_UNREACHABLE;
                        }
                    }
                    break;

                    case 2:
                    {
                        FMC_UNREACHABLE_ASSERT(ch >> 5 == 6);
                        FMC_STMT_ASSUME(ch >> 5 == 6);
                        bytes[0] = (FMC_Byte)ch & 0xFF;
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
                        bytes[1] = (FMC_Byte)ch & 0xFF;
                        FMC_Char* new_char = FMC_allocChar(bytes, utf8, FMC_FALSE, 2);
                        if (!new_char)
                        {
                            if (FMC_getDebugState())
                            {
                                FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_allocChar failed");
                                FMC_printRedError(stderr, err_int);
                            }
                            FMC_setError(FMC_ERR_INTERNAL, "FMC_allocChar failed");
                            FMC_freeStr(str);
                            return NULL;
                            FMC_UNREACHABLE;
                        }
                        if (!(str = FMC_append(str, new_char)))
                        {
                            if (FMC_getDebugState())
                            {
                                FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_append failed");
                                FMC_printRedError(stderr, err_int);
                            }
                            FMC_setError(FMC_ERR_INTERNAL, "FMC_append failed");
                            return NULL;
                            FMC_UNREACHABLE;
                        }
                    }
                    break;

                    case 3:
                    {
                        FMC_UNREACHABLE_ASSERT(ch >> 4 == 14);
                        FMC_STMT_ASSUME(ch >> 4 == 14);
                        bytes[0] = (FMC_Byte)ch & 0xFF;
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
                            bytes[i] = (FMC_Byte)ch & 0xFF;
                        }
                        FMC_Char* new_char = FMC_allocChar(bytes, utf8, FMC_FALSE, 3);
                        if (!new_char)
                        {
                            if (FMC_getDebugState())
                            {
                                FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_allocChar failed");
                                FMC_printRedError(stderr, err_int);
                            }
                            FMC_setError(FMC_ERR_INTERNAL, "FMC_allocChar failed");
                            FMC_freeStr(str);
                            return NULL;
                            FMC_UNREACHABLE;
                        }
                        if (!(str = FMC_append(str, new_char)))
                        {
                            if (FMC_getDebugState())
                            {
                                FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_append failed");
                                FMC_printRedError(stderr, err_int);
                            }
                            FMC_setError(FMC_ERR_INTERNAL, "FMC_append failed");
                            return NULL;
                            FMC_UNREACHABLE;
                        }
                    }
                    break;

                    case 4:
                    {
                        FMC_UNREACHABLE_ASSERT(ch >> 3 == 30);
                        FMC_STMT_ASSUME(ch >> 3 == 30);
                        bytes[0] = (FMC_Byte)ch & 0xFF;
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
                            bytes[i] = (FMC_Byte)ch & 0xFF;
                        }
                        FMC_Char* new_char = FMC_allocChar(bytes, utf8, FMC_FALSE, 4);
                        if (!new_char)
                        {
                            if (FMC_getDebugState())
                            {
                                FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_allocChar failed");
                                FMC_printRedError(stderr, err_int);
                            }
                            FMC_setError(FMC_ERR_INTERNAL, "FMC_allocChar failed");
                            FMC_freeStr(str);
                            return NULL;
                            FMC_UNREACHABLE;
                        }
                        if (!(str = FMC_append(str, new_char)))
                        {
                            if (FMC_getDebugState())
                            {
                                FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": FMC_append failed");
                                FMC_printRedError(stderr, err_int);
                            }
                            FMC_setError(FMC_ERR_INTERNAL, "FMC_append failed");
                            return NULL;
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
                        return NULL;
                        FMC_UNREACHABLE;
                }
                
            }
        }
        break;

        case utf16_le:
        {
            FMC_Byte bytes[4];
            while ((ch = fgetc(file->file)) != EOF)
            {

            }
        }
        break;

        case utf16_be:
        {
            FMC_Byte bytes[4];
            while ((ch = fgetc(file->file)) != EOF)
            {

            }
        }
        break;

        case utf32_le:
        {
            FMC_Byte bytes[4];
            while ((ch = fgetc(file->file)) != EOF)
            {

            }
        }
        break;

        case utf32_be:
        {
            FMC_Byte bytes[4];
            while ((ch = fgetc(file->file)) != EOF)
            {

            }
        }
        break;

        case ascii:
        {
            FMC_Byte bytes[4];
            while ((ch = fgetc(file->file)) != EOF)
            {

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
    return str;
    FMC_UNREACHABLE;
}