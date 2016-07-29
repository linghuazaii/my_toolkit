INCLUDE=-I./include

LIB=-L./lib \
	-lpthread \
	-liniparser \
	-Wl,-rpath=./lib:../lib

CC=g++
LFLAGS=-shared -rdynamic
CFLAGS=-fPIC -g -O3

OBJ=./lib/libdebug++.so
SRC=./src/debug++.o

TESTOBJ=./test/test
TESTSRC=./test/test.cpp

.PHONY: all
all: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(LFLAGS) $(LIB) -o $@ $^

%.o: %.cpp
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $^

%.o: %.c
	$(CC) $(INCLUDE) $(CFLAGS) -c -o $@ $^

.PHONY: clean test
test:
	$(CC) $(INCLUDE) -L./lib -I./src -ldebug++ -Wl,-rpath=../lib:./lib $(TESTSRC) -o $(TESTOBJ)
	@./test/test

clean:
	-rm $(OBJ) $(SRC) $(TESTOBJ)



