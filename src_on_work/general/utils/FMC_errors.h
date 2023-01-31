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

#include "../preprocessor/FMC_consts.h"
#include "../preprocessor/FMC_macros.h"

FMC_INLINE void FMC_resetStreamOutputStyle(FILE *stream)
{
    fprintf(stream, RESET);
}


FMC_INLINE void FMC_changeStreamTextColorToRed(FILE *stream)
{
    fprintf(stream, FG_RED);
}

FMC_INLINE void FMC_changeStreamTextColorToGreen(FILE *stream)
{
    fprintf(stream, FG_GREEN);
}

FMC_INLINE void FMC_changeStreamTextColorToYellow(FILE *stream)
{
    fprintf(stream, FG_YELLOW);
}

FMC_INLINE void FMC_changeStreamTextColorToBlue(FILE *stream)
{
    fprintf(stream, FG_BLUE);
}

FMC_INLINE void FMC_changeStreamTextColorToMagenta(FILE *stream)
{
    fprintf(stream, FG_MAGENTA);
}

FMC_INLINE void FMC_changeStreamTextColorToCyan(FILE *stream)
{
    fprintf(stream, FG_CYAN);
}

FMC_INLINE void FMC_changeStreamTextColorToWhite(FILE *stream)
{
    fprintf(stream, FG_WHITE);
}

FMC_INLINE void FMC_changeStreamTextColorToBrightRed(FILE *stream)
{
    fprintf(stream, FG_BRIGHT_RED);
}

FMC_INLINE void FMC_changeStreamTextColorToBrightGreen(FILE *stream)
{
    fprintf(stream, FG_BRIGHT_GREEN);
}

FMC_INLINE void FMC_changeStreamTextColorToBrightYellow(FILE *stream)
{
    fprintf(stream, FG_BRIGHT_YELLOW);
}

FMC_INLINE void FMC_changeStreamTextColorToBrightBlue(FILE *stream)
{
    fprintf(stream, FG_BRIGHT_BLUE);
}

FMC_INLINE void FMC_changeStreamTextColorToBrightMagenta(FILE *stream)
{
    fprintf(stream, FG_BRIGHT_MAGENTA);
}

FMC_INLINE void FMC_changeStreamTextColorToBrightCyan(FILE *stream)
{
    fprintf(stream, FG_BRIGHT_CYAN);
}

FMC_INLINE void FMC_changeStreamTextColorToBrightWhite(FILE *stream)
{
    fprintf(stream, FG_BRIGHT_WHITE);
}

FMC_INLINE void FMC_setBGStreamColorToRed(FILE *stream)
{
    fprintf(stream, BG_RED);
}

FMC_INLINE void FMC_setBGStreamColorToGreen(FILE *stream)
{
    fprintf(stream, BG_GREEN);
}

FMC_INLINE void FMC_setBGStreamColorToYellow(FILE *stream)
{
    fprintf(stream, BG_YELLOW);
}

FMC_INLINE void FMC_setBGStreamColorToBlue(FILE *stream)
{
    fprintf(stream, BG_BLUE);
}

FMC_INLINE void FMC_setBGStreamColorToMagenta(FILE *stream)
{
    fprintf(stream, BG_MAGENTA);
}

FMC_INLINE void FMC_setBGStreamColorToCyan(FILE *stream)
{
    fprintf(stream, BG_CYAN);
}

FMC_INLINE void FMC_setBGStreamColorToWhite(FILE *stream)
{
    fprintf(stream, BG_WHITE);
}

FMC_INLINE void FMC_setBGStreamColorToBrightRed(FILE *stream)
{
    fprintf(stream, BG_BRIGHT_RED);
}

FMC_INLINE void FMC_setBGStreamColorToBrightGreen(FILE *stream)
{
    fprintf(stream, BG_BRIGHT_GREEN);
}

FMC_INLINE void FMC_setBGStreamColorToBrightYellow(FILE *stream)
{
    fprintf(stream, BG_BRIGHT_YELLOW);
}

FMC_INLINE void FMC_setBGStreamColorToBrightBlue(FILE *stream)
{
    fprintf(stream, BG_BRIGHT_BLUE);
}

FMC_INLINE void FMC_setBGStreamColorToBrightMagenta(FILE *stream)
{
    fprintf(stream, BG_BRIGHT_MAGENTA);
}

FMC_INLINE void FMC_setBGStreamColorToBrightCyan(FILE *stream)
{
    fprintf(stream, BG_BRIGHT_CYAN);
}

FMC_INLINE void FMC_setBGStreamColorToBrightWhite(FILE *stream)
{
    fprintf(stream, BG_BRIGHT_WHITE);
}


#endif // FMC_ERRORS_H
