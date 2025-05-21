void selectionSort(int* array, int size) {
	for (int i = 0; i < size - 1; i++) {
		int minIndex = i;						//Index vom kleinsten Element initialisieren
		for (int j = i + 1; j < size; j++) {
			if (array[j] < array[minIndex]) {
				minIndex = j;					//Wenn das Element kleiner ist, dann den Index speichern
			}
		}
		if (minIndex != i) {
			int temp = array[i];				//kleinstes Element zwischenspeichern
			array[i] = array[minIndex];
			array[minIndex] = temp;
		}
	}
}