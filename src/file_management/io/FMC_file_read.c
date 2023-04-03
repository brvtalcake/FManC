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

#include "FMC_io.h"
#include "../../cpp/FMC_wrapper.h"

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_MALLOC(mi_free) FMC_String* FMC_slurpFile(FMC_File* const file)
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
    if (!file->isOpened || !file->fullMode || !*file->fullMode || !file->file || file->dataMode != binary)
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
    if (file->path) strcat(full_path, file->path);
    if (file->name) strcat(full_path, file->name);
    if (file->extension) strcat(full_path, file->extension);
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

    char buffer[file->fileSize + 1];
    memset(buffer, 0, file->fileSize + 1);
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
    switch (file->encoding)
    {
        case utf8_bom: // skip the BOM and then fallthru on utf8
        {
            if (fseek(file->file, 3, SEEK_SET) != 0)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fseek failed");
                    FMC_printRedError(stderr, err_int);
                }
                FMC_setError(FMC_ERR_INTERNAL, "Argument: file is not a regular file or a symbolic link");
                return NULL;
                FMC_UNREACHABLE;
            }
        }
        case utf8:
        {
            if (fread(buffer, sizeof(char), file->fileSize, file->file) != file->fileSize)
            {
                if (FMC_getDebugState())
                {
                    FMC_makeMsg(err_int, 3, "INTERNAL ERROR: In function: ", __func__, ": fread failed");
                    FMC_printRedError(stderr, err_int);
                }
                FMC_setError(FMC_ERR_INVALID_ARGUMENT, "Argument: file is not a regular file or a symbolic link");
                return NULL;
                FMC_UNREACHABLE;
            }
            break;
        }
    }
}