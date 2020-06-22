LIBS1:=  random.o functions.o

Esercizio09.1 : Esercizio09.1.cpp random.h functions.h ${LIBS1}
	g++ -Wall -o $@ $^

%.o : %.cpp %.h
	g++ -Wall -c $< ${INCS}

clean:
	rm Esercizio09.1
	rm *.o
