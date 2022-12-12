
/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * \defgroup fmanc_CH Core C headers
 * @{
 */

/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * \defgroup fmanc_MH Main C header
 * @ingroup fmanc_CH
 * @{
 */

/**
 * @file 	   fmanc.h
 *
 * @brief      This is the main header of the lib, where all of the headers are included.
 * @details	   If you don't want to have troubles, just include this one instead of including the others one by one.
 * 			   If you want to use the functions defined in \link fcmx.h this\endlink or \link lex_yy.h this\endlink source files, then write something like 
 * 			   \code{.c} #define USE_FCMX TRUE\endcode (actually, just define USE_FCMX with a certain value, no matter what it is).
 *
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * 
 */

/**
 * @}
 */
/**
 * @}
 */
#ifndef FMANC_H
#define FMANC_H

#include "fileMan.h"
#include "analyze.h"
#if defined(USE_FCMX)
#include "fcmx.h"
#include "./notByMe/lex_yy.h"
#endif

#endif

