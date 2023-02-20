[![CodeFactor](https://www.codefactor.io/repository/github/brvtalcake/fmanc/badge)](https://www.codefactor.io/repository/github/brvtalcake/fmanc)

# FManC

A portable file manager library in C

## The project

### Why did I start this project ?

I'm currently with no formation, since I previously decided to stop my studies in mathematics to switch to computer science. That's pretty much the whole thing that motivated me to start this little project : I have time and I want to learn more about computer science in general. Moreover, if I manage to make something great, it'll remain a great reusable ressource for future projects, even if it's just for me.

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

## ToDoList

- [ ] Implement the dir API in C++, and write a C wrapper to make it available in C
- [ ] Update these files due to the above TODO : FMC_macros.h, FMC_platform.h, Makefile, (... ?)
- [ ] Make more issue / pull request templates
- [ ] Documenting, as I'm starting to do with Doxygen
- [x] Make a real test folder with unit tests
- [x] Let the possibility to disable error messages

## Credits

The doxygen theme I'll use for my documentation is provided by [jothepro](https://github.com/jothepro) and hosted in [this repository](https://github.com/jothepro/doxygen-awesome-css) under the terms of the MIT license.
