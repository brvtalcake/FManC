# libfmanc
File manager in C
## IMPORTANT NOTE
There is still a lot to do to make this lib usable. Moreover, keep in mind that I'm just writing this lib to make easier the development of an extension of C (that will be implemented as a translator from my extended-C to standard C), including :
- structs mutators (kind of "methods")
- new types : dictionnaries, lists, trees, graphs, vectors.


However, if you want to download a PDF documentation, it's [here](https://github.com/brvtalcake/libfmanc/raw/main/docs/latex/refman.pdf).
For the HTML one, in local, just download the folder html in docs and open index.html in your favorite browser.
## ToDoList
- [x] Secure the library and change the returned type of functions that might dysfunction, instead of just exiting the program (I think it's good enough now)
- [x] Finish some function that I partially developped or just declared
- [ ] Adding features to develop my C "dialect", I would say (still don't really know how to call it and what extension I should use). Next things to implement should be : 
	- A function that translates declared mutators into the equivalent function stored in the program
	- A function that copy the source code from a .cmx or .hmx into a .c or .h file without the mutators and return the position (and the name of the file) where should be the equivalent function declaration, etc... (that will also be the great moment to see which coding restriction will be needed to do it in an easier way)
	- A function that puts the equivalent function into the the new source file code
	- (I'm actually realizing that I should really create a new repo for it)
- [ ] Documenting, as I'm starting to do with Doxygen 
- [ ] Find a way to put the documentation online (?)
- [x] Make a test folder 
- [ ] Put examples in it
- [x] Make a src folder in docs with the documented source code and keep the one in the project root undocumented
- [x] Create a shared lib in a bin folder and potentially make a command-line app(not for now) associated to the lib in bin folder
- [ ] Make the lib available for UNIX users
