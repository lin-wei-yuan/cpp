#!/bin/sh
if [ -z $1 ]; then
	echo "Set .cpp file to compile"
	exit
fi

if [ -d build ]; then
	rm -rf build
fi
mkdir build

# CC=c++11
CC=c++14

filename="${1##*/}"

g++ -std=$CC -Wall -pedantic -pthread $1 -Ibase/ -o build/$filename.executable #-lbenchmark -lgtest


if [ -e build/$filename.executable ]; then
	./build/$filename.executable
fi