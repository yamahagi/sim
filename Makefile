obj = gcc -c -g -O2
app = gcc -O2

.PHONY: [sim]

all: sim simcho.o simulate.o fpu.o ftools.o

simulate.o: simulate.c
	$(obj) simulate.c

simcho.o: simcho.c
	$(obj) simcho.c

ftools.o: ./fpu/ftools.c
	$(obj) ./fpu/ftools.c
ftools.o: ./fpu/fpu.c
	$(obj) ./fpu/fpu.c

sim: simcho.o simulate.o ftools.o fpu.o
	$(app) simcho.o simulate.o fpu.o ftools.o -o sim

silent: clean
	$(obj) simulate.c -D"SILENT=1"
	$(obj) simcho.c -D"SILENT=1"
	$(obj) ./fpu/ftools.c -D"SILENT=1"
	$(obj) ./fpu/fpu.c -D"SILENT=1"
	$(app) simcho.o simulate.o ftools.o -o sim

clean: 
	rm -rf ./*.o
	rm -rf ./sim
