CC=clang++
FLAGS=-Wall -O
LDLIBS=-lbox2d -lsfml-graphics -lsfml-window -lsfml-system

all:bin/carvelution

bin/carvelution: main.o car.o ground.o
	$(CC) $(LDLIBS) $(FLAGS) main.o car.o ground.o -o bin/carvelution

main.o: main.cpp car.hpp ground.hpp configurations.hpp
	$(CC) $(FLAGS) -c main.cpp

car.o: car.cpp car.hpp configurations.hpp
	$(CC) $(FLAGS) -c car.cpp

ground.o: ground.cpp ground.hpp configurations.hpp
	$(CC) $(FLAGS) -c ground.cpp

clean:
	rm *.o bin/carvelution
