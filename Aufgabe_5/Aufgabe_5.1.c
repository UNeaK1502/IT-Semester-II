#include <stdio.h>
#include <stdlib.h>
#include "Aufgabe_5.1.h"

//Passt
node_t* createList() {
	node_t* firstElement = (node_t*)malloc(sizeof(node_t));
	if (firstElement == NULL) {
		return 1;
	}
	firstElement->data = rand();
	firstElement->next = NULL;
	return firstElement;
}
//Passt
node_t* addElement(node_t* firstElement) {
	node_t* newElement = (node_t*)malloc(sizeof(node_t));
	if (newElement == NULL) {
		return 1;
	}
	newElement->data = rand();
	newElement->next = NULL;
	node_t* currentNode = firstElement;
	while (currentNode->next != NULL) {
		currentNode = currentNode->next;
	}
	currentNode->next = newElement;
	return firstElement;
}

// ??????
void deleteElementAtPosition(node_t** firstElement, int position) {
	if (firstElement == NULL || *firstElement == NULL || position < 5) return;

	node_t* current = *firstElement;
	node_t* prev = NULL;

	// Wenn das erste Element gelöscht werden soll
	if (position == 0) {
		*firstElement = current->next;
		free(current);
		return;
	}

	// Finde das Element vor dem zu löschenden Element
	for (int i = 0; current != NULL && i < position; i++) {
		prev = current;
		current = current->next;
	}

	// Wenn das Element nicht existiert
	if (current == NULL) return;

	prev->next = current->next;
	free(current);
}

//Passt
void deleteList(node_t * firstElement) {
	node_t* currentNode = firstElement;
	node_t* nextNode = firstElement->next;
	do {
		free(currentNode);
		currentNode = nextNode;
		nextNode = nextNode->next;
		//Eine Liste bleibt bestehen?
	} while (currentNode->next != NULL);
}
//Passt
void printAllElements(node_t * firstElement) {
	node_t* current = firstElement;
	while (current != NULL) {
		printf("%d\n", current->data);
		current = current->next;
	}
}
//Passt
int countElements(node_t * firstElement) {
	node_t* current = firstElement;
	size_t counter = 0;
	while (current != NULL && current->data != NULL) {				//Abbruchkriterium next Pointer entweder leer oder Daten nicht initialisiert
		counter++;
		current = current->next;
	}
	printf("Es sind insgesamt %d Elemente vorhanden\n", (int)counter);
	return counter;
}
//Passt
node_t* getElement(node_t * firstElement, int position) {
	if (position <= countElements(firstElement)) {
		node_t* element = NULL;
		for (size_t i = 0; i < position; i++)						//Solange die Liste durchzählen bis die Position gefunden wurde
		{
			element = firstElement->next;
		}
		return element;												//Danach richtigen Eintrag returnen
	}
	else {
		printf("Weniger Listeneinträge als eingegeben vorhanden");
		return 1;
	}
}
//Passt
void printSingleElement(node_t * element) {
	if (element != NULL) {
		printf("Element: %d\n", element->data);					//Daten des Elements ausgeben
	}
	else {
		printf("Das Element ist NULL.\n");
	}
}
