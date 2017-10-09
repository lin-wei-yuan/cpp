#!/bin/sh
FILE=main.cpp

if [ -d build ]; then
	rm -rf build
fi
mkdir build

# CC=c++11
CC=c++14

filename="${FILE##*/}"

g++ -std=$CC -Wall -pedantic -pthread $FILE -Igoogle-benchmark/include/ -o build/$filename.executable -lbenchmark


if [ -e build/$filename.executable ]; then
	./build/$filename.executable
fi