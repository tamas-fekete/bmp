picture : bmp.o canvas.o
	gcc -o picture bmp.o canvas.o -lm

canvas.o : canvas.c
	gcc -c canvas.c

bmp.o : bmp.c
	gcc -c bmp.c
