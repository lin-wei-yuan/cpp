CC = g++
FLAGS = -g -Wall -pedantic -rdynamic
FLAGS11 = $(FLAGS) -std=c++11

all:
	$(CC) $(FLAGS11) src/vec.cpp tests.cpp -o impl.out
	./impl.out

doc:
	doxygen doxygen.cfg.in
