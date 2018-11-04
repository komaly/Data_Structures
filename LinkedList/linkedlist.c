/*
	Implementation of a linked list in C.
*/

#include <stdio.h>
#include <stdlib.h>

//Creates a Node object for the linked list
typedef struct Node
{
	int data;
	struct Node* nextNode;
} Node;

//Returns the length of the linked list
int getListLength(struct Node* head)
{
	struct Node* temp = head;
	int count = 0;

	while (temp != NULL)
	{
		count++;
		temp = temp->nextNode;
	}

	return count;
}

//Adds a Node to the linked list at the given index
void addNodeAtIndex(struct Node** head, int data, int index)
{
	if (index > getListLength(*head) || index < 0)
	{
		fprintf(stderr, "%s\n", "Index out of range.");
	 	exit(-1);
	}

	struct Node* newNode = (struct Node*) malloc(sizeof(struct Node));

	if (index == 0)
	{
		newNode->data = data;
		newNode->nextNode = *head;
		*head = newNode;
		return;
	}

	int count = 0;
	struct Node* curr= *head;
	struct Node* prev = *head;

	while (count < index)
	{
		prev = curr;
		curr = curr->nextNode;
		count++;
	}

	prev->nextNode = newNode;
	newNode->data = data;
	newNode->nextNode = curr;
}

//Removes the Node at the given index from the linked list
void removeNodeAtIndex(struct Node** head, int index)
{
	if (*head == NULL)
	{
		fprintf(stderr, "%s\n", "No nodes in linked list, nothing is removed.");
	 	exit(-1);
	}
	
	if (index > getListLength(*head) || index < 0)
	{
		fprintf(stderr, "%s\n", "Index out of range.");
	 	exit(-1);
	}

	if (index == 0)
	{
		*head = (*head)->nextNode;	
		return;
	}


	int count = 0;
	struct Node* curr = *head;
	struct Node* prev = *head;

	while (count < index)
	{
		prev = curr;
		curr = curr->nextNode;
		count++;
	}

	prev->nextNode = curr->nextNode;
}

//Returns the index of a given Node in the linked list
int findNode(struct Node* head, int data)
{
	int index = 0;
	struct Node* temp = head;

	while (temp->data != data)
	{
		temp = temp->nextNode;
		index++;

		if (temp == NULL)
		{
			fprintf(stderr, "%s\n", "Node not found.");
	 		exit(-1);
		}
	}

	return index;
}

//Prints the linked list
void printLL(struct Node* head)
{
	struct Node* temp = head;

	while (temp != NULL)
	{
		printf("%d\n", temp->data);
		temp = temp->nextNode;
	}
}


int main(void)
{
	struct Node* head = NULL;
	addNodeAtIndex(&head, 32, 0);
	addNodeAtIndex(&head, 35, 1);
	addNodeAtIndex(&head, 36, 0);
	addNodeAtIndex(&head, 31, 3);
	addNodeAtIndex(&head, 37, 0);

	removeNodeAtIndex(&head, 0);

	addNodeAtIndex(&head, 45, 2);
	removeNodeAtIndex(&head, 4);
	printLL(head);

	printf("%d\n", findNode(head, 35));
}