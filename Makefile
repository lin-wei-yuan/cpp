CC = g++
FLAGS = -g -Wall -pedantic -rdynamic

exceptions:
	$(CC) $(FLAGS) -std=c++11 exceptions.cpp -o exceptions.out
	./exceptions.out

pointers:
	$(CC) $(FLAGS) pointers.cpp -o pointers.out
	./pointers.out

containers:
	$(CC) $(FLAGS) containers.cpp -o containers.out
	./containers.out

virtual:
	$(CC) $(FLAGS) -std=c++11 virtual.cpp -o virtual.out
	./virtual.out

vtable:
	$(CC) $(FLAGS) -std=c++11 -fdump-class-hierarchy vtable.cpp -o vtable.out
	./vtable.out


typecast:
	$(CC) $(FLAGS) -std=c++11 typecast.cpp -o typecast.out
	./typecast.out
