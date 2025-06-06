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

// Passt
void deleteElementAtPosition(node_t** firstElement, int position) {
	//int count = countElements(*firstElement);												//Anzahl der Elemente ermitteln
	//if (firstElement == NULL || *firstElement == NULL || position > count) return;		//Position kann mit CountElements() ermittelt werden
	if (firstElement == NULL || *firstElement == NULL) return;

	node_t* current = *firstElement;				//Dereferenzieren
	node_t* prev = NULL;

	// Sonderfall erstes Element löschen
	if (position == 0) {
		*firstElement = current->next;
		free(current);
		return;
	}														// Finde das Element vor dem zu löschenden Element
	for (int i = 0; current != NULL && i < position; i++) {
		prev = current;									//Merken welches Element vorher war
		current = current->next;						//Aktuelles Element weiter setzen
	}														// Wenn das Element nicht existiert
	if (current == NULL || prev == NULL) return;

	prev->next = current->next;							//Pointer vom vorherigen auf das übernächste Element setzen
	free(current);										//Aktuelles Element freigeben
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
	while (current != NULL && current->next != NULL) {				//Abbruchkriterium next Pointer entweder leer oder Daten nicht initialisiert
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
