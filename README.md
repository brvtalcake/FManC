[![CodeFactor](https://www.codefactor.io/repository/github/brvtalcake/fmanc/badge)](https://www.codefactor.io/repository/github/brvtalcake/fmanc)

# FManC

A portable file manager library in C

## The project

### The goals

The goal of this project is to provide a portable and easy to use library to manage files and their content **in general**, and in a single library. That means that I really want to incorporate a lot of functionnalities in this lib (for more informations about some ideas I had you can take a look at [this file](https://github.com/brvtalcake/FManC/blob/main/ideas.md)).
Another goal is to make UTF-X handling easier, since this is currently something that can be annoying to do in C.

## How to find the documentation

If you want to download a PDF documentation, it's [here](https://github.com/brvtalcake/libfmanc/raw/main/man/refman.pdf).
[Here is the HTML documentation](https://brvtalcake.github.io/FManC/), wich looks better to me.

## Architecture of the repository

### Folder structure

#### The repository is organized as follow

| Folder | Content |
|:------:|:-------:|
| [.github](https://github.com/brvtalcake/FManC/tree/main/.github) | This folder contains the usual workflow files for GitHub actions, and so on. |
| [bin](https://github.com/brvtalcake/FManC/tree/main/bin) | This folder simply contains the Windows DLL (and maybe one day will contain the binary for a CLI app). |
| [third_party_libs](https://github.com/brvtalcake/FManC/tree/main/third_party_libs) | This folder contains the submodules used in the library. Please read the [additionnal README](https://github.com/brvtalcake/FManC/tree/main/third_party_libs). |
| [docs](https://github.com/brvtalcake/FManC/tree/main/docs) | This folder contains the built HTML documentation (as mentionned above). |
| [include](https://github.com/brvtalcake/FManC/tree/main/include) | This folder contains the header files of the library. |
| [lib](https://github.com/brvtalcake/FManC/tree/main/lib) | This folder contains the built library. |
| [man](https://github.com/brvtalcake/FManC/tree/main/man) | This folder contains the built PDF documentation. |
| obj | This folder contains the object files of the library. You probably don't see it, since .gitignore's are still working, as far I know. |
| [src](https://github.com/brvtalcake/FManC/tree/main/src) | This folder contains the source files of the library. This folder is divided into many subfolders. |
| [test](https://github.com/brvtalcake/FManC/tree/main/test) | This folder contains the source files of the unit tests and coverage reports that you may not be able to see (again). |

#### Source code folder structure

**TODO**.

## ToDoList for things other than just continuing the lib development

- [x] Rewrite part of the filesystem API in pure C
- [x] Update these files due to the above TODO : FMC_macros.h, FMC_platform.h, Makefile, (... ?)
- [ ] Make more issue / pull request templates
- [ ] Globally change all the \_\_attribute\_\_((malloc(free_func))) to only \_\_attribute\_\_((malloc))
- [ ] Documenting, as I'm starting to do with Doxygen
- [x] Wrap decls with FMC_BEGING_DECLS / FMC_END_DECLS
- [ ] Print error message when trying to use the C++ wrapped functions in C++, since it's better to simply use the standard functions (or maybe use GCC's visibility attribute)
- [ ] Make use of GCC's symver attribute
- [ ] Support handling symlinks
- [x] Build a better error system to make functions more simple (maybe think about asserting obvious "in" conditions that must be satisfied)
- [ ] Make a header to put all pre-include macro definitions
- [x] Make a real test folder with unit tests
- [x] Let the possibility to disable error messages

## Credits

The doxygen theme I'll use for my documentation is provided by [jothepro](https://github.com/jothepro) and hosted in [this repository](https://github.com/jothepro/doxygen-awesome-css) under the terms of the MIT license.
