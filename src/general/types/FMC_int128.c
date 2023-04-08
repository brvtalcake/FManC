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
#include "FMC_int128.h"



// FMC_SHARED FMC_FUNC_JUST_MALLOC FMC_Uint128* FMC_Uint128Alloc(uint64_t right_part, uint64_t left_part)
// {
//     FMC_Uint128* ptr = malloc(sizeof(FMC_Uint128));
//     if (ptr != NULL)
//     {
//         ptr->high = left_part;
//         ptr->low = right_part;
//     }
//     return ptr;
// }

// FMC_SHARED void FMC_Uint128Free(FMC_Uint128* ptr)
// {
//     free(ptr);
// }

// FMC_SHARED void FMC_Uint128And(FMC_Uint128* restrict self, FMC_Uint128 const* restrict const to_and)
// {
//     self->high &= to_and->high;
//     self->low &= to_and->low;
// }

// FMC_SHARED void FMC_Uint128Or(FMC_Uint128* restrict self, FMC_Uint128 const* restrict const to_or)
// {
//     self->high |= to_or->high;
//     self->low |= to_or->low;
// }

// FMC_SHARED void FMC_Uint128Xor(FMC_Uint128* restrict self, FMC_Uint128 const* restrict const to_xor)
// {
//     self->high ^= to_xor->high;
//     self->low ^= to_xor->low;
// }

// FMC_SHARED void FMC_Uint128Not(FMC_Uint128* restrict self)
// {
//     self->high = ~self->high;
//     self->low = ~self->low;
// }

// FMC_SHARED int FMC_Uint128Compare(FMC_Uint128* restrict self, FMC_Uint128 const* restrict const to_compare)
// {
//     if (self->high > to_compare->high)
//     {
//         return 1;
//     }
//     else if (self->high < to_compare->high)
//     {
//         return -1;
//     }
//     else
//     {
//         if (self->low > to_compare->low)
//         {
//             return 1;
//         }
//         else if (self->low < to_compare->low)
//         {
//             return -1;
//         }
//         else
//         {
//             return 0;
//         }
//     }
// }

// FMC_SHARED FMC_Uint128* FMC_Uint128Sum(FMC_Uint128* self, FMC_Uint128 const* const to_sum)
// {
    
// }