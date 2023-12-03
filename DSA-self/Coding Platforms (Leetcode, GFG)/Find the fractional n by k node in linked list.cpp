/*
Easy
Find the fractional (or n/k – th) node in linked list
Last Updated: 28-11-2019
Given a singly linked list and a number k, write a function to find the (n/k)-th element, where n is the number of elements in the list. We need to consider ceil value in case of decimals.
*/
// C++ program to find fractional node in a linked list 
#include <bits/stdc++.h> 

/* Linked list node */
struct Node { 
	int data; 
	Node* next; 
}; 

/* Function to create a new node with given data */
Node* newNode(int data) 
{ 
	Node* new_node = new Node; 
	new_node->data = data; 
	new_node->next = NULL; 
	return new_node; 
} 

/* Function to find fractional node in the linked list */
Node* fractionalNodes(Node* head, int k) 
{ 
	// Corner cases 
	if (k <= 0 || head == NULL) 
		return NULL; 

	Node* fractionalNode = NULL; 
	
	// Traverse the given list 
	int i = 0; 
	for (Node* temp = head; temp != NULL; temp = temp->next) { 

		// For every k nodes, we move fractionalNode one 
		// step ahead. 
		if (i % k == 0) { 

			// First time we see a multiple of k 
			if (fractionalNode == NULL) 
				fractionalNode = head; 

			else
				fractionalNode = fractionalNode->next; 
		} 
		i++; 
	} 
	return fractionalNode; 
} 

// A utility function to print a linked list 
void printList(Node* node) 
{ 
	while (node != NULL) { 
		printf("%d ", node->data); 
		node = node->next; 
	} 
	printf("\n"); 
} 

/* Driver program to test above function */
int main(void) 
{ 
	Node* head = newNode(1); 
	head->next = newNode(2); 
	head->next->next = newNode(3); 
	head->next->next->next = newNode(4); 
	head->next->next->next->next = newNode(5); 
	int k = 2; 

	printf("List is "); 
	printList(head); 

	Node* answer = fractionalNodes(head, k); 
	printf("\nFractional node is "); 
	printf("%d\n", answer->data); 

	return 0; 
} 
