CC = g++
FLAGS = -g -Wall -pedantic

exceptions:
	$(CC) $(FLAGS) exceptions.cpp -o exceptions.out
	./exceptions.out
