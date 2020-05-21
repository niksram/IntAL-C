GFLAGS=-g

a.out: intal_sampletest.o PES1201801972.o
	gcc $(GFLAGS) PES1201801972.o intal_sampletest.o

intal_sampletest.o: intal_sampletest.c intal.h	
	gcc -c intal_sampletest.c intal.h

PES1201801972.o: PES1201801972.c intal.h
	gcc -c PES1201801972.c intal.h 

clean:
	rm -f intal_sampletest.o PES1201801972.o intal.h.gch a.out