target = main.exe
dependencies = testcase.h LU.h
objects = main.o testcase.o LU.o

cc = gcc
cFlags = -Wall -Werror -Wextra -std=gnu99

all: $(target)

%.o: %.c $(dependencies)
	$(cc) $(cFlags) -c -o $@ $<

$(target): $(objects)
	$(cc) $(cFlags) -o $(target).o $^

clean:
	rm -f *.exe *.obj *.o
