/*
 * MazeBuilder.c
 * Name / StudentID
 */

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "Maze.h"

#define MAX_BUFFER_SIZE 1028

void flushStdin();
Cell getCell(const Maze M, const char* cellName);
void printUsage(const char* programName);
void readRowsAndCols(char* argv[], int* rows, int* cols);

int main(int argc, char* argv[]) {
    if (argc != 3) {
        printUsage(argv[0]);
        exit(0); 
    }
    int rows = 0, cols = 0;
    readRowsAndCols(argv, &rows, &cols);

    // Run maze builder
    Maze* M = Maze_Init(rows, cols);
    do {
        Maze_Print(M);
        printf("\nEnter two neighboring cells to break a wall.\n");
        Cell C1 = getCell(*M, "First"), C2 = getCell(*M, "Second");
        Maze_BreakWall(M, C1, C2);
    } while (Maze_IsIncomplete(M));
    Maze_Print(M);
    printf("Your maze is complete!\n");
    return 0;
}

void flushStdin() {
    char c;
    while ((c = getchar()) != EOF && c != '\n') {}
}

Cell getCell(const Maze M, const char* cellName) {    
    printf("%s cell: ", cellName);
    int i = 0, j = 0;
    int scanfResult = scanf("%d %d", &i, &j);
    flushStdin();
    while (scanfResult != 2 || i >= M.rows || j >= M.cols) {
        printf("Cell out of bounds. Try again.\n");
        scanfResult = scanf("%d %d", &i, &j);
        flushStdin();
    }
    return Cell_Init(i, j);
}

void printUsage(const char* programName) {
    printf("Usage: %s <number of rows> <number of cols>\n", programName);
}

void readRowsAndCols(char* argv[], int* rows, int* cols) {
    *rows = atoi(argv[1]);
    *cols = atoi(argv[2]);
    if ((rows < 0) || (cols < 0)) {
	printf("Usage: MazeBuilder <number of rows> <number of cols>\n<number of rows> and <number of cols> must be positive\n");
	exit(0);
	}
}
