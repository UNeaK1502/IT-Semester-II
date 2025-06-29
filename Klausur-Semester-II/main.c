//Libraries
#include <stdio.h>
#include "ll.h"
#include "app.h"
#include "rind.h"




//Definitionen
#define MATRIKELNR_LEN		8			//Laenge der Matrikelnummer

int matrikelnr(char* nr, int maxlen) {
	char matrNr[MATRIKELNR_LEN] = { "5635349" };
	if (strlen(matrNr) < maxlen) {
		//Wenn eingegebene Matrikelnummer kleiner als 8 ist, dann Matrikelnr schreiben und 0 zurueckgeben
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
	
	ll_t* rinder = NULL;	// Start: keine Rinder im System
	app_menu(&rinder);		// Menue starten
	return 0;
}
