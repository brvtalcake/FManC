#ifndef BUILD_H
#define BUILD_H



int check_if_modified(const char* const file, const char* const target);

int build_static_linux(void);

int check_for_static_lin_obj(const char* file);



#endif /* BUILD_H */
