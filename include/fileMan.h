#ifndef FILEMAN_H
#define FILEMAN_H 


#define MAX_FEXT_SIZE 50
#define MAX_FNAME_SIZE 256
#define getFileExtension(sourceFileName, extension) char extension[MAX_FEXT_SIZE]; fgetFileExtension(sourceFileName, extension)
#define getFileName(sourceFilePath, name) char name[MAX_FNAME_SIZE]; fgetFileName(sourceFilePath, name)


typedef struct 
{
	char *name;
}fileExtension;

void copyFileWithoutTabAndLineBreak(char *sourceFilePath, char **pathToCopy); // copied file will be named like <sourceFile name>_copied
void fgetFileExtension(char *sourceFileName, char *extension);
void fgetFileName(char *sourceFilePath, char *fileName);

#endif