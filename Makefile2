target = lu_main.exe
dependencies = testcase.h LU.h
objects = testcase.o LU.o

cc = gcc
cFlags = -std=gnu99

all: $(target)

%.o: %.c $(dependencies)
	$(cc) $(cFlags) -c -o $@ $<

$(target): $(objects)
	$(cc) $(cFlags) -o $(target).o $^

clean:
	rm -f *.exe *.obj *.o
