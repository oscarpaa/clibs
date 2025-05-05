CC=gcc
LIBS=libs
INC=$(LIBS)/inc
CFLAGS=-Wall -I$(INC)

all: test_ll test_cll

test_ll: test_ll
test_cll: test_cll

tests/%.o: tests/%.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(LIBS)/%.o: $(LIBS)/%.c $(INC)/%.h
	$(CC) $(CFLAGS) -c -o $@ $<

test_%: tests/test_%.o $(LIBS)/%.o
	$(CC) $(CFLAGS) -o $@ $^

clean:
	del tests\*.o *.exe
	del libs\*.o
