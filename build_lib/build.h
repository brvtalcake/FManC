#ifndef BUILD_H
#define BUILD_H

typedef char** LibDependencies;


/* COMMON */
// ALL
int check_if_modified(const char* const file, const char* const target);
// LINUX
void clean_objs_lin(void);

/* STATIC LIBS */
// LINUX
int build_static_linux(LibDependencies* lib_deps);

// WINDOWS


/* DYNAMIC LIBS */

// LINUX

// WINDOWS



#endif /* BUILD_H */
