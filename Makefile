CC = g++
FLAGS = -g -Wall -pedantic -rdynamic
FLAGS11 = $(FLAGS) -std=c++11

exceptions:
	$(CC) $(FLAGS11) exceptions.cpp -o exceptions.out
	./exceptions.out

pointers:
	$(CC) $(FLAGS) pointers.cpp -o pointers.out
	./pointers.out

containers:
	$(CC) $(FLAGS) containers.cpp -o containers.out
	./containers.out

virtual:
	$(CC) $(FLAGS11) virtual.cpp -o virtual.out
	./virtual.out

vtable:
	$(CC) $(FLAGS) -fdump-class-hierarchy vtable.cpp -o vtable.out
	./vtable.out

typecast:
	$(CC) $(FLAGS11) -fdump-class-hierarchy typecast.cpp -o typecast.out
	./typecast.out

references:
	$(CC) $(FLAGS11) references.cpp -o references.out
	./references.out

types:
	$(CC) $(FLAGS11) types.cpp -o types.out
	./types.out

asm:
	$(CC) -S -o asm.s asm.cpp
	objdump -S --disassemble asm.out > asm.dump
