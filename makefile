.PHONY: clean

picture : bmp.o canvas.o vector.o main.o
	gcc -o picture main.o bmp.o canvas.o vector.o -lm

canvas.o : canvas.c
	gcc -c canvas.c

bmp.o : bmp.c
	gcc -c bmp.c

vector.o : vector.c
	gcc -c vector.c

main.o : main.c
	gcc -c main.c

clean : 
	rm -r *.o


