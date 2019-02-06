SHELL = /bin/sh
EXE = test.x
CXX = c++
CXXFLAGS = -I -g -std=c++11 -Wall -Wextra

SRC= test.cc
OBJ=$(SRC:.cc=.o)
INC = ../include/BST.h

# eliminate default suffixes
.SUFFIXES:
SUFFIXES =

# just consider our own suffixes
.SUFFIXES: .cc .o

all: $(EXE)

.PHONY: all

%.o: %.cc $(INC)
	$(CXX) -c $< -o $@ $(CXXFLAGS)

$(EXE): $(OBJ)
	$(CXX) $^ -o $(EXE)

.PHONY: clean

clean:
		@rm -rf $(OBJ) $(EXE) .*~ ../include/*~ *~
