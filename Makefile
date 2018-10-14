obj = gcc -c -g
app = gcc

.PHONY: [sim]

all: sim simcho.o simulate.o

simulate.o: simulate.c
	$(obj) simulate.c 

simcho.o: simcho.c
	$(obj) simcho.c

sim: simcho.o simulate.o
	$(app) simcho.o simulate.o -o sim

clean: 
	rm -rf ./*.o
	rm -rf ./sim
