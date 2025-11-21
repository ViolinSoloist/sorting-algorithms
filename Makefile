run: main
	./main

main: main.c fila.c queue.h
	gcc main.c fila.c -o main -Wall

fila.o: fila.c queue.h
	gcc fila.c -o -Wall

clean:
	rm *.o main

.PHONY: run clean