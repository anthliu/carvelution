CC=clang++
FLAGS=-Wall -O
LDLIBS=-lbox2d -lsfml-graphics -lsfml-window -lsfml-system

all:bin/carvelution

bin/carvelution: main.o car.o ground.o randomgen.o
	$(CC) $(LDLIBS) $(FLAGS) main.o car.o ground.o randomgen.o -o bin/carvelution

main.o: main.cpp car.hpp ground.hpp configurations.hpp
	$(CC) $(FLAGS) -c main.cpp

car.o: car.cpp car.hpp configurations.hpp
	$(CC) $(FLAGS) -c car.cpp

ground.o: ground.cpp ground.hpp configurations.hpp
	$(CC) $(FLAGS) -c ground.cpp

randomgen.o: randomGen.cpp randomGen.hpp configurations.hpp
	$(CC) $(FLAGS) -c randomgen.cpp

clean:
	rm *.o bin/carvelution
