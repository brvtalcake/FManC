# Main ideas

| Ideas | Status|
|:-------------------:|:--:|
| Data Compression    |:x: |
| File management (copy, move, delete, work on file names)    |:x: |
| Encrypt / Decrypt    |:x: |
| Simple work on datas in file (search for words, ...)    |:x: |
| Search for words corresponding to a regex |:x: |
| Implement multithreading for big files |:x: |
| Implement a portable file, encoded strings, ... representation |:x: |
| Locate a file in a folder and subfolders |:x: |
| Convert encoded files |:x: |
| Implement a support for many other file types (for exemple a JSON parser, reading a JPEG and return arrays of RGBA pixels), detecting more kind of files |:x:|
| Manipulate file metadatas    |:x: |
| Manipulate file versionning, syncing, sharing, backup and restore, tagging and labelling |:x: |

---

## How to build theses ideas

### Implement a portable file, encoded strings, ... representation

- [ ] Implement a generic character representation, with metadata related to its encoding, ... .
- [ ] Implement functions to manipulate these characters.

### File management (copy, move, delete, work on file names)

- [ ] Reimplement the previously implemented functions with way more solid basis that the previous representations will provide, and add more simple functions (like moving a file, deleting a file, ...).

### Data Compression

- [ ] Implement a simple algorithm to pack bytes from many files into one single file. These bytes will be packed with their metadata (file name, file size, file type, ...), and each block of file + metadata will be separated by a bunch of bytes that we'll have to determine. This will be the final step of the compression algorithm.
- [ ] Implement an algorithm to compress the files to be archived. This algorithm should be something like BWT + Huffman coding, in a similar way to bzip2. Performing this step before the one above will allow us to compress multiple files in the same time with multithreading.
- [ ] Implement a function to decompress the files from the archive.
