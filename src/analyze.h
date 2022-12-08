#ifndef ANALYZE_H
#define ANALYZE_H 

typedef struct 
{
	size_t charCount;
	long *pos;
}stringOccurrences;

long int countCharInFile(char *filePath);
stringOccurrences *init_StringOccurences(size_t sizeOfString);
void free_stringOccurrences(stringOccurrences *toBeDeleted);
stringOccurrences *searchStringInFile(char *filePath, char *toSearch);
void replaceStringInFile(char *filePath, char *toReplaceString, char *toAddString);


#endif