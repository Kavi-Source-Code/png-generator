CC = cc

.PHONY: all clean

all: png

png: png.c
	$(CC) png.c -o png

clean:
	rm -f png

