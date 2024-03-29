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

#ifndef FMC_SYS_H
#define FMC_SYS_H

#include "../../general/FMC_general.h"

#if defined(FMC_COMPILING_ON_WINDOWS)
    #define SECURITY_WIN32
    #include <windows.h>
    #include <Security.h>
#else
    #include <sys/stat.h>
    #include <sys/types.h>
    #include <dirent.h>
    #include <pwd.h>
    #include <unistd.h>
#endif

#include <stdlib.h>

FMC_BEGIN_DECLS

// TODO: FMC_getProgLocation

// TODO: Rewrite symbol versioning conditionals here
#if !defined(USE_FMC_getCurrentUserName_VER) || USE_FMC_getCurrentUserName_VER == FMC_MK_VER_NUM(1, 0, 0) || defined(FMC_BUILD_SO) || defined(FMC_USE_SO)
FMC_SHARED FMC_FUNC_NONNULL(1) FMC_FUNC_COLD 
FMC_DEF_SYM(char*, FMC_getCurrentUserName, 1_0_0)(char* const user_name, const size_t len);
#endif

// TODO: Rewrite symbol versioning conditionals here
#if !defined(USE_FMC_getAllUIDs_VER) || USE_FMC_getAllUIDs_VER == FMC_MK_VER_NUM(1, 0, 0) || defined(FMC_BUILD_SO) || defined(FMC_USE_SO)
#if !defined(FMC_COMPILING_ON_WINDOWS)
FMC_SHARED FMC_FUNC_WARN_UNUSED_RESULT FMC_FUNC_JUST_MALLOC
FMC_DEF_SYM(unsigned int*, FMC_getAllUIDs, 1_0_0)(unsigned int range_count, ...);
#endif
#endif

FMC_END_DECLS

#endif // FMC_SYS_H
