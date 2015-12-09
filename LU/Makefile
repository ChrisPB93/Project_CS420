filesSeq = sequentialLU.c test.c timer.c
filesPar = parallelLU.c test.c timer.c

cc = mpiicc
cFlags = -O0 -g -std=c99
mpi = mpiicc
mpiFlags = -O0 -g -std=c99 -qopenmp

all: sequentialLU parallelLU

sequentialLU: $(objectsSeq)
	$(cc) $(cFlags) $(filesSeq) -lm -o $@.exe

parallelLU:
	$(mpi) $(mpiFlags) $(filesPar) -lm -o $@.exe

clean:
	rm -f *.exe *.obj *.o
