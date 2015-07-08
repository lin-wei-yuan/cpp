CC = g++
FLAGS = -g -Wall -pedantic -rdynamic -std=c++11

exceptions:
	$(CC) $(FLAGS) exceptions.cpp -o exceptions.out
	./exceptions.out
