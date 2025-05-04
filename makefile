CC=gcc
LIBS=libs
INC=$(LIBS)/inc
CFLAGS=-Wall -I$(INC)

all: tests

tests: test_ll

$(LIBS)/%.o: $(LIBS)/%.c $(INC)/%.h
	$(CC) $(CFLAGS) -c -o $@ $<

tests/%.o: tests/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

test_ll: tests/test_ll.o $(LIBS)/ll.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	del tests\*.o *.exe
	del libs\*.o
