SHELL=/bin/bash

CC=mpiicc
CCFLAGS = -O0 -g -std=c99 -openmp 

#SRC=
TARGETS=$(SRC:.c=.exe)

all: $(TARGETS)

CG_seq.exe: test.c CG.c CG_main.c
	$(CC) $(CCFLAGS) $? -lm -o $@

CG_parallel.exe: test.c CG_parallel.c CG_parallel_main.c 
	$(CC) $(CCFLAGS) $? -lm -o $@

clean:
	rm -f *.o $(TARGETS) out_CG.txt
