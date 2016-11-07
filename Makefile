#
# Makefile
#

# compiler to use
CXX ?= clang++

ifeq "$(CXX)" "clang++"
    HEADER_PATH = -stdlib=libc++
else
    HEADER_PATH =
endif

SRC = hillCipher.cpp main.cpp

EXE = main

LD = -lm -lpthread -lcrypto


# flags to pass compiler
CXXFLAGS =  -ggdb3 -O0 -std=c++14 -Werror -Wall -pedantic-errors

all:
	$(CXX) $(HEADER_PATH) $(CXXFLAGS) $(LD) $(SRC) -o $(EXE)

run:
	./$(EXE)

debug:
	gdb ./$(EXE)

memleak:
	valgrind -v --leak-check=full --show-leak-kinds=all ./$(EXE)


clean:
	rm -f core *.o $(EXE)
