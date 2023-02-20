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

#pragma once

#ifndef FMC_FILE_MANAGEMENT_H
#define FMC_FILE_MANAGEMENT_H

#include "../general/FMC_general.h"

/**
 * @author Axel PASCON
 * @date 2023
 * @fn char *FMC_extractFilename(const char * restrict const path, char * restrict filename, const size_t filename_size)
 * @brief Gets the filename from a complete path.
 * @details Basically, this function only detects the last '/' or '\' character. For example, if the path is "C:\\Users\\someone\\Documents\\MyFile.txt", the function will return "MyFile.txt". If the path is "/home/someone/Desktop", then Desktop will be considered as the filename. This function is designed to only operate on strings, and do not check if the path is valid, is a file or a directory, etc.
 * @param[in] path The path to extract the filename from.
 * @param[out] filename The buffer where the filename will be stored.
 * @param[in] filename_size The size of the filename buffer.
 * @return A pointer to the filename buffer.
 * @retval NULL If the path is NULL, if the filename buffer is NULL or if an error occured. The error can be viewed by setting @link FMC_ENABLE_DEBUG FMC_ENABLE_DEBUG @endlink to @link True True @endlink.
 * @warning The filename buffer must be at least as big as the path.
 * @note The maximum filename size is @link MAX_FNAME_SIZE MAX_FNAME_SIZE @endlink. You can disable some warnings or error messages by defining @link FMC_ENABLE_DEBUG FMC_ENABLE_DEBUG @endlink to @link False False @endlink.
 */
FMC_SHARED FMC_FUNC_HOT FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1, 2) char *FMC_extractFilename(const char * restrict const path, char * restrict filename, const size_t filename_size);
FMC_SHARED FMC_FUNC_HOT FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1, 2) char *FMC_cutFilename(const char * restrict const path, char * restrict dirs, const size_t dirs_size);
FMC_SHARED FMC_FUNC_HOT FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1, 2) char *FMC_getExtension(const char * restrict const path, char * restrict ext, const size_t ext_size);

#endif // FMC_FILE_MANAGEMENT_H
