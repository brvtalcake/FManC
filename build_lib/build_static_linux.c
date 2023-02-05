
#include "build.h"

#define CFLAGS "-Wall", "-Wextra", "-std=c11", "-pedantic", "-Werror", "-O3"


static int rebuild_everything = 0;
static int built_something = 0;
static char *buff_file = NULL;

static void state_deps_recursively(const char *path)
{
    if (IS_DIR(path)) {
        FOREACH_FILE_IN_DIR(file, path, {
            const char *child = PATH(path, file);
            Cstr temp2 = NOEXT(file);
            buff_file = strcpy(buff_file, "obj/lin/static/");
            buff_file = strcat(buff_file, temp2);
            buff_file = strcat(buff_file, ".o");
            if (!IS_DIR(child) &&  ENDS_WITH(child, ".c") && !rebuild_everything && (!check_for_static_lin_obj(child) || check_if_modified(child, buff_file) || check_if_modified(child, "lib/libFManC.linux.a"))) {
                CMD("gcc", child, CFLAGS, "-c", "-o", buff_file);
                built_something = 1;
            }
            else if (!IS_DIR(child) &&  ENDS_WITH(child, ".h") && !rebuild_everything && (!check_for_static_lin_obj(child) || check_if_modified(child, "lib/libFManC.linux.a")))
            {
                rebuild_everything = 1;
            }
            else if (IS_DIR(child) && !ENDS_WITH(child, ".") && !rebuild_everything) {
                state_deps_recursively(child);
            }
        });
    }
}

static void build_all_objs_recursively(const char *path)
{
    if (IS_DIR(path)) {
        FOREACH_FILE_IN_DIR(file, path, {
            const char *child = PATH(path, file);
            Cstr temp2 = NOEXT(file);
            buff_file = strcpy(buff_file, "obj/lin/static/");
            buff_file = strcat(buff_file, temp2);
            buff_file = strcat(buff_file, ".o");
            if (!IS_DIR(child) &&  ENDS_WITH(child, ".c")) {
                CMD("gcc", child, CFLAGS, "-c", "-o", buff_file);
            }
            else if (IS_DIR(child) && !ENDS_WITH(child, ".")) {
                build_all_objs_recursively(child);
            }
        });
    }
}

int check_for_static_lin_obj(const char* src_file)
{
    char *temp1 = malloc(256*sizeof(char));
    if(!temp1)
    {
        ERROR("Failed to allocate memory at line %d", __LINE__);
        return 2;
    }
    
    Cstr temp2 = NOEXT(src_file);
    temp1 = strcpy(temp1, "obj/lin/static/");
    temp1 = strcat(temp1, temp2);
    temp1 = strcat(temp1, ".o");
    if (PATH_EXISTS(temp1))
    {
        free(temp1);
        return 1;
    }

    free(temp1);
    return 0;
}

static void copy_headers_recursively_lin(const char *path)
{
    if (IS_DIR(path)) {
        FOREACH_FILE_IN_DIR(file, path, {
            const char *child = PATH(path, file);
            buff_file = strcpy(buff_file, "include/");
            buff_file = strcat(buff_file, file);
            if (!IS_DIR(child) && ENDS_WITH(child, ".h") && check_if_modified(child, buff_file)) {
                CMD("cp", child, "include/");
            }
            else if (IS_DIR(child) && !ENDS_WITH(child, ".")) {
                copy_headers_recursively_lin(child);
            }
        });
    }
}

int build_static_linux(void)
{
    built_something = 0;
    rebuild_everything = 0;
    buff_file = malloc(256*sizeof(char));
    if(!buff_file)
    {
        ERROR("Failed to allocate memory at line %d", __LINE__);
        return 1;
    }
    if(!PATH_EXISTS("./lib/libFManC.linux.a"))
    {
        rebuild_everything = 1;
    }
    else
    {
        check_for_state_deps_recursively("src");
    }

    if (rebuild_everything)
    {
        WARN("Rebuilding everything");
        built_something = 1;
        build_all_objs_recursively("src");
    }
    // to be finished : we need to copy headers, and then archive the objects in the newly built lib
    CMD("ar", "-rcs", "lib/libFManC.linux.a", "obj/lin/static/*.o");
    copy_headers_recursively_lin("src");
    

    free(buff_file);
    return built_something;
}

#undef CFLAGS
