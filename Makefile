SHELL=/bin/bash

CC=mpiicc
CCFLAGS = -O0 -g -openmp 

#SRC=
TARGETS=$(SRC:.c=.exe)

all: $(TARGETS)

CG_seq.exe: testcase.c CG.c CG_main.c
	$(CC) $(CCFLAGS) $? -lm -o $@

CG_parallel.exe: testcase.c CG_parallel.c CG_parallel_main.c 
	$(CC) $(CCFLAGS) $? -lm -o $@

clean:
	rm -f *.o $(TARGETS) out_CG.txt
