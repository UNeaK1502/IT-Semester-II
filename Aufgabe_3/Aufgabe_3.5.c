// Aufgabe 3.5: Insertion sort
void insertionSort(int* array, int size) {
	for (int i = 0; i < size; i++)
	{
		int key = array[i];						//Nächstes Element picken (unsortiert)
		int j = i;
		while (j > 0 && array[j - 1] > key)		//Solange im array zurücklaufen, bis ein Element gefunden wurde, was kleiner als Key ist
		{
			array[j] = array[j - 1];			//Platz schaffen, in dem das Element vom kleineren Index nach hinten geschoben wird
			j--;
		}
		array[j] = key;							//Key an die richtige Stelle setzen
	}
}