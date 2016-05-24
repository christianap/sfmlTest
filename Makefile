default: debug
debug: build/debug/main
release: build/release/main
run: build/debug/main
	./build/debug/main

run-release: build/release/main
	./build/release/main

build/debug/main: src/main/cpp/main.cpp
	mkdir -p build/debug/
	g++ -std=c++11 -Wall -g -Og src/main/cpp/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -o build/debug/main

build/release/main: src/main/cpp/main.cpp
	mkdir -p build/release/
	g++ -std=c++11 -Wall -g -O3 src/main/cpp/*.cpp -lsfml-graphics -lsfml-window -lsfml-system -o  build/release/main
