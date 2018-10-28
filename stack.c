/*
	Implementation of a stack in C.
*/

#include <stdio.h>
#include <stdlib.h>

//Pushes an element onto the stack
int push(int* stack, int* top, int* physical_size, int element)
{
	if (*top > *physical_size)
	{
		*physical_size = *physical_size * 2;
		int* temp = (int*) malloc(*physical_size * sizeof(int));
		
		if (temp == NULL)
		{
			fprintf(stderr, "%s\n", "Not enough memory to reallocate stack.");
			free(stack);
			exit(-1);
		}

		for (int i = 0; i < *top; i++)
			temp[i] = stack[i];

		free(stack);

		stack = temp;
	}

	stack[(*top)++] = element;
	return element;
}

//Pops off the element on the top of the stack
int pop(int* stack, int* top)
{
	if (*top == 0)
		return *top;

	return stack[--(*top)];
}

//Returns the element on the top of the stack
int peek(int* stack, int* top)
{
	return stack[(*top) - 1];
}

//Prints the stack
void printStack(int* stack, int top)
{
	printf("\n%s\n", "Current stack: ");
	for (int i = top - 1; i >= 0; i--)
	{
		printf("%d\n", stack[i]);
	}
}

//Initializes the physical size of the stack, the stack itself,
//and a variable indicating the current index of the top of the stack.
//Elements are pushed, popped, and peeked on the stack.
int main(void)
{
	int physical_size = 10;
	int* stack = (int*) malloc(physical_size * sizeof(int));
	int top = 0;

	if (stack == NULL)
	{
		fprintf(stderr, "%s\n", "Not enough memory to allocate stack.");
		free(stack);
		exit(-1);
	}

	for (int i = 1; i < 11; i++)
	{
		push(stack, &top, &physical_size, i);
		printf("%d pushed onto the stack.\n", stack[i - 1]);
	}

	printf("\nCurrent element on top of stack: %d\n", peek(stack, &top));

	printf("\n%d popped off stack. \n",pop(stack, &top));

	printStack(stack, top);

	printf("\nCurrent element on top of stack: %d\n", peek(stack, &top));

	printf("\n%d pushed onto the stack.\n", push(stack, &top, &physical_size, 11));
	printf("\n%d pushed onto the stack.\n", push(stack, &top, &physical_size, 12));

	printf("\nCurrent element on top of stack: %d\n", peek(stack, &top));

	printStack(stack, top);

	printf("\n%d popped off stack. \n",pop(stack, &top));
	
	printStack(stack, top);
}