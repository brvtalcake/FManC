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

#ifndef FMC_VER_H
#define FMC_VER_H

/* 
 * This header is meant to be user by users of the library before compiling it.
 * It lets the user define some macros to define wich version of some functions should be compiled.
 * By default, latest version of functions are compiled, except in ELF shared library, where older symbols are kept.
 * When using ELF shared library, you can decide to use a different version of a function via the macro :
 *     FMC_USE_SYMVER(sym, major, minor, patch)
 * put directly in your source file.
 * (again, default is latest version, and this macro only does something when using ELF shared library).
 * 
 * For other platforms or non shared ELF library, then you can use this header to define wich version of functions you want to use.
 * It is done via defining the macros :
 *     #define USE_<symbol_name>_VER FMC_MK_VER_NUM(major, minor, patch)
*/


#endif // FMC_VER_H
