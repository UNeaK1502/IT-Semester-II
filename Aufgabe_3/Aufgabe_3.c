#include <stdio.h>
#include <math.h>
#include "Aufgabe_3.2.h"
#include "Aufgabe_3.3.h"
#include "Aufgabe_3.4.h"
#include "Aufgabe_3.5.h"
//Hier Aufruf der Methoden und Definiton der teilaufgaben

/// <summary>
/// Implementiere eine Funktion, die mittels linearer Suche einen Wert vom Typ int in einem Array aus
/// Elementen vom Typ int sucht und die Position, an der das Element gefunden wurde, zur¨uck gibt.
/// </summary>
void Teilaufgabe_1() {
	const int array[] = { 1, 2, 3, 4, 5 };
	int size = sizeof(array) / sizeof(array[0]); // Berechne die Größe des Arrays
	int valueToFind = 0;
	for (int i = 0; i < size; i++)
		printf("%d ", array[i]);
	printf("\n");

	printf("Gebe den Wert ein, den gesucht werden soll: ");
	scanf_s("%d", &valueToFind);
	int position = -1;							// Initialisiere die Position mit -1 (nicht gefunden)
	for (int i = 0; i < size; i++) {
		if (array[i] == valueToFind) {
			position = i;						// Setze die Position, wenn der Wert gefunden wird
			break;								// Beende die Schleife, wenn der Wert gefunden wurde
		}
	}
	printf("Position von %d ist an Stelle: %d\n", valueToFind, position + 1);
}
/// <summary>
/// Implementiere eine Funktion, die rekursiv mittels bin¨arer Suche einen Wert vom Typ int in einem Array
/// aus Elementen vom Typ int sucht und die Position, an der das Element gefunden wurde, zur¨uck gibt.
/// </summary>
void Teilaufgabe_2() {
	const int array[] = { 1, 2, 3, 4, 5 };
	int size = sizeof(array) / sizeof(array[0]); // Berechne die Größe des Arrays
	int valueToFind = 0;
	printf("Geben Sie den Wert ein, den Sie suchen möchten: ");
	scanf_s("%d", &valueToFind);
	int position = -1; // Initialisiere die Position mit -1 (nicht gefunden)
	position = binarySearch(array, 0, size - 1, valueToFind);
	printf("Position von %d ist an Stelle: %d\n", valueToFind, position + 1);
}
/// <summary>
/// Bubblesort implentieren
/// </summary>
void Teilaufgabe_3() {
	int array[5] = { 5, 2, 4, 1,15 };
	int size = sizeof(array) / sizeof(array[0]); // Berechne die Größe des Arrays
	printf("Unsortierter Array:\n");
	//Ursprüngliches Array ausgeben
	for (size_t i = 0; i < size; i++)
	{
		printf("[%d] ", array[i]);
	}
	//sortierten Array ausgeben
	bubblesort(array, size); // Bubblesort aufrufen
	printf("\nSortierter Array: \n");
	for (size_t i = 0; i < size; i++)
	{
		printf("[%d] ", array[i]);
	}
}
/// <summary>
/// Selectionsort implementieren
/// </summary>
void Teilaufgabe_4() {
	int array[5] = { 5, 2, 4, 1,15 };
	int size = sizeof(array) / sizeof(array[0]); // Berechne die Größe des Arrays
	printf("Geben Sie den Wert ein, den Sie suchen möchten: ");
	//Ursprüngliches Array ausgeben
	for (size_t i = 0; i < size; i++)
	{
		printf("[%d] ", array[i]);
	}
	//sortierten Array ausgeben
	selectionSort(array, size); // Selection aufrufen
	printf("\nSortierter Array: \n");
	for (size_t i = 0; i < size; i++)
	{
		printf("[%d] ", array[i]);
	}
}
/// <summary>
/// Insertionsort implementieren
/// </summary>
void Teilaufgabe_5() {
	int array[5] = { 5, 2, 4, 1,15 };
	int size = sizeof(array) / sizeof(array[0]); // Berechne die Größe des Arrays
	printf("Geben Sie den Wert ein, den Sie suchen möchten: ");
	//Ursprüngliches Array ausgeben
	for (size_t i = 0; i < size; i++)
	{
		printf("[%d] ", array[i]);
	}
	//sortierten Array ausgeben
	insertionSort(array, size); // Bubblesort aufrufen
	printf("\nSortierter Array: \n");
	for (size_t i = 0; i < size; i++)
	{
		printf("[%d] ", array[i]);
	}
}