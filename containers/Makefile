CC = g++
FLAGS = -g -Wall -pedantic
FLAGS11 = $(FLAGS) -std=c++11

all:
	$(CC) $(FLAGS) tests.cpp -o impl.out
	./impl.out

doc:
	doxygen doxygen.cfg.in
