#! /bin/bash

CXXFLAGS = `wx-config --cxxflags`
EXEC = ACS
INCLUDES = -include wx/wx.h
LIBS = `wx-config --libs`
SRC = $(wildcard src/*.cpp)
OBJ = $(addprefix obj/,$(notdir $(SRC:.cpp=.o))) /usr/lib/x86_64-linux-gnu/libwx_gtk2u_stc-2.8.so.0

all: $(EXEC)

clean:
	rm $(EXEC) $(OBJ);

$(EXEC): $(OBJ) 
	g++ -o $(EXEC) $(OBJ) $(LIBS)

obj/%.o: src/%.cpp
	g++ $(CXXFLAGS) $(INCLUDES) -o $@ -c $<
