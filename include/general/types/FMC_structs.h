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

#ifndef FMC_STRUCTS_H
#define FMC_STRUCTS_H


#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include "../preprocessor/FMC_consts.h"
#include "../preprocessor/FMC_macros.h"
#include "FMC_enums.h"
#include "FMC_typedefs.h"

FMC_BEGIN_DECLS

FMC_SHARED struct FManC_ErrStackElement
{
    struct FManC_ErrStackElement *next;
    char additionalInfo[FMC_ERR_STR_LEN / 2];
    FMC_Error errorNum;
};
typedef struct FManC_ErrStackElement FMC_ErrStackElement;

FMC_SHARED struct FManC_ErrStack
{
    FMC_ErrStackElement *lastError;
    uint8_t stackSize;
};
typedef struct FManC_ErrStack FMC_ErrStack;

FMC_SHARED struct FManC_Perms
{
    unsigned int permFlags;
    // TODO
};


FMC_SHARED struct FManC_Directory
{
    size_t fileCount;
    size_t dirCount;
    size_t totalCount;
    char pathList[][MAX_FPATH_SIZE + MAX_FNAME_SIZE + MAX_FEXT_SIZE];
};
typedef struct FManC_Directory FMC_Directory;

FMC_SHARED struct FManC_File
{
    FILE* file;
    // mtx_t fileMutex;
    unsigned long long int fileSize;
    FMC_Encodings encoding;
    enum FMC_File_orientation
    {
        failed_to_change = 1,
        not_set          = 2,
        byte_oriented    = 512,    // To stick to the corresponding flags in FMC_flags.h
        wide_oriented    = 1024,   // To stick to the corresponding flags in FMC_flags.h
    } orientation;
    enum FMC_File_dataMode
    {
        undefined = 1,
        binary    = 128,   // To stick to the corresponding flags in FMC_flags.h
        text      = 256,   // To stick to the corresponding flags in FMC_flags.h
    } dataMode;
    FMC_FileState isOpened;
    char path[MAX_FPATH_SIZE];
    char name[MAX_FNAME_SIZE];
    char extension[MAX_FEXT_SIZE];
    char fullMode[MAX_MODE_SIZE];
};
typedef struct FManC_File FMC_File;

#ifdef DEBUG_STRUCTS
static_assert(sizeof(FMC_File) == sizeof(FILE*) + sizeof(unsigned long long int) + sizeof(FMC_Encodings) + sizeof(enum { a,b }) + sizeof(FMC_FileState) + sizeof(char[MAX_FPATH_SIZE]) + sizeof(char[MAX_FNAME_SIZE]) + sizeof(char[MAX_FEXT_SIZE]) + sizeof(char[MAX_MODE_SIZE]) , "FMC_File has some padding bytes");
#endif

FMC_SHARED struct FManC_StrOcc
{
	size_t charCount;
	long long int *pos;
};
typedef struct FManC_StrOcc FMC_StrOcc;

// the least significant byte is byte1. For instance, in 257, byte1 = 0000 0001, byte2 = 0000 0001, 
//                                                            byte3 = 0000 0000, byte4 = 0000 0000.
FMC_SHARED struct FManC_CharComp
{
    FMC_Byte byte1 : 8;
    FMC_Byte byte2 : 8;
    FMC_Byte byte3 : 8;
    FMC_Byte byte4 : 8;
};
typedef struct FManC_CharComp FMC_CharComp;

FMC_SHARED struct FManC_Char
{
    struct FManC_Char* next;
    struct FManC_Char* prev;
    FMC_Encodings encoding;
    FMC_CharComp comp;
    FMC_CharControl isNull;
    uint8_t byteNumber;
};
typedef struct FManC_Char FMC_Char;


FMC_SHARED struct FManC_String
{
    FMC_Char *firstChar;
    FMC_Char *lastChar;
    uint64_t size;
};
typedef struct FManC_String FMC_String;

FMC_SHARED struct FManC_CStrView
{
    size_t size;
    char *str;
};
typedef struct FManC_CStrView FMC_CStrView;

FMC_SHARED struct FManC_Uint128
{
    uint64_t high;
    uint64_t low;
};
typedef struct FManC_Uint128 FMC_Uint128;

/*#include <threads.h>


FMC_SHARED struct FManC_ArenaElement
{
    void* current;
    size_t alignement;
};

FMC_SHARED struct FManC_Arena
{
    void* start;
    void* end;

};*/

FMC_END_DECLS

#endif // FMC_STRUCTS_H
