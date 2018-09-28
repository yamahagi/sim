# OCB = ocamlbuild -use-ocamlfind -use-menhir -I src
OCB = ocamlbuild -use-ocamlfind -I src

all:
	$(OCB) main.native
clean:
	$(OCB) -clean



