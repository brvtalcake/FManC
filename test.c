/* This file contains a bunch of personnal tests with third-party libs */
#include <stdio.h>
#include <stdint.h>
/*
void func2(char *str) {
    printf("Hello %s!\n", str);
}

void func3(char *str1, char *str2) {
    printf("Hello %s %s!\n", str1, str2);
}

void func4(char* str1, char* str2, char* str3) {
    printf("Hello %s %s %s!\n", str1, str2, str3);
}

#define func(x,...) _Generic((x), \
    char*: )


int print_uint128(__int128_t n) {
  if (n == 0)  return printf("0\n");

  char str[40] = {0}; // log10(1 << 128) + '\0'
  char *s = str + sizeof(str) - 1; // start at the end
  while (n != 0) {
    if (s == str) return -1; // never happens

    *--s = "0123456789"[n % 10]; // save last digit
    n /= 10;                     // drop it
  }
  return printf("%s\n", s);
}

__attribute__((constructor(101))) void init() {
    printf("init\n");
}

__attribute__((constructor(102))) void init2() {
    printf("init2\n");
}

__attribute__((destructor(102))) void fini3() {
    printf("fini\n");
}
__attribute_warn_unused_result__ int fini() {
    printf("fini\n");
    return 0;
}
#ifndef FMC_ACCESS
        #if __has_attribute(access) 
            #define FMC_ACCESS(access_type, position) __attribute__((access(access_type, position)))
        #else
            #define FMC_ACCESS(access_type, position) void
        #endif // FMC_ACCESS     
    #endif // FMC_ACCESS
FMC_ACCESS(read_only, 1) void printf_nb(int *a) {
    printf("printf_nb %d\n", *a);
}

#ifndef FMC_ALIAS_FUNC
        #define FMC_ALIAS_FUNC(func_name, aliased) __attribute__((alias(#aliased))) __attribute__((copy(aliased))) __typeof__(aliased) func_name
    #endif // FMC_ALIAS_OF
FMC_ALIAS_FUNC(fini2, fini);

int main()
{
    func(void, void);
    func("world", void);
    func(1, 2);
    return 0;
}


*/


/*
 * demo.c
 *
 *  Created on: 2017-09-14
 *      Author: sboehler
 */



/*
void foo_void(void)
{
    puts("void");
}
void foo_int(int c)
{
    printf("int: %d\n", c);
}
void foo_char(char c)
{
    printf("char: %c\n", c);
}
void foo_double(double c)
{
    printf("double: %.2f\n", c);
}
void foo_double_int(double c, int d)
{
    printf("double: %.2f, int: %d\n", c, d);
}
void foo_double_char(double c, char d)
{
    printf("double: %.2f, char: %c\n", c, d);
}
void foo_char_char(char c, char d)
{
    printf("char: %c, char: %c\n", c, d);
}*/
/*
#define foo(...) SELECT(__VA_ARGS__)(__VA_ARGS__)
*/
/*
#define SELECT(...) CONCAT(SELECT_, NARG(__VA_ARGS__))(__VA_ARGS__)
#define CONCAT(X, Y) CONCAT_(X, Y)
#define CONCAT_(X, Y) X ## Y

#define SELECT_0() foo_void
#define SELECT_1(_1) _Generic ((_1), \
        int: foo_int,                \
        char: foo_char,              \
        double: foo_double           \
)
#define SELECT_2(_1, _2) _Generic((_1), \
        double: _Generic((_2), int: foo_double_int , char: foo_double_char), \
        char: foo_char_char                               \
)

#define ARGN(...) ARGN_(__VA_ARGS__)
#define ARGN_(_0, _1, _2, N, ...) N

#define NARG(...) ARGN(__VA_ARGS__ COMMA(__VA_ARGS__) 3, 2, 1, 0)
#define HAS_COMMA(...) ARGN(__VA_ARGS__, 1, 1, 0)

#define SET_COMMA(...) ,

#define COMMA(...) SELECT_COMMA             \
(                                           \
        HAS_COMMA(__VA_ARGS__),             \
        HAS_COMMA(__VA_ARGS__ ()),          \
        HAS_COMMA(SET_COMMA __VA_ARGS__),   \
        HAS_COMMA(SET_COMMA __VA_ARGS__ ()) \
)

#define SELECT_COMMA(_0, _1, _2, _3) SELECT_COMMA_(_0, _1, _2, _3)
#define SELECT_COMMA_(_0, _1, _2, _3) COMMA_ ## _0 ## _1 ## _2 ## _3

#define COMMA_0000 ,
#define COMMA_0001 
#define COMMA_0010 ,
#define COMMA_0011 ,
#define COMMA_0100 ,
#define COMMA_0101 ,
#define COMMA_0110 ,
#define COMMA_0111 ,
#define COMMA_1000 ,
#define COMMA_1001 ,
#define COMMA_1010 ,
#define COMMA_1011 ,
#define COMMA_1100 ,
#define COMMA_1101 ,
#define COMMA_1110 ,
#define COMMA_1111 ,




#define PP_NARG(...) \
         PP_NARG_(__VA_ARGS__,PP_RSEQ_N())
#define PP_NARG_(...) \
         PP_ARG_N(__VA_ARGS__)
#define PP_ARG_N( \
          _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, \
         _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, \
         _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, \
         _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, \
         _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, \
         _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, \
         _61,_62,_63,N,...) N
#define PP_RSEQ_N() \
         63,62,61,60,                   \
         59,58,57,56,55,54,53,52,51,50, \
         49,48,47,46,45,44,43,42,41,40, \
         39,38,37,36,35,34,33,32,31,30, \
         29,28,27,26,25,24,23,22,21,20, \
         19,18,17,16,15,14,13,12,11,10, \
         9,8,7,6,5,4,3,2,1,0

#include <metalang99.h>

#define overload(func,...) \
    ML99_EVAL(ML99_variadicsForEach)

#define make_list(...) ML99_call(make_list, v(__VA_ARGS__))
#define make_list_IMPL(...) ML99_list(v(__VA_ARGS__))

#define make_list_from_tuple(...) ML99_call(make_list_from_tuple, v(__VA_ARGS__))
#define make_list_from_tuple_IMPL(...) ML99_call(make_list,ML99_untuple(v((__VA_ARGS__))))

#define compare(x,y) ML99_call(compare, v(x), v(y))
#define compare_IMPL(x,y) ML99_natEq(v(x),v(y))

#define take_2nd(list) ML99_call(take_2nd, v(list))
#define take_2nd_IMPL(list) ML99_listGet(v(1), v(list))

#define check_ident_eq(x,y) ML99_call(iden, v(x), v(y))

#define TAKE_2ND_IMPL(_1, _2, ...) v(_2)
#define TAKE_2ND(_1, _2, ...) ML99_call(TAKE_2ND, _1, _2, __VA_ARGS__)

#define foo(...) \

*/

