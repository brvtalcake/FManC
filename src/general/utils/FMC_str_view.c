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

#include <stdlib.h>
#include <string.h>
#include "FMC_str_view.h"

FMC_SHARED FMC_FUNC_MALLOC(FMC_freeStrView, 1) FMC_CStrView* FMC_allocStrView(const char* const str, size_t len)
{
    FMC_CStrView* view = malloc(sizeof(FMC_CStrView));
    if (view == NULL)
    {
        return NULL;
    }
    view->size = len + 1;
    view->str = malloc(sizeof(char) * view->size);
    if (view->str == NULL)
    {
        free(view);
        return NULL;
    }
    strncpy(view->str, str, view->size);
    return view;
}

FMC_SHARED void FMC_freeStrView(FMC_CStrView* view)
{
    free(view->str);
    free(view);
}