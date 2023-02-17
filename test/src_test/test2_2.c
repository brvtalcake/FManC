#include <assert.h>
#include <stdio.h>
#include "test_suite.h"

void test_FMC_getEncoding()
{
    FILE *file1 = fopen("../../plain_text_data/lorem.txt", "rb"); // UTF-8
    FILE *file2 = fopen("../../plain_text_data/empty", "rb"); // EMPTY
    FILE *file3 = fopen("../../plain_text_data/test5_0", "rb"); // UTF-16 BE
    FILE *file4 = fopen("../../plain_text_data/test5_2", "rb"); // UTF-8
    FILE *file5 = fopen("../../plain_text_data/rand_5040", "rb"); // UTF-8 with BOM
    assert(FMC_getEncoding(file1) == utf8);
    assert(FMC_getEncoding(file2) == unknown);
    assert(FMC_getEncoding(file3) == utf16_be);
    assert(FMC_getEncoding(file4) == utf8);
    assert(FMC_getEncoding(file5) == utf8_bom);
    assert(FMC_getEncoding(NULL) == error);

    fclose(file1);
    fclose(file2);
    fclose(file3);
    fclose(file4);
    fclose(file5);
}

void test_FMC_checkEncodingFlag()
{
    assert(FMC_checkEncodingFlag(ASCII) == ascii);
    assert(FMC_checkEncodingFlag(UTF8) == utf8);
    assert(FMC_checkEncodingFlag(UTF8_BOM) == utf8_bom);
    assert(FMC_checkEncodingFlag(UTF16_LE) == utf16_le);
    assert(FMC_checkEncodingFlag(UTF16_BE) == utf16_be);
    assert(FMC_checkEncodingFlag(UTF32_LE) == utf32_le);
    assert(FMC_checkEncodingFlag(UTF32_BE) == utf32_be);
    assert(FMC_checkEncodingFlag(UNKNOWN) == unknown);

    assert(FMC_checkEncodingFlag(1) == FMC_checkEncodingFlag(UTF8));
    assert(FMC_checkEncodingFlag(2) == FMC_checkEncodingFlag(UTF8_BOM));
    assert(FMC_checkEncodingFlag(4) == FMC_checkEncodingFlag(UTF16_LE));
    assert(FMC_checkEncodingFlag(8) == FMC_checkEncodingFlag(UTF16_BE));
    assert(FMC_checkEncodingFlag(16) == FMC_checkEncodingFlag(UTF32_LE));
    assert(FMC_checkEncodingFlag(32) == FMC_checkEncodingFlag(UTF32_BE));
    assert(FMC_checkEncodingFlag(64) == FMC_checkEncodingFlag(ASCII));
    assert(FMC_checkEncodingFlag(128) == FMC_checkEncodingFlag(UNKNOWN));
}