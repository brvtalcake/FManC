#ifndef ANALYZE_H
#define ANALYZE_H 

typedef struct 
{
	unsigned int charCount;
	long *pos;
}stringOccurrences;

long int countCharInFile(char *filePath);
stringOccurrences *init_StringOccurences(const unsigned int sizeOfString);
void free_stringOccurrences(stringOccurrences *toBeDeleted);
stringOccurrences *searchStringInFile(char *filePath, const char *toSearch);
void replaceStringInFile(char *filePath, char *toReplace, char *toAdd);


#endif