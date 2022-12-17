#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include <locale.h>
#include <limits.h>
#include <stddef.h>
#include <stdint.h>
#include <wchar.h>
#include "analyze.h"
#include "fileMan.h"

SHARED size_t countCharInFile(char *filePath)
{
	errno = 0;
	setlocale(LC_ALL, "fr_FR.UTF8");
	FILE *fil = fopen(filePath, "r, ccs=UTF-8");
	if (fil == NULL)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		return -1;
	}
	size_t returned = 0;
	rewind(fil);
	while (fgetwc(fil) != WEOF)
	{
		returned++;
	}

	fclose(fil);
	return returned;
}




SHARED stringOccurrences *init_StringOccurences(size_t sizeOfString)
{
	
	long long int *position = malloc(sizeof(long long int));
	*position = -1;
	stringOccurrences *returned = malloc(sizeof(stringOccurrences));
	returned->pos = position;
	returned->charCount = sizeOfString;

	return returned;
}

SHARED void free_stringOccurrences(stringOccurrences *toBeDeleted)
{
	free(toBeDeleted->pos);
	free(toBeDeleted);
}


SHARED stringOccurrences *searchStringInFile(char *filePath, char *toSearch) 
{
	errno = 0;
	wchar_t toSearchW[strlen(toSearch)+1];

	if (setlocale(LC_ALL, "fr_FR.UTF8") == NULL)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		return NULL;
	}


	if (mbstowcs(toSearchW, toSearch, strlen(toSearch)) == (size_t) - 1)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		return NULL;
	}

	

	toSearchW[strlen(toSearch)] = L'\0';

	if (countCharInFile(filePath) > LLONG_MAX || wcslen(toSearchW) > SIZE_MAX)
	{
		getFileName(filePath, fErrorName);
		fprintf(stderr, "Error : your file named \"%s\" contains too much characters\n", fErrorName);
		return NULL;
	}


	stringOccurrences *occurencesToSearch = init_StringOccurences(wcslen(toSearchW));

	
	FILE *fil = fopen(filePath, "r, ccs=UTF-8");
	if (fil == NULL)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		free_stringOccurrences(occurencesToSearch);
		return NULL;
	}
	rewind(fil);


	unsigned int cpt_occ = 0;
	wchar_t temp[wcslen(toSearchW)+1];
	for (size_t i = 0; i < wcslen(toSearchW)+1; ++i)
	{
		temp[i] = '\0';
	}
	size_t cpt = 0;
	
	long long int cpt2 = 0;
	cpt2 = ftell(fil);
	wint_t temp2 = fgetwc(fil);
	while(temp2 != WEOF)
	{
		fseek(fil, cpt2, SEEK_SET);
		while(cpt <= wcslen(toSearchW))
		{
			temp[cpt] = fgetwc(fil);
			
			if (temp[cpt] != toSearchW[cpt] || temp[cpt] == WEOF)
			{
				if (temp[cpt] == toSearchW[cpt])
				{
					cpt++;
				}
				break;
			}
			else
			{
				cpt++;
			}
		}

		if (cpt == wcslen(toSearchW))
		{
			cpt_occ++;
			occurencesToSearch->pos = realloc(occurencesToSearch->pos, cpt_occ*sizeof(long long));
			*(occurencesToSearch->pos + cpt_occ - 1) = cpt2;
		}
		cpt = 0;
		for (size_t i = 0; i < wcslen(toSearchW)+1; ++i)
		{
			temp[i] = '\0';
		}
		fseek(fil, cpt2, SEEK_SET);
		temp2 = fgetwc(fil);
		cpt2 = ftell(fil);
	}
	if (cpt_occ == 0)
	{
		occurencesToSearch->pos = realloc(occurencesToSearch->pos, sizeof(long long));
		*(occurencesToSearch->pos) = -1;
	}
	else
	{
		occurencesToSearch->pos = realloc(occurencesToSearch->pos, (cpt_occ + 1)*sizeof(long long));
		*(occurencesToSearch->pos + cpt_occ) = -1;
	}

	fclose(fil);
	return occurencesToSearch;
}


