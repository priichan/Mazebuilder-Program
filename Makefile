CC=gcc
FLAGS=-Wall -Werror -g

all: MazeBuilder 
Wall.o: Wall.c 
	gcc -Wall -Werror -g -c Wall.c -o Wall.o
Maze.o: Maze.c
	gcc -Wall -Werror -g -c Maze.c -o Maze.o
DisjointSetADT.o: DisjointSetADT.c 
	gcc -Wall -Werror -g -c DisjointSetADT.c -o DisjointSetADT.o
MazeBuilder.o: MazeBuilder.c
	gcc -Wall -Werror -g -c MazeBuilder.c -o MazeBuilder.o
MazeBuilder:  MazeBuilder.c Wall.o Maze.o DisjointSetADT.o
	gcc -Wall -Werror -g MazeBuilder.c Wall.o Maze.o DisjointSetADT.o -o MazeBuilder
clean:
	rm -f *.o
