#ifndef FILEMAN_H
#define FILEMAN_H 


#define MAX_FEXT_SIZE 50
#define getFileExtension(sourceFileName, extension) char extension[MAX_FEXT_SIZE]; fgetFileExtension(sourceFileName, extension)


typedef struct 
{
	char *name;
}fileExtension;

void copyFileWithoutTabAndLineBreak(char *sourceFilePath, char **pathToCopy); // copied file will be named like <sourceFile name>_copied
void fgetFileExtension(char *sourceFileName, char *extension);

#endif