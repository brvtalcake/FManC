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

#ifndef FMC_STR_VIEW_H
#define FMC_STR_VIEW_H

#include "../FMC_general.h"

#ifndef FMC_makeStrView
    #define FMC_makeStrView(_str, _len) ((FMC_CStrView){ .str = _str, .size = (size_t)_len })
#endif

FMC_BEGIN_DECLS

FMC_SHARED FMC_DEF_SYM(FMC_freeStrView, 1_0_0) void FMC_freeStrView(FMC_CStrView* view);
FMC_SHARED FMC_DEF_SYM(FMC_allocStrView, 1_0_0) FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_JUST_MALLOC FMC_CStrView* FMC_allocStrView(const char* const str, size_t len);

FMC_END_DECLS

#endif // FMC_STR_VIEW_H
