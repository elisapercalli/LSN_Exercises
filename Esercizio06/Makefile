CC = g++
CFLAGS = -Wall -O3 --std=c++11

Esercizio06.1 : Esercizio06.1.o random.o
	$(CC) -o $@ $^

Esercizio06.1.o : Esercizio06.1.cpp
	$(CC) -c Esercizio06.1.cpp -o Esercizio06.1.o $(CFLAGS)

random.o : random.cpp random.h
	$(CC) -c random.cpp -o random.o $(CFLAGS)

clean :
	rm *.o Esercizio06.1
