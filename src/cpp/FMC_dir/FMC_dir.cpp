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

#if __cplusplus < 201703L
    #error "The contents of <filesystem> are available only with C++17 or later."
#endif

#include "FMC_dir.hpp"
#include <filesystem>
#include <string.h>
#include <string>

namespace fs = std::filesystem;

int FMC_dirExists_(const char *path) 
{
    return fs::exists(path);
}

int FMC_isDir_(const char *path) 
{
    if(fs::exists(path))
    {
        return fs::is_directory(path);
    }
    else return -1;
}

int FMC_isRegFile_(const char *path) 
{
    if(fs::exists(path))
    {
        return fs::is_regular_file(path);
    }
    else return -1;
}

int FMC_isSymLink_(const char *path) 
{
    if (fs::exists(path)) 
    {
        return fs::is_symlink(path);
    }
    else return -1;
}

int FMC_isBlock_(const char* path)
{
    if (fs::exists(path))
    {
        return fs::is_block_file(path);
    }
    else return -1;
}

int FMC_isCharFile_(const char* path)
{
    if (fs::exists(path))
    {
        return fs::is_character_file(path);
    }
    else return -1;
}

int FMC_isSocket_(const char* path)
{
    if (fs::exists(path))
    {
        return fs::is_socket(path);
    }
    else return -1;
}

int FMC_isFIFO_(const char* path)
{
    if (fs::exists(path))
    {
        return fs::is_fifo(path);
    }
    else return -1;
}

int FMC_isOther_(const char* path)
{
    if (fs::exists(path))
    {
        return fs::is_other(path);
    }
    else return -1;
}

/*
char *FMC_readSymlink_(char *path_sym, const char * path, const int size)
{
    memset(path_sym, 0, size);
    fs::path p(path);
    if (is_symlink(p) && exists(p) && size) >= fs::read_symlink(p).string().size()) // to be changed 
    {
        fs::path target = fs::read_symlink(p);
        strcpy(path_sym, target.c_str());
    }
    return path_sym;
} */

int FMC_isEmpty_(const char *path) 
{
    if(fs::exists(path))
    {
        return fs::is_empty(path);
    }
    else return -1;
}

/*int FMC_createDir_(const char *path) 
{
    return fs::create_directory(path);
}*/

char *FMC_getCurrentPath_(char *path, const size_t size)
{
    std::string s = fs::current_path().string();
    if (size >= s.length()+1) 
    {
        memset(path, 0, size);
        strcpy(path, fs::current_path().c_str());
        if (strrchr(path, '/') != NULL) strcat(path, "/");
        else if (strrchr(path, '\\') != NULL) strcat(path, "\\");
        else return NULL;
        return path;
    }
    else return NULL;
}

char *FMC_getAbsolutePath_(char *path, char *buffer, const size_t size)
{
    
    if(fs::exists(path) && size > fs::absolute(path).string().length())
    {
        memset(buffer, 0, size);
        strncpy(buffer, fs::absolute(path).c_str(), fs::absolute(path).string().length());
        if (strrchr(path, '/') != NULL) strcat(buffer, "/");
        else if (strrchr(path, '\\') != NULL) strcat(buffer, "\\");
        else return NULL;
        return buffer;
    }
    else return NULL;
}