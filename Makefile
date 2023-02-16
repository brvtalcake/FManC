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
CFLAGS=-O3 -Wall -Wextra -Werror -std=gnu17
CXX_FLAGS=-O3 -Wall -Wextra -Werror -std=gnu++17

LD_FLAGS_DLL=-lstdc++ "-Wl,--out-implib,libFManC.dll.a,--export-all-symbols"
LD_FLAGS_SO=-lstdc++ -Wl,-soname,


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
	@printf "\e[92mBuilt everything for $(PRINTED_OS)\n\e[0m"

all_win : static shared copy_headers doc test
	@echo Built everything for $(PRINTED_OS)

static : $(STAT_TARGET)

static_lin : $(LIB_LIN_STATIC_FILES) copy_headers 
	@printf "\e[92mBuilt static library for $(PRINTED_OS)\n\e[0m"

static_win : $(LIB_WIN_STATIC_FILES) copy_headers 
	@echo Built static library for $(PRINTED_OS)

shared : $(SHARED_TARGET)

shared_lin : $(LIB_LIN_SHARED_FILES) copy_headers
	@printf "\e[92mBuilt shared library for $(PRINTED_OS)\n\e[0m"

shared_win : $(LIB_WIN_SHARED_FILES) copy_headers
	@echo Built shared library for $(PRINTED_OS)

test : $(TEST_TARGET)

test_lin : $(LIB_LIN_STATIC_FILES) $(LIB_LIN_SHARED_FILES)
	@printf "\e[92mRunning tests for $(PRINTED_OS)\n\e[0m"
## TO DO

test_win : $(LIB_WIN_STATIC_FILES) $(LIB_WIN_SHARED_FILES)
	@echo Running tests for $(PRINTED_OS)
## TO DO

clean : $(CLEAN_TARGET)

clean_lin : 
	@rm -f $(O_LIN_STATIC_FILES) $(O_LIN_SHARED_FILES) $(LIB_LIN_STATIC_FILES) $(LIB_LIN_SHARED_FILES)
	@printf "\e[92mCleaned everything for $(PRINTED_OS)\n\e[0m"

clean_win : 
	@erase -f $(subst /,\,$(O_WIN_STATIC_FILES) $(O_WIN_SHARED_FILES) $(LIB_WIN_STATIC_FILES) $(LIB_WIN_SHARED_FILES))
	@echo Cleaned everything for $(PRINTED_OS)
## TO DO : check if rm exists on windows

copy_headers : $(COPY_HEADERS_TARGET)

copy_headers_lin : $(subst src/,include/,$(H_SRC_FILES) $(HPP_SRC_FILES))
	@printf "\e[92mCopied headers for $(PRINTED_OS)\n\e[0m"

copy_headers_win : $(subst src/,include/,$(H_SRC_FILES) $(HPP_SRC_FILES))
	@echo Copied headers for $(PRINTED_OS)

doc : $(DOC_TARGET)

doc_lin : $(SRC_FILES)
	doxygen doxylin

doc_win : $(SRC_FILES)
	doxygen doxywin

include/%.h : src/%.h
	@cp -f -u -T $^ $@ 

include/%.hpp : src/%.hpp
	@cp -f -u -T $^ $@ 

lib/libFManC_linux_x86_64.a : $(O_LIN_STATIC_FILES)
	$(AR) $(AR_FLAGS) $@ $^
	@printf "\e[92mBuilt $@ sucessfully\n\n\e[0m"

lib/libFManC_win_x86_64.a : $(O_WIN_STATIC_FILES)
	$(AR) $(AR_FLAGS) $@ $^
	@echo Built $@ sucessfully

obj/lin/static/%.o : %.c $(H_SRC_FILES) $(HPP_SRC_FILES)
	$(CC) $< $(CFLAGS) -c -o $@
	@printf "\e[92mBuilt $@ sucessfully\n\n\e[0m"

obj/lin/static/%.o : %.cpp $(H_SRC_FILES) $(HPP_SRC_FILES)
	$(CCXX) $< $(CXX_FLAGS) -c -o $@
	@printf "\e[92mBuilt $@ sucessfully\n\n\e[0m"

obj/win/static/%.o : %.c $(H_SRC_FILES) $(HPP_SRC_FILES)
	$(CC) -D FMC_STATIC $< $(CFLAGS) -c -o $@
	@echo Built $@ sucessfully

obj/win/static/%.o : %.cpp $(H_SRC_FILES) $(HPP_SRC_FILES)
	$(CCXX) -D FMC_STATIC $< $(CXX_FLAGS) -c -o $@
	@echo Built $@ sucessfully

bin/libFManC_x86_64.so : $(O_LIN_SHARED_FILES)
	rm -f $@ && rm -f $@.$(MAJOR_VERSION) && rm -f $@.$(VERSION)
	$(CC) $(O_LIN_SHARED_FILES) $(CFLAGS) -shared -fPIC -o $@.$(VERSION) $(LD_FLAGS_SO)libFManC_x86_64.so.$(MAJOR_VERSION)

	ln -s $@.$(VERSION) $@.$(MAJOR_VERSION) && ln -s $@.$(MAJOR_VERSION) $@
	@printf "\e[92mBuilt $@ sucessfully\n\n\e[0m"

bin/libFManC_x86_64.dll : lib/libFManC_x86_64.dll.a
	@echo Built DLL for $(PRINTED_OS)

lib/libFManC_x86_64.dll.a : $(O_WIN_SHARED_FILES)
	$(CC) $(O_WIN_SHARED_FILES) $(CFLAGS) -shared -o bin/libFManC_x86_64.dll $(LD_FLAGS_DLL)
	@move /Y .\\libFManC.dll.a .\\lib\\
	@echo Built $@ sucessfully

obj/lin/shared/%.o : %.c $(H_SRC_FILES) $(HPP_SRC_FILES)
	$(CC) $< $(CFLAGS) -c -fPIC -o $@
	@printf "\e[92mBuilt $@ sucessfully\n\n\e[0m"

obj/lin/shared/%.o : %.cpp $(H_SRC_FILES) $(HPP_SRC_FILES)
	$(CCXX) $< $(CXX_FLAGS) -c -fPIC -o $@
	@printf "\e[92mBuilt $@ sucessfully\n\n\e[0m"

obj/win/shared/%.o : %.c $(H_SRC_FILES) $(HPP_SRC_FILES)
	$(CC) -D FMC_BUILD_DLL $< $(CFLAGS) -c -o $@

obj/win/shared/%.o : %.cpp $(H_SRC_FILES) $(HPP_SRC_FILES)
	$(CCXX) -D FMC_BUILD_DLL $< $(CXX_FLAGS) -c -o $@