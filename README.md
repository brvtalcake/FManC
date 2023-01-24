[![CodeFactor](https://www.codefactor.io/repository/github/brvtalcake/fmanc/badge)](https://www.codefactor.io/repository/github/brvtalcake/fmanc)

# libFManC 
File manager in C 


## IMPORTANT NOTE
There is still a lot to do to make this lib usable, or at least to make it interesting and with enough interesting content. But before all I really want to organize the repo, with a perfect structure, so that'll be more easy to develop it. 

<!--- Moreover, keep in mind that I'm just writing this lib to make easier the development of an extension of C (that will be implemented as a translator from my extended-C to standard C), including :
- structs mutators (kind of "methods")
- new types : dictionnaries, lists, trees, graphs, vectors.
--->

However, if you want to download a PDF documentation, it's [here](https://github.com/brvtalcake/libfmanc/raw/main/man/refman.pdf).
[Here is the HTML documentation](https://brvtalcake.github.io/FManC/), wich looks better to me.


## ToDoList
<!---
- [ ] Adding features to develop my C "dialect", I would say (still don't really know how to call it and what extension I should use). Next things to implement should be : 
	- A function that translates declared mutators into the equivalent function stored in the program
	- A function that copy the source code from a .cmx or .hmx into a .c or .h file without the mutators and return the position (and the name of the file) where should be the equivalent function declaration, etc... (that will also be the great moment to see which coding restriction will be needed to do it in an easier way)
	- A function that puts the equivalent function into the the new source file code
	- (I'm actually realizing that I should really create a new repo for it)
--->
- [ ] Fix the problem of tests not working in github workflow (although they're working on my computer). Check if it a LF/CRLF problem. Maybe add a .gitattributes to fix this
- [ ] Documenting, as I'm starting to do with Doxygen 
- [x] Find a way to put the documentation online (?) (didn't know github pages were existing)
- [ ] Rename test folder as example and put actual exemples in it
- [ ] Make a real test folder 
- [x] Make the lib available for UNIX users
- [ ] Let the possibility to define the locale
- [ ] Let the possibility to disable error messages 
<!---
(by defining an extern variable in fmanc.h)
--->

## Credits
The doxygen theme I'll use for my documentation is provided by [jothepro](https://github.com/jothepro) and hosted in [this repository](https://github.com/jothepro/doxygen-awesome-css) under the terms of the MIT license.