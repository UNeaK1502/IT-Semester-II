//Libraries
#include <stdio.h>
#include "ll.h"



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
	
	//neuen int pointer "age" erstellen, und 23 zuweisen

	int age = 23;
	int age2 = 22;
	int age3 = 21;
	ll_t* ll = ll_new(&age);
	int result = ll_print(ll, print_int);
	printf("Ergebnis der Ausgabe: %d\n", result);
	ll_append(ll, &age2);
	ll_append(ll, &age3);
	ll_print(ll, print_int);
	printf("\n");
	int bla = ll_count(ll);
	printf("Anzahl der Elemente in der Liste: %zu\n", bla);

	ll_remove(&ll, 0); // Entfernt das Element an Index 1 (age2)
	ll_print(ll, print_int);
	bla = ll_count(ll);
	printf("Anzahl der Elemente in der Liste: %zu\n", bla);
	ll_print(ll, ll_get(ll, 0)); // Gibt das Element an Index 0
	// Speicher aufräumen
	//free(ll);

	return 0;
}