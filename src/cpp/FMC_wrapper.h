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

#ifndef FMC_WRAPPER_H
#define FMC_WRAPPER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "../general/preprocessor/FMC_macros.h"

#include <stddef.h>

// FMC_dir
/**
 * @author Axel PASCON
 * @date 2023
 * @fn int FMC_dirExists(const char *path)
 * @brief Checks if a directory exists.
 * @details This function is a wrapper around the C++ filesystem library assciated function.
 * 
 * @param[in] path The path whose existence is to be checked.
 * @return An integer value.
 * @retval 1 if the directory exists.
 * @retval 0 if the directory does not exist. 
 */

FMC_SHARED int FMC_dirExists(const char *path);
/**
 * @author Axel PASCON
 * @date 2023
 * @fn int FMC_isDir(const char *path)
 * @brief Checks if a path is a directory.
 * @details This function is a wrapper around the C++ filesystem library assciated function.
 * 
 * @param[in] path The path to check.
 * @return An integer value.
 * @retval 1 if the path is a directory.
 * @retval 0 if the path is not a directory.
 * @retval -1 if an error occured. 
 */
FMC_SHARED int FMC_isDir(const char *path);
/**
 * @author Axel PASCON
 * @date 2023
 * @fn int FMC_isRegFile(const char *path)
 * @brief Checks if a path is a regular file.
 * @details This function is a wrapper around the C++ filesystem library assciated function.
 * 
 * @param[in] path The path to check.
 * @return An integer value.
 * @retval 1 if the path is a regular file.
 * @retval 0 if the path is not a regular file.
 * @retval -1 if an error occured. 
 */
FMC_SHARED int FMC_isRegFile(const char *path);
/**
 * @author Axel PASCON
 * @date 2023
 * @fn int FMC_isSymLink(const char *path)
 * @brief Checks if a path is a symbolic link.
 * @details This function is a wrapper around the C++ filesystem library assciated function.
 * 
 * @param[in] path The path to check.
 * @return An integer value.
 * @retval 1 if the path is a symbolic link.
 * @retval 0 if the path is not a symbolic link.
 * @retval -1 if an error occured. 
 */
FMC_SHARED int FMC_isSymLink(const char *path);
/**
 * @author Axel PASCON
 * @date 2023
 * @fn int FMC_isBlock(const char *path)
 * @brief Checks if a path is a block device.
 * @details This function is a wrapper around the C++ filesystem library assciated function.
 * 
 * @param[in] path The path to check.
 * @return An integer value.
 * @retval 1 if the path is a block device.
 * @retval 0 if the path is not a block device.
 * @retval -1 if an error occured. 
 */
FMC_SHARED int FMC_isBlock(const char* path);
/**
 * @author Axel PASCON
 * @date 2023
 * @fn int FMC_isCharFile(const char *path)
 * @brief Checks if a path is a character device.
 * @details This function is a wrapper around the C++ filesystem library assciated function.
 * 
 * @param[in] path The path to check.
 * @return An integer value.
 * @retval 1 if the path is a character device.
 * @retval 0 if the path is not a character device.
 * @retval -1 if an error occured. 
 */
FMC_SHARED int FMC_isCharFile(const char* path);
/**
 * @author Axel PASCON
 * @date 2023
 * @fn int FMC_isSocket(const char *path)
 * @brief Checks if a path is a socket.
 * @details This function is a wrapper around the C++ filesystem library assciated function.
 * 
 * @param[in] path The path to check.
 * @return An integer value.
 * @retval 1 if the path is a socket.
 * @retval 0 if the path is not a socket.
 * @retval -1 if an error occured. 
 */
FMC_SHARED int FMC_isSocket(const char* path);
/**
 * @author Axel PASCON
 * @date 2023
 * @fn int FMC_isFIFO(const char *path)
 * @brief Checks if a path is a FIFO.
 * @details This function is a wrapper around the C++ filesystem library assciated function.
 * 
 * @param[in] path The path to check.
 * @return An integer value.
 * @retval 1 if the path is a FIFO.
 * @retval 0 if the path is not a FIFO.
 * @retval -1 if an error occured. 
 */
FMC_SHARED int FMC_isFIFO(const char* path);
/**
 * @author Axel PASCON
 * @date 2023
 * @fn int FMC_isOther(const char *path)
 * @brief Checks if a path is of an unknown type.
 * @details This function is a wrapper around the C++ filesystem library assciated function.
 * 
 * @param[in] path The path to check.
 * @return An integer value.
 * @retval 1 if the path is of an unknown type.
 * @retval 0 if the path is not of an unknown type.
 * @retval -1 if an error occured. 
 */
FMC_SHARED int FMC_isOther(const char* path);
/**
 * @author Axel PASCON
 * @date 2023
 * @fn int FMC_isEmpty(const char *path)
 * @brief Checks if a directory is empty.
 * @details This function is a wrapper around the C++ filesystem library assciated function.
 * 
 * @param[in] path The path to check.
 * @return An integer value.
 * @retval 1 if the directory is empty.
 * @retval 0 if the directory is not empty.
 * @retval -1 if an error occured. 
 */
FMC_SHARED int FMC_isEmpty(const char *path);
/**
 * @author Axel PASCON
 * @date 2023
 * @fn char* FMC_getCurrentPath(char *path, const size_t size)
 * @brief This function is equivalent to $PWD in bash.
 * @details This function is a wrapper around the C++ filesystem library assciated function.
 * 
 * @param[out] path The memory buffer to store the current path.
 * @param[in] size The size of the memory buffer.
 * @return A pointer to the memory buffer.
 * @retval NULL if an error occured.
 * @retval path The pointer to path after the call if the function succeeded.
 */
FMC_SHARED char *FMC_getCurrentPath(char *path, const size_t size);
/**
 * @author Axel PASCON
 * @date 2023
 * @fn char* FMC_getAbsolutePath(char *path, char *buffer, const size_t size)
 * @brief This function converts a relative path into an absolute one.
 * @details This function is a wrapper around the C++ filesystem library assciated function.
 * 
 * @param[in] path The path to convert.
 * @param[out] buffer The memory buffer to store the absolute path.
 * @param[in] size The size of the memory buffer.
 * @return A pointer to the memory buffer.
 * @retval NULL if an error occured.
 * @retval buffer The pointer to the buffer after the call if the function succeeded.
 */
FMC_SHARED char *FMC_getAbsolutePath(char *path, char *buffer, const size_t size);
// !FMC_dir

#ifdef __cplusplus
}
#endif


#endif // FMC_WRAPPER_H
