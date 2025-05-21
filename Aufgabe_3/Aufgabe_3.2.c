int binarySearch(int* array, int left, int right, int value) {
	if (left > right) {
		return -1; // Wert nicht gefunden
	}
	int mid = left + ((right - left) / 2);		//Mitte berechnen
	if (array[mid] == value) {
		return mid; // Wert gefunden
	}
	else if (array[mid] < value) {
		return binarySearch(array, mid + 1, right, value); // Weitere Suche im rechten Teil
	}
	else {
		return binarySearch(array, left, mid - 1, value); // Suche im linken Teil
	}
}