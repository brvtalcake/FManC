/**
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * \defgroup fmanc_CSRC Core C source code
 * @{
 */



/**
 * @file 	   fileMan.c
 *
 * @brief      These functions are made to do operate simple operation on files or file names, when there is no neee to analyze something like orccurrences, ...
 *
 * @author     Axel PASCON (a.k.a. brvtalcake)
 * @date       2022
 * 
 */


/**
 * @}
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "fileMan.h"

char *copyFileWithoutTabAndLineBreak(char *sourceFilePath, char **pathToCopy) //not finished 
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
		copiedName = strcat(strcat(sourceFileName,"_copied"), sourceFileExtension);
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
	char *returnedName;
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

void fgetFileName(char *sourceFilePath, char *fileName)
{
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
		for (int i = cpt; i < strlen(sourceFilePath); ++i)
		{
			res[i - cpt] = *(sourceFilePath + i);
		}
		res[strlen(sourceFilePath)-cpt] = '\0';
		for (int i = 0; i < strlen(res); ++i)
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

void fgetFilePath(char *sourceFilePath, char *filePath)
{
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
		fprintf(stderr, "\nError : incorrect file path\n");
	}
	else
	{
		char res[cpt+1];
		for (int i = 0; i < cpt; ++i)
		{
			res[i] = *(sourceFilePath + i);
		}
		res[cpt + 1] = '\0';
		for (int i = 0; i < strlen(res); ++i)
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