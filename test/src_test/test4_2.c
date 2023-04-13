#include "test_suite.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

void test_FMC_getOptIOBufSize()
{
    char opt_buf_size_res[10];
    snprintf(opt_buf_size_res, 10, "%lld", FMC_getOptIOBufSize("test.txt"));
    FMC_makeMsg(msg_opt_buf_size, 2, "Optimal write buffer size: ", opt_buf_size_res);
    FMC_printBlueText(stderr, msg_opt_buf_size);
    assert(FMC_getOptIOBufSize("test.txt") > 0);
    assert(FMC_getOptIOBufSize(NULL) == 0); 
    assert(FMC_getOptIOBufSize("file_that_doesnt_exist.ext") == 0);
}

void test_FMC_extractFilename()
{
    char file_path[MAX_FNAME_SIZE + MAX_FEXT_SIZE + MAX_FPATH_SIZE] = "/home/axel/Documents/programmation/c/FManC/test/test_builds/lin/test.txt";
    char buffer[MAX_FNAME_SIZE];
    FMC_extractFilename(file_path, buffer, MAX_FNAME_SIZE);
    assert(strcmp(buffer, "test.txt") == 0);
}

void test_FMC_getExtension()
{
    char file_path[MAX_FNAME_SIZE + MAX_FEXT_SIZE + MAX_FPATH_SIZE] = "/home/axel/Documents/programmation/c/FManC/test/test_builds/lin/test.txt";
    char buffer[MAX_FEXT_SIZE];
    FMC_getExtension(file_path, buffer, MAX_FEXT_SIZE);
    assert(strcmp(buffer, ".txt") == 0);
}

void test_FMC_cutFilename()
{
    char file_path[MAX_FNAME_SIZE + MAX_FEXT_SIZE + MAX_FPATH_SIZE] = "/home/axel/Documents/programmation/c/FManC/test/test_builds/lin/test.txt";
    char buffer[MAX_FPATH_SIZE];
    FMC_cutFilename(file_path, buffer, MAX_FPATH_SIZE);
    assert(strcmp(buffer, "/home/axel/Documents/programmation/c/FManC/test/test_builds/lin/") == 0);
}

void test_FMC_FileAPI()
{
    #if !defined(FMC_COMPILING_ON_WINDOWS) // TODO: see how to manage fwide on Windows, since it is not implemented
    FILE* FILE_file = fopen("./test.txt", "rb");
    assert(FILE_file != NULL);
    assert(fwide(FILE_file, 0) == 0);
    assert(FMC_changeStreamOrientation(FILE_file,"rb", BYTE_ORIENTED, "./test.txt") == BYTE_ORIENTED);
    assert(fwide(FILE_file, 0) < 0);
    fclose(FILE_file);
    #endif

    FMC_File* file = FMC_allocFile("./test.txt", "rb", FMC_mergeFlags(TO_OPEN, GET_ENCODING, GET_SIZE, BYTE_ORIENTED));
    assert(file != NULL);
    off64_t file_size = FMC_getFileSize("./test.txt");
    assert(file_size == 3); // because the UTF-8 BOM is 3 bytes long
    assert(file->fileSize == file_size);
    assert(file->encoding == FMC_getEncoding(file->file));
    FMC_freeFile(file);

    file = FMC_allocFile("./test.txt", "rb", 0U);
    assert(file == NULL);
}

void test_FMC_readFile()
{
    assert(FMC_isRegFile("./read_file.txt"));
    FMC_File* file = FMC_allocFile("./read_file.txt", "rb", FMC_mergeFlags(TO_OPEN, GET_ENCODING, GET_SIZE, BYTE_ORIENTED));
    FMC_String* content = FMC_readFile(file);
    assert(content != NULL);
    assert(content->size == 13); // "hello world!"
    char expected_content[] = "hello world!";
    for (uint64_t i = 0; i < content->size; i++)
    {
        assert(FMC_getCharAt(content, i)->comp.byte0 /* because it's utf-8 with only assci characters */ == expected_content[i]);
    }
    FMC_freeStr(content);
    FMC_freeFile(file);
}