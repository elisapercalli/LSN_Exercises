LIBS1:= funzioni.o random.o

Esercizio01.1 : Esercizio01.1.cpp random.h funzioni.h ${LIBS1}
	g++ -Wall -o $@ $^

Esercizio01.2 :: Esercizio01.2.cpp random.h funzioni.h ${LIBS1}
	g++ -Wall -o $@ $^

Esercizio01.3 :: Esercizio01.3.cpp random.h funzioni.h ${LIBS1}
		g++ -Wall -o $@ $^

%.o: %.cpp %.h
	g++ -Wall -c -O3 $<

clean:
	rm esercizio01.1
	rm esercizio01.2
	rm esrecizio01.3
	rm *.o
