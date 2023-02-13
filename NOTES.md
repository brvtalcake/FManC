# General notes that I want myself to remind of (especially when it'll come to write documentation the project)

## About paths

- All paths must be specified with a '/' or an escaped '\' after EACH directory. For example :
  - "/something/or/another" will lead the lib to consider that another is a file without extension, even when it's a directory, when using functions like "FMC_extractFilename" or stuffs like that. The proper way then is : "/something/or/another/".
  - The same happens when specifying something like "C:\\Users\\Someone_s__dir".
- Only this set {'/' , '\'} of separators are detected.
- '~' : this character can figure in paths since it's not useful to detect filenames and so on.
- "~somepath/to/file" or "C:Something" are of course not valid paths, even though they are not detected.
