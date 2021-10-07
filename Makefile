default: build

build:
	gcc -o graph src/main.c src/graph.c src/point.c

debug:
	gcc -o graph src/main.c src/graph.c src/point.c -g

run: build
	./graph