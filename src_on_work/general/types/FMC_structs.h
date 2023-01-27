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

#if defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) && !defined(STATIC)
    #if defined(BUILD_DLL)
        #define SHARED __declspec(dllexport)
    #elif defined(USE_FMC_DLL)
        #define SHARED __declspec(dllimport)
    #else
        #error "You must define BUILD_DLL to build the DLL or USE_FMC_DLL to use the built DLL. To use or build the static library, please define STATIC."
    #endif
#elif defined(_WIN32) || defined(WIN32) || defined(_WIN64) || defined(WIN64) || defined(__WIN32__) || defined(__TOS_WIN__) || defined(__WINDOWS__) && defined(STATIC)
   #define SHARED
#elif defined(__linux__) || defined(__unix__) || defined(__APPLE__) || defined(__MACH__) && !defined(STATIC) && !defined(USE_FMC_DLL) && !defined(BUILD_DLL) // Linux, Unix, Mac OS X

    #if defined(STATIC) || defined(USE_FMC_DLL) || defined(BUILD_DLL)
        #warning "You don't have to specify STATIC, USE_FMC_DLL or BUILD_DLL on Linux, Unix or Mac OS X."
    #endif
    #define SHARED
#else
    #error "Unsupported platform"
#endif // PLATFORMS

#include <stdio.h>
#include "../preprocessor/FMC_consts.h"

SHARED struct FManC_File
{
    FILE *file;
    char path[MAX_FPATH_SIZE];
    char name[MAX_FNAME_SIZE];
    char extension[MAX_FEXT_SIZE];
    FMC_Encodings encoding;
};

SHARED typedef struct FManC_File FMC_File;

SHARED struct FManC_StrOcc
{
	size_t charCount;
	long long int *pos;
};

SHARED typedef struct FManC_StrOcc FMC_StrOcc;

SHARED struct FManC_CharComp
{
    int mostLeft : 8;
    int middleLeft : 8;
    int middleRight : 8;
    int mostRight : 8;
};

SHARED typedef struct FManC_CharComp FMC_CharComp;

SHARED struct FManC_Char
{
    FMC_Encodings encoding;
    FMC_CharComp comp;
    FMC_CharControl isNull;
};

SHARED typedef struct FManC_Char FMC_Char;

#endif // FMC_STRUCTS_H