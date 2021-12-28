#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

#include "tas.h"

/****************************************************************
* TOUTES LES FONCTIONS DANS CE FICHIER SAUF destroyMinHeap ONT ETES PRISES
* DE CE SITE : https://www.geeksforgeeks.org/prims-mst-for-adjacency-list-representation-greedy-algo-6/?ref=lbp
****************************************************************/


// Initialise un noeud d'un tas 
// Complexité : O(1)
MinHeapNode* newMinHeapNode(int v, int key)
{
	MinHeapNode* minHeapNode = (MinHeapNode*)malloc(sizeof(MinHeapNode));
	minHeapNode->v = v;
	minHeapNode->key = key;
	return minHeapNode;
}

// Initialise un tas 
// Complexité : O(1)
MinHeap* createMinHeap(int capacity)
{
	MinHeap* minHeap = (MinHeap*)malloc(sizeof(MinHeap));
	minHeap->pos = (int*)malloc(capacity * sizeof(int));
	minHeap->size = 0;
	minHeap->capacity = capacity;
	minHeap->array = (MinHeapNode**)malloc(capacity * sizeof(MinHeapNode**));
	return minHeap;
}

// liberer la memoire d'un tas 
// Complexité : O(1)
void destroyMinHeap(MinHeap* minHeap)
{
    free(minHeap->array);
    free(minHeap->pos);
    free(minHeap);
}

// échanger entre le noeud a et le noeud b dans le tas
// Complexité : O(1)
void swapMinHeapNode(MinHeapNode** a, MinHeapNode** b)
{
	MinHeapNode* t = *a;
	*a = *b;
	*b = t;
}

// entasser un tas à partir d'un indice donné 
// Complexité : O(log n) n nombre de noeuds dans le tas
void minHeapify(MinHeap* minHeap, int idx)
{
	int smallest, left, right;
	smallest = idx;
	left = 2 * idx + 1;
	right = 2 * idx + 2;

	if (left < minHeap->size && minHeap->array[left]->key < minHeap->array[smallest]->key)
		smallest = left;

	if (right < minHeap->size && minHeap->array[right]->key < minHeap->array[smallest]->key)
		smallest = right;

	if (smallest != idx) {
		// The nodes to be swapped in min heap
		MinHeapNode* smallestNode = minHeap->array[smallest];
		MinHeapNode* idxNode = minHeap->array[idx];

		// Swap positions
		minHeap->pos[smallestNode->v] = idx;
		minHeap->pos[idxNode->v] = smallest;

		// Swap nodes
		swapMinHeapNode(&minHeap->array[smallest], &minHeap->array[idx]);

		minHeapify(minHeap, smallest);
	}
}

// Complexité : O(1)
int isEmpty(MinHeap* minHeap)
{
	return minHeap->size == 0;
}

// éxtraire le noeud de la valeur (key) minimum (la racine)
//    puis entasser le tas et reduire la taille du tas.
// Complexité : O(log n)
MinHeapNode* extractMin(MinHeap* minHeap)
{
	if (isEmpty(minHeap))
		return NULL;

	// Store the root node
    
	MinHeapNode* root = minHeap->array[0];

    
	// Replace root node with last node
	MinHeapNode* lastNode = minHeap->array[minHeap->size - 1];
    
	minHeap->array[0] = lastNode;

	// Update position of last node
	minHeap->pos[root->v] = minHeap->size - 1;
	minHeap->pos[lastNode->v] = 0;

	// Reduce heap size and heapify root
	--minHeap->size;

	//O(log n)
	minHeapify(minHeap, 0);
	return root;
}


// decrementer la valeur d'un sommet v dans le tas
// Complexité : O(log n)
void decreaseKey(MinHeap* minHeap, int v, int key)
{
	// Get the index of v in heap array
	int i = minHeap->pos[v];

	// Get the node and update its key value
	minHeap->array[i]->key = key;

	// Travel up while the complete tree is not hepified.
	// This is a O(Logn) loop
	while (i && minHeap->array[i]->key < minHeap->array[(i - 1) / 2]->key) {
		// Swap this node with its parent
		minHeap->pos[minHeap->array[i]->v] = (i - 1) / 2;
		minHeap->pos[minHeap->array[(i - 1) / 2]->v] = i;
		swapMinHeapNode(&minHeap->array[i], &minHeap->array[(i - 1) / 2]);

		// move to parent index
		i = (i - 1) / 2;
	}
}


// Complexité : O(1)
int isInMinHeap(MinHeap* minHeap, int v)
{
	if (minHeap->pos[v] < minHeap->size)
		return 1;
	return 0;
}
