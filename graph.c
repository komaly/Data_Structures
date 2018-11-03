/*
	Implementation of a graph in C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <inttypes.h>
#include <string.h>

#define WORDLENGTH 64

typedef struct Graph
{
	uint64_t* adjacencyMatrix;
	uint64_t* nodeSet;
	int nodeCount;
	int size;
} Graph;

static inline uint64_t setBit(uint64_t* element, int pos)
{
	*element |= (1ULL << pos);
	return *element;
}

static inline uint64_t unsetBit(uint64_t* element, int pos)
{
	*element &= ~(1ULL << pos);
	return *element;
}

static inline uint64_t checkBit(uint64_t element, int pos)
{
	return element & (1ULL << pos); //if 0, its not set, else, set
}

void addNode(Graph* G, int element)
{
	if (element < 0)
	{
		fprintf(stderr, "%s\n", "Node must be an integer greater than 0.");
		exit(-1);
	}

	int nodeSetIndex = element / G->size;
	int bitNum = element & 63;

	if (checkBit(G->nodeSet[nodeSetIndex], bitNum) != 0)
	{
		fprintf(stderr, "%s\n", "Node is already in the graph.");
		exit(-1);
	}

	if (nodeSetIndex > G->size - 1)
	{
		//make nodeset bigger 
	}

	setBit(&(G->nodeSet[nodeSetIndex]), bitNum);
	G->nodeCount++;
}

void deleteNode(Graph* G, int element)
{
	int nodeSetIndex = element / G->size;
	int bitNum = element & 63;

	if (checkBit(G->nodeSet[nodeSetIndex], bitNum) == 0)
	{
		fprintf(stderr, "%s\n", "Node is not in the graph.");
		exit(-1);
	}

	unsetBit(&(G->nodeSet[nodeSetIndex]), bitNum);

	//delete edges associated with node

	G->nodeCount--;
}

void addEdge(Graph* G, int rowElement, int colElement)
{
	int wordsPerRow = G->size / WORDLENGTH;
	int bit = colElement / WORDLENGTH;

	if (checkBit(G->adjacencyMatrix[(rowElement * wordsPerRow) + bit], bit) != 0)
	{
		fprintf(stderr, "%s\n", "There is already an edge between these 2 nodes.");
	 	exit(-1);
	}

	setBit(&(G->adjacencyMatrix[(rowElement * wordsPerRow) + bit]), bit);

}

void deleteEdge(Graph* G, int element1, int element2)
{
	int wordsPerRow = G->size / WORDLENGTH;
	int bit = colElement / WORDLENGTH;

	if (checkBit(G->adjacencyMatrix[(rowElement * wordsPerRow) + bit], bit) == 0)
	{
		fprintf(stderr, "%s\n", "There is already no edge between these 2 nodes.");
	 	exit(-1);
	}

	unsetBit(&(G->adjacencyMatrix[(rowElement * wordsPerRow) + bit]), bit);
	
}

void printNodeSetVal(Graph* G, int element)
{
	printf("NodeSet:\n");
	
	int a = element / G->size;
	printf("%llu\n", G->nodeSet[a]);

}

void printAdjacencyMatrixVal(Graph* G, int element)
{
	// printf("Adjacency Matrix: \n");
	// for (int i = 0; i < 64; i++)
	// {
	// 	if (G->nodeSet[i] == element)
	// 		printf("%" PRIu64 "\n", G->adjacencyMatrix[i]);
	// }
}

int main(void)
{
	struct Graph G;
	G.adjacencyMatrix = (uint64_t*) malloc(G.size * sizeof(uint64_t));
	G.nodeSet = (uint64_t*) malloc(G.size * sizeof(uint64_t));
	G.nodeCount = 0;
	G.size = 64;
	
	memset(G.adjacencyMatrix, 0, G.size * sizeof(uint64_t));
	memset(G.nodeSet, 0, G.size * sizeof(uint64_t));

	addNode(&G, 3);
	addNode(&G, 30);
	addNode(&G, 33);
	printNodeSetVal(&G, 36);
	
	deleteNode(&G, 33);
	printNodeSetVal(&G, 33);
	// addNode(&G, &size, 37);
	// addNode(&G, &size, 39);
	// addNode(&G, &size, 43);
	// printf("NODE COUNT %d\n", G.nodeCount);
	// printNodeSet(&G);
	// deleteNode(&G, size, 43);
	// printf("NODE COUNT %d\n", G.nodeCount);
	// printNodeSet(&G);
	// addEdge(&G, 36, 37);
	// printAdjacencyMatrixVal(&G, 36);
	// printAdjacencyMatrixVal(&G, 37);
	// printAdjacencyMatrixVal(&G, 39);
	// addEdge(&G, 36, 39);
	// printAdjacencyMatrixVal(&G, 36);
	// printAdjacencyMatrixVal(&G, 37);
	// printAdjacencyMatrixVal(&G, 39);
	// deleteEdge(&G, 36, 39);
	// printAdjacencyMatrixVal(&G, 36);
	// printAdjacencyMatrixVal(&G, 37);
	// printAdjacencyMatrixVal(&G, 39);
	// deleteEdge(&G, 36, 39);
}