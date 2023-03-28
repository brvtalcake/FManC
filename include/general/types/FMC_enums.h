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

#ifndef FMC_ENUMS_H
#define FMC_ENUMS_H

#include "../preprocessor/FMC_macros.h"

FMC_SHARED enum FManC_Encodings
{
	utf8     = 1,
	utf8_bom = 2,
	utf16_le = 4,
	utf16_be = 8,
	utf32_le = 16,
	utf32_be = 32,
	ascii    = 64,
	unknown  = 128,
	error    = 256
};
typedef enum FManC_Encodings FMC_Encodings;

FMC_SHARED enum FManC_Error
{
	FMC_OK                      	= 0,
	FMC_ERR_PUSH                	= 1,
	FMC_ERR_NULL_PTR            	= 2,
	FMC_ERR_WRONG_FLAGS_COMBINATION = 3,
	FMC_ERR_INTERNAL          		= 4,
	FMC_ERR_INVALID_ARGUMENT        = 5,
	FMC_ERR_FILE			  		= 6,
	FMC_ERR_UTF			  			= 7,
};
typedef enum FManC_Error FMC_Error;

#endif  // FMC_ENUMS_H
