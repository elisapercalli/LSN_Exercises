LIBS1:= Metropolis.o Block_err.o random.o

Esercizio05.1 : Esercizio05.1.cpp  Metropolis.h Block_err.h random.h ${LIBS1}
	g++ -Wall -o $@ $^

%.o: %.cpp %.h
	g++ -Wall -c -O3 $<

clean:
	rm esercizio05.1
	rm *.o
