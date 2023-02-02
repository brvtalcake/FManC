#include "build.h"
#include "../nobuild.h"

static void make_obj_static_linux(int *built_something)
{

}

void clean_objs_lin(void)
{
    FOREACH_FILE_IN_DIR(file, ".",
    {
        if(!IS_DIR(file))
        {
            if(ENDS_WITH(file, ".o"))
            {
                CMD("rm", file);
            }
        }
    });
}


int build_static_linux(LibDependencies* lib_deps)
{
    clean_objs_lin();
    int built_something = 0;
    int rebuild_everything = 0;
    char *buff_file = malloc(256*sizeof(char));
    if(!buff_file)
    {
        ERROR("Failed to allocate memory at line %d", __LINE__);
        return 1;
    }

    FOREACH_FILE_IN_DIR(file, "./src/",
    {
        if(!IS_DIR(file) && !rebuild_everything)
        {
            if(ENDS_WITH(file, ".c") && !rebuild_everything)
            {
                buff_file = strcpy(buff_file, "./src/");
                buff_file = strcat(buff_file, file);
                if(check_if_modified(buff_file, "./lib/libFManC.linux.a") && !rebuild_everything)
                {
                    built_something = 1;
                    CMD("gcc", buff_file, "-c");
                }
            }
            else if(ENDS_WITH(file, ".h") && !rebuild_everything)
            {
                buff_file = strcpy(buff_file, "./src/");
                buff_file = strcat(buff_file, file);
                if(check_if_modified(buff_file, "./lib/libFManC.linux.a") && !rebuild_everything)
                {
                    rebuild_everything = 1;
                }
            }
        }
    });

    FOREACH_FILE_IN_DIR(file, "./src/third_party/",
    {
        if(!IS_DIR(file) && !rebuild_everything)
        {
            if(ENDS_WITH(file, ".c") && !rebuild_everything)
            {
                buff_file = strcpy(buff_file, "./src/third_party/");
                buff_file = strcat(buff_file, file);
                if(check_if_modified(buff_file, "./lib/libFManC.linux.a") && !rebuild_everything)
                {
                    built_something = 1;
                    CMD("gcc", buff_file, "-c");
                }
            }
            else if(ENDS_WITH(file, ".h") && !rebuild_everything)
            {
                buff_file = strcpy(buff_file, "./src/third_party/");
                buff_file = strcat(buff_file, file);
                if(check_if_modified(buff_file, "./lib/libFManC.linux.a") && !rebuild_everything)
                {
                    rebuild_everything = 1;
                }
            }
        }
    });

    if(rebuild_everything)
    {
        built_something = 1;
        FOREACH_FILE_IN_DIR(file, "./src/third_party/",
        {
            if(!IS_DIR(file))
            {
                if(ENDS_WITH(file, ".c"))
                {
                    buff_file = strcpy(buff_file, "./src/third_party/");
                    buff_file = strcat(buff_file, file);
                    CMD("gcc", buff_file, "-c");
                }
            }
        });

        FOREACH_FILE_IN_DIR(file, "./src/",
        {
            if(!IS_DIR(file))
            {
                if(ENDS_WITH(file, ".c"))
                {
                    buff_file = strcpy(buff_file, "./src/");
                    buff_file = strcat(buff_file, file);
                    CMD("gcc", buff_file, "-c");
                }
            }
        });
    }
    clean_objs_lin();
    free(buff_file);
    return built_something;
}