/*
	Implementation of a queue in C.
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define SIZE 15

// Returns true if the queue is full
bool isFull(int *elementCount)
{
	return *elementCount == SIZE;
}

// Returns true if the queue is empty
bool isEmpty(int *start, int *end, int *elementCount)
{
	return *start == *end && !isFull(elementCount);
}

// Adds an element to the next available space in the queue
int enqueue(int *queue, int *start, int *end, int *elementCount, int element)
{
	if (isFull(elementCount))
	{
		fprintf(stderr, "%s\n", "Queue is full, cannot enqueue another element.");
		exit(-1);
	}

	if (*end < SIZE)
		queue[(*end)++] = element;

	else
	{
		*end = 0;
		queue[(*end)++] = element;
	}

	(*elementCount)++;
	return element;
}

// Removes the element at the front of the queue 
int dequeue(int *queue, int *start, int *end, int *elementCount)
{
	if (isEmpty(start, end, elementCount))
	{
		fprintf(stderr, "%s\n", "Queue is empty, cannot dequeue an element.");
		exit(-1);
	}

	(*elementCount)--;
	return queue[(*start)++];
}

// Returns the element at the front of the queue
int peek(int* queue, int* start)
{
	return queue[*start];
}

// Prints the queue
void printQueue(int* queue, int start, int end)
{
	printf("\n%s\n", "Current queue: ");

	if (start >= end)
	{
		for (int i = start; i < SIZE; i++)
			printf("%d\n", queue[i]);

		if (end == 0)
			printf("%d\n", queue[end]);

		else
		{
			for (int i = 0; i < end; i++)
				printf("%d\n", queue[i]);
		}
	}

	else
	{
		for (int i = start; i < end; i++)
			printf("%d\n", queue[i]);
	}

	printf("\n");
}

// Initializes the queue, a variable indicating the current index 
// of the start of the queue, a variable indicating the current 
// index of the end of the queue, and a variable indicating the 
// number of elements in the queue. Elements are enqueued, dequeued, 
// and peeked on the queue.
int main(int argc, char const *argv[])
{
	int queue[SIZE];
	int start = 0;
	int end = 0;
	int elementCount = 0;

	for (int i = 1; i < 15; i++)
	{
		enqueue(queue, &start, &end, &elementCount, i);
	}

	printQueue(queue, start, end);

	dequeue(queue, &start, &end, &elementCount);
	dequeue(queue, &start, &end, &elementCount);
	dequeue(queue, &start, &end, &elementCount);

	printQueue(queue, start, end);
	printf("\n%d\n", peek(queue, &start));

	enqueue(queue, &start, &end, &elementCount, 35);
	enqueue(queue, &start, &end, &elementCount, 67);

	printQueue(queue, start, end);
	printf("\n%d\n", peek(queue, &start));

	enqueue(queue, &start, &end, &elementCount, 109);
	
	printQueue(queue, start, end);

	enqueue(queue, &start, &end, &elementCount, 109);
	
	printQueue(queue, start, end);

	dequeue(queue, &start, &end, &elementCount);
	
	printQueue(queue, start, end);
	printf("%d\n", peek(queue, &start));

	enqueue(queue, &start, &end, &elementCount, 25);
	
	printQueue(queue, start, end);
	printf("%d\n", peek(queue, &start));
}