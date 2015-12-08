filesSeq = sequentialLU.c test.c timer.c
filesPar = parallelLU.c test.c timer.c

cc = gcc
cFlags = -O0 -std=c99
mpi = mpicc
mpiFlags = -O0 -std=c99 -fopenmp

all: sequentialLU parallelLU

sequentialLU: $(objectsSeq)
	$(cc) $(cFlags) $(filesSeq) -lm -o $@.exe

parallelLU:
	$(mpi) $(mpiFlags) $(filesPar) -lm -o $@.exe

clean:
	rm -f *.exe *.obj *.o
