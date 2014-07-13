CC=clang++
FLAGS=-Wall -O
LDLIBS=-lbox2d -lsfml-graphics -lsfml-window -lsfml-system

all:bin/carvelution

bin/carvelution: main.o car.o
	$(CC) $(LDLIBS) $(FLAGS) main.o car.o -o bin/carvelution

main.o: main.cpp car.hpp configurations.hpp
	$(CC) $(FLAGS) -c main.cpp

car.o: car.cpp car.hpp configurations.hpp
	$(CC) $(FLAGS) -c car.cpp

clean:
	rm *.o bin/carvelution
