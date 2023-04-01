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

#ifndef FMC_STD_IO_H
#define FMC_STD_IO_H

#include <stdio.h>

#include "../preprocessor/FMC_macros.h"
#include "../preprocessor/FMC_consts.h"
#include "../types/FMC_enums.h"

#if defined(FMC_COMPILING_ON_LINUX)
    #include <unistd.h>
#endif

FMC_BEGIN_DECLS

#if defined(FMC_COMPILING_ON_LINUX)

inline ssize_t FMC_fastWrite(int fd, const void *buf, size_t size) 
{
    register int64_t rax __asm__ ("rax") = 1;
    register int rdi __asm__ ("rdi") = fd;
    register const void *rsi __asm__ ("rsi") = buf;
    register size_t rdx __asm__ ("rdx") = size;
    __asm__ volatile (
        "syscall"
        : "+r" (rax)
        : "r" (rdi), "r" (rsi), "r" (rdx)
        : "rcx", "r11", "memory"
    );
    return rax;
    FMC_UNREACHABLE;
}

#else // !defined(FMC_COMPILING_ON_LINUX)
    #define FMC_fastWrite(fd, buf, size)     \
        if (size > 0)                        \
        {                                    \
            switch(fd)                       \
            {                                \
                case 1:                      \
                    fputs(buf, stdout);      \
                    break;                   \
                case 2:                      \
                    fputs(buf, stderr);      \
                    break;                   \
                default:                     \
                    break;                   \
            }                                \
        }
#endif

/* FMC_SHARED FMC_FUNC_FORMAT(printf, 3, 4) int FMC_fprintf(FMC_Encodings stream_encoding, FILE *stream, const char *format, ...); */

FMC_END_DECLS


#endif // FMC_STD_IO_H
