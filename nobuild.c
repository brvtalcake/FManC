#define NOBUILD_IMPLEMENTATION
#include "build_lib/build.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*
void build_tool(const char *tool)
{
    Cstr tool_path = PATH("tools", tool);
#ifndef _WIN32
    CMD("cc", CFLAGS, "-o", NOEXT(tool_path), tool_path);
#else
    CMD("cl.exe", "/Fe.\\tools\\", tool_path);
#endif
}

void build_tools(void)
{
    FOREACH_FILE_IN_DIR(tool, "tools", {
        if (ENDS_WITH(tool, ".c")) {
            build_tool(tool);
        }
    });
}

void run_example(const char *example)
{
    Cstr example_path = PATH("examples", example);
#ifndef _WIN32
    CMD("cc", CFLAGS, "-o", NOEXT(example_path), example_path);
#else
    CMD("cl.exe", "/Fe.\\examples\\", example_path);
#endif
    CMD(NOEXT(example_path));
}

void run_examples(void)
{
    FOREACH_FILE_IN_DIR(example, "examples", {
        if (ENDS_WITH(example, ".c")) {
            run_example(example);
        }
    });
}


void print_chain(const Chain *chain)
{
    INFO("input: %s", chain->input_filepath);
    INFO("output: %s", chain->output_filepath);
    FOREACH_ARRAY(Cmd, cmd, chain->cmds, {
        INFO("cmd: %s", cmd_show(*cmd));
    });
} */


int main(int argc, char **argv)
{
    GO_REBUILD_URSELF(argc, argv);

    if (argv[1] && strcmp(argv[1], "win") == 0)
    {
        // build_static_windows() ? INFO("\x1b[32;1mWindows build successful\x1b[0m") : INFO("\x1b[34;1mFiles didn't change\x1b[0m");
    }
    else if (argv[1] && strcmp(argv[1], "lin") == 0)
    {
        build_static_linux() ? INFO("\x1b[32;1mLinux build successful\x1b[0m") : INFO("\x1b[34;1mFiles didn't change\x1b[0m");
    }
    else
    {
        INFO("Usage: ./nobuild win|lin");
    }
    
    
    return 0;

    
}
