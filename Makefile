main.out: main.o ai.o estadoTablero.o
	gcc -g -Wall -o main main.o ai.o estadoTablero.o `pkg-config --cflags --libs gtk+-2.0`

main.o: main.c
	gcc -g -Wall -c main.c `pkg-config --cflags --libs gtk+-2.0`

ai.o: ai.c
	gcc -g -Wall -c ai.c `pkg-config --cflags --libs gtk+-2.0`

estadoTablero.o: estadoTablero.c
	gcc -g -Wall -c estadoTablero.c `pkg-config --cflags --libs gtk+-2.0`

clean:
	rm *.o
