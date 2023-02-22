# Filesystem API reference

## **Summary**
- [Functions](#functions)
	- [FMC_dirExists](#fmc_direxists)
	- [FMC_isDir](#fmc_isdir)
## **Functions**
---
### _FMC_dirExists_

=== "Function signature"

	``` c
	int FMC_dirExists(const char *path); 
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
		system(/* insert a command here to do whatever you want */);
	}
	else
		// ...
	```

**Parameters**

**_`#!C path`_** : the path whose you want to check the existence. The file can either be a regular file, a directory, or any valid device, socket... Multi-byte caracters are not supported.

**Return value** 

The function returns 1 if the path effectively exists, 0 otherwise.

**Description**

This function is a small wrapper around the _[std::filesystem C++ library](https://en.cppreference.com/w/cpp/filesystem)_. This function may be rewritten in pure C in the future.

---

### _FMC_isDir_

=== "Function signature"

	``` c 
	int FMC_isDir(const char *path);
	```
=== "Example 1"
	```c
	if(FMC_isDir("/home/you/random_folder/") == 0) // (1)
	{
		DIR *your_dir;
		struct dirent *entries;
		your_dir = opendir("/home/you/random_folder/");
		while((entries = readdir(your_dir)) != NULL)
		{
			printf("%s\n", entries->d_name);
		}
		closedir(your_dir);
		// ... (2)
	}
	```

	1.	Do not write something like `#!C if(!FMC_isDir("./your/dir"))`, because it can return -1 when the path doesn't exist, for example.
	2.	This example is not that usefull by itself since you could have checked `#!C your_dir != NULL` after it has been opened, but the whole interest is the fact that it's a portable and simple way to check for a dir.


**Parameters**

**_`#!C path`_** : the path whose you want to check if it's a directory. Multi-byte caracters are not supported.

**Return value**

The function returns 1 if the path effectively exists, 0 if not, and -1 if the directory doesn't exist or if an error occured.

**Description**

This function is a small wrapper around the _[std::filesystem C++ library](https://en.cppreference.com/w/cpp/filesystem)_. This function may be rewritten in pure C in the future.