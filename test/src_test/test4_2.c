#include "test_suite.h"
#include <assert.h>
#include <string.h>

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
    FMC_File* file = FMC_allocFile("./test.txt", "rb", FMC_mergeFlags(TO_OPEN, GET_ENCODING, GET_SIZE, BYTE_ORIENTED));
    off64_t file_size = FMC_getFileSize("./test.txt");
    fprintf(stderr, "File orientation: %d\n", file->orientation);
    fprintf(stderr, "Encoding values:\n%d\t%d", (int)FMC_getEncoding(file->file), file->encoding);
    assert(file_size == 0);
    assert(file->fileSize == file_size);
    assert(file->encoding == FMC_getEncoding(file->file));
}