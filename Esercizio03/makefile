LIBS1:= funzioni.o random.o pricing.o

Esercizio03.1 : Esercizio03.1.cpp random.h funzioni.h pricing.h ${LIBS1}
	g++ -Wall -o $@ $^

%.o: %.cpp %.h
	g++ -Wall -c -O3 $<

clean:
	rm esercizio03.1
	rm *.o
