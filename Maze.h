#ifndef _MAZE_H_
#define _MAZE_H_

#include "DisjointSetADT.h"
#include "Wall.h"

typedef struct {
	unsigned int i, j;
} Cell;

typedef struct {
	unsigned int rows, cols;
	DisjointSet* cells;
	Wall** walls;
} Maze;

// Create a cell with fields i, j
Cell Cell_Init(unsigned int i, unsigned int j);

// Initialize a rows x cols maze with all walls up
Maze* Maze_Init(unsigned int rows, unsigned int cols);

// Allocates space for walls and initializes them so that
// each cell is completely surrounded by walls. This function
// is called by Maze_Init and should not be called by a user
void Maze_InitializeWalls(Maze* M);

// Break wall between cells if they neighbor and there is no
// current path between each other
void Maze_BreakWall(Maze* M, Cell C1, Cell C2);

// Returns true if not complete
// Maze is complete if every pair of cells has a path between each other
bool Maze_IsIncomplete(const Maze* M);

// Print maze
void Maze_Print(const Maze* M);

// Deallocate memory used for Maze
void Maze_Destroy(Maze* M);

#endif  // _MAZE_H_
