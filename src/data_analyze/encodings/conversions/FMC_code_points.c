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

#include "FMC_conversions.h"

FMC_SHARED FMC_FUNC_NONNULL(1) FMC_CodePoint FMC_codePointFromUTF8(const uint8_t* restrict const utf8_hex_values)
{
    #pragma GCC diagnostic ignored "-Wnonnull-compare"
    if (!utf8_hex_values)
    {
        if (FMC_getDebugState())
        {
            FMC_makeMsg(err_inv_arg, 1, "ERROR: FMC_codePointFromUTF8: utf8_hex_values is NULL");
            FMC_printRedError(stderr, err_inv_arg);
        }
        FMC_setError(FMC_ERR_INVALID_ARGUMENT, "FMC_codePointFromUTF8: utf8_hex_values is NULL");
        return FMC_CODE_POINT_NULL;
        FMC_UNREACHABLE;
    }
    #pragma GCC diagnostic pop

    FMC_CodePoint code_point = FMC_CODE_POINT_NULL;
    const uint8_t byte_count = FMC_getUTF8ByteCount(utf8_hex_values[0]);

    FMC_UNIMPLEMENTED(FMC_codePointFromUTF8: not implemented yet.);

}