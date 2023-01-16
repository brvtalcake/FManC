VERSION=1.0.0
MAJOR_VERSION=1

ifneq (,$(findstring Windows,$(OS)))
	SHELL=cmd
else ifneq (,$(findstring windows,$(OS)))
	SHELL=cmd
endif

SRC_FILES=$(wildcard src/*.c) $(wildcard src/third_party/*.c)
HEADER_FILES=$(wildcard src/*.h) $(wildcard src/third_party/*.h)
OBJ_FILES=$(subst src/,,$(subst third_party/,,$(SRC_FILES:.c=.o)))

CC=gcc
AR=ar

AR_FLAGS=-rsc

CFLAGS_STATIC=-O3 -D STATIC -Wall -Wextra -pedantic -Werror -std=c11 -c

CFLAGS_DLL_1=-O3 -Wall -Werror -Wextra -pedantic -std=c11 -c -D BUILD_DLL
CFLAGS_DLL_2_1=-O3 -Wall -Werror -Wextra -pedantic -std=c11 -shared $(OBJ_FILES) -o
CFLAGS_DLL_2_2="-Wl,--out-implib,libFManC.dll.a,--export-all-symbols"

CFLAGS_DYN_LIN_1=-O3 -Wall -Wextra -pedantic -Werror -std=c11 -c -fPIC
CFLAGS_DYN_LIN_2_1=-O3 -Wall -Wextra -pedantic -Werror -std=c11 -fPIC -shared $(OBJ_FILES) -o
CFLAGS_DYN_LIN_2_2=-Wl,-soname,

.PHONY : stat_win stat_lin dyn_win dyn_lin clean_win clean_lin doxy

stat_win : libFManC.a cpHeaders_win clean_win doxy

stat_lin : libFManC.linux.a cpHeaders_lin clean_lin doxy
 
dyn_win : FManC.dll cpHeaders_win clean_win doxy

dyn_lin : libFManC.so cpHeaders_lin clean_lin doxy


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

# For linux dynamic lib
libFManC.so : $(SRC_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS_DYN_LIN_1) $(SRC_FILES)
	$(CC) $(CFLAGS_DYN_LIN_2_1) lib/$@.$(VERSION) $(CFLAGS_DYN_LIN_2_2)$@.$(MAJOR_VERSION)
	$(CC) $(CFLAGS_DYN_LIN_2_1) test/test_with_so/lib/$@.$(VERSION) $(CFLAGS_DYN_LIN_2_2)$@.$(MAJOR_VERSION)
	cd ./lib/ && ln -s $@.$(VERSION) $@.$(MAJOR_VERSION) && ln -s $@.$(MAJOR_VERSION) $@
	cd ./test/test_with_so/lib/ && ln -s $@.$(VERSION) $@.$(MAJOR_VERSION) && ln -s $@.$(MAJOR_VERSION) $@

cpHeaders_win : $(HEADER_FILES)
	@copy /V /Y .\\src\\*.h .\\include\\
	@copy /V /Y .\\src\\third_party\\*.h .\\include\\third_party\\
	@copy /V /Y .\\src\\*.h .\\test\\test_with_dll\\include\\
	@copy /V /Y .\\src\\third_party\\*.h .\\test\\test_with_dll\\include\\third_party\\
	@copy /V /Y .\\src\\*.h .\\test\\test_with_static\\include\\
	@copy /V /Y .\\src\\third_party\\*.h .\\test\\test_with_static\\include\\third_party\\
	@copy /V /Y .\\src\\*.h .\\test\\test_with_so\\include\\
	@copy /V /Y .\\src\\third_party\\*.h .\\test\\test_with_so\\include\\third_party\\

cpHeaders_lin : $(HEADER_FILES)
	@cp *.h ./src/ ./include/
	@cp *.h ./src/third_party/ ./include/third_party/
	@cp *.h ./src/ ./test/test_with_dll/include/
	@cp *.h ./src/third_party/ ./test/test_with_dll/include/third_party/
	@cp *.h ./src/ ./test/test_with_static/include/
	@cp *.h ./src/third_party/ ./test/test_with_static/include/third_party/
	@cp *.h ./src/ ./test/test_with_so/include/
	@cp *.h ./src/third_party/ ./test/test_with_so/include/third_party/

clean_win :
	@erase *.o

clean_lin :
	@rm -f *.o

doxy :
	@doxygen Doxyfile
	cd docs/man && make