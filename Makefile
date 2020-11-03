C = gcc
CFLAGS = -Wall -Wextra -Isrc

all:	
	$(C) $(CFLAGS) src/*.c -o basm
test: all
	./basm test/preprocessor.txt bruh	
clean:
	rm basm
