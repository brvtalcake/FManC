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

#pragma once

#ifndef FMC_TYPEDEFS_H
#define FMC_TYPEDEFS_H

#include <stdint.h>
#include "../preprocessor/FMC_macros.h"

#if defined(FMC_COMPILING_ON_WINDOWS)
    #include <windows.h>
#else 
    #include <pthread.h>
#endif

FMC_BEGIN_DECLS

typedef uint8_t FMC_Byte;
typedef _Bool FMC_CharControl;
typedef _Bool FMC_FileState;
typedef _Bool FMC_Bool;

#if defined(FMC_COMPILING_ON_WINDOWS)
    typedef HANDLE FMC_Mutex;
#else 
    typedef pthread_mutex_t FMC_Mutex;
#endif

FMC_END_DECLS

#endif // FMC_TYPEDEFS_H