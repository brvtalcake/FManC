/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * \defgroup lex_file Flex source files
 * @{
 */

/**
 * @file     noComments.l
 *
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * 
 */

/**
 * @}
 */

%option noyywrap

%{
#include <string.h>
#include <errno.h>
#include "../fileMan.h"
#include "lex_yy.h"
/* remove C comments */

/* replace each comment with a single blank */

extern int fileno(FILE *);      /* avoid gcc warning */
%}

%x String Char Comment CPPComment

%%

\"      /* "String" */ ECHO; BEGIN( String);

\'      /* 'Char' */ ECHO; BEGIN( Char);

"/*"    /* comment */ BEGIN( Comment);

"//"    /* C++ comment */ BEGIN( CPPComment);

.|\n    /* everything else */ ECHO;

<String>{
  \\.           /* escape sequence */ ECHO;
  [^"]          /* not "quote" */ ECHO;
  \"            /* end of "String" */ ECHO; BEGIN( INITIAL);
}

<Char>{
  \\.           /* escape sequence */ ECHO;
  [^']          /* not 'quote' */ ECHO;
  \'            /* end of 'Char' */ ECHO; BEGIN( INITIAL);
}

<Comment>{
  [^*]*         /* not a '*' */
  "*"+[^/]      /* '*'s not followed by '/' */
  "*"+"/"       /* end of Comment */ putchar( ' '); BEGIN(INITIAL);
}

<CPPComment>{
  .*            /* to end of line */
  \n            ECHO; BEGIN( INITIAL);
}

%%

void (*jj_junk)(int,char *) = yyunput; /* avoid gcc warnings */
int (*jj2_junk)(void) = input;

int deleteCStyleComments(char *filePath)
{
    errno = 0;
  yyin=fopen(filePath,"r");

    getFileName(filePath, sName);
    getFileExtension(filePath, sExtension);
    getFilePath(filePath, sPath);
    char *filToR = strcat(sPath, strcat(strcat(sName,"_"),sExtension));
  yyout=fopen(filToR,"w");
  yylex();
    fclose(yyin);
    fclose(yyout);
    if (remove(filePath) != 0)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        return -2;
    }
    if (rename(filToR,filePath) != 0)
    {
        fprintf(stderr, "%s\n", strerror(errno));
        return -1;
    }
    return 0;
}