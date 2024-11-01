.PHONY: all test clean editor client common server build

compile-debug:
	mkdir -p build/
	cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Debug $(EXTRA_GENERATE)
	cmake --build  build/ $(EXTRA_COMPILE)

build:
	mkdir -p build/
	cmake -S . -B ./build -DCMAKE_BUILD_TYPE=Release $(EXTRA_GENERATE)
	cmake --build  build/ $(EXTRA_COMPILE)

test: compile-debug
	./build/TESTS

server: build
	./build/SERVER

client: build
	./build/CLIENT

all: clean test

clean:
	rm -Rf build/*
