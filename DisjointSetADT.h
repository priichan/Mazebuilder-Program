#ifndef _DISJOINT_SET_ADT_
#define _DISJOINT_SET_ADT_

#include <stdbool.h>

typedef struct {
	unsigned int n, numberOfSets;
	unsigned int* setRepresentative;
} DisjointSet;

// Initialize a DisjointSet data structure
DisjointSet* DisjointSet_Init(unsigned int n);

// Merge sets containing elements i and j
// Returns true if a union occurred and false if
// the union was unnecessary
bool DisjointSet_Union(DisjointSet* ds, unsigned int i, unsigned int j);

// Find set representative of element i
unsigned int DisjointSet_Find(DisjointSet* ds, unsigned int i);

// Returns true if and only if elements i and j are in the same set
bool DisjointSet_SameSet(DisjointSet* ds, unsigned int i, unsigned int j);

// Returns the number of sets (intially n)
unsigned int DisjointSet_NumberOfSets(DisjointSet* ds);

// De-allocates DisjointSet
void DisjointSet_Destroy(DisjointSet* ds);

#endif  // _DISJOINT_SET_ADT_
