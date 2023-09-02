build:
	clang main.c -o main
debug:
	clang -g -O0 -O main.c -o main
