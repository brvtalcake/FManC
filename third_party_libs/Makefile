CC = gcc
CFLAGS = -O3 -Wall -Wextra -Werror $(USER_CFLAGS)
INC = -I./metalang99/include/

.PHONY : all static shared clean

all : static shared

clean :
	find ./exCept/build/ -type f -delete

static : exCept/build/static/libexCept.a

shared : exCept/build/shared/libexCept.so

exCept/build/static/libexCept.a : exCept/build/static_exCept.o
	ar -rsc $@ $<

exCept/build/static_exCept.o : exCept/exCept.c exCept/exCept.h
	$(CC) $(CFLAGS) $(INC) $< -c -o $@