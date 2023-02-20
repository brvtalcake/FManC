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

#include "FMC_errors.h"
#include "../preprocessor/FMC_macros.h"
#include <stdio.h>
#include <stdarg.h>
#include <string.h>

FMC_SHARED void FMC_makeMsg_f(char *buff, unsigned int argc, ...)
{
    va_list args;
    va_start(args, argc);
    for (unsigned int i = 0; i < argc; i++)
    {
        char *arg = va_arg(args, char *);
        buff = strcat(buff, arg);
    }
    va_end(args);
}

extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_resetStreamOutputStyle(FILE *stream);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToRed(FILE *stream);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToGreen(FILE *stream);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToYellow(FILE *stream);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBlue(FILE *stream);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToMagenta(FILE *stream);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToCyan(FILE *stream);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToWhite(FILE *stream);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightRed(FILE *stream);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightGreen(FILE *stream);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightYellow(FILE *stream);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightBlue(FILE *stream);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightMagenta(FILE *stream);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightCyan(FILE *stream);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightWhite(FILE *stream);

extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printRedText(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printGreenText(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printYellowText(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBlueText(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printMagentaText(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printCyanText(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printWhiteText(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightRedText(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightGreenText(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightYellowText(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightBlueText(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightMagentaText(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightCyanText(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightWhiteText(FILE *stream, const char *text);

extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printRedError(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printGreenError(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printYellowError(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBlueError(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printMagentaError(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printCyanError(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printWhiteError(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightRedError(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightGreenError(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightYellowError(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightBlueError(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightMagentaError(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightCyanError(FILE *stream, const char *text);
extern FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightWhiteError(FILE *stream, const char *text);
