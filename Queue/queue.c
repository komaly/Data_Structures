/*
	Implementation of a queue in C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

bool isFull(int* end, int* physical_size)
{
	return *end > *physical_size;
}

bool isEmpty(int* queue, int* start, int* end)
{
	return *start == *end;
}

int enqueue(int* queue, int* physical_size, int* start, int* end, int element)
{
	if (isFull(end, physical_size))
	{
		*physical_size = *physical_size * 2;
		int* temp = (int*) malloc(*physical_size * sizeof(int));
		
		if (temp == NULL)
		{
			fprintf(stderr, "%s\n", "Not enough memory to reallocate queue.");
			free(queue);
			exit(-1);
		}

		for (int i = *start; i < *end - 1; i++)
		{
			temp[i] = queue[i];
			printf("%d\n", queue[i]);
		}

		printf("HII\n");
		free(queue);
		printf("HELOO\n");
		queue = temp;
		printf("WAHH\n"); 
	}

	queue[(*end)++] = element;
	return element;
}

int dequeue(int* queue, int* start, int* end)
{
	if (isEmpty(queue, start, end))
	{
		fprintf(stderr, "%s\n", "Queue is empty, cannot dequeue.");
		free(queue);
		exit(-1);
	}

	return queue[(*start)++];
}

int peek(int* queue, int* start)
{
	return queue[*start];
}

void printQueue(int* queue, int start, int end)
{
	printf("\n%s\n", "Current queue: ");
	for (int i = start; i < end; i++)
	{
		printf("%d\n", queue[i]);
	}

	printf("\n");
}

int main(int argc, char const *argv[])
{
	int physical_size = 10;
	int* queue = (int*) malloc(physical_size * sizeof(int));
	int start = 0;
	int end = 0;

	if (queue == NULL)
	{
		fprintf(stderr, "%s\n", "Not enough memory to allocate queue.");
		free(queue);
		exit(-1);
	}

	for (int i = 1; i < 10; i++)
	{
		enqueue(queue, &physical_size, &start, &end, i);
	}

	printQueue(queue, start, end);

	dequeue(queue, &start, &end);
	dequeue(queue, &start, &end);
	dequeue(queue, &start, &end);

	printQueue(queue, start, end);

	printf("%d\n", peek(queue, &start));
}