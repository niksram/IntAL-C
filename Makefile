GFLAGS=

a.out: off_intal_sampletest.o PES1201801972.o
	gcc $(GFLAGS) PES1201801972.o off_intal_sampletest.o

off_intal_sampletest.o: off_intal_sampletest.c intal.h	
	gcc -c off_intal_sampletest.c intal.h

PES1201801972.o: PES1201801972.c intal.h
	gcc -c PES1201801972.c intal.h 

clean:
	rm -f off_intal_sampletest.o PES1201801972.o intal.h.gch a.out