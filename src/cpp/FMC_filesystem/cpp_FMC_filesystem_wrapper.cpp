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

#include "../FMC_wrapper.h"
#include "cpp_FMC_filesystem.hpp"
#include <stddef.h>

#ifdef __cplusplus
extern "C" {
#endif

/* FMC_SHARED int FMC_dirExists(const char *path)
{
    return FMC_dirExists_(path);
}

FMC_SHARED int FMC_isDir(const char *path)
{
    return FMC_isDir_(path);
}

FMC_SHARED int FMC_isRegFile(const char *path)
{
    return FMC_isRegFile_(path);
} */

FMC_SHARED int FMC_isSymLink(const char *path)
{
    return FMC_isSymLink_(path);
}

FMC_SHARED int FMC_isBlock(const char* path)
{
    return FMC_isBlock_(path);
}

/* FMC_SHARED int FMC_isCharFile(const char* path)
{
    return FMC_isCharFile_(path);
}

FMC_SHARED int FMC_isSocket(const char* path)
{
    return FMC_isSocket_(path);
} */

FMC_SHARED int FMC_isFIFO(const char* path)
{
    return FMC_isFIFO_(path);
}

FMC_SHARED int FMC_isOther(const char* path)
{
    return FMC_isOther_(path);
}

FMC_SHARED int FMC_isEmpty(const char *path)
{
    return FMC_isEmpty_(path);
}

//FMC_SHARED int FMC_createDir_(const char *path);

FMC_SHARED char *FMC_getCurrentPath(char *path, const size_t size)
{
    return FMC_getCurrentPath_(path, size);
}

FMC_SHARED char *FMC_getAbsolutePath(char *path, char *buffer, const size_t size)
{
    return FMC_getAbsolutePath_(path, buffer, size);
}

#ifdef __cplusplus
}
#endif