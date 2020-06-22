LIBS1:= Block_err.o

Esercizio04.1 : Esercizio04.1.cpp  Esercizio04.1.h
	g++ -Wall -o $@ $^

Esercizio04.2 : Esercizio04.2.cpp  Esercizio04.2.h Block_err.h ${LIBS1}
		g++ -Wall -o $@ $^

Esercizio04.07 : Esercizio04.07.cpp  Esercizio04.07.h Block_err.h ${LIBS1}
		g++ -Wall -o $@ $^
		
%.o: %.cpp %.h
	g++ -Wall -c -O3 $<

clean:
	rm esercizio04.1
	rm esercizio04.2
	rm *.o
