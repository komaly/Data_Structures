/*
	Implementation of a graph in C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h> 
#include <inttypes.h>
#include <string.h>

typedef struct Graph
{
	uint64_t* adjacencyMatrix;
	int nodeCount;
	int* nodeSet;
}Graph;

void addNode(Graph* G, int* size, int element)
{
	if (G->nodeCount >= *size)
	{
		*size = *size * 2;
		int* temp = (int*) malloc(*size * sizeof(int));
		
		if (temp == NULL)
		{
			fprintf(stderr, "%s\n", "Not enough memory to add more nodes.");
			free(G->nodeSet);
			exit(-1);
		}

		for (int i = 0; i < G->nodeCount; i++)
			temp[i] = G->nodeSet[i];

		free(G->nodeSet);
		G->nodeSet = temp;
	}


	G->nodeSet[G->nodeCount++] = element;
}

int getIndexOfNode(Graph* G, int element)
{
	for (int i = 0; i < G->nodeCount; i++)
	{
		if (G->nodeSet[i] == element)
			return i;
	}

	return -1;
}

void deleteNode(Graph* G, int size, int element)
{
	int index = getIndexOfNode(G, element);

	if (index == -1)
	{
		fprintf(stderr, "%s\n", "Element to delete not found.");
		exit(-1);
	}

	int* temp = (int*) malloc(size * sizeof(int));

	for (int j = 0; j < index; j++)
		temp[j] = G->nodeSet[j];

	for (int k = index; k < G->nodeCount; k++)
		temp[k] = G->nodeSet[k+1];

	G->nodeCount--;

	free(G->nodeSet);
	G->nodeSet = temp;
	//delete edges associated with node
}

int checkBit(int element, int pos)
{
	return element & (1 << pos); //if 0, not set, else, set
}

void addEdge(Graph* G, int element1, int element2)
{
	//get indexes of element1 and 2
	//at index of element1 in matrix, change bit #element2 index
	//at index of element2 in matrix, change bit #element1 index
	int element1Index = getIndexOfNode(G, element1);
	int element2Index = getIndexOfNode(G, element2);

	if (element1Index == -1 || element2Index == -1)
	{
		fprintf(stderr, "%s\n", "Node to add edge not found.");
		exit(-1);
	}

	//if bit not set, set it
	if (checkBit(G->adjacencyMatrix[element1Index], element2Index) == 0)
	{
		G->adjacencyMatrix[element1Index] = G->adjacencyMatrix[element1Index] ^ (1 << element2Index);
		G->adjacencyMatrix[element2Index] = G->adjacencyMatrix[element2Index] ^ (1 << element1Index);
	}

	else
	{
		fprintf(stderr, "%s\n", "There is already an edge between these 2 nodes.");
		exit(-1);
	}

}

void deleteEdge(Graph* G, int element1, int element2)
{
	int element1Index = getIndexOfNode(G, element1);
	int element2Index = getIndexOfNode(G, element2);

	if (element1Index == -1 || element2Index == -1)
	{
		fprintf(stderr, "%s\n", "Node to remove edge not found.");
		exit(-1);
	}

	if (checkBit(G->adjacencyMatrix[element1Index], element2Index) != 0)
	{
		G->adjacencyMatrix[element1Index] = G->adjacencyMatrix[element1Index] ^ (1 << element2Index);
		G->adjacencyMatrix[element2Index] = G->adjacencyMatrix[element2Index] ^ (1 << element1Index);
	}

	else
	{
		fprintf(stderr, "%s\n", "There is no edge between these 2 nodes.");
		exit(-1);
	}
	
}

void printNodeSet(Graph* G)
{
	printf("NodeSet:\n");
	for (int i = 0; i < G->nodeCount; i++)
	{
		printf("%d\n", G->nodeSet[i]);
	}
}

void printAdjacencyMatrixVal(Graph* G, int element)
{
	printf("Adjacency Matrix: \n");
	for (int i = 0; i < 64; i++)
	{
		if (G->nodeSet[i] == element)
			printf("%" PRIu64 "\n", G->adjacencyMatrix[i]);
	}
}

int main(void)
{
	struct Graph G;
	int size = 64;
	G.adjacencyMatrix = (uint64_t*) malloc(size * sizeof(uint64_t));
	memset(G.adjacencyMatrix, 0, size * sizeof(uint64_t));

	G.nodeCount = 0;
	G.nodeSet = (int*) malloc(size * sizeof(int));

	//printAdjacencyMatrix(&G);
	addNode(&G, &size, 35);
	addNode(&G, &size, 36);
	addNode(&G, &size, 37);
	addNode(&G, &size, 39);
	addNode(&G, &size, 43);
	printf("NODE COUNT %d\n", G.nodeCount);
	printNodeSet(&G);
	deleteNode(&G, size, 43);
	printf("NODE COUNT %d\n", G.nodeCount);
	printNodeSet(&G);
	addEdge(&G, 36, 37);
	printAdjacencyMatrixVal(&G, 36);
	printAdjacencyMatrixVal(&G, 37);
	printAdjacencyMatrixVal(&G, 39);
	addEdge(&G, 36, 39);
	printAdjacencyMatrixVal(&G, 36);
	printAdjacencyMatrixVal(&G, 37);
	printAdjacencyMatrixVal(&G, 39);
	deleteEdge(&G, 36, 39);
	printAdjacencyMatrixVal(&G, 36);
	printAdjacencyMatrixVal(&G, 37);
	printAdjacencyMatrixVal(&G, 39);
	deleteEdge(&G, 36, 39);
}