#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Aufgabe_5.1.h"


//Implementiere eine verkettete Liste, die Zahlen vom Typ int speichert. Deklariere dazu zunächst eine
//geeignete Datenstruktur und implementiere dann folgende Funktionen :
//• Anlegen einer Liste mit einem Element
//• Anhängen eines Elementes an eine Liste
//• Entfernen eines Elementes		- Passt
//• Löschen der Liste				- Passt
//• Ausgeben aller Elemente der Liste - Passt
//• Elemente zählen				 - Passt
//• Element an Position i finden - Passt
void Teilaufgabe_1() {

	node_t* firstelement = createList();
	addElement(firstelement);
	addElement(firstelement);
	addElement(firstelement);
	printAllElements(firstelement);
	deleteElementAtPosition(&firstelement, 2); // &firstelement statt firstelement
	printAllElements(firstelement);

}


