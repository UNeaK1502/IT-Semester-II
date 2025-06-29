//Libraries
#include <stdio.h>
#include "ll.h"
#include "app.h"
#include "rind.h"




//Definitionen
#define MATRIKELNR_LEN		8			//Länge der Matrikelnummer

int matrikelnr(char* nr, int maxlen) {
	char matrNr[MATRIKELNR_LEN] = { "5635349" };
	if (strlen(matrNr) < maxlen) {
		//Wenn eingegebene Matrikelnummer kleiner als 8 ist, dann Matrikelnr schreiben und 0 zurückgeben
		strcpy_s(nr, maxlen, matrNr);
		printf("Matrikelnummer: %s\n", nr);
		return 0;
	}
	else {
		printf("Fehler: Matrikelnummer zu lang\n");
		return -1;
	}
}



//Hauptprogramm
int main() {
	

	srand((unsigned int)time(NULL)); // Zufall initialisieren

	// 1. Rind erstellen
	rind_t* kuh = rind_create("Berta", 5, 25);
	if (!kuh) {
		printf("Fehler beim Erstellen des Rinds.\n");
		return 1;
	}
	int result = rind_print(kuh);

	return 0;
}