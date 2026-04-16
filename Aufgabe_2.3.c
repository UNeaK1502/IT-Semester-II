/// <summary>
/// Schreibe eine Funktion, die rekursiv und ohne Verwendung von Schleifen das größte Element in
/// einem Array vom Typ int findet.Dazu bietet es sich an, das Array rekursiv als ”Erstes Element“ und 
/// Rest aufzufassen, wobei der Rest wiederum aus erstem Element und Rest besteht. Die Rekursion endet,
/// wenn der Rest die Länge 0 hat
/// </summary>

int findMax(int * array, int length) {
	if (length == 0) {
		return -1;												// Sonderfall wenn das Array leer ist, z.B. das Array komplett durchgelaufen wurde
	}
	if (length == 1) {
		return array[0];										// Wenn nur ein Element übrig ist, ist es das Maximum
	}
	int maxOfRest = findMax(array + 1, length - 1);				// Rekursiver Aufruf mit dem Rest des Arrays, Pointer um 1 weiter schieben
	return (array[0] > maxOfRest) ? array[0] : maxOfRest;		// Vergleich des ersten Elements mit dem Maximum des Rests
}