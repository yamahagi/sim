test: simulate.c simcho.c
	gcc  -c simulate.c
	gcc  -c simcho.c
	gcc simulate.o simcho.o -o test

clean:
	rm -rf ./*.o
