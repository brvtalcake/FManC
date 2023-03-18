#include "test_suite.h"
#include <assert.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <wchar.h>

void test_FMC_getOptimalWriteBufferSize()
{
    char opt_buf_size_res[10];
    snprintf(opt_buf_size_res, 10, "%lld", FMC_getOptimalWriteBufferSize("test.txt"));
    FMC_makeMsg(msg_opt_buf_size, 2, "Optimal write buffer size: ", opt_buf_size_res);
    FMC_printBlueText(stderr, msg_opt_buf_size);
    assert(FMC_getOptimalWriteBufferSize("test.txt") > 0);
    assert(FMC_getOptimalWriteBufferSize(NULL) == 0); 
    assert(FMC_getOptimalWriteBufferSize("file_that_doesnt_exist.ext") == 0);
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
    FILE* FILE_file = fopen("./test.txt", "rb");
    assert(FILE_file != NULL);
    assert(fwide(FILE_file, 0) == 0);
    assert(FMC_changeStreamOrientation(FILE_file,"rb", BYTE_ORIENTED) == BYTE_ORIENTED);
    assert(fwide(FILE_file, 0) < 0);
    fclose(FILE_file);

    FMC_File* file = FMC_allocFile("./test.txt", "rb", FMC_mergeFlags(TO_OPEN, GET_ENCODING, GET_SIZE, BYTE_ORIENTED));
    assert(file != NULL);
    off64_t file_size = FMC_getFileSize("./test.txt");
    assert(file_size == 3); // because the UTF-8 BOM is 3 bytes long
    assert(file->fileSize == file_size);
    assert(file->encoding == FMC_getEncoding(file->file));
    FMC_freeFile(file);

    file = FMC_allocFile("./test.txt", "rb", 0U);
    assert(file != NULL);
    assert(file->fileSize == 0);
    assert(!file->file);
    assert(file->encoding == unknown);
    assert(0);
}