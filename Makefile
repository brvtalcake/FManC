VERSION=1.0.0
MAJOR_VERSION=1

TEST_RES_FOLD=lin

ifneq (,$(findstring Windows,$(OS)))
	TEST_RES_FOLD=win
	SHELL=cmd
else ifneq (,$(findstring windows,$(OS)))
	SHELL=cmd
	TEST_RES_FOLD=win
endif

SRC_FILES=$(wildcard src/*.c) $(wildcard src/third_party/*.c)
HEADER_FILES=$(wildcard src/*.h) $(wildcard src/third_party/*.h)
OBJ_FILES=$(subst src/,,$(subst third_party/,,$(SRC_FILES:.c=.o)))

CC=gcc
AR=ar

AR_GH_ACTION=gcc-ar

AR_FLAGS=-rsc

CFLAGS_STATIC=-O3 -D STATIC -Wall -Wextra -pedantic -Werror -std=c11 -c

CFLAGS_DLL_1=-O3 -Wall -Werror -Wextra -pedantic -std=c11 -c -D BUILD_DLL
CFLAGS_DLL_2_1=-O3 -Wall -Werror -Wextra -pedantic -std=c11 -shared $(OBJ_FILES) -o
CFLAGS_DLL_2_2="-Wl,--out-implib,libFManC.dll.a,--export-all-symbols"

CFLAGS_DYN_LIN_1=-O3 -Wall -Wextra -pedantic -Werror -std=c11 -c -fPIC
CFLAGS_DYN_LIN_2_1=-O3 -Wall -Wextra -pedantic -Werror -std=c11 -fPIC -shared $(OBJ_FILES) -o
CFLAGS_DYN_LIN_2_2=-Wl,-soname,


.PHONY : stat_win stat_lin dyn_win dyn_lin

.PHONY : clean_win clean_lin doxy clean_so 

.PHONY : stat_win_only stat_lin_only dyn_win_only dyn_lin_only

.PHONY : test_lin test_win


stat_win : libFManC.a cpHeaders_win clean_win doxy test_win

stat_win_only : libFManC.a cpHeaders_win clean_win # For GitHub Action

stat_lin : libFManC.linux.a cpHeaders_lin clean_lin doxy test_lin

stat_lin_only : libFManC.linux.a cpHeaders_lin clean_lin # For GitHub Action
 
dyn_win : FManC.dll cpHeaders_win clean_win doxy test_win

dyn_win_only : FManC.dll cpHeaders_win clean_win # For GitHub Action

dyn_lin : clean_so libFManC.so cpHeaders_lin clean_lin doxy test_lin

dyn_lin_only : clean_so libFManC.so cpHeaders_lin clean_lin # For GitHub Action


# For the windows static lib	
libFManC.a : $(SRC_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS_STATIC) $(SRC_FILES)
	$(AR) $(AR_FLAGS) lib/$@ $(OBJ_FILES)

# For linux static lib
libFManC.linux.a : $(SRC_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS_STATIC) $(SRC_FILES)
	$(AR) $(AR_FLAGS) lib/$@ $(OBJ_FILES)

# For windows dll and lib
FManC.dll : $(SRC_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS_DLL_1) $(SRC_FILES)
	$(CC) $(CFLAGS_DLL_2_1) bin/$@ $(CFLAGS_DLL_2_2)
	@move /Y .\\libFManC.dll.a .\\lib\\

# For linux dynamic lib
libFManC.so : $(SRC_FILES) $(HEADER_FILES)
	$(CC) $(CFLAGS_DYN_LIN_1) $(SRC_FILES)
	$(CC) $(CFLAGS_DYN_LIN_2_1) lib/$@.$(VERSION) $(CFLAGS_DYN_LIN_2_2)$@.$(MAJOR_VERSION)
	cd ./lib/ && ln -s $@.$(VERSION) $@.$(MAJOR_VERSION) && ln -s $@.$(MAJOR_VERSION) $@

# I should change the name of these two following rules since they don't only copy header now
cpHeaders_win : $(HEADER_FILES) $(SRC_FILES) 
	@copy /V /Y .\\src\\*.h .\\include\\
	@copy /V /Y .\\src\\third_party\\*.h .\\include\\third_party\\
	@copy /V /Y .\\src\\*.h .\\test\\src_lib\\
	@copy /V /Y .\\src\\third_party\\*.h .\\test\\src_lib\\third_party\\
	@copy /V /Y .\\src\\*.c .\\test\\src_lib\\
	@copy /V /Y .\\src\\third_party\\*.c .\\test\\src_lib\\third_party\\

cpHeaders_lin : $(HEADER_FILES) $(SRC_FILES)
	@cp ./src/*.h ./include/
	@cp ./src/third_party/*.h ./include/third_party/
	@cp ./src/*.h ./test/src_lib/
	@cp ./src/third_party/*.h ./test/src_lib/third_party/
	@cp ./src/*.c ./test/src_lib/
	@cp ./src/third_party/*.c ./test/src_lib/third_party/

clean_win :
	@erase *.o

clean_lin :
	@rm -f *.o

doxy :
	@doxygen Doxyfile
	cd man && make

clean_so : 
	@cd lib/ && rm -f libFManC.so && rm -f libFManC.so.$(MAJOR_VERSION) && rm -f libFManC.so.$(VERSION)

TEST_DEPENDENCIES_FILES=$(wildcard test/src_lib/*.c) $(wildcard test/src_lib/third_party/*.c) $(wildcard test/src_lib/*.h) $(wildcard test/src_lib/third_party/*.h) $(wildcard test/src_test/*.h) $(wildcard test/src_test/*.c) 

TEST_FILES_TO_COMPILE=$(wildcard test/src_lib/*.c) $(wildcard test/src_lib/third_party/*.c) $(wildcard test/src_test/*.c) 

CFLAGS_DEBUG=-fprofile-arcs -ftest-coverage -O0 -Wall -Wextra -pedantic -Werror -std=c11 -D USE_CODE_UTILS

test_lin : cpHeaders_lin $(TEST_DEPENDENCIES_FILES)
	$(CC) $(CFLAGS_DEBUG) $(TEST_FILES_TO_COMPILE) -o test/test_builds/$(TEST_RES_FOLD)/$@.out -I./test/third_party/
	cd test/test_builds/$(TEST_RES_FOLD)/ && ./$@.out

test_win : cpHeaders_win $(TEST_DEPENDENCIES_FILES)
	$(CC) $(CFLAGS_DEBUG) -D STATIC $(TEST_FILES_TO_COMPILE) -o test/test_builds/$(TEST_RES_FOLD)/$@.exe -I./test/third_party/
	cd test/test_builds/$(TEST_RES_FOLD)/ && $@.exe

# rep_cov : 
