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

#include "FMC_strings.h"

/* FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_HOT FMC_Char FMC_getChar(FMC_File *file)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (file == NULL)
    {
        FMC_makeMsg(err_nullarg, 3, "ERROR : In function : ", __func__, " : the provided file pointer is NULL");
        FMC_printRedError(stderr, err_nullarg);
    }
    #pragma GCC diagnostic pop
    if (!file->isOpened || file->name)
    {

    }

} */