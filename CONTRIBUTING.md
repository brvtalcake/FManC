# How to contribute ? (This work is not finished)

First of all, I'd say that given the fact I'm no a professionnal, any help would then be hugely appreciated. So how can you help ?

## Open an issue

At the moment the only templates I have are to :

- report a bug
- ask for a new feature

I think I'll try to make more templates later. However, go [there](https://github.com/brvtalcake/FManC/issues) and feel free to open an issue if you want to.

## Collaborate with pull requests

The one thing you should do before going further is to read the [code of conduct](https://github.com/brvtalcake/FManC/blob/main/CODE_OF_CONDUCT.md), and accept the fact that your work will be licensed under the [MIT licence](https://github.com/brvtalcake/FManC/blob/main/LICENCE). Here you go. Now, here are a few coding guidelines to collaborate on this project, that you should try to respect as much as possible :

### Functions

- **Add "FMC_" to functions** to simulate a namespace.
- The remaing part of the function should be written in **_camelCase_**.
- Function names should be as explicit as possible (even if long), but you still have the possibility to cut parts of a word that could be obvious to understand.

For example, here is a "good" function :

```c
int FMC_doSomethingOrAnother(int *a, char **b);
```

### Variables

- Variable names should follow a **_snake_case_** convention.
- There is no particular need to make them explicit, but think about commenting them if they're not trivial.

For example, here are a bunch of "good" variables :

```c
size_t arr_len;
const char *const target_name;
```

### Composite types

- New types should be namespaced the same way as functions, execept for their full names (see the example below).
- The fields should respect the **_camelCase_** convention, and names (except the namespace in capitals) should respect a **_PascalCase_** convention.
- New types should be short. For example, to make a new type for "character composition", it should be someting like (namespace)CharComp.
- Typedefs of structs, enums, or bitfields should not be in FMC_typedefs.h, but should appear just after the associated structs, enums, or bitfields.

The way you should declare structs, enums, bitfields, and custom types in general should be something like :

```c
struct FManC_MyStruct
{
    unsigned int something;
    float anotherThing;
};

typedef struct FManC_MyStruct FMC_MyStruct;
```

### Macros

### Documentation

### Generalities

- Add your name in the licence comment on the top of the file you worked on.
