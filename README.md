# libfmanc
File manager in C
## IMPORTANT NOTE
There is still a lot to do to make this lib usable. Moreover, keep in mind that I'm just writing this lib to make easier the development of an extension of C, including :
- structs mutators (kind of "methods")
- new types : dictionnaries, lists, trees, graphs, vectors.
## ToDoList
- [x] Secure the library and change the returned type of functions that might dysfunction, instead of just exiting the program (I think it's good enough now)
- [ ] Finish some function that I partially developped or just declared
- [ ] Adding features to develop my C "dialect", I would say (still don't really know how to call it and what extension I should use). Next things to implement should be : 
	- A function that translates declared mutators into the equivalent function stored in the program
	- A function that copy the source code from a .cmx or .hmx into a .c or .h file without the mutators and return the position (and the name of the file) where should be the equivalent function declaration, etc... (that will also be the great moment to see which coding restriction will be needed to do it in an easier way)
	- A function that puts the equivalent function into the the new source file code
	- (I'm actually realizing that I should really create a new repo for it)
- [ ] Documenting, as I'm starting to do with Doxygen 
- [ ] Find a way to put the documentation online
- [ ] Make a test folder with examples 
- [ ] Make a src folder in docs with the documented source code and keep the one in the project root undocumented
- [ ] Create a shared lib in a bin folder and potentially make a command-line app associated to the lib in bin folder