SHARED int replaceStringInFile(char *filePath, char *toReplaceString, char *toAddString) 
{
	stringOccurrences *toReplaceOccurrences = searchStringInFile(filePath, toReplaceString);
	errno = 0;
	wchar_t toAdd[strlen(toAddString)+1];
	wchar_t toReplace[strlen(toReplaceString)+1];
	
	if (toReplaceOccurrences == NULL || *(toReplaceOccurrences->pos) == -1)
	{
		return 3;
	}
	
	if (setlocale(LC_ALL, "fr_FR.UTF8") == NULL)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		return -3;
	}

	if (mbstowcs(toAdd, toAddString, strlen(toAddString)) == (size_t) - 1)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		return -4;
	}

	if (mbstowcs(toReplace, toReplaceString, strlen(toReplaceString)) == (size_t) - 1)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		return -4;
	}

	toAdd[strlen(toAddString)] = L'\0';
	toReplace[strlen(toReplaceString)] = L'\0';

	FILE *filToR = fopen(filePath, "r, ccs=UTF-8");
	if (filToR == NULL)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		return -1;
	}
	rewind(filToR);

	
	getFilePath(filePath, sFilePath);
	

	getFileName(filePath, sFileName);
	if (sFileName[0] == '\0')
	{
		return -2;
	}
	getFileExtension(filePath, sFileExt);
	if (sFileExt[0] == '\0')
	{
		return -2;
	}

	FILE *filToW = NULL;
	char *replaced = "replaced";
	char *tempName = malloc((MAX_FNAME_SIZE + MAX_FPATH_SIZE + MAX_FEXT_SIZE)*sizeof(char));
	*tempName = '\0';
	if(sFilePath[0] != '\0')
	{
		tempName = strcat(tempName, sFilePath);
		tempName = strcat(tempName, replaced);
		tempName = strcat(tempName, sFileExt);
		filToW = fopen(tempName, "w+, ccs=UTF-8");
	}
	else
	{
		tempName = strcat(tempName, replaced);
		tempName = strcat(tempName, sFileExt);
		filToW = fopen(tempName, "w+, ccs=UTF-8");
	}
	

	if (filToW == NULL)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		return -1;
	}
	rewind(filToW);
	
	int cpt = 0;
	int old_cpt = 0;
	wchar_t temp = L'\0';
	wchar_t temp2 = fgetwc(filToR);

	
	while(temp2!=WEOF) 
	{
		ungetwc(temp2, filToR);
		while(*(toReplaceOccurrences->pos + cpt) != -1 && *(toReplaceOccurrences->pos + cpt) >= 0)
		{
			if (ftell(filToR) == *(toReplaceOccurrences->pos + cpt))
			{
				for (size_t i = 0; i < wcslen(toAdd); ++i)
				{
					if(fputwc(toAdd[i], filToW) != toAdd[i])
					{
						fprintf(stderr, "ERR :%s\n", strerror(errno));
						return 1;
					}
				}
				cpt++;
				for (size_t i = 0; i<toReplaceOccurrences->charCount; ++i)
				{
					if(fgetwc(filToR) == WEOF)
						break;
				}
			}

			if (temp2!=WEOF && old_cpt == cpt)
			{
				temp = fgetwc(filToR);
				if(fputwc(temp, filToW) != temp)
				{
					fprintf(stderr, "ERR :%s\n", strerror(errno));
					return 1;
				}
			}
			else
			{
				old_cpt++;
			}
			

		}

		if (temp!=WEOF)
		{
			temp = fgetwc(filToR);
			if(fputwc(temp, filToW) != temp)
			{
				fprintf(stderr, "ERR :%s\n", strerror(errno));
				return 1;
			}
		}
		temp2 = fgetwc(filToR);
	}
	
	fclose(filToR);
	fclose(filToW);



	if (remove(filePath) != 0)
	{
		fprintf(stderr, "ERR :%s\n", strerror(errno));
		return 2;
	}
	else if (rename(tempName, filePath) != 0)
	{
		fprintf(stderr, "ERR :%s\n", strerror(errno));
		return 2;
	}
	
	

	


	free(tempName);	
	free_stringOccurrences(toReplaceOccurrences);

	return 0;
}