picture : bmp.o canvas.o vector.o
	gcc -o picture bmp.o canvas.o vector.o -lm

canvas.o : canvas.c
	gcc -c canvas.c

bmp.o : bmp.c
	gcc -c bmp.c

vector.o : vector.c
	gcc -c vector.c
