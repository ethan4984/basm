CC = gcc
CFLAGS = -Wall -Wextra -Isrc

all:	
	$(CC) $(CFLAGS) src/*.c -o basm
test: all
	./basm test/preprocessor.txt bruh	
clean:
	rm basm
