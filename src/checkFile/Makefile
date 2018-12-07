CC = gcc

DUBFLG=
CFLAGS += -g -O2 ${DUBFLG} -Wall -Werror

all:checkAccount clean

checkAccount:md5.o checkAccount.o HashTable.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm *.o

.SUFFIXES: .c .o

.c.o:
	$(CC) $(CFLAGS) -c $*.c -o $@

.PHONY: all clean

.DEFAULT: all
