//Wie in der Datenstruktur ersichtlich, kann ein Rind zwei Status haben: entweder es ist ver-
// fuegbar(RIND_STAT_AVAIL), oder es ist bereits im Stall des Milchhofs(RIND_STAT_COWSHED).
// Fuer den Namen der Rinder soll ein String konstanter Laenge(z.B. 30) reserviert werden.
// Weiterhin soll fuer jedes Rind eine Historie mit abgegebener Milch pro Tag gespeichert werden.
// Dies ist fuer den Milchhof sehr wichtig, um fuer jedes Rind evaluieren zu koennen, ob das Rind die
// erwartete Milchleistung erbringt.Die Historie wird als verkettete Liste gespeichert, wobei der
// Pointer milk_log der Datenstruktur rind_t auf das erste Element dieser zeigt.Die verkettete
// Liste soll die Funktionen der Teilaufgabe 0.3 verwenden und jeder Knoten der Liste soll Daten
// des Typs milk_entry_t beinhalten


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "rind.h"
#include "ll.h"

rind_t* rind_create(const char* name, int age, int milkperday) {
	// Pruefen der Eingabewerte
	if (age < 0 || age > 30 || milkperday < 15 || milkperday > 40) return NULL;
	// speicher reservieren
	rind_t* r = malloc(sizeof(rind_t));
	if (!r) return NULL;
	// Name kopieren und sicherstellen, dass er nicht zu lang ist
	strncpy_s(r->name, RIND_NAME_LEN + 1, name, RIND_NAME_LEN);
	//r->name[RIND_NAME_LEN] = '\0'; // optional, falls name genau 30 Zeichen lang ist
	r->age = age;
	r->milkPerDay = milkperday;
	r->status = RIND_STAT_AVAIL;
	r->milk_log = NULL;
	// erstelltes Rind zurueckgeben
	return r;
}
/// <summary>
/// Gibt die Informationen eines Rinds aus.
/// </summary>
/// <param name="rind">Rind welches geprintet werden soll</param>
/// <returns>1 bei Erfolg, 0 bei Fehler</returns>
int rind_print(const void* rind) {
	// const weil rind_t nur gelesen wird + cast zu rind_t
	const rind_t* r = (const rind_t*)rind;
	if (!r) return 0;

	printf("Name: %s, Alter: %d, Milchleistung: %d L/Tag\n", r->name, r->age, r->milkPerDay);
	return 1;
}
/// <summary>
/// Sucht in der verketteten Liste nach einem Rind mit dem angegebenen Namen.
/// Ueberprueft genau ein Rind, nicht die gesamte Liste. Mehr siehe in ll_search.
/// </summary>
/// <param name="rind">Pointer zur Liste</param>
/// <param name="name">Name der geprueft werden soll</param>
/// <returns>0 wenn kein Name gefunden wurde, ansonsten nicht null</returns>
int rind_search_name(const void* rind, const void* name) {
	const rind_t* r = (const rind_t*)rind;
	const char* n = (const char*)name;
	return strncmp(r->name, n, RIND_NAME_LEN) == 0;
}
/// <summary>
/// Rinder im Stall werden gemolken.
/// </summary>
/// <param name="rind">Pointer zur Liste der Rinder</param>
/// <param name="date">Aktuelles Melk-Datum</param>
/// <returns></returns>
int rind_milk(rind_t* rind, date_t date) {
	if (!rind || rind->status != RIND_STAT_COWSHED || rind->age < 3) return 0;

	milk_entry_t* entry = malloc(sizeof(milk_entry_t));
	if (!entry) return 0;

	entry->date = date;
	entry->liters = (rand() % 251 + 150);	// %251 macht 0-250 (bzw 25.0), +150 macht 150-400
	
	if (!rind->milk_log) {
		rind->milk_log = ll_new(entry);		// Erstes Element der Liste
	}
	else {
		ll_append(rind->milk_log, entry);	// Jedes weitere Element anhaengen
	}

	return entry->liters;
}
/// <summary>
/// Methode um zu entscheiden, ob das Rind in den Stall kommt oder draussen bleibt.
/// </summary>
/// <param name="rind"></param>
/// <returns></returns>
rind_status_t rind_decide(rind_t* rind) {
	if (!rind) return RIND_STAT_AVAIL;
	//Wenn die Random Zahl gerade ist, dann kommt das Rind in den Stall, sonst bleibt es draussen
	if (rand() % 2 == 0) {
		rind->status = RIND_STAT_COWSHED;
	}
	else {
		rind->status = RIND_STAT_AVAIL;
	}
	return rind->status;
}
/// <summary>
/// Methode um Stallinhalt zu printen.
/// </summary>
/// <param name="rind"></param>
/// <returns></returns>
int rind_print_shed(const void* rind) {
	const rind_t* r = (const rind_t*)rind;		//Cast von void* zu rind_t*
	if (!r || r->status != RIND_STAT_COWSHED) return 0;

	printf("Name: %s, Alter: %d, Milchleistung: %d L/Tag\n", r->name, r->age, r->milkPerDay);

	int count = 0;
	int sum = 0;
	// Ausgabe der Milch-Historie
	ll_t* node = r->milk_log;
	//solange node != NULL, also Einträge vorhanden sind
	while (node) {
		milk_entry_t* entry = (milk_entry_t*)node->data;		// Cast von void* zu milk_entry_t*
		//formatierungen
		printf("  %02d.%02d.%04d: %.1f L\n", entry->date.day, entry->date.month, entry->date.year, entry->liters / 10.0);
		sum += entry->liters;
		count++;		//Zum dúrchschnitt berechnen
		node = node->next;	// Weiter zum naechsten Eintrag in der Liste
	}
	// Durchschnitt berechnen, wenn verfügbar
	if (count > 0) {
		float avg = sum / (float)count / 10.0;
		printf("  Durchschnitt: %.1f L/Tag -> ", avg);
		if (avg < r->milkPerDay)
			printf("unter Soll\n");
		else if (avg == r->milkPerDay)
			printf("im Soll\n");
		else
			printf("ueber Soll\n");
	}
	else {
		printf("  Keine Milchdaten vorhanden.\n");
	}

	return 1;
}


