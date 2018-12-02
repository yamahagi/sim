
all:add sub mul div

add: test/test_add.c fpu.c ftools.c
	gcc test/test_add.c fpu.c ftools.c -o add
sub: test/test_sub.c fpu.c ftools.c
	gcc test/test_sub.c fpu.c ftools.c -o sub
mul: test/test_mul.c fpu.c ftools.c
	gcc test/test_mul.c fpu.c ftools.c -o mul
div: test/test_div.c fdiv.c ftools.c
	gcc test/test_div.c fdiv.c ftools.c -o div

clean:
	rm add sub mul div
