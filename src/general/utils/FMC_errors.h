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

#ifndef FMC_ERRORS_H
#define FMC_ERRORS_H

#include <stdio.h>
#include "../preprocessor/FMC_consts.h"
#include "../preprocessor/FMC_macros.h"

FMC_SHARED void FMC_makeMsg_f(char *buff, unsigned int argc, ...);

#define FMC_makeMsg(err_var_name, argc, ...)         \
    char err_var_name[256];                          \
    FMC_makeMsg_f(err_var_name, argc, __VA_ARGS__)

FMC_FUNC_INLINE void FMC_resetStreamOutputStyle(FILE *stream)
{
    fprintf(stream, RESET);
}


FMC_FUNC_INLINE void FMC_changeStreamTextColorToRed(FILE *stream)
{
    fprintf(stream, FG_RED);
}

FMC_FUNC_INLINE void FMC_changeStreamTextColorToGreen(FILE *stream)
{
    fprintf(stream, FG_GREEN);
}

FMC_FUNC_INLINE void FMC_changeStreamTextColorToYellow(FILE *stream)
{
    fprintf(stream, FG_YELLOW);
}

FMC_FUNC_INLINE void FMC_changeStreamTextColorToBlue(FILE *stream)
{
    fprintf(stream, FG_BLUE);
}

FMC_FUNC_INLINE void FMC_changeStreamTextColorToMagenta(FILE *stream)
{
    fprintf(stream, FG_MAGENTA);
}

FMC_FUNC_INLINE void FMC_changeStreamTextColorToCyan(FILE *stream)
{
    fprintf(stream, FG_CYAN);
}

FMC_FUNC_INLINE void FMC_changeStreamTextColorToWhite(FILE *stream)
{
    fprintf(stream, FG_WHITE);
}

FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightRed(FILE *stream)
{
    fprintf(stream, FG_BRIGHT_RED);
}

FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightGreen(FILE *stream)
{
    fprintf(stream, FG_BRIGHT_GREEN);
}

FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightYellow(FILE *stream)
{
    fprintf(stream, FG_BRIGHT_YELLOW);
}

FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightBlue(FILE *stream)
{
    fprintf(stream, FG_BRIGHT_BLUE);
}

FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightMagenta(FILE *stream)
{
    fprintf(stream, FG_BRIGHT_MAGENTA);
}

FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightCyan(FILE *stream)
{
    fprintf(stream, FG_BRIGHT_CYAN);
}

FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightWhite(FILE *stream)
{
    fprintf(stream, FG_BRIGHT_WHITE);
}

FMC_FUNC_INLINE void FMC_setBGStreamColorToRed(FILE *stream)
{
    fprintf(stream, BG_RED);
}

FMC_FUNC_INLINE void FMC_setBGStreamColorToGreen(FILE *stream)
{
    fprintf(stream, BG_GREEN);
}

FMC_FUNC_INLINE void FMC_setBGStreamColorToYellow(FILE *stream)
{
    fprintf(stream, BG_YELLOW);
}

FMC_FUNC_INLINE void FMC_setBGStreamColorToBlue(FILE *stream)
{
    fprintf(stream, BG_BLUE);
}

FMC_FUNC_INLINE void FMC_setBGStreamColorToMagenta(FILE *stream)
{
    fprintf(stream, BG_MAGENTA);
}

FMC_FUNC_INLINE void FMC_setBGStreamColorToCyan(FILE *stream)
{
    fprintf(stream, BG_CYAN);
}

FMC_FUNC_INLINE void FMC_setBGStreamColorToWhite(FILE *stream)
{
    fprintf(stream, BG_WHITE);
}

FMC_FUNC_INLINE void FMC_setBGStreamColorToBrightRed(FILE *stream)
{
    fprintf(stream, BG_BRIGHT_RED);
}

FMC_FUNC_INLINE void FMC_setBGStreamColorToBrightGreen(FILE *stream)
{
    fprintf(stream, BG_BRIGHT_GREEN);
}

