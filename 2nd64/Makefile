obj = gcc -c -g -O2
app = gcc -O2

.PHONY: [sim]

all: sim simcho.o simulate64.o ftools.o fpu.o fdiv.o

simulate64.o: simulate64.c
	$(obj) simulate64.c 

simcho.o: simcho.c 
	$(obj) simcho.c

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
	$(app) simcho.o simulate64.o  ./include/print_reg.c fpu.o fdiv.o fi.o fless.o feq.o ftools.o -o sim
	rm -rf ./*.o

fib: sim /Users/ohagimasaya/Desktop/B3/3A/cpuex/mine/bin/fib/safe/fib.ml.linked.s.txt
	./sim /Users/ohagimasaya/Desktop/B3/3A/cpuex/mine/bin/fib/safe/fib.ml.linked.s.txt  fib.txt

minrt: sim /Users/ohagimasaya/Desktop/B3/3A/cpuex/mine/bin/minrt/safe/minrt.ml.linked.s.txt
	./sim /Users/ohagimasaya/Desktop/B3/3A/cpuex/mine/bin/minrt/safe/minrt.ml.linked.s.txt  minrt.txt

mandelbrot: sim /Users/ohagimasaya/Desktop/B3/3A/cpuex/mine/bin/mandelbrot/safe/mandelbrot.ml.linked.s.txt
	./sim /Users/ohagimasaya/Desktop/B3/3A/cpuex/mine/bin/mandelbrot/safe/mandelbrot.ml.linked.s.txt  mandelbrot.txt

mandelbrot30: sim /Users/ohagimasaya/Desktop/B3/3A/cpuex/mine/bin/mandelbrot/safe-30/mandelbrot.ml.linked.s.txt
	./sim /Users/ohagimasaya/Desktop/B3/3A/cpuex/mine/bin/mandelbrot/safe-30/mandelbrot.ml.linked.s.txt  mandelbrot30.txt

silent: clean
	$(obj) -DSILENT simulate64.c
	$(obj) simcho.c
	$(obj) ./fpu/ftools.c
	$(obj) ./fpu/fpu.c
	$(obj) ./fpu/fdiv.c
	$(obj) ./fpu/fless.c
	$(obj) ./fpu/feq.c
	$(obj) ./fpu/fi.c
	$(app) simcho.o simulate64.o  ./include/print_reg.c fpu.o fdiv.o fi.o fless.o feq.o ftools.o -o sim
	rm -rf ./*.o

silentreg: clean
	$(obj) simulate64.c -D"SILENTREG=1"
	$(obj) simcho.c -D"SILENT=1"
	$(obj) ./fpu/ftools.c -D"SILENT=1"
	$(obj) ./fpu/fpu.c -D"SILENT=1"
	$(obj) ./fpu/fdiv.c
	$(obj) ./fpu/fless.c
	$(obj) ./fpu/feq.c
	$(obj) ./fpu/fi.c
	$(app) simcho.o simulate64.o  ./include/print_reg.c fpu.o fdiv.o fi.o fless.o feq.o ftools.o -o sim
	rm -rf ./*.o

silentmem: clean
	$(obj) -DSILENTMEM simulate64.c
	$(obj) simcho.c
	$(obj) ./fpu/ftools.c
	$(obj) ./fpu/fpu.c
	$(obj) ./fpu/fdiv.c
	$(obj) ./fpu/fless.c
	$(obj) ./fpu/feq.c
	$(obj) ./fpu/fi.c
	$(app) -DSILENTMEM simcho.o simulate64.o  ./include/print_reg.c fpu.o fdiv.o fi.o fless.o feq.o ftools.o -o sim
	rm -rf ./*.o

clean: 
	rm -rf ./*.o
	rm -rf ./sim
