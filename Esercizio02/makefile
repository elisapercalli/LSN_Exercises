LIBS1:= funzioni.o random.o integral.o
LIBS2:= funzioni.o random.o

Esercizio02.1 : Esercizio02.1.cpp random.h funzioni.h integral.h ${LIBS1}
	g++ -Wall -o $@ $^

Esercizio02.2 :: Esercizio02.2.cpp random.h funzioni.h ${LIBS2}
	g++ -Wall -o $@ $^

%.o: %.cpp %.h
	g++ -Wall -c -O3 $<

clean:
	rm esercizio01.1
	rm esercizio02.2
	rm *.o
