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

#if 0

FMC_SHARED FMC_FUNC_COLD int64_t FMC_getLevenshtein(FMC_String* str1, FMC_String* str2)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!str1 || !str2)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_nullarg, 3, "ERROR: In function: ", __func__, ": one or both of arguments is (or are) null");
            FMC_printRedError(stderr, err_nullarg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "ERROR: In function: FMC_getLevenshtein: one or both of arguments is (or are) null");
        return -1;
        FMC_UNREACHABLE;
    }
    #pragma diagnostic pop
    // if (!FMC_isStrConsistent(str1) || ...) ... 
    if (!str1->firstChar || !str1->lastChar)
    {
        return ((!str2->firstChar && !str2->lastChar) || str2->firstChar->isNull || !str2->size) ? 0 : str2->size;
        FMC_UNREACHABLE;
    }
    if (!str2->firstChar || !str2->lastChar)
    {
        return ((!str1->firstChar && !str1->lastChar) || str1->firstChar->isNull || !str1->size) ? 0 : str1->size;
        FMC_UNREACHABLE;
    }
    FMC_removeTrailNullChars(str1);
    FMC_removeTrailNullChars(str2);
    if (!FMC_checkEncoding(str1) || !FMC_checkEncoding(str2))
    {
        
    }
    if (!(str1->firstChar->encoding))
    return 0;
}

#endif