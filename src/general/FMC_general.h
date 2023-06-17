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

#ifndef FMC_GENERAL_H
#define FMC_GENERAL_H


// #include <defer.h>
// #include <exCept.h>
#include "preprocessor/FMC_platform.h"
#if defined(FMC_COMPILING_ON_WINDOWS)
    #if defined(_WIN32_WINNT) || defined(WINVER)
        #undef _WIN32_WINNT
        #undef WINVER
    #endif
    #define _WIN32_WINNT 0x0A00
    #define WINVER FMC_ID(_WIN32_WINNT)
#endif
#include "preprocessor/FMC_macros.h"
#include "preprocessor/FMC_consts.h"
#include "preprocessor/FMC_flags.h"
#include "preprocessor/FMC_attributes.h"
#include "types/FMC_structs.h"
#include "types/FMC_typedefs.h"
#include "types/FMC_enums.h"
#include "utils/FMC_errors.h"
#include "utils/FMC_globals.h"
#include "utils/FMC_deprecated.h"
#include "utils/FMC_str_view.h"
#include "utils/FMC_std_io.h"
#include "types/FMC_int128.h"

#endif // FMC_GENERAL_H
