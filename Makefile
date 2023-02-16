# Project informations
VERSION=1.0.0
MAJOR_VERSION=1
MINOR_VERSION=0
PATCH_VERSION=0
PROJECT_NAME=FManC
PROJECT_DESCRIPTION="File Management C Library"
PROJECT_AUTHOR="Axel PASCON"
PROJECT_AUTHOR_EMAIL="axlpascon@gmail.com"

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
CPP_SRC_SUBDIRS=src/cpp/ src/cpp/FMC_dir/
C_SRC_SUBDIRS=src/ src/general/ src/general/preprocessor/ src/general/types/ src/general/utils/ src/files/ src/data_analyze/ src/data_analyze/encodings/ src/data_analyze/strings/ src/code_utils/
SRC_SUBDIRS=$(C_SRC_SUBDIRS) $(CPP_SRC_SUBDIRS)

VPATH=$(subst / ,/:,$(SRC_SUBDIRS))

# Project files
CPP_SRC_FILES=$(foreach dir,$(SRC_SUBDIRS),$(wildcard $(dir)/*.cpp))
HPP_SRC_FILES=$(foreach dir,$(SRC_SUBDIRS),$(wildcard $(dir)/*.hpp))
C_SRC_FILES=$(foreach dir,$(SRC_SUBDIRS),$(wildcard $(dir)/*.c))
H_SRC_FILES=$(foreach dir,$(SRC_SUBDIRS),$(wildcard $(dir)/*.h))
SRC_FILES=$(CPP_SRC_FILES) $(C_SRC_FILES) $(HPP_SRC_FILES) $(H_SRC_FILES)

# Object files
O_LIN_STATIC_FILES=$(addprefix obj/lin/static/,$(notdir $(C_SRC_FILES:.c=.o))) $(addprefix obj/lin/static/,$(notdir $(CPP_SRC_FILES:.cpp=.o)))
O_LIN_SHARED_FILES=$(addprefix obj/lin/shared/,$(notdir $(C_SRC_FILES:.c=.o))) $(addprefix obj/lin/shared/,$(notdir $(CPP_SRC_FILES:.cpp=.o)))
O_WIN_STATIC_FILES=$(addprefix obj/win/static/,$(notdir $(C_SRC_FILES:.c=.o))) $(addprefix obj/win/static/,$(notdir $(CPP_SRC_FILES:.cpp=.o)))
O_WIN_SHARED_FILES=$(addprefix obj/win/shared/,$(notdir $(C_SRC_FILES:.c=.o))) $(addprefix obj/win/shared/,$(notdir $(CPP_SRC_FILES:.cpp=.o)))

# Library files
LIB_LIN_STATIC_FILES=lib/libFManC_linux_x86_64.a
LIB_LIN_SHARED_FILES=bin/libFManC_x86_64.so
LIB_WIN_STATIC_FILES=lib/libFManC_win_x86_64.a
LIB_WIN_SHARED_FILES=bin/libFManC_x86_64.dll lib/libFManC_x86_64.dll.a

# Compiler and friends
CC=gcc
CCXX=g++
AR=ar

# Compiler and archiver flags
AR_FLAGS=-rsc
CFLAGS=-O3 -Wall -Wextra -pedantic -Werror -std=gnu17
CXX_FLAGS=-O3 -Wall -Wextra -pedantic -Werror -std=gnu++17


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
	@printf "\e[32mBuilt everything for $(PRINTED_OS)\e[0m"

all_win : static shared copy_headers doc test
	@printf "\e[32mBuilt everything for $(PRINTED_OS)\e[0m"

static : $(STAT_TARGET)

static_lin : $(LIB_LIN_STATIC_FILES) copy_headers doc test
	@printf "\e[32mBuilt static library for $(PRINTED_OS)\e[0m"

static_win : $(LIB_WIN_STATIC_FILES) copy_headers doc test
	@printf "\e[32mBuilt static library for $(PRINTED_OS)\e[0m"

shared : $(SHARED_TARGET)

shared_lin : $(LIB_LIN_SHARED_FILES) copy_headers doc test
	@printf "\e[32mBuilt shared library for $(PRINTED_OS)\e[0m"

shared_win : $(LIB_WIN_SHARED_FILES) copy_headers doc test
	@printf "\e[32mBuilt shared library for $(PRINTED_OS)\e[0m"

test : $(TEST_TARGET)

test_lin : $(LIB_LIN_STATIC_FILES) $(LIB_LIN_SHARED_FILES)
	@printf "\e[32mRunning tests for $(PRINTED_OS)\e[0m"
## TO DO

test_win : $(LIB_WIN_STATIC_FILES) $(LIB_WIN_SHARED_FILES)
	@printf "\e[32mRunning tests for $(PRINTED_OS)\e[0m"
## TO DO

clean : $(CLEAN_TARGET)

clean_lin : $(O_LIN_STATIC_FILES) $(O_LIN_SHARED_FILES) $(LIB_LIN_STATIC_FILES) $(LIB_LIN_SHARED_FILES)
	@rm -f $(O_LIN_STATIC_FILES) $(O_LIN_SHARED_FILES) $(LIB_LIN_STATIC_FILES) $(LIB_LIN_SHARED_FILES)
	@printf "\e[32mCleaned everything for $(PRINTED_OS)\e[0m"

clean_win : $(O_WIN_STATIC_FILES) $(O_WIN_SHARED_FILES) $(LIB_WIN_STATIC_FILES) $(LIB_WIN_SHARED_FILES)
	@rm -f $(O_WIN_STATIC_FILES) $(O_WIN_SHARED_FILES) $(LIB_WIN_STATIC_FILES) $(LIB_WIN_SHARED_FILES)
	@printf "\e[32mCleaned everything for $(PRINTED_OS)\e[0m"
## TO DO : check if rm exists on windows

copy_headers : $(COPY_HEADERS_TARGET)

copy_headers_lin : $(H_SRC_FILES) $(HPP_SRC_FILES)
	@cp $(addsuffix /,$(addprefix ./,$(H_SRC_FILES))) -t ./include/
	@printf "\e[32mCopied headers for $(PRINTED_OS)\e[0m"

copy_headers_win : $(H_SRC_FILES)
	@cp $(addsuffix \,$(addprefix .\,$(H_SRC_FILES))) .\\include\\ 
	@printf "\e[32mCopied headers for $(PRINTED_OS)\e[0m"

lib/libFManC_linux_x86_64.a : $(O_LIN_STATIC_FILES)
	$(AR) $(AR_FLAGS) $@ $^

lib/libFManC_win_x86_64.a : $(O_WIN_STATIC_FILES)
	$(AR) $(AR_FLAGS) $@ $^

obj/lin/static/%.o : %.c $(H_SRC_FILES) $(HPP_SRC_FILES)
	$(CC) $< $(CFLAGS) -c -o $@

obj/lin/static/%.o : %.cpp $(H_SRC_FILES) $(HPP_SRC_FILES)
	$(CCXX) $< $(CXX_FLAGS) -c -o $@

obj/win/static/%.o : %.c $(H_SRC_FILES) $(HPP_SRC_FILES)
	$(CC) -D FMC_STATIC $< $(CFLAGS) -c -o $@

obj/win/static/%.o : %.cpp $(H_SRC_FILES) $(HPP_SRC_FILES)
	$(CCXX) -D FMC_STATIC $< $(CXX_FLAGS) -c -o $@
