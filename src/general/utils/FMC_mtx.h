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

#ifndef FMC_MTX_H
#define FMC_MTX_H

#include "../preprocessor/FMC_macros.h"
#include "../preprocessor/FMC_platform.h"
#include "../preprocessor/FMC_attributes.h"
#include "../types/FMC_typedefs.h"

#if defined(FMC_COMPILING_ON_WINDOWS)
    #include <windows.h>
#else 
    #include <pthread.h>
#endif

FMC_BEGIN_DECLS

FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT FMC_Mutex FMC_createErrMutex(void);


FMC_END_DECLS

#endif // FMC_MTX_H
