#include <stdio.h>
#include <stdlib.h>

// Funktion zum Zusammenf�hren von zwei Teilarrays
void merge(int* array, int left, int mid, int right) {
	//anzahl der Elemente im Array ermitteln
	int n1 = mid - left + 1;
	int n2 = right - mid;

	// Tempor�re Arrays erstellen
	int* leftArray = (int*)malloc(n1 * sizeof(int));
	int* rightArray = (int*)malloc(n2 * sizeof(int));

	// Daten in die tempor�ren Arrays kopieren
	for (int i = 0; i < n1; i++)
	{
		leftArray[i] = array[left + i];
	}
	for (int i = 0; i < n2; i++) {
		rightArray[i] = array[mid + 1 + i];
	}
	int i = 0, j = 0, k = left;

	// Zusammenf�hren der Arrays
	while (i < n1 && j < n2) {                  //Solange machen, bis ein array abegearbeitet wurde
		if (leftArray[i] <= rightArray[j]) {    //Fall dass der Wert im linken Array kleiner ist
			array[k] = leftArray[i];            //kleineren Wert in das Array schreiben
			i++;                                //n�chstes Element im linken Array f�r neuen Durchlauf
		}
		else {
			array[k] = rightArray[j];
			j++;
		}
		k++;                                    //Index vom sortierten Array erh�hen
	}

	// Restliche Elemente von leftArray kopieren
	while (i < n1) {
		array[k] = leftArray[i];
		i++;
		k++;
	}
	// Restliche Elemente von rightArray kopieren
	while (j < n2) {
		array[k] = rightArray[j];
		j++;
		k++;
	}
	// Speicher freigeben
	free(leftArray);
	free(rightArray);
}

/// <summary>
/// Arrays aufteilen
/// </summary>
/// <param name="arr">Array der aufgespalten werden soll</param>
/// <param name="left">linker Startwert</param>
/// <param name="right">Rechtes Ende</param>
void mergeSort(int* array, int left, int right) {
	if (left < right) {                             //Links ist kleiner Rechts wenn der Array 2 oder mehr Elemente hat -> Kann aufgeteilt werden
		int mid = left + (right - left) / 2;

		// Linke H�lfte und rechte H�lfte teilen
		mergeSort(array, left, mid);
		mergeSort(array, mid + 1, right);

		// Zusammenf�hren der sortierten H�lften
		merge(array, left, mid, right);
	}
	return array;
}