FMC_FUNC_INLINE void FMC_setBGStreamColorToBrightYellow(FILE *stream)
{
    fprintf(stream, BG_BRIGHT_YELLOW);
}

FMC_FUNC_INLINE void FMC_setBGStreamColorToBrightBlue(FILE *stream)
{
    fprintf(stream, BG_BRIGHT_BLUE);
}

FMC_FUNC_INLINE void FMC_setBGStreamColorToBrightMagenta(FILE *stream)
{
    fprintf(stream, BG_BRIGHT_MAGENTA);
}

FMC_FUNC_INLINE void FMC_setBGStreamColorToBrightCyan(FILE *stream)
{
    fprintf(stream, BG_BRIGHT_CYAN);
}

FMC_FUNC_INLINE void FMC_setBGStreamColorToBrightWhite(FILE *stream)
{
    fprintf(stream, BG_BRIGHT_WHITE);
}

FMC_FUNC_INLINE void FMC_setTextStyleToBold(FILE *stream)
{
    fprintf(stream, TXT_BOLD);
}

FMC_FUNC_INLINE void FMC_setTextStyleToDim(FILE *stream)
{
    fprintf(stream, TXT_DIM);
}

FMC_FUNC_INLINE void FMC_setTextStyleToUnderlined(FILE *stream)
{
    fprintf(stream, TXT_UNDERLINED);
}

FMC_FUNC_INLINE void FMC_setTextStyleToBlink(FILE *stream)
{
    fprintf(stream, TXT_BLINK);
}

FMC_FUNC_INLINE void FMC_setTextStyleToReverse(FILE *stream)
{
    fprintf(stream, TXT_REVERSE);
}

FMC_FUNC_INLINE void FMC_setTextStyleToHidden(FILE *stream)
{
    fprintf(stream, TXT_HIDDEN);
}


FMC_FUNC_INLINE void FMC_printRedText(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToRed(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printGreenText(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToGreen(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printYellowText(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToYellow(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBlueText(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBlue(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printMagentaText(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToMagenta(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printCyanText(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToCyan(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printWhiteText(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToWhite(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBrightRedText(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBrightRed(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBrightGreenText(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBrightGreen(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBrightYellowText(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBrightYellow(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBrightBlueText(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBrightBlue(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBrightMagentaText(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBrightMagenta(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBrightCyanText(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBrightCyan(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBrightWhiteText(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBrightWhite(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printRedError(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToRed(stream);
    FMC_setTextStyleToBold(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printGreenError(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToGreen(stream);
    FMC_setTextStyleToBold(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printYellowError(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToYellow(stream);
    FMC_setTextStyleToBold(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBlueError(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBlue(stream);
    FMC_setTextStyleToBold(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printMagentaError(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToMagenta(stream);
    FMC_setTextStyleToBold(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printCyanError(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToCyan(stream);
    FMC_setTextStyleToBold(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printWhiteError(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToWhite(stream);
    FMC_setTextStyleToBold(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBrightRedError(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBrightRed(stream);
    FMC_setTextStyleToBold(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBrightGreenError(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBrightGreen(stream);
    FMC_setTextStyleToBold(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBrightYellowError(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBrightYellow(stream);
    FMC_setTextStyleToBold(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBrightBlueError(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBrightBlue(stream);
    FMC_setTextStyleToBold(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBrightMagentaError(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBrightMagenta(stream);
    FMC_setTextStyleToBold(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBrightCyanError(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBrightCyan(stream);
    FMC_setTextStyleToBold(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

FMC_FUNC_INLINE void FMC_printBrightWhiteError(FILE *stream, const char *error)
{
    FMC_changeStreamTextColorToBrightWhite(stream);
    FMC_setTextStyleToBold(stream);
    fprintf(stream, "%s\n", error);
    FMC_resetStreamOutputStyle(stream);
}

#endif // FMC_ERRORS_H
