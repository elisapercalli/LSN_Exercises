# LSN_Exercises
Note di compilazione ed esecuzione programmi:

Per far girare i programmi in ogni cartella vi è un makefile, che basta far girare con make Esercizio##.# (es: make Esercizio 09.1). Quasi tutti gli esericizi hanno eseguibili diversi, che si chiamano come detto sopra. Come da richiesta non ho creato sotto coartelle, quindi mi scuso se alcune cartelle sono leggermente confuse, a causa dei numerosi file di output. I jupyter-notebook si trovano tutti sotto il nome di Exercise##.ipynb (sono in inglese).

Altre note:
- per l'esercizio 10 la compilazione con mpi è gia scritta nel makefile, quindi forse facendolo girare su altre macchine potrebbe essere necessario dare altri comandi per compilarlo ed eseguirlo (sul mio computer si esegue con "mpiexec -np 4 ./Esercizio10.2").
- Nell'esercitazione 4 non c'è un file separato per l'esercizio 04.3, dato che era lo stesso codice dell'esercizio 04.2, ma con diversi input. L'esercizio 04.2 prende come input il file input.dat(con parametri programma), redo.dat(0 per partire da 0, 1 per partire da una vecchia configurazione), config.0/config.final.

