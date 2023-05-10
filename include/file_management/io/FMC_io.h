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

#ifndef FMC_IO_H
#define FMC_IO_H

#include "../../general/FMC_general.h"
#include "../filesystem/FMC_filesystem.h"
#include "../../data_analyze/strings/FMC_strings.h"

FMC_BEGIN_DECLS

// TODO: FMC_readFileByPath(const FMC_Path* const path);

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_NONNULL(1) FMC_FUNC_WARN_UNUSED_RESULT FMC_String* FMC_readFile(FMC_File* const file);

// TODO : 
/* FMC_SHARED FMC_FUNC_NONNULL(1, 2) FMC_Bool FMC_writeFile(FMC_File* const file, const FMC_String* const str); */

FMC_END_DECLS

#endif // FMC_IO_H
