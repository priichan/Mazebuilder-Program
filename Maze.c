#include "Maze.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// Create a cell with fields i, j
// 
// typedef struct {
// 	unsigned int i, j;
// } Cell;
Cell Cell_Init(unsigned int i, unsigned int j) {
	Cell result;
	result.i = i;
	result.j = j;
	return result;
}

// Initialize a rows x cols maze with all walls up
// 
// typedef struct {
// 	unsigned int rows, cols;
// 	DisjointSet* cells;
// 	Wall** walls;
// } Maze;
	Maze* Maze_Init(unsigned int rows, unsigned int cols) {
	Maze* result = malloc(sizeof(Maze));
	result->rows = rows;
	result->cols = cols;
	Maze_InitializeWalls(result);
	result->cells = DisjointSet_Init(rows * cols);
	return result;
}

// Allocates space for walls and initializes them so that
// each cell is completely surrounded by walls
void Maze_InitializeWalls(Maze* M) {
	// malloc array of pointers
	
	unsigned int wallRows = 1 + M->rows;
	unsigned int wallCols = 1 + M->cols;
	M->walls = (Wall**)malloc(sizeof(Wall*) * wallRows);
	// malloc each array (row)
	for (int i = 0; i < wallRows; ++i) {
		M->walls[i] = (Wall*)malloc(sizeof(Wall) * wallCols);
	}

	// initialize every wall cell to be a cross
	for (int i = 0; i < wallRows; ++i) {
		for (int j = 0; j < wallCols; ++j) {
			M->walls[i][j] = Wall_Init();
		}
	}

	// cut off wall parts as necessary
	for (int i = 0; i < wallRows; ++i) {
		for (int j = 0; j < wallCols; ++j) {
			if (i == 0) {
				Wall_RemoveUpperWall(&(M->walls[i][j]));
			}
			if (j == 0) {
				Wall_RemoveLeftWall(&(M->walls[i][j]));
			}
			if (j == wallCols - 1) {
				Wall_RemoveRightWall(&(M->walls[i][j]));
			}
			if (i == wallCols - 1) {
				Wall_RemoveLowerWall(&(M->walls[i][j]));
			}
		}
	}

}

// Break wall between cells if they neighbor and there is no
// current path between each other. Returns true if it succeeds
// and false otherwise
void Maze_BreakWall(Maze* M, Cell C1, Cell C2) {
	// check if cells are adjacent

	if (((C2.i == C1.i) && (C2.j == (C1.j - 1))) || ((C2.i == (C1.i - 1)) && (C2.j == C1.j)) || ((C2.i == C1.i) && (C2.j == (C1.j + 1))) || ((C2.i == (C1.i + 1)) && (C2.j == C1.j))) {
		// check if cells are in the same room
		unsigned int C1CellID = (M->cols) * C1.i + C1.j;
		unsigned int C2CellID = (M->cols) * C2.i + C2.j;
		if (DisjointSet_SameSet(M->cells, C1CellID, C2CellID) == true) {
			printf("Cells already have a path between them. Try again.\n");
		}
		else {
			DisjointSet_Union(M->cells, C1CellID, C2CellID);
			if ((C1CellID == C2CellID + 1) || (C1CellID == C2CellID - 1)) { // horizontally adjacent cells
				int largerIndex = 0;
				if (C1.j > C2.j) {
					largerIndex = C1.j;
				}
				else {
					largerIndex = C2.j;
				}
				Wall_RemoveLowerWall(&(M->walls[C1.i][largerIndex])); // remove lower wall of upper wall portion
				Wall_RemoveUpperWall(&(M->walls[C1.i + 1][largerIndex])); // remove upper wall of lower wall portion
			}
			else {
				int largerIndex = 0;
				if (C1.i > C2.i) {
					largerIndex = C1.i;
				}
				else {
					largerIndex = C2.i;
				}
				Wall_RemoveRightWall(&(M->walls[largerIndex][C1.j])); // remove right wall of left wall portion
				Wall_RemoveLeftWall(&(M->walls[largerIndex][C1.j + 1])); // remove left wall of right wall portion
			}

		}
	}
	else {
		printf("Cells are not adjacent. Try again.\n");
	}
}

// Returns true if not complete.
// Maze is complete if every pair of cells has a path between each other
bool Maze_IsIncomplete(const Maze* M) {
	if (DisjointSet_NumberOfSets(M->cells) != 1) {
		return true;
	}
	else {
		return false;
	}
}

// Print maze
void Maze_Print(const Maze* M) {
	
	for (int i = 0; i < (M->rows + 1); ++i) {
		for (int j = 0; j < (M->cols + 1); ++j) {
			Wall_Print(M->walls[i][j]);
		}
		printf("\n");
	}
}

// Deallocate memory used for Maze
void Maze_Destroy(Maze* M) {
	free(M->walls);
	DisjointSet_Destroy(M->cells);
}
