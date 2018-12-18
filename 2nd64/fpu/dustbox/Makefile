
all:add sub mul div

add: test/test_add.c fpu.c ftools.c
	gcc test/test_add.c fpu.c ftools.c -o add
sub: test/test_sub.c fpu.c ftools.c
	gcc test/test_sub.c fpu.c ftools.c -o sub
mul: test/test_mul.c fpu.c ftools.c
	gcc test/test_mul.c fpu.c ftools.c -o mul
div: test/test_div.c fdiv.c ftools.c
	gcc test/test_div.c fdiv.c ftools.c -o div
sqrt: testsq.c ../fsqrt.c ../ftools.c
	gcc testsq.c ../fsqrt.c ../ftools.c -o sqrt
ftoi: test/test_ftoi.c fi.c ftools.c
	gcc test/test_ftoi.c fi.c ftools.c -o ftoi
itof: test/test_itof.c fi.c ftools.c
	gcc test/test_itof.c fi.c ftools.c -o itof
clean:
	rm add sub mul div sqrt ftoi itof
