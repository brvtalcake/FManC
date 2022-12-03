#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <stdbool.h>
#include "analyze.h"
#include "fileMan.h"

long int countCharInFile(char *filePath)
{
	errno = 0;
	FILE *fil = fopen(filePath, "r");
	if (fil == NULL)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		exit(EXIT_FAILURE);
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


stringOccurrences *init_StringOccurences(const unsigned int sizeOfString)
{
	stringOccurrences *returned = malloc(sizeof(stringOccurrences));
	returned->pos = malloc(sizeof(long));
	*(returned->pos) = -1;
	returned->charCount = sizeOfString;

	return returned;
}

void free_stringOccurrences(stringOccurrences *toBeDeleted)
{
	free(toBeDeleted->pos);
	free(toBeDeleted);
}

stringOccurrences *searchStringInFile(char *filePath, const char *toSearch)
{
	stringOccurrences *occurencesToSearch = init_StringOccurences(strlen(toSearch));
	occurencesToSearch->charCount = strlen(toSearch);
	errno = 0;
	FILE *fil = fopen(filePath, "r");
	if (fil == NULL)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	rewind(fil);

	unsigned int cpt_occ = 0;
	char temp[strlen(toSearch)];
	for (int i = 0; i < strlen(toSearch); ++i)
	{
		temp[i] = ' ';
	}
	unsigned int cpt = 0;
	fpos_t *cpt2 = NULL;
	fgetpos(fil, cpt2);

	while(fgetc(fil) != EOF)
	{
		fgetpos(fil, cpt2);
		fseek(fil, -1, SEEK_CUR);
		while(cpt < strlen(toSearch))
		{
			temp[cpt] = (char)fgetc(fil);
			if (temp[cpt] != toSearch[cpt] || temp[cpt] == EOF)
			{
				break;
			}
			else
				cpt++;
		}

		if (cpt == strlen(toSearch))
		{
			cpt_occ++;
			occurencesToSearch->pos = realloc(occurencesToSearch->pos, cpt_occ*sizeof(long));
			*(occurencesToSearch->pos + cpt_occ - 1) = ftell(fil) - strlen(toSearch);
		}
		cpt = 0;
		for (int i = 0; i < strlen(toSearch); ++i)
		{
			temp[i] = ' ';
		}
		fsetpos(fil, cpt2);
	}
	if (cpt_occ == 0)
	{
		occurencesToSearch->pos = realloc(occurencesToSearch->pos, sizeof(long));
		*(occurencesToSearch->pos) = -1;
	}
	else
	{
		occurencesToSearch->pos = realloc(occurencesToSearch->pos, (cpt_occ + 1)*sizeof(long));
		*(occurencesToSearch->pos + cpt_occ) = -1;
	}

	fclose(fil);
	return occurencesToSearch;
}

void replaceStringInFile(char *filePath, char *toReplace, char *toAdd)
{
	stringOccurrences *toReplaceOccurrences = searchStringInFile(filePath, toReplace);
	errno = 0;
	
	FILE *filToR = fopen(filePath, "r");
	if (filToR == NULL)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	rewind(filToR);

	FILE *filToW = fopen("replaced.txt", "w+");
	if (filToW == NULL)
	{
		fprintf(stderr, "Error :%s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	rewind(filToW);
	
	int cpt = 0;
	int old_cpt = 0;
	int temp = 0;
	while(fgetc(filToR)!=EOF)
	{
		fseek(filToR, -1, SEEK_CUR);
		while(*(toReplaceOccurrences->pos + cpt) != -1 && *(toReplaceOccurrences->pos + cpt) >= 0)
		{
			if (ftell(filToR) == *(toReplaceOccurrences->pos + cpt))
			{
				for (int i = 0; i < strlen(toAdd); ++i)
				{
					if(fputc(toAdd[i], filToW) != (int)toAdd[i])
					{
						fprintf(stderr, "ERR :%s\n", strerror(errno));
						exit(EXIT_FAILURE);
					}
				}
				cpt++;
				if(fseek(filToR, toReplaceOccurrences->charCount - 1, SEEK_CUR) != 0)
				{
					fprintf(stderr, "ERR :%s\n", strerror(errno));
					exit(EXIT_FAILURE);

				}
			}
			if (fgetc(filToR)!=EOF && old_cpt == cpt)
			{
				if(fseek(filToR, -1, SEEK_CUR) != 0)
				{
					fprintf(stderr, "ERR :%s\n", strerror(errno));
					exit(EXIT_FAILURE);

				}
				temp = fgetc(filToR);
				if(fputc(temp, filToW) != temp)
				{
					fprintf(stderr, "ERR :%s\n", strerror(errno));
					exit(EXIT_FAILURE);
				}
			}
			else
			{
				old_cpt++;
			}
			

			
		}

		if (fgetc(filToR)!=EOF)
		{
			if(fseek(filToR, -1, SEEK_CUR) != 0)
			{
				fprintf(stderr, "ERR :%s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
			temp = fgetc(filToR);
			if(fputc(temp, filToW) != temp)
			{
				fprintf(stderr, "ERR :%s\n", strerror(errno));
				exit(EXIT_FAILURE);
			}
		}

	}

	
	fclose(filToR);
	fclose(filToW);
	free_stringOccurrences(toReplaceOccurrences);
	
}