#!/bin/sh
if [ -z $1 ]; then
	echo "Set .cpp file to compile"
	exit
fi

if [ -d build ]; then
	rm -rf build
fi
mkdir build

CC=c++98

g++ -std=$CC -Wall -pedantic $1 -o build/$1.executable


if [ -e build/$1.executable ]; then
	./build/$1.executable
fi