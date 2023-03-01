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

#ifndef FMC_GLOBALS_H
#define FMC_GLOBALS_H

#include "../types/FMC_typedefs.h"
#include "../types/FMC_enums.h"
#include "../preprocessor/FMC_macros.h"
#include "../preprocessor/FMC_consts.h"

FMC_BEGIN_DECLS

FMC_SHARED FMC_FUNC_COLD FMC_Bool FMC_setDebugState(FMC_Bool state);
FMC_SHARED FMC_FUNC_HOT FMC_Bool FMC_getDebugState(void);

// TODO : Implement a global error manager (as errno in C)

FMC_END_DECLS

#endif // FMC_GLOBALS_H
