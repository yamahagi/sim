obj = gcc -c -g -O2
app = gcc -O2

.PHONY: [sim]

all: sim simcho.o simulate64.o ftools.o fpu.o fdiv.o

simulate64.o: simulate64.c ./include/print_reg.c
	$(obj) simulate64.c ./include/print_reg.c

simcho.o: simcho.c ./include/print_reg.c
	$(obj) simcho.c ./include/print_reg.c

ftools.o: ./fpu/ftools.c
	$(obj) ./fpu/ftools.c
fpu.o: ./fpu/fpu.c
	$(obj) ./fpu/fpu.c

fdiv.o: ./fpu/fdiv.c
	$(obj) ./fpu/fdiv.c

fi.o: ./fpu/fi.c
	$(obj) ./fpu/fi.c

fless.o: ./fpu/fless.c
	$(obj) ./fpu/fless.c

feq.o: ./fpu/feq.c
	$(obj) ./fpu/feq.c

sim: simcho.o simulate64.o ./include/print_reg.c ftools.o fpu.o fdiv.o fi.o fless.o feq.o
	$(app) simcho.o simulate64.o ./include/print_reg.c fpu.o fdiv.o fi.o fless.o feq.o ftools.o -o sim

silent: clean
	$(obj) simulate64.c -D"SILENT=1"
	$(obj) simcho.c -D"SILENT=1"
	$(obj) ./fpu/ftools.c -D"SILENT=1"
	$(obj) ./fpu/fpu.c -D"SILENT=1"
	$(app) simcho.o simulate64.o ftools.o -o sim

clean: 
	rm -rf ./*.o
	rm -rf ./sim
