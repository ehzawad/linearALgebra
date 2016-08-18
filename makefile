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

SRC = main.cpp

EXE = main

LD = -lm


# flags to pass compiler
CXXFLAGS =  -ggdb3 -O0 -std=c++11 -lpthread -Werror -pedantic-errors

all:
	$(CXX) $(HEADER_PATH) $(CXXFLAGS) $(LD) $(SRC) -o $(EXE)

run:
	./$(EXE)

debug:
	gdb ./$(EXE)

memleak:
	valgrind -v ./$(EXE)

clean:
	rm -f core *.o $(EXE)
