#include "build.h"

extern int is_path1_modified_after_path2(const char* const path1, const char* const path2);

int check_if_modified(const char* const file, const char* const target)
{
    if(!PATH_EXISTS(target))
    {
        return 1;
    }
    else if (is_path1_modified_after_path2(file, target))
    {
        return 1;
    }
    return 0;
}

