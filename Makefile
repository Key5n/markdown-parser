SRC = $(wildcard **/*.c)
MAIN = ./task8
INPUT = in.md

# test: ./task8.c ./markdown/generator.c ./markdown/parser.c ./lib/regexp.c ./lib/list.c
# 	gcc ./task8.c ./markdown/generator.c ./markdown/parser.c ./lib/regexp.c ./lib/list.c -o task8
# 		$(MAIN) $(INPUT) 

task8: task8.o parser.o generator.o list.o regexp.o
	gcc -o task8 task8.o parser.o generator.o list.o regexp.o 
	$(MAIN) $(INPUT)

task8.o: task8.c
	gcc -c task8.c

parser.o: markdown/parser.c
	gcc -c markdown/parser.c

generator.o: markdown/generator.c lib/list.c
	gcc -c markdown/generator.c lib/list.c

list.o: lib/list.c
	gcc -c lib/list.c

regexp.o: lib/regexp.o
	gcc -c lib/regexp.c