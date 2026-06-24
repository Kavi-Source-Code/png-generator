CC = cc

.PHONY: all clean

all: png grad

png: png.c
	$(CC) png.c -o png

grad: grad.c
	$(CC) grad.c -o grad

clean:
	rm -f png grad

