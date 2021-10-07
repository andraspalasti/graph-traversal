default: build

build:
	gcc -o graph src/main.c src/graph.c src/coordinate.c src/edges.c src/node.c

debug:
	gcc -o graph src/main.c src/graph.c src/coordinate.c src/edges.c src/node.c -g

run: build
	./graph