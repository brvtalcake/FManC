/*

MIT License

Copyright (c) 2022 Axel PASCON

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

#ifndef FMC_STRUCTS_H
#define FMC_STRUCTS_H


#include <stdio.h>
#include "../preprocessor/FMC_consts.h"
#include "../preprocessor/FMC_macros.h"
#include "FMC_enums.h"
#include "FMC_typedefs.h"

FMC_SHARED struct FManC_File
{
    FILE *file;
    char path[MAX_FPATH_SIZE];
    char name[MAX_FNAME_SIZE];
    char extension[MAX_FEXT_SIZE];
    FMC_Encodings encoding;
};

FMC_SHARED typedef struct FManC_File FMC_File;

FMC_SHARED struct FManC_StrOcc
{
	size_t charCount;
	long long int *pos;
};

FMC_SHARED typedef struct FManC_StrOcc FMC_StrOcc;

FMC_SHARED struct FManC_CharComp
{
    int mostLeft : 8;
    int middleLeft : 8;
    int middleRight : 8;
    int mostRight : 8;
};

FMC_SHARED typedef struct FManC_CharComp FMC_CharComp;

FMC_SHARED struct FManC_Char
{
    FMC_Encodings encoding;
    FMC_CharComp comp;
    FMC_CharControl isNull;
};

FMC_SHARED typedef struct FManC_Char FMC_Char;

#endif // FMC_STRUCTS_H