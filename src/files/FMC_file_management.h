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

FMC_BEGIN_DECLS

FMC_SHARED FMC_FUNC_HOT FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1, 2) char *FMC_extractFilename(const char * restrict const path, char * restrict filename, const size_t filename_size);
FMC_SHARED FMC_FUNC_HOT FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1, 2) char *FMC_cutFilename(const char * restrict const path, char * restrict dir, const size_t dir_size);
FMC_SHARED FMC_FUNC_HOT FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1, 2) char *FMC_getExtension(const char * restrict const path, char * restrict ext, const size_t ext_size);

#if defined(FMC_COMPILING_ON_WINDOWS)
FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT LONGLONG FMC_getFileSize(const char* restrict path);
#else
FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT off64_t FMC_getFileSize(const char* restrict path);
#endif
FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT int FMC_dirExists(const char* restrict path);
FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT int FMC_isRegFile(const char* restrict path);
FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT int FMC_isDir(const char* restrict path);
FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT int FMC_isCharDevice(const char* restrict path);
FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT int FMC_isSocket(const char* restrict path);

FMC_END_DECLS

#endif // FMC_FILE_MANAGEMENT_H
