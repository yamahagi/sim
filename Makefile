obj = gcc -c -g
app = gcc

simulate.o: simulate.c
	$(obj) simulate.c 

simcho.o: simcho.c
	$(obj) simcho.c

test: simcho.o simulate.o
	$(app) simcho.o simulate.o -o test

clean: 
	rm -rf ./*.o
	rm -rf ./sim
