default: debug
debug: build/debug/main
run: build/debug/main
	./build/debug/main

build/debug/main: src/main/cpp/main.cpp
	mkdir -p build/debug/
	g++ -std=c++11 -Wall -g -Og src/main/cpp/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -o build/debug/main
