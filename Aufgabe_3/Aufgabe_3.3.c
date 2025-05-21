void bubblesort(int* array, int size) {
	for (int i = 0; i < size - 1; i++) { // Äußere Schleife für die Anzahl der Durchläufe

		for (int j = 0; j < size - i - 1; j++) { // Innere Schleife für den Vergleich der Elemente
			if (array[j] > array[j + 1]) {
				// Wenn linkes element größer ist wie das rechte Element, mit Hilfe von Temp tauschen
				int temp = array[j];
				array[j] = array[j + 1];
				array[j + 1] = temp;
			}
		}
	}
}