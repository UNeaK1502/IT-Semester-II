//Hier Methoden f�r Aufgabe 2.1

/// <summary>
/// Fakult�t rekursiv berechnen
/// </summary>
/// <param name="number"></param>
/// <returns></returns>
int rekursion(int number) {
	if (number <= 1) {
		return 1;
	}
	else {
		return number * rekursion(number - 1);
	}
}