SRC = $(wildcard **/*.c)
MAIN = ./task8
INPUT = in.md

test: ./task8.c ./markdown/generator.c ./markdown/parser.c ./lib/regexp.c ./lib/list.c
	gcc ./task8.c ./markdown/generator.c ./markdown/parser.c ./lib/regexp.c ./lib/list.c -o task8
		$(MAIN) $(INPUT) 