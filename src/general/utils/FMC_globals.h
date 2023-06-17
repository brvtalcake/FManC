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

#include "../preprocessor/FMC_macros.h"
#include "../types/FMC_enums.h"
#include "../types/FMC_typedefs.h"

FMC_BEGIN_DECLS

FMC_SHARED FMC_FUNC_COLD FMC_Bool FMC_setDebugState(FMC_Bool state);
FMC_SHARED FMC_FUNC_HOT FMC_Bool  FMC_getDebugState(void);

FMC_SHARED FMC_Error FMC_setError(FMC_Error err, const char* const additionnal_message);

FMC_SHARED FMC_FUNC_HOT FMC_Error FMC_getLastErrorNum(void);
FMC_SHARED FMC_FUNC_HOT char*     FMC_getLastErrorStr(char* str, size_t len);
FMC_SHARED FMC_FUNC_HOT FMC_Error FMC_getLastErrorNum_noDepop(void);
FMC_SHARED FMC_Bool               FMC_searchError(FMC_Error err);
FMC_SHARED FMC_Bool FMC_FUNC_NONNULL(1) FMC_searchErrorMsg(const char* restrict const msg);
FMC_SHARED FMC_FUNC_NONNULL(1) char* FMC_getLastErrorStr_noDepop(char* to_fill, size_t len);

FMC_SHARED void FMC_clearErrorStack(void);
FMC_SHARED void FMC_destroyErrorStack(void);

FMC_SHARED const char* const FMC_version(void);

FMC_END_DECLS

#endif  // FMC_GLOBALS_H
