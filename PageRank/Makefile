CC=g++
CFLAGS= -std=c++11 -Wall -Wextra -pedantic -g -lm -Wno-unused-variable -Wno-unused-parameter



all: main mult

main: main.cpp Matriz.cpp
	$(CC) $(CFLAGS) $^ -o $@

mult: mult.cpp Matriz.cpp
	$(CC) $(CFLAGS) $^ -o $@
	


clean:
	rm main
	rm mult
	rm *.txt

