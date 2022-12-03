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
	yyin=fopen(char *filePath,"r");

  getFileName(filePath, sname);
  getFileExtension(filePath, sExtension);
  getFilePath(filePath, sPath);
	yyout=fopen(strcat(sPath, strcat(strcat(sName,_),sExtension)),"w");
	yylex();

  if (remove(filePath) != 0)
  {
    fprintf(stderr, "%s\n", strerror(errno));
    return -2;
  }
  if (rename(strcat(sPath, strcat(strcat(sName,_),sExtension)),filePath) != 0)
  {
    return -1;
  }
  return 0;
}