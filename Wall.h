#ifndef _WALL_H_
#define _WALL_H_

#include <stdbool.h>

typedef struct {
	bool upper, lower, left, right;
} Wall;

Wall Wall_Init();

// Remove the lower wall
void Wall_RemoveLowerWall(Wall* wall);

// Remove the upper wall of a cell
void Wall_RemoveUpperWall(Wall* wall);

// Remove the left wall of a cell
void Wall_RemoveLeftWall(Wall* wall);

// Remove the right wall of a cell
void Wall_RemoveRightWall(Wall* wall);

// Prints the character defined by the wall
// Walls: ╋ ┻ ┣ ┳ ┫ ┃ ┗ ┛ ┏ ┓ ━
void Wall_Print(Wall wall);

// Shows you how to use the Unicode wall characters
void Wall_ShowWallChars();

# endif  // _WALL_H_
