#include "test_suite.h"
#include <assert.h>
#include <string.h>
#include <stdlib.h>

void test_FMC_dirExists()
{
    assert(FMC_dirExists("./main.c") == 0);
    assert(FMC_dirExists("../../src_test/test.c") == 1);
    assert(FMC_dirExists(" ") == 0);
    assert(FMC_dirExists("./") == 1);
}

void test_FMC_isDir()
{
    assert(FMC_isDir("./main.c") == 0);
    assert(FMC_isDir("../../src_test/test.c") == 0);
    assert(FMC_isDir(" ") == 0);
    assert(FMC_isDir("./") == 1);
}

void test_FMC_isRegFile()
{
    assert(FMC_isRegFile("./main.c") == 0);
    assert(FMC_isRegFile("../../src_test/test.c") == 1);
    assert(FMC_isRegFile(" ") == 0);
    assert(FMC_isRegFile("./") == 0);
}

void test_FMC_isSymLink()
{
    assert(FMC_isSymLink("./main.c") == 0);
    assert(FMC_isSymLink("../../src_test/test.c") == 0);
    assert(FMC_isSymLink(" ") == 0);
    assert(FMC_isSymLink("../../../bin/libFManC_x86_64.so") == 1);
}

void test_FMC_getCurrentPath()
{
    char path[1024];
    FMC_getCurrentPath(path, 1024);
    assert(strncmp(path, "/home/axel/Documents/programmation/c/FManC/test/test_builds/lin/", strlen("/home/axel/Documents/programmation/c/FManC/test/test_builds/lin/") + 1) == 0);
    assert(FMC_isDir(path) == 1);

    char nopath[1];
    assert(FMC_getCurrentPath(nopath, 1) == NULL);
}

void test_FMC_getAbsolutePath()
{
    char buffer[1024];
    FMC_getAbsolutePath("", buffer, 1024);
    assert(strncmp(buffer, "/home/axel/Documents/programmation/c/FManC/test/test_builds/lin/", strlen("/home/axel/Documents/programmation/c/FManC/test/test_builds/lin/") + 1) == 0);
    assert(FMC_isDir(buffer) == 1);

    FMC_getAbsolutePath("../../..", buffer, 1024);
    assert(strncmp(buffer, "/home/axel/Documents/programmation/c/FManC/test/test_builds/lin/../../../", strlen("/home/axel/Documents/programmation/c/FManC/test/test_builds/lin/../../../") + 1) == 0);
    assert(FMC_isDir(buffer) == 1);
}

void test_FMC_mkDir_rmDir()
{
    FMC_mkDir("../../safe_dir_test_folder/created_dir");
    assert(FMC_isDir("../../safe_dir_test_folder/created_dir"));
    FMC_mkDir("../../safe_dir_test_folder/created_dir/created_dir2");
    assert(FMC_isDir("../../safe_dir_test_folder/created_dir/created_dir2"));
    FILE* file = fopen("../../safe_dir_test_folder/created_dir/created_dir2/file.txt", "w");
    assert(file != NULL);
    fclose(file);
    FMC_printBrightBlueText(stderr, "\nPlease confirm to continue the tests\n");
    FMC_rmDir("../../safe_dir_test_folder/created_dir/created_dir2", FMC_mergeFlags(RM_DIR_RECURSIVE, CONFIRMATION));
    assert(!FMC_isDir("../../safe_dir_test_folder/created_dir/created_dir2"));
    FMC_mkDir("../../safe_dir_test_folder/created_dir/created_dir2");
    FMC_rmDir("../../safe_dir_test_folder/created_dir", FMC_mergeFlags(RM_DIR_RECURSIVE, NO_CONFIRMATION));
    assert(!FMC_isDir("../../safe_dir_test_folder/created_dir"));

}