#ifndef FMC_DEFER
    #define FMC_DEFER(stmt) \
    void func_##__LINE__(void) { stmt; }; \
    \
        __attribute__((cleanup(func_##__LINE__))) int ____##__LINE__
#endif // FMC_DEFER
#define FMC_STRINGIZE_MACROS
    #define FMC_STRINGIZE10(x) #x
    #define FMC_STRINGIZE9(x) FMC_STRINGIZE10(x)
    #define FMC_STRINGIZE8(x) FMC_STRINGIZE9(x)
    #define FMC_STRINGIZE7(x) FMC_STRINGIZE8(x)
    #define FMC_STRINGIZE6(x) FMC_STRINGIZE7(x)
    #define FMC_STRINGIZE5(x) FMC_STRINGIZE6(x)
    #define FMC_STRINGIZE4(x) FMC_STRINGIZE5(x)
    #define FMC_STRINGIZE3(x) FMC_STRINGIZE4(x)
    #define FMC_STRINGIZE2(x) FMC_STRINGIZE3(x)
    #define FMC_STRINGIZE(x) FMC_STRINGIZE2(x)

    #define DECL_METHOD(name, ret, ...) \
        ret (*name)(__VA_ARGS__)

    #define INIT_STRUCT_METHOD(method, associated_function) \
        .method = associated_function

    #define INIT_STRUCT(field) \
        {.field1 = field, \
        INIT_STRUCT_METHOD(method, &return_field), \
        INIT_STRUCT_METHOD(method2, &return_int) }

typedef struct mystruct
{
    int field1;
    DECL_METHOD(method, int, struct mystruct self, int);
    DECL_METHOD(method2, int, struct mystruct self, int);
} mystruct;

int return_field(mystruct self, int a)
{
    return self.field1;
}

int return_int(mystruct self, int a)
{
    return a;
}
int main(int argc, char** argv)
{
//    foo();
//    foo(7);
//    foo(10.12);
//    foo(12.10, 7);
//    foo((char)'s');
//    foo(12.10, (char)'s');
//    foo((char)'s', (char)'b');
   // printf("%d\n", TAKE_2ND(1,2,3,6,9));
//   __typeof__("ciao") a = "ciao";

    //FMC_DEFER(printf("ciao\n"));
    mystruct s = INIT_STRUCT(10);
    printf("%d\n%d\n%s\n%s\n", s.method(s, 2), s.method2(s, 2), FMC_STRINGIZE(typeof(int (struct mystruct self))), FMC_STRINGIZE(typeof(typeof(int (struct mystruct self))*)));
    return 0;
    //ML99_EVAL(ML99_call(ML99_if, ML99_boolEq(TAKE_2ND(1,2,3,4,5,6), v(2)), v(printf("empty")), v(printf("not empty"))));
}

/*
ML99_EVAL(ML99_call(TAKE_2ND, v(1), v(2), v(3), v(4), v(5), v(6)))

ML99_EVAL(TAKE_2ND(v(1), v(2), v(3), v(4), v(5), v(6)))

#define list1 make_list(1,2,3,4,5,6)

ML99_EVAL(ML99_call(ML99_listLen,make_list((1,2,3,4,5,6), (9,5,4,2,8,4))))

ML99_EVAL(ML99_call(take_2nd, make_list((0,2,4,9,8),(543,68,2,16),(1,2,3,4,5,6))))

ML99_EVAL(compare(1,2))
ML99_EVAL(compare(1,1))

ML99_EVAL(ML99_call(ML99_listUnwrapCommaSep, make_list(1,2,3,4,5,6)))
*/
/*#define X_IMPL(op)        ML99_call(op, v(123))
#define CALL_X_IMPL(a) ML99_call(X, v(ID))
#define ID_IMPL(x)        v(x)

ML99_EVAL(ML99_call(X, v(CALL_X)))
*/
