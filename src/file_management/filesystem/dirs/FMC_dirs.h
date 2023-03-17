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

#ifndef FMC_DIRS_H
#define FMC_DIRS_H

#include "../../../general/FMC_general.h"

#if defined(FMC_COMPILING_ON_WINDOWS)
    #include <windows.h>
#else
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <pwd.h>
    #include <unistd.h>
#endif

FMC_BEGIN_DECLS

FMC_SHARED int_fast64_t FMC_getDirEntryCount(const char* restrict const path);
FMC_SHARED int FMC_mkDir(const char* restrict path);
FMC_SHARED int FMC_rmDir(const char* restrict path, unsigned int user_flags);

FMC_END_DECLS

#endif // FMC_DIRS_H
