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

#ifndef FMC_FILES_H
#define FMC_FILES_H

#include "../../general/FMC_general.h"

FMC_BEGIN_DECLS

FMC_SHARED FMC_FUNC_HOT FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1, 2) char *FMC_extractFilename(const char * restrict const path, char * restrict filename, const size_t filename_size);
FMC_SHARED FMC_FUNC_HOT FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1, 2) char *FMC_cutFilename(const char * restrict const path, char * restrict dir, const size_t dir_size);
FMC_SHARED FMC_FUNC_HOT FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_NONNULL(1, 2) char *FMC_getExtension(const char * restrict const path, char * restrict ext, const size_t ext_size);

FMC_SHARED FMC_FUNC_NONNULL(1) void FMC_freeFile(FMC_File* restrict file);
FMC_SHARED FMC_FUNC_MALLOC(FMC_freeFile, 1) FMC_File *FMC_allocFile(const char* restrict const path, const char* restrict const full_mode, const unsigned int user_flags);
FMC_SHARED FMC_FUNC_NONNULL(1, 2) unsigned int FMC_changeStreamOrientation(FILE* restrict file, const char* restrict const mode, const unsigned int orientation_flag);
FMC_SHARED unsigned long long FMC_getOptimalWriteBufferSize(const char* restrict const path);

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_WARN_UNUSED_RESULT FMC_File* FMC_openFile_withoutFlags(FMC_File* file, const char* mode);
FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_WARN_UNUSED_RESULT FMC_File* FMC_openFile_withFlags(FMC_File* file, const char* const mode, const unsigned int user_flags);
#define FMC_openFile(file, mode, ...) FMC_CHOOSE_FUNC(2)(FMC_openFile_withoutFlags, FMC_openFile_withFlags, file, mode, __VA_ARGS__)
FMC_SHARED void FMC_closeFile(FMC_File* restrict file);
FMC_SHARED FMC_FUNC_NONNULL(1, 2, 3) FMC_File* FMC_reopenFile(FMC_File* restrict file, const char* restrict const new_path, const char* restrict const full_mode, const unsigned int user_flags);

FMC_END_DECLS

#endif // FMC_FILES_H
