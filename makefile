all: a.out

CC=g++
CPPFLAGS=-O3

a.out: rk.cpp
	$(CC) $(CPPFLAGS) $< -o $@

clean:
	rm -f a.out *.dat
