obj = gcc -c -g
app = gcc

.PHONY: [sim]

all: sim simcho.o simulate.o ftools.o

simulate.o: simulate.c
	$(obj) simulate.c

simcho.o: simcho.c
	$(obj) simcho.c

ftools.o: ./fpu/ftools.c
	$(obj) ./fpu/ftools.c

sim: simcho.o simulate.o ftools.o
	$(app) simcho.o simulate.o ftools.o -o sim

clean: 
	rm -rf ./*.o
	rm -rf ./sim
