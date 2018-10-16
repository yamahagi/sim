obj = gcc -c -g
app = gcc

.PHONY: [sim]

all: sim simcho.o simulate.o ftest.o

simulate.o: simulate.c
	$(obj) simulate.c

simcho.o: simcho.c
	$(obj) simcho.c

ftest.o: ./fpu/ftest.c
	$(obj) ./fpu/ftest.c

sim: simcho.o simulate.o ftest.o
	$(app) simcho.o simulate.o ftest.o -o sim

clean: 
	rm -rf ./*.o
	rm -rf ./sim
