#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "fileMan.h"

SHARED char *copyFileWithoutTabAndLineBreak(char *sourceFilePath, char **pathToCopy) //not finished 
{

	errno = 0;
	getFileName(sourceFilePath, sourceFileName);
	getFileExtension(sourceFilePath, sourceFileExtension);
	
	FILE *sourceFile = fopen(sourceFilePath, "r");

	if (sourceFile == NULL)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		return NULL;
	}
	rewind(sourceFile);
	char *copiedName = NULL;
	if (pathToCopy == NULL)
	{
		copiedName = strcat(strcat(sourceFileName,"_copied"), sourceFileExtension); //modify here
	}
	else
	{
		copiedName = *pathToCopy;
	}

	FILE *copiedFile = fopen(copiedName, "w");
	if (copiedFile == NULL)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		fclose(sourceFile);
		return NULL;
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
	char *returnedName = NULL;
	int i = 0;
	while(sourceFileName[i] != '\0')
	{
		*(returnedName + i) = sourceFileName[i];
		i++;
	}
	*(returnedName + i) = '\0';
	fclose(copiedFile);
	fclose(sourceFile);
	return returnedName;
}

SHARED void fgetFileExtension(char *sourceFilePath, char *extension)
{
	if (strlen(sourceFilePath) > MAX_FEXT_SIZE + MAX_FPATH_SIZE + MAX_FNAME_SIZE)
	{
		fprintf(stderr, "\nError : Full path is too big\n");
		return;
	}
	int cpt = strlen(sourceFilePath);
	char pt = *(sourceFilePath + cpt);
	
	
	while((pt != '.') && (cpt >= 0))
	{
		cpt--;
		pt = *(sourceFilePath + cpt);
	}
	if (cpt < 0)
	{
		fprintf(stderr, "\nError : incorrect file path\n");
	}
	else
	{
		char res[strlen(sourceFilePath)-cpt+1];
		for (size_t i = cpt; i < strlen(sourceFilePath); ++i)
		{
			res[i - cpt] = *(sourceFilePath + i);
		}
		res[strlen(sourceFilePath)-cpt] = '\0';
		for (size_t i = 0; i < strlen(res); ++i)
		{
			*(extension + i) = res[i];
		}
		*(extension + strlen(res)) = '\0';
		
	}
}

SHARED void fgetFileName(char *sourceFilePath, char *fileName)
{
	if (strlen(sourceFilePath) > MAX_FEXT_SIZE + MAX_FPATH_SIZE + MAX_FNAME_SIZE)
	{
		fprintf(stderr, "\nError : Full path is too big\n");
		return;
	}
	int cpt = strlen(sourceFilePath);
	char pt = *(sourceFilePath + cpt);
	
	while(cpt >= 0)
	{
		cpt--;
		pt = *(sourceFilePath + cpt);
		if (pt == '/' || pt == '\\')
		{
			break;
		}
	}
	cpt++;
	if (cpt < 0)
	{
		fprintf(stderr, "\nError : incorrect file path\n");
	}
	else
	{
		char res[strlen(sourceFilePath)-cpt+1];
		for (size_t i = cpt; i < strlen(sourceFilePath); ++i)
		{
			res[i - cpt] = *(sourceFilePath + i);
		}
		res[strlen(sourceFilePath)-cpt] = '\0';
		for (size_t i = 0; i < strlen(res); ++i)
		{
			*(fileName + i) = res[i];
		}
		*(fileName + strlen(res)) = '\0';
		cpt = strlen(fileName) - 1;
		while(fileName[cpt] != '.')
		{
			fileName[cpt] = '\0';
			cpt--;
		}
		fileName[cpt] = '\0';
	}
}

SHARED void fgetFilePath(char *sourceFilePath, char *filePath)
{
	if (strlen(sourceFilePath) > MAX_FEXT_SIZE + MAX_FPATH_SIZE + MAX_FNAME_SIZE)
	{
		fprintf(stderr, "\nError : Full path is too big\n");
		return;
	}
	int cpt = strlen(sourceFilePath);
	char pt = *(sourceFilePath + cpt);
	
	while(cpt >= 0)
	{
		cpt--;
		pt = *(sourceFilePath + cpt);
		if (pt == '/' || pt == '\\')
		{
			break;
		} 
	}
	
	if (cpt < 0)
	{
		return;
	}

	else
	{
		char res[cpt+1];
		for (size_t i = 0; i < (size_t)cpt; ++i) // cpt >= 0 anyway so we can actually do this to avoid this useless gcc -Wextra warning
		{
			res[i] = *(sourceFilePath + i);
		}
		res[cpt + 1] = '\0';
		for (size_t i = 0; i < strlen(res); ++i)
		{
			*(filePath + i) = res[i];
		}
		if (pt == '/')
		{
			*(filePath + strlen(res)-1) = '/';
		}
		else
		{
			*(filePath + strlen(res)-1) = '\\';
		}
		*(filePath + strlen(res)) = '\0';
		
	}
}