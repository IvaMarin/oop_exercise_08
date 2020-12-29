CC=g++
FLAGS=-std=c++17 -pedantic -Wall -Wextra -Wno-unused-variable -pthread
OUTPUT=oop_exercise_08

all: main.cpp
	$(CC) $(FLAGS) main.cpp -o $(OUTPUT)
clean:
	rm *.o $(OUTPUT)