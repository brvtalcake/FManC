#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "fileMan.h"

void copyFileWithoutTabAndLineBreak(char *sourceFilePath, char **pathToCopy)
{

	errno = 0;

	FILE *sourceFile = fopen(sourceFilePath, "r");

	if (sourceFile == NULL)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	rewind(sourceFile);

	FILE *copiedFile = fopen("fromage.txt", "w");
	if (copiedFile == NULL)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		fclose(sourceFile);
		exit(EXIT_FAILURE);
	}
	rewind(copiedFile);

	while(fgetc(sourceFile) != EOF)
	{
		fseek(sourceFile, -1, SEEK_CUR);
		if (fgetc(sourceFile) != '\n')
		{
			fseek(sourceFile, -1, SEEK_CUR);
			if (fgetc(sourceFile) != '\t')
			{
				fseek(sourceFile, -1, SEEK_CUR);
				fputc(fgetc(sourceFile), copiedFile);
			}
		}
	}

	fclose(copiedFile);
	fclose(sourceFile);
}

void fgetFileExtension(char *sourceFileName, char *extension)
{
	int cpt = strlen(sourceFileName);
	char pt = *(sourceFileName + cpt);
	
	
	while((pt != '.') && (cpt > 0))
	{
		cpt--;
		pt = *(sourceFileName + cpt);
	}
	if (cpt <= 0)
	{
		fprintf(stderr, "\nError : incorrect file name\n");
	}
	else
	{
		char res[strlen(sourceFileName)-cpt+1];
		for (int i = cpt; i < strlen(sourceFileName); ++i)
		{
			res[i - cpt] = *(sourceFileName + i);
		}
		res[strlen(sourceFileName)-cpt] = '\0';
		for (int i = 0; i < strlen(res); ++i)
		{
			*(extension + i) = res[i];
		}
		*(extension + strlen(res)) = '\0';
		
	}
}