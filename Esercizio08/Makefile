LIBS:=`root-config --libs`
INCS:=`root-config --cflags`
LIBS1:= Metropolis.o Block_err.o random.o

%.o : %.cpp %.h
	g++ -Wall -c $< ${INCS}

Esercizio08.1 : Esercizio08.1.cpp  Metropolis.h Block_err.h random.h ${LIBS1}
	g++ -Wall -o $@ $^

Esercizio08.2 : Esercizio08.2.cpp  Metropolis.h Block_err.h random.h ${LIBS1}
		g++ -Wall -o $@ $^

Esercizio08.3: Esercizio08.3.o
		g++ -O3 -Wall -o $@ $^ ${LIBS}

Esercizio08.3.o: Esercizio08.3.cpp
		g++ -Wall -c $< ${INCS}

clean:

	rm Esercizio08.1
	rm Esercizio08.2
	rm Esercizio08.3
	rm *.o
