VERSION=1.0.0
MAJOR_VERSION=1

SHELL=cmd

SRC_FILES=$(wildcard src/*.c) $(wildcard src/notByMe/*.c)
HEADER_FILES=$(wildcard src/*.h) $(wildcard src/notByMe/*.h)
OBJ_FILES=$(subst src/,,$(subst notByMe/,,$(SRC_FILES:.c=.o)))

CC=gcc
AR=ar

AR_FLAGS=-rsc

CFLAGS_STATIC=-O3 -D STATIC -Wall -Werror -std=c11 -c

CFLAGS_DLL_1=-O3 -Wall -Werror -std=c11 -c -D BUILD_DLL
CFLAGS_DLL_2_1=-O3 -Wall -Werror -std=c11 -shared $(OBJ_FILES) -o
CFLAGS_DLL_2_2="-Wl,--out-implib,libFManC.dll.a,--export-all-symbols"

.PHONY : stat_win stat_lin dyn_win dyn_lin clean_win clean_lin 

stat_win : libFManC.a cpHeaders_win clean_win

stat_lin : libFManC.linux.a clean_lin

dyn_win : FManC.dll cpHeaders_win clean_win

dyn_lin : test/test_with_so/lib/FManC.so lib/FManC.so cpHeaders_lin clean_lin


# For the windows static lib	
libFManC.a : $(SRC_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS_STATIC) $(SRC_FILES)
	$(AR) $(AR_FLAGS) test/test_with_static/lib/$@ $(OBJ_FILES)
	$(AR) $(AR_FLAGS) lib/$@ $(OBJ_FILES)

# For linux static lib
libFManC.linux.a : $(SRC_FILES) $(HEADER_FILES)
	sh $(CC) $(CFLAGS_STATIC) $(SRC_FILES)
	sh $(AR) $(AR_FLAGS) test/test_with_static/lib/$@ $(OBJ_FILES)
	sh $(AR) $(AR_FLAGS) lib/$@ $(OBJ_FILES)

# For windows dll and lib
FManC.dll : $(SRC_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS_DLL_1) $(SRC_FILES)
	$(CC) $(CFLAGS_DLL_2_1) bin/$@ $(CFLAGS_DLL_2_2)
	$(CC) $(CFLAGS_DLL_2_1) test/test_with_dll/bin/$@ $(CFLAGS_DLL_2_2)
	@copy /Y .\\libFManC.dll.a .\\lib\\
	@move /Y .\\libFManC.dll.a .\\test\\test_with_dll\\lib\\

cpHeaders_win : $(HEADER_FILES)
	@copy /V /Y .\\src\\*.h .\\include\\
	@copy /V /Y .\\src\\notByMe\\*.h .\\include\\notByMe\\
	@copy /V /Y .\\src\\*.h .\\test\\test_with_dll\\include\\
	@copy /V /Y .\\src\\notByMe\\*.h .\\test\\test_with_dll\\include\\notByMe\\
	@copy /V /Y .\\src\\*.h .\\test\\test_with_static\\include\\
	@copy /V /Y .\\src\\notByMe\\*.h .\\test\\test_with_static\\include\\notByMe\\
	@copy /V /Y .\\src\\*.h .\\test\\test_with_so\\include\\
	@copy /V /Y .\\src\\notByMe\\*.h .\\test\\test_with_so\\include\\notByMe\\

cpHeaders_lin : $(HEADER_FILES)

clean_win :
	@erase *.o

clean_lin :
	@rm -f *.o

#gcc -O3 -Wall -Wextra -Werror -std=c11 -c -fPIC src/*.c src/notByMe/*.c
#gcc -O3 -Wall -Wextra -Werror -std=c11 -fPIC -shared *.o -o lib/libFManC.so.$(VERSION) -Wl,-soname
#gcc -O3 -Wall -Wextra -Werror -std=c11 -fPIC -shared *.o -o test/test_with_so/lib/libFManC.so.$(VERSION) -Wl,-soname