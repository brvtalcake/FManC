# Project informations
VERSION=1.0.0
MAJOR_VERSION=1

# OS-dependant variables
DETECTED_OS=lin
PRINTED_OS=Linux
TEST_RES_FOLD=lin
## Another idea to detect OS could be to parse the output of gcc -print-multiarch
ifneq (,$(findstring Windows,$(OS)))
	TEST_RES_FOLD=win
	DETECTED_OS=win
	PRINTED_OS=$(OS)
	SHELL=cmd
else ifneq (,$(findstring windows,$(OS)))
	SHELL=cmd
	DETECTED_OS=win
	PRINTED_OS=$(OS)
	TEST_RES_FOLD=win
endif

# Project subdirectories
SRC_SUBDIRS=src src/general src/general/preprocessor src/general/types src/general/utils src/file_management src/file_management src/data_analyze src/data_analyze/encodings src/data_analyze/strings src/code_utils

# Project files
C_SRC_FILES=$(foreach dir,$(SRC_SUBDIRS),$(wildcard $(dir)/*.c))
H_SRC_FILES=$(foreach dir,$(SRC_SUBDIRS),$(wildcard $(dir)/*.h))

# Object files
O_LIN_STATIC_FILES=$(addprefix obj/lin/static/,$(notdir $(C_SRC_FILES:.c=.o)))
O_LIN_SHARED_FILES=$(addprefix obj/lin/shared/,$(notdir $(C_SRC_FILES:.c=.o)))
O_WIN_STATIC_FILES=$(addprefix obj/win/static/,$(notdir $(C_SRC_FILES:.c=.o)))
O_WIN_SHARED_FILES=$(addprefix obj/win/shared/,$(notdir $(C_SRC_FILES:.c=.o)))

# Library files
LIB_LIN_STATIC_FILES=lib/libFManC_linux_x86_64.a
LIB_LIN_SHARED_FILES=bin/libFManC_x86_64.so
LIB_WIN_STATIC_FILES=lib/libFManC_win_x86_64.a
LIB_WIN_SHARED_FILES=bin/libFManC_x86_64.dll lib/libFManC_x86_64.dll.a

# Compiler and friends
CC=gcc
AR=ar

# Compiler and archiver flags
AR_FLAGS=-rsc
CFLAGS=-O3 -Wall -Wextra -pedantic -Werror -std=c11
CFLAGS_STATIC=-O3 -D STATIC -Wall -Wextra -pedantic -Werror -std=c11 -c
CFLAGS_DLL_1=-O3 -Wall -Werror -Wextra -pedantic -std=c11 -c -D BUILD_DLL
CFLAGS_DLL_2_1=-O3 -Wall -Werror -Wextra -pedantic -std=c11 -shared -o
CFLAGS_DLL_2_2="-Wl,--out-implib,libFManC.dll.a,--export-all-symbols"
CFLAGS_DYN_LIN_1=-O3 -Wall -Wextra -pedantic -Werror -std=c11 -c -fPIC
CFLAGS_DYN_LIN_2_1=-O3 -Wall -Wextra -pedantic -Werror -std=c11 -fPIC -shared -o
CFLAGS_DYN_LIN_2_2=-Wl,-soname,

# All target
ALL_TARGET=$(addsuffix _$(DETECTED_OS), all)
.PHONY : all

# Static library target
STAT_TARGET=$(addsuffix _$(DETECTED_OS), static)
.PHONY : static

# Shared library target
SHARED_TARGET=$(addsuffix _$(DETECTED_OS), shared)
.PHONY : shared

# Tests target
TEST_TARGET=$(addsuffix _$(DETECTED_OS), test)
.PHONY : test

# Clean target
CLEAN_TARGET=$(addsuffix _$(DETECTED_OS), clean)
.PHONY : clean

# Copy headers target
COPY_HEADERS_TARGET=$(addsuffix _$(DETECTED_OS), copy_headers)
.PHONY : copy_headers

# Documentation target
DOC_TARGET=$(addsuffix _$(DETECTED_OS), doc)
.PHONY : doc

all : $(ALL_TARGET)

all_lin : static shared copy_headers doc test 
	@echo "\e[32mBuilt everything for $(PRINTED_OS)\e[0m"

all_win : static shared copy_headers doc test
	@echo "\e[32mBuilt everything for $(PRINTED_OS)\e[0m"

static : $(STAT_TARGET)

static_lin : $(LIB_LIN_STATIC_FILES) copy_headers doc test
	@echo "\e[32mBuilt static library for $(PRINTED_OS)\e[0m"

static_win : $(LIB_WIN_STATIC_FILES) copy_headers doc test
	@echo "\e[32mBuilt static library for $(PRINTED_OS)\e[0m"

shared : $(SHARED_TARGET)

shared_lin : $(LIB_LIN_SHARED_FILES) copy_headers doc test
	@echo "\e[32mBuilt shared library for $(PRINTED_OS)\e[0m"

shared_win : $(LIB_WIN_SHARED_FILES) copy_headers doc test
	@echo "\e[32mBuilt shared library for $(PRINTED_OS)\e[0m"

test : $(TEST_TARGET)

test_lin : $(LIB_LIN_STATIC_FILES) $(LIB_LIN_SHARED_FILES)
	@echo "\e[32mRunning tests for $(PRINTED_OS)\e[0m"
## TO DO

test_win : $(LIB_WIN_STATIC_FILES) $(LIB_WIN_SHARED_FILES)
	@echo "\e[32mRunning tests for $(PRINTED_OS)\e[0m"
## TO DO

clean : $(CLEAN_TARGET)

clean_lin : $(O_LIN_STATIC_FILES) $(O_LIN_SHARED_FILES) $(LIB_LIN_STATIC_FILES) $(LIB_LIN_SHARED_FILES)
	@echo "\e[32mCleaned everything for $(PRINTED_OS)\e[0m"
	@rm -f $(O_LIN_STATIC_FILES) $(O_LIN_SHARED_FILES) $(LIB_LIN_STATIC_FILES) $(LIB_LIN_SHARED_FILES)

clean_win : $(O_WIN_STATIC_FILES) $(O_WIN_SHARED_FILES) $(LIB_WIN_STATIC_FILES) $(LIB_WIN_SHARED_FILES)
	@echo "\e[32mCleaned everything for $(PRINTED_OS)\e[0m"
	@rm -f $(O_WIN_STATIC_FILES) $(O_WIN_SHARED_FILES) $(LIB_WIN_STATIC_FILES) $(LIB_WIN_SHARED_FILES)
## TO DO : check if rm exists on windows

copy_headers : $(COPY_HEADERS_TARGET)

copy_headers_lin : $(H_SRC_FILES) 
	@echo "\e[32mCopied headers for $(PRINTED_OS)\e[0m"
	@cp $(addsuffix /,$(addprefix ./,$(H_SRC_FILES))) -t ./include/

copy_headers_win : $(H_SRC_FILES) # This one should not work.
	@echo "\e[32mCopied headers for $(PRINTED_OS)\e[0m"
	@cp $(addsuffix \,$(addprefix .\,$(H_SRC_FILES))) .\\include\\ 

