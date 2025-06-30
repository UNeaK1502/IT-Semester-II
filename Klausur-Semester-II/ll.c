#include <stdlib.h>
#include "ll.h"
/// <summary>
/// Durchsucht eine erkettenliste nach einem Element.
/// </summary>
/// <param name="ll">Die verkettete Liste die durchsucht werden soll.</param>
/// <param name="search_fn">Suchfunktion als Pointer</param>
/// <param name="search">Nach was gesucht werden soll</param>
/// <param name="idx">Index des gefundenen Elements</param>
/// <returns>Wahr oder falsch</returns>
ll_t* ll_search(ll_t* ll, int (*search_fn)(const void*, const void*), const void* search, int* idx) {
	//checken ob ein Parameter ungueltig ist
	if (ll == NULL || search_fn == NULL || idx == NULL) {
		return NULL;
	}
	ll_t* current = ll;
	*idx = -1;					// Standardwert, falls kein Element gefunden wird
	size_t index = 0;
	while (current != NULL) {
		if (search_fn(current->data, search)) {
			*idx = (int)index;		// Index des gefundenen Elements
			return current;		// Gefundenes Element zurueckgeben
		}
		current = current->next;
		index++;				//index zum tracken
	}
	return NULL; // Kein Element gefunden
}
/// <summary>
/// Eine verkettete Liste printen
/// </summary>
/// <param name="ll">Zu printende Liste</param>
/// <param name="print_fn">Entsprechende print Funktion</param>
/// <returns>0 Wenn nichts geprintet wurde bzw. Fehler, nicht-Null wenn etwas geprintet wurde</returns>
int ll_print(const ll_t* ll, int (*print_fn)(const void*)) {
	//checken ob ein Parameter ungueltig ist
	if (ll == NULL || print_fn == NULL) {
		return 0; // Keine Ausgabe erfolgt
	}
	const ll_t* current = ll;
	int count = 0;
	// Solange current != NULL, also solange Elemente vorhanden sind
	while (current != NULL) {
		if (print_fn(current->data)) {
			count++; 
			// Ausgabe erfolgreich
		}
		current = current->next;
	}
	return count; // Anzahl der erfolgreich ausgegebenen Elemente zurueckgeben
}
/// <summary>
/// Neue Liste anlegen und erstes Element mit Daten initialisieren.
/// </summary>
/// <param name="data"></param>
/// <returns></returns>
ll_t* ll_new(void* data) {
	//Speicher reservieren und Daten initialisieren
	ll_t* new_ll = (ll_t*)malloc(sizeof(ll_t));
	if (new_ll == NULL) {
		return NULL; // Speicher konnte nicht zugewiesen werden
	}
	new_ll->data = data;
	new_ll->next = NULL;
	return new_ll; // Zeiger auf die neue Liste zurueckgeben
}
/// <summary>
/// Neues Element an die Liste anhaengen
/// </summary>
/// <param name="ll">Liste an die etwas angehaengt werden soll</param>
/// <param name="data">Daten die angehaengt werden sollen</param>
void ll_append(ll_t* ll, void* data) {
	//checken ob ein Parameter ungueltig ist
	if (ll == NULL || data == NULL) {
		return; // Keine Aktion, Daten ungueltig 
	}
	ll_t* new_node = (ll_t*)malloc(sizeof(ll_t));
	if (new_node == NULL) {
		return; // Speicher konnte nicht zugewiesen werden
	}
	new_node->data = data;
	new_node->next = NULL;
	ll_t* current = ll;
	// Bis zum letzten Element der Liste gehen
	while (current->next != NULL) {
		current = current->next;
	}
	current->next = new_node; // Neues Element anhaengen
}
/// <summary>
/// Gibt das Element an der angegebenen Position zurueck
/// </summary>
/// <param name="ll">Liste aus der Element geholt werden soll</param>
/// <param name="index">Index des Elements was zurueckgegeben werden soll</param>
/// <returns></returns>
ll_t* ll_get(ll_t* ll, size_t index) {
	//checken ob ein Parameter ungueltig ist
	if (ll == NULL || index < 0) {
		return NULL; // Keine Aktion, ungueltiger Index
	}
	ll_t* current = ll;
	size_t current_index = 0;
	while (current != NULL) {
		if (current_index == index) {
			return current; // Element an der angegebenen Position zurueckgeben
		}
		current = current->next;
		current_index++;		// Index erhoehen
	}
	return NULL; // Kein Element an der angegebenen Position gefunden
}
/// <summary>
/// Entfernt Element an Stelle index aus Liste.
/// </summary>
/// <param name="p_ll">zu bearbeitende Liste</param>
/// <param name="index">Index des zu loeschenden Elements</param>
void ll_remove(ll_t** p_ll, size_t index) {
	//checken ob ein Parameter ungueltig ist
	if (p_ll == NULL || *p_ll == NULL || index < 0) {
		return; // Keine Aktion, ungueltiger Index oder Liste
	}
	ll_t* current = *p_ll;
	ll_t* previous = NULL;
	size_t current_index = 0;
	while (current != NULL) {
		if (current_index == index) {
			if (previous == NULL) {
				// Element ist das erste Element der Liste
				*p_ll = current->next; // Kopf der Liste aktualisieren
			}
			else {
				previous->next = current->next; // Vorheriges Element ueberspringen
			}
			free(current); // Speicher freigeben
			return; // Element entfernt, Funktion beenden
		}
		previous = current;
		current = current->next;
		current_index++;
	}
}
/// <summary>
/// Zaehlt die Anzahl der Elemente in der Liste.
/// </summary>
/// <param name="ll">Zu zaehlende Liste</param>
/// <returns>Laenge der Liste</returns>
size_t ll_count(const ll_t* ll) {
	//checken ob ein Parameter ungueltig ist
	if (ll == NULL) {
		return 0; // Keine Elemente in der Liste
	}
	size_t count = 0;
	const ll_t* current = ll;
	// Solange zählen bis current NULL ist
	while (current != NULL) {
		count++; // Zaehler erhoehen fuer jedes Element
		current = current->next; // Zum naechsten Element gehen
	}
	return count; // Anzahl der Elemente zurueckgeben
}
/// <summary>
/// Funktion zum printen von int-Daten.
/// </summary>
/// <param name="data"></param>
/// <returns></returns>
int print_int(const void* data) {
	printf("%d\n", *(const int*)data);	//Zum const int pointer Casten, derefenzieren und als dezimal ausgeben
	return 1;  // Erfolgreich ausgegeben
}
/// <summary>
/// Funktion zum printen von String-Daten.
/// </summary>
/// <param name="data"></param>
/// <returns></returns>
int print_string(const void* data) {
	printf("%s\n", (const char*)data); //Zum const char pointer Casten, derefenzieren und string ausgeben
	return 1;  // Erfolgreich ausgegeben
}