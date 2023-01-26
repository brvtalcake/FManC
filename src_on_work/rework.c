#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <wchar.h>
#include "rework.h"

typedef int found_bs_n;
typedef int found_bs_t;
typedef int found_bs_r_bs_n;

int copyFileWithoutTabAndLineBreak_remade(char *sourceFilePath, char *pathToCopy) //not finished. TODO : change the return value
{
	errno = 0;
    if (sourceFilePath == NULL)
    {
        fprintf(stderr, "Error :%s\n", strerror(errno));
        return -1;
    }
    else if (strlen(sourceFilePath)> 100)
    {
        fprintf(stderr, "Error : The path provided is too long\n");
        return -2;
    }

    FILE *sourceFile = fopen(sourceFilePath, "r, ccs=UTF-8");
    if (sourceFile == NULL)
    {
        fprintf(stderr, "Error :%s\n", strerror(errno));
        return -3;
    }
    rewind(sourceFile);
    found_bs_n n = 0;
    found_bs_t t = 0;
    found_bs_r_bs_n rn = 0;
    wint_t *content_to_rewrite = NULL;
    content_to_rewrite = realloc(content_to_rewrite, sizeof(wint_t));
    *content_to_rewrite = '\0';
    wint_t buff_ch[2] = {'\0'};
    size_t lengthOf_content = 0;
    while((typeof(WEOF))(buff_ch[0] = fgetwc(sourceFile)) != WEOF)
    {
        buff_ch[1] = fgetwc(sourceFile); // be aware to check for WEOF
        if(buff_ch[0] == L'\r')
        {
            if ((typeof(WEOF)) buff_ch[1] != WEOF && buff_ch[1] == L'\n')
            {
                rn = 1;
            }
        }
        else if (buff_ch[0] == L'\n')
        {
            n = 1;
        }
        else if (buff_ch[0] == L'\t')
        {
            t = 1;
        }
        else 
        {
            t = 0;
            n = 0;
            rn = 0;
        }
        if (rn == 0 && n == 0 && t == 0)
        {
            
            lengthOf_content++;
            content_to_rewrite = realloc(content_to_rewrite, sizeof(wint_t) * (lengthOf_content+1));
            if (content_to_rewrite == NULL)
            {
                fprintf(stderr, "Error :%s\n", strerror(errno));
                fclose(sourceFile);
                return -4;
            }
            *(content_to_rewrite + lengthOf_content-1) = buff_ch[0];
            *(content_to_rewrite + lengthOf_content) = '\0';
            ungetwc(buff_ch[1],sourceFile);
        }
        else if (rn == 1 && (typeof(WEOF))(buff_ch[0] = fgetwc(sourceFile)) != WEOF)
        {
            buff_ch[1] = fgetwc(sourceFile); 
        }
        
    }
    
    fclose(sourceFile);
    FILE *copyFile = NULL;
    if (pathToCopy != NULL)
    {
        copyFile = fopen(pathToCopy, "w, ccs=UTF-8");
    }
    else
    {
        char *tmp_str = (char*) malloc(sizeof(char) * (strlen(sourceFilePath) + 10));
        tmp_str = strcpy(tmp_str, "copied_"); 
        tmp_str = strcat(tmp_str, sourceFilePath);
        copyFile = fopen(tmp_str, "w, ccs=UTF-8");
        free(tmp_str);
    }
    rewind(copyFile);
    if (copyFile == NULL)
    {
        free(content_to_rewrite);
        fprintf(stderr, "Error :%s\n", strerror(errno));
        return -5;
    }
    if (fputws(content_to_rewrite, copyFile) == EOF)
    {
        fprintf(stderr, "Error :%s\n", strerror(errno));
        free(content_to_rewrite);
        fclose(copyFile);
        return -6;
    }
    fclose(copyFile);
    free(content_to_rewrite);
    return 0;
}