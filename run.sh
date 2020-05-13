gcc intal.h
gcc -c intal_sampletest.c intal.h
gcc -c PES1201801972.c intal.h
gcc PES1201801972.o intal_sampletest.o
rm -f intal_sampletest.o PES1201801972.o intal.h.gch
./a.out