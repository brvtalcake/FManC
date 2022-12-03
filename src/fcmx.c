#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "fileMan.h"

/*
int deleteCStyleComments(char *filePath) // unfinished
{
	errno = 0;
	stringOccurrences *occ_ft = searchStringInFile(filePath, "//");
	stringOccurrences *occ_st = searchStringInFile(filePath, "/*"); 

	FILE *sFil = fopen(filePath, "r");
	if (sFil == NULL)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}

	getFileName(filePath, sName);
	getFileExtension(filePath, sExtension);
	getFilePath(filePath, sPath);

	FILE *tFil = fopen(strcat(sPath, strcat(strcat(sName,_),sExtension)), "w");
	if (tFil == NULL)
	{
		fprintf(stderr, "%s\n", strerror(errno));
		return -1;
	}


	fclose(fil);
	free_stringOccurrences(occ_ft);
	free_stringOccurrences(occ_st);
	return 0;
}
*/