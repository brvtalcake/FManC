# **Filesystem API reference**

## **Summary**
- [**Filesystem API reference**](#filesystem-api-reference)
	- [**Summary**](#summary)
	- [**Functions**](#functions)
		- [File type checking](#file-type-checking)
			- [_FMC\_dirExists_](#fmc_direxists)
			- [_FMC\_isDir_](#fmc_isdir)
			- [_FMC\_isRegFile_](#fmc_isregfile)
			- [_FMC\_isCharDevice_](#fmc_ischardevice)
			- [_FMC\_isSocket_](#fmc_issocket)
		- [Directory management](#directory-management)
## **Functions**
---
### File type checking
---
#### _FMC_dirExists_

=== "Function signature"

	``` c
	int FMC_dirExists(const char* restrict path); 
	```
=== "Example 1"
	``` c
	if (FMC_dirExists("test/main.c"))
	{
		FILE *src_file = fopen("test/main.c", "rb");
		// do something with it
	}
	else
	{
		
	}
		// ...
	```
=== "Example 2"
	``` c
	char directory[128] = "C:\\Users\\YourFolder\\";
	if (FMC_dirExists(directory))
	{
		printf("Entering directory %s\n", directory);
		// ...
	}
	else
		// ...
	```

**Parameters**

**_`#!C path`_** : the path whose you want to check the existence. The file can either be a regular file, a directory, or any valid device, socket... Multi-byte caracters are not supported.

**Return value** 

The function returns non-zero value if the path effectively exists, 0 otherwise.

**Description**

You can use this function on any Unix system or Windows. The Windows version uses the Win32 filesystem API and thus does not require any particular compiler. The Unix version uses the usual stat function.

---

#### _FMC_isDir_

=== "Function signature"

	``` c 
	int FMC_isDir(const char* restrict path);
	```
=== "Example of use"
	```c
	if(FMC_isDir("/home/you/random_folder/") == 0) 
	{
		DIR *your_dir;
		struct dirent *entries;
		your_dir = opendir("/home/you/random_folder/");
		while((entries = readdir(your_dir)) != NULL)
		{
			printf("%s\n", entries->d_name);
		}
		closedir(your_dir);
		// ... (1)
	}
	```

	1.	This example is not that usefull by itself since you could have checked `#!C your_dir != NULL` after it has been opened, but the whole interest is the fact that it's a portable and simple way to check for a dir.


**Parameters**

**_`#!C path`_** : the path whose you want to check if it's a directory. Multi-byte caracters are not supported.

**Return value**

The function returns non-zero value if the path effectively exists, 0 if not.

**Description**

You can use this function on any Unix system or Windows. The Windows version uses the Win32 filesystem API and thus does not require any particular compiler. The Unix version uses the usual stat function.

#### _FMC_isRegFile_

=== "Function signature"

	``` c 
	int FMC_isRegFile(const char* restrict path);
	```
=== "Example of use"

	```c
	// To be done
	```

#### _FMC_isCharDevice_

To be done

#### _FMC_isSocket_


### Directory management