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

#ifndef FMC_ERRORS_H
#define FMC_ERRORS_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#include "../preprocessor/FMC_consts.h"
#include "../preprocessor/FMC_macros.h"
#include "FMC_std_io.h"

#if defined(FMC_COMPILING_ON_LINUX)
    #define fileno(...) fileno(__VA_ARGS__)
#elif defined(FMC_COMPILING_ON_WINDOWS)
    #include <io.h>
    #if !defined(fileno)
        #define fileno(...) _fileno(__VA_ARGS__)
    #endif
#else
    #define fileno(...) fileno(__VA_ARGS__)
#endif

FMC_BEGIN_DECLS

FMC_SHARED FMC_FUNC_NONNULL(1) void FMC_makeMsg_f(char *buff, unsigned int argc, ...);

#define FMC_makeMsg(err_var_name, argc, ...)         \
    char err_var_name[256] = {"\0"};                 \
    FMC_makeMsg_f(err_var_name, argc, __VA_ARGS__)

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_resetStreamOutputStyle(FILE *stream)
{
    FMC_fastWrite(fileno(stream), RESET, FMC_arrSize(RESET));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToRed(FILE *stream)
{
    FMC_fastWrite(fileno(stream), FG_RED, FMC_arrSize(FG_RED));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToGreen(FILE *stream)
{
    FMC_fastWrite(fileno(stream), FG_GREEN, FMC_arrSize(FG_GREEN));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToYellow(FILE *stream)
{
    FMC_fastWrite(fileno(stream), FG_YELLOW, FMC_arrSize(FG_YELLOW));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBlue(FILE *stream)
{
    FMC_fastWrite(fileno(stream), FG_BLUE, FMC_arrSize(FG_BLUE));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToMagenta(FILE *stream)
{
    FMC_fastWrite(fileno(stream), FG_MAGENTA, FMC_arrSize(FG_MAGENTA));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToCyan(FILE *stream)
{
    FMC_fastWrite(fileno(stream), FG_CYAN, FMC_arrSize(FG_CYAN));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToWhite(FILE *stream)
{
    FMC_fastWrite(fileno(stream), FG_WHITE, FMC_arrSize(FG_WHITE));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightRed(FILE *stream)
{
    FMC_fastWrite(fileno(stream), FG_BRIGHT_RED, FMC_arrSize(FG_BRIGHT_RED));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightGreen(FILE *stream)
{
    FMC_fastWrite(fileno(stream), FG_BRIGHT_GREEN, FMC_arrSize(FG_BRIGHT_GREEN));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightYellow(FILE *stream)
{
    FMC_fastWrite(fileno(stream), FG_BRIGHT_YELLOW, FMC_arrSize(FG_BRIGHT_YELLOW));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightBlue(FILE *stream)
{
    FMC_fastWrite(fileno(stream), FG_BRIGHT_BLUE, FMC_arrSize(FG_BRIGHT_BLUE));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightMagenta(FILE *stream)
{
    FMC_fastWrite(fileno(stream), FG_BRIGHT_MAGENTA, FMC_arrSize(FG_BRIGHT_MAGENTA));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightCyan(FILE *stream)
{
    FMC_fastWrite(fileno(stream), FG_BRIGHT_CYAN, FMC_arrSize(FG_BRIGHT_CYAN));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_changeStreamTextColorToBrightWhite(FILE *stream)
{
    FMC_fastWrite(fileno(stream), FG_BRIGHT_WHITE, FMC_arrSize(FG_BRIGHT_WHITE));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setBGStreamColorToRed(FILE *stream)
{
    FMC_fastWrite(fileno(stream), BG_RED, FMC_arrSize(BG_RED));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setBGStreamColorToGreen(FILE *stream)
{
    FMC_fastWrite(fileno(stream), BG_GREEN, FMC_arrSize(BG_GREEN));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setBGStreamColorToYellow(FILE *stream)
{
    FMC_fastWrite(fileno(stream), BG_YELLOW, FMC_arrSize(BG_YELLOW));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setBGStreamColorToBlue(FILE *stream)
{
    FMC_fastWrite(fileno(stream), BG_BLUE, FMC_arrSize(BG_BLUE));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setBGStreamColorToMagenta(FILE *stream)
{
    FMC_fastWrite(fileno(stream), BG_MAGENTA, FMC_arrSize(BG_MAGENTA));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setBGStreamColorToCyan(FILE *stream)
{
    FMC_fastWrite(fileno(stream), BG_CYAN, FMC_arrSize(BG_CYAN));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setBGStreamColorToWhite(FILE *stream)
{
    FMC_fastWrite(fileno(stream), BG_WHITE, FMC_arrSize(BG_WHITE));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setBGStreamColorToBrightRed(FILE *stream)
{
    FMC_fastWrite(fileno(stream), BG_BRIGHT_RED, FMC_arrSize(BG_BRIGHT_RED));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setBGStreamColorToBrightGreen(FILE *stream)
{
    FMC_fastWrite(fileno(stream), BG_BRIGHT_GREEN, FMC_arrSize(BG_BRIGHT_GREEN));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setBGStreamColorToBrightYellow(FILE *stream)
{
    FMC_fastWrite(fileno(stream), BG_BRIGHT_YELLOW, FMC_arrSize(BG_BRIGHT_YELLOW));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setBGStreamColorToBrightBlue(FILE *stream)
{
    FMC_fastWrite(fileno(stream), BG_BRIGHT_BLUE, FMC_arrSize(BG_BRIGHT_BLUE));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setBGStreamColorToBrightMagenta(FILE *stream)
{
    FMC_fastWrite(fileno(stream), BG_BRIGHT_MAGENTA, FMC_arrSize(BG_BRIGHT_MAGENTA));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setBGStreamColorToBrightCyan(FILE *stream)
{
    FMC_fastWrite(fileno(stream), BG_BRIGHT_CYAN, FMC_arrSize(BG_BRIGHT_CYAN));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setBGStreamColorToBrightWhite(FILE *stream)
{
    FMC_fastWrite(fileno(stream), BG_BRIGHT_WHITE, FMC_arrSize(BG_BRIGHT_WHITE));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setTextStyleToBold(FILE *stream)
{
    FMC_fastWrite(fileno(stream), TXT_BOLD, FMC_arrSize(TXT_BOLD));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setTextStyleToDim(FILE *stream)
{
    FMC_fastWrite(fileno(stream), TXT_DIM, FMC_arrSize(TXT_DIM));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setTextStyleToUnderlined(FILE *stream)
{
    FMC_fastWrite(fileno(stream), TXT_UNDERLINED, FMC_arrSize(TXT_UNDERLINED));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setTextStyleToBlink(FILE *stream)
{
    FMC_fastWrite(fileno(stream), TXT_BLINK, FMC_arrSize(TXT_BLINK));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setTextStyleToReverse(FILE *stream)
{
    FMC_fastWrite(fileno(stream), TXT_REVERSE, FMC_arrSize(TXT_REVERSE));
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_setTextStyleToHidden(FILE *stream)
{
    FMC_fastWrite(fileno(stream), TXT_HIDDEN, FMC_arrSize(TXT_HIDDEN));
}


FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printRedText(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToRed(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printGreenText(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToGreen(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printYellowText(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToYellow(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBlueText(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBlue(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printMagentaText(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToMagenta(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printCyanText(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToCyan(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printWhiteText(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToWhite(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightRedText(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBrightRed(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightGreenText(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBrightGreen(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightYellowText(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBrightYellow(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightBlueText(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBrightBlue(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightMagentaText(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBrightMagenta(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightCyanText(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBrightCyan(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightWhiteText(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBrightWhite(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printRedError(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToRed(stream);
    FMC_setTextStyleToBold(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printGreenError(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToGreen(stream);
    FMC_setTextStyleToBold(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printYellowError(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToYellow(stream);
    FMC_setTextStyleToBold(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBlueError(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBlue(stream);
    FMC_setTextStyleToBold(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printMagentaError(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToMagenta(stream);
    FMC_setTextStyleToBold(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printCyanError(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToCyan(stream);
    FMC_setTextStyleToBold(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printWhiteError(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToWhite(stream);
    FMC_setTextStyleToBold(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightRedError(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBrightRed(stream);
    FMC_setTextStyleToBold(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightGreenError(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBrightGreen(stream);
    FMC_setTextStyleToBold(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightYellowError(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBrightYellow(stream);
    FMC_setTextStyleToBold(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightBlueError(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBrightBlue(stream);
    FMC_setTextStyleToBold(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightMagentaError(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBrightMagenta(stream);
    FMC_setTextStyleToBold(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightCyanError(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBrightCyan(stream);
    FMC_setTextStyleToBold(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_SHARED FMC_FUNC_FLATTEN FMC_FUNC_INLINE void FMC_printBrightWhiteError(FILE *stream, char *text)
{
    FMC_changeStreamTextColorToBrightWhite(stream);
    FMC_setTextStyleToBold(stream);
    char to_print[FMC_ERR_STR_LEN] = {'\0'};
    sprintf(to_print, "%s\n", text);
    FMC_fastWrite(fileno(stream), to_print, strlen(to_print));
    FMC_resetStreamOutputStyle(stream);
}

FMC_END_DECLS

#endif // FMC_ERRORS_H
