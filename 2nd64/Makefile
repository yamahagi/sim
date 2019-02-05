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

fsqrt.o: ./fpu/fsqrt.c
	$(obj) ./fpu/fsqrt.c

print_reg.o: ./include/print_reg.c
	$(obj) ./include/print_reg.c

sim: simcho.o simulate64.o ./include/print_reg.o ftools.o fpu.o fdiv.o fi.o fless.o feq.o fsqrt.o
	$(app) simcho.o simulate64.o  ./include/print_reg.o fpu.o fdiv.o fi.o fless.o feq.o fsqrt.o ftools.o -o sim
	rm -rf ./*.o

fib: silent ./test/bin/fib/safe/fib.ml.linked.s.txt 
	./silent ./test/bin/fib/safe/fib.ml.linked.s.txt  fib.txt

minrt: silent ./test/bin/minrt/safe/minrt.ml.linked.s.txt
	./silent ./test/bin/minrt/safe/minrt.ml.linked.s.txt  minrt.ppm ./test/bin/minrt/contest.bin

mandelbrot: silent ./test/bin/mandelbrot/safe/mandelbrot.ml.linked.s.txt
	./silent ./test/bin/mandelbrot/safe/mandelbrot.ml.linked.s.txt mandelbrot.txt

mandelbrot30: silent ./test/bin/mandelbrot/safe-30/mandelbrot.ml.linked.s.txt
	./silent ./test/bin/mandelbrot/safe-30/mandelbrot.ml.linked.s.txt mandelbrot30.txt

silent: clean
	$(obj) simulate64.c -D"SILENT=1" -D"SILENTMEM=1" -D"SILENTREG=1"
	$(obj) simcho.c -D"SILENT=1" -D"SILENTMEM=1" -D"SILENTREG=1"
	$(obj) ./fpu/ftools.c -D"SILENT=1" -D"SILENTMEM=1" -D"SILENTREG=1"
	$(obj) ./fpu/fpu.c -D"SILENT=1" -D"SILENTMEM=1" -D"SILENTREG=1"
	$(obj) ./fpu/fdiv.c -D"SILENT=1" -D"SILENTMEM=1" -D"SILENTREG=1"
	$(obj) ./fpu/fless.c -D"SILENT=1" -D"SILENTMEM=1" -D"SILENTREG=1"
	$(obj) ./fpu/feq.c -D"SILENT=1" -D"SILENTMEM=1" -D"SILENTREG=1"
	$(obj) ./fpu/fi.c -D"SILENT=1" -D"SILENTMEM=1" -D"SILENTREG=1"
	$(obj) ./fpu/fsqrt.c -D"SILENT=1" -D"SILENTMEM=1" -D"SILENTREG=1"
	$(obj) ./include/print_reg.c -D"SILENT=1" -D"SILENTMEM=1" -D"SILENTREG=1"
	$(app) simcho.o simulate64.o  ./include/print_reg.o fpu.o fdiv.o fi.o fless.o feq.o fsqrt.o ftools.o -o silent -D"SILENT=1" -D"SILENTMEM=1" -D"SILENTREG=1"
	rm -rf ./*.o

silentreg: clean
	$(obj) simulate64.c -D"SILENTREG=1"
	$(obj) simcho.c -D"SILENTREG=1"
	$(obj) ./fpu/ftools.c -D"SILENTREG=1"
	$(obj) ./fpu/fpu.c -D"SILENTREG=1"
	$(obj) ./fpu/fdiv.c -D"SILENTREG=1"
	$(obj) ./fpu/fless.c -D"SILENTREG=1"
	$(obj) ./fpu/feq.c -D"SILENTREG=1"
	$(obj) ./fpu/fi.c -D"SILENTREG=1"
	$(obj) ./fpu/fsqrt.c -D"SILENTREG=1"
	$(obj) ./include/print_reg.c -D"SILENTREG=1"
	$(app) simcho.o simulate64.o  ./include/print_reg.o fpu.o fdiv.o fi.o fless.o feq.o fsqrt.o ftools.o -o silentreg -D"SILENTREG=1"
	rm -rf ./*.o

silentmem: clean
	$(obj) simulate64.c -D"SILENTMEM=1"
	$(obj) simcho.c -D"SILENTMEM=1"
	$(obj) ./fpu/ftools.c -D"SILENTMEM=1"
	$(obj) ./fpu/fpu.c -D"SILENTMEM=1"
	$(obj) ./fpu/fdiv.c -D"SILENTMEM=1"
	$(obj) ./fpu/fless.c -D"SILENTMEM=1"
	$(obj) ./fpu/feq.c -D"SILENTMEM=1"
	$(obj) ./fpu/fi.c -D"SILENTMEM=1"
	$(obj) ./fpu/fsqrt.c -D"SILENTMEM=1"
	$(obj) ./include/print_reg.c -D"SILENTMEM=1"
	$(app) simcho.o simulate64.o  ./include/print_reg.o fpu.o fdiv.o fi.o fless.o feq.o fsqrt.o ftools.o -o silentmem -D"SILENTMEM=1"
	rm -rf ./*.o

silentmemreg: clean
	$(obj) simulate64.c -D"SILENTREG=1" -D"SILENTMEM=1"
	$(obj) simcho.c -D"SILENTREG=1" -D"SILENTMEM=1"
	$(obj) ./fpu/ftools.c -D"SILENTREG=1" -D"SILENTMEM=1"
	$(obj) ./fpu/fpu.c -D"SILENTREG=1" -D"SILENTMEM=1"
	$(obj) ./fpu/fdiv.c -D"SILENTREG=1" -D"SILENTMEM=1"
	$(obj) ./fpu/fless.c -D"SILENTREG=1" -D"SILENTMEM=1"
	$(obj) ./fpu/feq.c -D"SILENTREG=1" -D"SILENTMEM=1"
	$(obj) ./fpu/fi.c -D"SILENTREG=1" -D"SILENTMEM=1"
	$(obj) ./fpu/fsqrt.c -D"SILENTREG=1" -D"SILENTMEM=1"
	$(obj) ./include/print_reg.c -D"SILENTREG=1" -D"SILENTMEM=1"
	$(app) simcho.o simulate64.o  ./include/print_reg.o fpu.o fdiv.o fi.o fless.o feq.o fsqrt.o ftools.o -o silentmemreg -D"SILENTREG=1" -D"SILENTMEM=1"
	rm -rf ./*.o


clean: 
	rm -rf ./*.o
	rm -rf ./sim
	rm -rf ./silent
	rm -rf ./silentreg
	rm -rf ./silentmem
	rm -rf ./silentmemreg
