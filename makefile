CC=gcc
LIBS=libs
INC=$(LIBS)/inc
CFLAGS=-Wall -I$(INC)
OBJS=$(LIBS)/ll.o

all: main

libs/%.o: $(LIBS)/%.c $(INC)/%.h
	$(CC) $(CFLAGS) -c -o $@ $<

main.o: main.c
	$(CC) $(CFLAGS) -c -o $@ $<

main: main.o $(OBJS)
	$(CC) $(CFLAGS) -o main main.o $(OBJS)

clean:
	del *.o main.exe
	del libs\*.o
