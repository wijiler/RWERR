build:
	clang main.c -o ./Build/rwe
debug:
	clang -g -O0 -O main.c -o main
