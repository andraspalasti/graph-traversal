default: build

build:
	gcc -o graph src/main.c src/graph.c src/coordinate.c src/edges.c

debug:
	gcc -o graph src/main.c src/graph.c src/coordinate.c src/edges.c -g

run: build
	./graph