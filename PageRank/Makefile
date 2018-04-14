CC=g++
CFLAGS= -std=c++11 -Wall -Wextra -pedantic -g -lm -Wno-unused-variable -Wno-unused-parameter



all: main mult

main: main.cpp VectorMapMatrix.cpp Util.cpp
	$(CC) $(CFLAGS) $^ -o tp1
	
mult: mult.cpp VectorMapMatrix.cpp Util.cpp
	$(CC) $(CFLAGS) $^ -o $@

clean:
	rm main
	rm mult
	rm *.txt

