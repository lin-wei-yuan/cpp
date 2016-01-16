CC = g++
FLAGS = -g -Wall -pedantic -rdynamic

exceptions:
	$(CC) $(FLAGS) exceptions.cpp -o exceptions.out
	./exceptions.out

pointers:
	$(CC) $(FLAGS) pointers.cpp -o pointers.out
	./pointers.out

containers:
	$(CC) $(FLAGS) containers.cpp -o containers.out
	./containers.out

virtual:
	$(CC) $(FLAGS) virtual.cpp -o virtual.out
	./virtual.out

vtable:
	$(CC) $(FLAGS) -fdump-class-hierarchy vtable.cpp -o vtable.out
	./vtable.out

typecast:
	$(CC) $(FLAGS) -fdump-class-hierarchy typecast.cpp -o typecast.out
	./typecast.out

references:
	$(CC) $(FLAGS) references.cpp -o references.out
	./references.out

types:
	$(CC) $(FLAGS) types.cpp -o types.out
	./types.out
