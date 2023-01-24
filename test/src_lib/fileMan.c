#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include "fileMan.h"

SHARED char *copyFileWithoutTabAndLineBreak(char *sourceFilePath, char *pathToCopy) //not finished. TODO : change the return value
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
	char *copiedName = (char*) malloc((strlen(pathToCopy)+10)*sizeof(char));
	
	if(copiedName == NULL) return copiedName;
	if (pathToCopy == NULL)
	{
		copiedName = strcat(strcat(sourceFileName,"_copied"), sourceFileExtension); 
	}
	else
	{
		copiedName = strcpy(copiedName, pathToCopy);
	}
	if(copiedName == NULL) return copiedName;
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
	static char returnedName[MAX_FEXT_SIZE+MAX_FNAME_SIZE+MAX_FPATH_SIZE] = {'\0'}; // find a way to modify this
	int i = 0;
	while(sourceFileName[i] != '\0' && (size_t) i < strlen(sourceFileName))
	{
		*(returnedName + i) = sourceFileName[i];
		i++;
	}
	*(returnedName + i) = '\0';

	fclose(copiedFile);
	fclose(sourceFile);
	free(copiedName);
	return returnedName;
}

SHARED void fgetFileExtension(const char* const sourceFilePath, char *extension)
{
	if (strlen(sourceFilePath) > MAX_FEXT_SIZE + MAX_FPATH_SIZE + MAX_FNAME_SIZE)
	{
		fprintf(stderr, "\nError : Full path is too big\n");
		return;
	}
	int cpt = strlen(sourceFilePath);
	char pt = *(sourceFilePath + cpt);
	
	
	while((pt != '.') && (cpt >= 0) && (pt != '/') && (pt != '\\'))
	{
		cpt--;
		if (cpt>=0)
		{
			pt = *(sourceFilePath + cpt);
		}
		else break;
	}
	if (cpt < 0)
	{
		fprintf(stderr, "\nError : incorrect file path\n");
		return;
	}
	else if (pt == '/' || pt == '\\')
	{
		fprintf(stderr, "\nError : incorrect file path\n");
		return;
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

SHARED void fgetFileName(const char* const sourceFilePath, char *fileName)
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
		if (cpt>=0)
		{
			pt = *(sourceFilePath + cpt);
		}
		else break;
		if (pt == '/' || pt == '\\' || pt == '~')
		{
			break;
		}
	}
	cpt++;
	if (cpt < 0 || (size_t) cpt == strlen(sourceFilePath))
	{
		fprintf(stderr, "\nError : incorrect file path\n");
		return;
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
		char *tmp_recov = (char*) malloc((strlen(fileName)+10)*sizeof(char));
		int tmp_recov_char_num = strlen(fileName) + 1;

		tmp_recov = strncpy(tmp_recov, fileName, tmp_recov_char_num);
		if (tmp_recov == NULL)
		{
			fprintf(stderr, "\nInternal problem into the lib\n");
			free(tmp_recov);
			return;
		}
		else
		{
			while(cpt >= 0 && fileName[cpt] != '.')
			{
				fileName[cpt] = '\0';
				cpt--;
			}
			if (cpt < 0)
			{
				fileName = strncpy(fileName, tmp_recov, tmp_recov_char_num);
				fileName[tmp_recov_char_num-1] = '\0';
			}
			else fileName[cpt] = '\0';
			
		}
		free(tmp_recov);
		
	}
}

SHARED void fgetFilePath(const char* const sourceFilePath, char *filePath)
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
		if (cpt>=0)
		{
			pt = *(sourceFilePath + cpt);
		}
		else break;
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
		for (size_t i = 0; i < (size_t)cpt; ++i) // cpt >= 0 anyway so we can actually do this cast to avoid this useless gcc -Wextra warning
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