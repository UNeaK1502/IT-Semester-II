/// <summary>
/// Schreibe eine Funktion, die �berpr�ft, ob in einem Array von Typ int ein Wert doppelt vorkommt. Welche
/// Komplexit�tsklasse hat diese Funktion ?
/// </summary>
int checkDuplicate(int* array) {
	int length = sizeof(array) / sizeof(array[0]);		// L�nge vom Array f�r Schleife berechnen
	//Abbruchbedingungen
	if (length == 0) {
		return 0;										// Sonderfall wenn das Array leer ist
	}
	if (length == 1) {
		return 0;										// Wenn nur ein Element �brig ist, gibt es keine Duplikate
	}
	int firstValue = array[0];
	for (int i = 1; i < length; i++) {					//Schleife durchlaufen und Werte vergleichen
		if (array[i] == firstValue) {
			return 1; // Duplikat gefunden
		}
	}
	return checkDuplicate(array + 1);					// Rekursiver Aufruf mit dem Rest des Arrays, Pointer +1 verschieben	
}