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

#ifndef CPP_FMC_FILESYSTEM_H
#define CPP_FMC_FILESYSTEM_H

#include <cstddef>

// int FMC_dirExists_(const char *path);
// int FMC_isDir_(const char *path);
// int FMC_isRegFile_(const char *path);
int FMC_isSymLink_(const char *path);
int FMC_isBlock_(const char* path);
// int FMC_isCharFile_(const char* path);
// int FMC_isSocket_(const char* path);
int FMC_isFIFO_(const char* path);
int FMC_isOther_(const char* path);
//char *FMC_readSymlink_(char *path_sym, const char * path);
int FMC_isEmpty_(const char *path);
//int FMC_createDir_(const char *path);
char *FMC_getCurrentPath_(char *path, const size_t size);
char *FMC_getAbsolutePath_(char *path, char *buffer, const size_t size);

#endif // CPP_FMC_FILESYSTEM_H
