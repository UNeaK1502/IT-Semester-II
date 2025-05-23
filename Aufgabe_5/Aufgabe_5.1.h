#pragma once
typedef struct node {
	int data;
	struct node* next;
} node_t;
node_t* createList();
node_t* addElement(node_t* firstElement);
void deleteElementAtPosition(node_t** firstElement, int position);
void printAllElements(node_t* firstElement);
int countElements(node_t* firstElement);
node_t* getElement(node_t* firstElement, int position);
void printSingleElement(node_t* element);
