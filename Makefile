.PHONY: all test clean editor client common server build

compile-debug:
	mkdir -p build/
	cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Debug $(EXTRA_GENERATE)
	cmake --build  build/ $(EXTRA_COMPILE)

build:
	mkdir -p build/
	cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Release $(EXTRA_GENERATE)
	cmake --build  build/ $(EXTRAM_COMPILE)

test: compile-debug
	./build/TESTS

server:
	./build/SERVER 4040

editor:
	./build/EDITOR

client:
	./build/CLIENT localhost 4040

all: clean test

clean:
	rm -Rf build/*
