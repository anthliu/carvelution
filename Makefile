CPP_FILES=$(wildcard src/*.cpp)
HPP_FILES=$(wildcard include/*.hpp)
OBJ_FILES=$(addprefix obj/,$(notdir $(CPP_FILES:.cpp=.o)))
CC=clang++
FLAGS=-Wall -O
LDLIBS=-lbox2d -lsfml-graphics -lsfml-window -lsfml-system

all:carvelution

carvelution: $(OBJ_FILES)
	$(CC) $(LDLIBS) $(FLAGS) -o $@ $^

obj/%.o: src/%.cpp
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm obj/*.o carvelution
