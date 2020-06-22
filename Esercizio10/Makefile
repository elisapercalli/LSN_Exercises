LIBS1:=  random.o element.o Metropolis.o
LIBS2:=  random.o functions.o

Esercizio10.1 : Esercizio10.1.cpp random.h element.h Metropolis.h ${LIBS1}
	g++ -Wall -o $@ $^

Esercizio10.2 : Esercizio10.2.cpp random.h functions.h ${LIBS2}
	mpicxx -o $@ $^

%.o : %.cpp %.h
	g++ -Wall -c $< ${INCS}

clean:
	rm Esercizio10.1
	rm Esercizio10.2
	rm *.o
