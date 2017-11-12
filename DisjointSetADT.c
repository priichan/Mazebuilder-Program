#include "DisjointSetADT.h"

#include <stdbool.h>
#include <stdlib.h>

void DisjointSet_PathCompress(DisjointSet* ds, unsigned int i, unsigned int rep) {
	int j = i;
	while (j != rep) {
		unsigned int temp = ds->setRepresentative[j];
		ds->setRepresentative[j] = rep;
		j = temp;
	}
}

// Initialize a DisjointSet data structure
DisjointSet* DisjointSet_Init(unsigned int n) {
	DisjointSet* result = malloc(sizeof(DisjointSet));
	result->n = n;
	result->numberOfSets = n;
	result->setRepresentative = malloc(sizeof(unsigned int) * n);
	for (unsigned int i = 0; i < n; i++) {
		result->setRepresentative[i] = i;
	}
	return result;
}

// Merge sets containing elements i and j
// Returns true if a union occurred and false if
// the union was unnecessary
bool DisjointSet_Union(DisjointSet* ds, unsigned int i, unsigned int j) {
	if (DisjointSet_SameSet(ds, i, j)) {
		return false;
	} else {
		ds->setRepresentative[DisjointSet_Find(ds, i)] = DisjointSet_Find(ds, j);
		ds->numberOfSets--;
		return true;
	}
}

// Find set representative of element i
unsigned int DisjointSet_Find(DisjointSet* ds, unsigned int i) {
  unsigned int rep = i;
  while (ds->setRepresentative[rep] != rep) {
  	rep = ds->setRepresentative[rep];
  }
  DisjointSet_PathCompress(ds, i, rep);
  return rep;
}

// Returns true if and only if elements i and j are in the same set
bool DisjointSet_SameSet(DisjointSet* ds, unsigned int i, unsigned int j) {
	return DisjointSet_Find(ds, i) == DisjointSet_Find(ds, j);
}

// Returns the number of sets (intially n)
unsigned int DisjointSet_NumberOfSets(DisjointSet* ds) {
	return ds->numberOfSets;
}

// De-allocates DisjointSet
void DisjointSet_Destroy(DisjointSet* ds) {
	free(ds->setRepresentative);
	free(ds);
}
