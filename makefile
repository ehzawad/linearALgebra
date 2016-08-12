#
# Makefile
#

# compiler to use
# CXX = clang++
CXX ?= clang++

SRC = main.cpp

EXE = main

LD = -lm

# flags to pass compiler
CXXFLAGS =  -ggdb3 -O0 -std=c++14 -lpthread -Werror -pedantic-errors

all:
	$(CXX) $(CXXFLAGS) $(LD) $(SRC) -o $(EXE)

clean:
	rm -f core *.o $(EXE)
