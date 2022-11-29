#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "analyze.h"

long int countCharInFile(char *filePath)
{
	errno = 0;
	FILE *fil = fopen(filePath, "r");
	if (fil == NULL)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
	}
	long int returned = 0;
	rewind(fil);
	while(feof(fil) == 0)
	{
		if(fgetc(fil) != EOF)
		{
			returned++;
		}
		
	}

	fclose(fil);
	return returned;
}