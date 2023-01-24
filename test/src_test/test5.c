#include "../src_lib/fmanc.h"
#include <assert.h>
#include "test_suite.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <metalang99.h>

#define SOURCE_FILE_X(i) ML99_EVAL(ML99_call(ML99_stringify, ML99_cat(v(../../plain_text_data/test5_), v(i))))
#define DEST_FILE_X(i) ML99_EVAL(ML99_call(ML99_stringify, ML99_cat3(v(../../tmp/test5_), v(i), v(_tmp))))
#define SOURCE_FILE_NAME_X(i) ML99_EVAL(ML99_call(ML99_stringify, ML99_cat(v(test5_), v(i))))

#define TEST_X(i)                                                                                    \
    FILE *f##i = fopen(SOURCE_FILE_X(i), "rb");                                                      \
                                                                                                     \
    fseek(f##i, 0, SEEK_END);                                                                        \
    fsize = ftell(f##i);                                                                             \
    fseek(f##i, 0, SEEK_SET);                                                                        \
                                                                                                     \
    buf = (char*) realloc(buf, fsize + 1);                                                           \
    assert(buf!=NULL);                                                                               \
    fread(buf, fsize, 1, f##i);                                                                      \
    fclose(f##i);                                                                                    \
                                                                                                     \
    buf[fsize] = '\0';                                                                               \
                                                                                                     \
    for (size_t j = 0; j < fsize; j++)                                                               \
    {                                                                                                \
        if ((buf_ch = buf[j]) == '\t' || (buf_ch = buf[j]) == '\n')                                  \
        {                                                                                            \
            cpt_tab_lb++;                                                                            \
        }                                                                                            \
    }                                                                                                \
                                                                                                     \
    assert(cpt_tab_lb >= 1);                                                                         \
    cpt_tab_lb = 0;                                                                                  \
    return_ = copyFileWithoutTabAndLineBreak(SOURCE_FILE_X(i), DEST_FILE_X(i));                      \
    assert(!strcmp(return_, SOURCE_FILE_NAME_X(i)));                                                 \
                                                                                                     \
    f##i = fopen(DEST_FILE_X(i), "rb");                                                              \
                                                                                                     \
    fseek(f##i, 0, SEEK_END);                                                                        \
    fsize = ftell(f##i);                                                                             \
    fseek(f##i, 0, SEEK_SET);                                                                        \
                                                                                                     \
    buf = (char*) realloc(buf, fsize + 1);                                                           \
    assert(buf!=NULL);                                                                               \
    fread(buf, fsize, 1, f##i);                                                                      \
    fclose(f##i);                                                                                    \
                                                                                                     \
    buf[fsize] = '\0';                                                                               \
                                                                                                     \
    for (size_t j = 0; j < fsize; j++)                                                               \
    {                                                                                                \
        if ((buf_ch = buf[j]) == '\t' || (buf_ch = buf[j]) == '\n')                                  \
        {                                                                                            \
            cpt_tab_lb++;                                                                            \
        }                                                                                            \
    }                                                                                                \
                                                                                                     \
    assert(cpt_tab_lb == 0);                                                                         \
    cpt_tab_lb = 0   


void test_copyFileWithoutTabAndLineBreak(void)
{
    size_t cpt_tab_lb = 0;
    char buf_ch = 0;
    char *buf = (char*) malloc(sizeof(char));
    char *return_ = NULL;
    size_t fsize = 0;
    
    TEST_X(0);
    TEST_X(1);
    TEST_X(2);



    free(buf);
}
