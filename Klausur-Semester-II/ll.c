#include "ll.h"
#include <stdlib.h>
// Die Funktion ll_search bekommt per Pointer search_fn eine Funktion �bergeben, welche
// zwei Argumente vom Typ const void* erwartet: die Daten des jeweils aktuellen Elements,
// sowie den Parameter search der Funktion ll_search.Die Funktion soll Wahr / Falsch zur�ck -
// geben, je nachdem, ob das aktuelle Element die gesuchten Daten enth�lt.Dadurch kann die
// Funktion ll_search generisch Daten suchen(vergleichbar mit qsort).In den Pointer idx soll
// die Funktion den Index des gefundenen Elements, bzw. - 1, wenn kein Element gefunden wurde,
// eintragen.Die Funktion soll einen Zeiger auf das gefundene Element, bzw.NULL zur�ckgeben.
// 
// Die Funktion ll_print ist auch generisch programmiert und gibt alle Elemente der verketteten Liste aus.
// Dazu erwartet sie eine Funktion print_fn, welche als const void* Argument
// die Daten des jeweils aktuellen Elements zur Ausgabe erh�lt.
// Die Funktionen print_fn und ll_print k�nnen jeweils optional per int - R�ckgabewert signalisieren, 
// ob eine Ausgabe tats�chlich erfolgt ist.

ll_t* ll_search(ll_t* ll, int (*search_fn)(const void*, const void*), const void* search, int* idx) {
	//checken ob ein Parameter ungueltig ist
	if (ll == NULL || search_fn == NULL || idx == NULL) {
		return NULL;
	}
	ll_t* current = ll;
	*idx = -1; // Standardwert, falls kein Element gefunden wird
	size_t index = 0;
	while (current != NULL) {
		if (search_fn(current->data, search)) {
			*idx = index; // Index des gefundenen Elements
			return current; // Gefundenes Element zur�ckgeben
		}
		current = current->next;
		index++;
	}
	return NULL; // Kein Element gefunden
}
int ll_print(const ll_t* ll, int (*print_fn)(const void*)) {
	//checken ob ein Parameter ungueltig ist
	if (ll == NULL || print_fn == NULL) {
		return 0; // Keine Ausgabe erfolgt
	}
	const ll_t* current = ll;
	int count = 0;
	while (current != NULL) {
		if (print_fn(current->data)) {
			count++; // Ausgabe erfolgreich
		}
		current = current->next;
	}
	return count; // Anzahl der erfolgreich ausgegebenen Elemente zur�ckgeben
}
/// <summary>
/// Neue Liste anlegen und erstes Element mit Daten initialisieren.
/// </summary>
/// <param name="data"></param>
/// <returns></returns>
ll_t* ll_new(void* data) {
	ll_t* new_ll = (ll_t*)malloc(sizeof(ll_t));
	if (new_ll == NULL) {
		return NULL; // Speicher konnte nicht zugewiesen werden
	}
	new_ll->data = data;
	new_ll->next = NULL;
	return new_ll; // Zeiger auf die neue Liste zur�ckgeben
}
/// <summary>
/// Neues Element an die Liste anh�ngen
/// </summary>
/// <param name="ll">Liste an die etwas angeh�ngt werden soll</param>
/// <param name="data">Daten die angeh�ngt werden sollen</param>
void ll_append(ll_t* ll, void* data) {
	//checken ob ein Parameter ungueltig ist
	if (ll == NULL || data == NULL) {
		return; // Keine Aktion, Daten ung�ltig 
	}
	ll_t* new_node = (ll_t*)malloc(sizeof(ll_t));
	if (new_node == NULL) {
		return; // Speicher konnte nicht zugewiesen werden
	}
	new_node->data = data;
	new_node->next = NULL;
	ll_t* current = ll;
	while (current->next != NULL) {
		current = current->next; // Zum letzten Element der Liste gehen
	}
	current->next = new_node; // Neues Element anh�ngen
}
/// <summary>
/// Gibt das Element an der angegebenen Position zur�ck
/// </summary>
/// <param name="ll">Liste aus der Element geholt werden soll</param>
/// <param name="index">Index des Elements was zur�ckgegeben werden soll</param>
/// <returns></returns>
ll_t* ll_get(ll_t* ll, size_t index) {
	//checken ob ein Parameter ungueltig ist
	if (ll == NULL || index < 0) {
		return NULL; // Keine Aktion, ung�ltiger Index
	}
	ll_t* current = ll;
	size_t current_index = 0;
	while (current != NULL) {
		if (current_index == index) {
			return current; // Element an der angegebenen Position zur�ckgeben
		}
		current = current->next;
		current_index++;
	}
	return NULL; // Kein Element an der angegebenen Position gefunden
}
/// <summary>
/// Entfernt Element an Stelle index aus Liste.
/// </summary>
/// <param name="p_ll">zu bearbeitende Liste</param>
/// <param name="index">Index des zu l�schenden Elements</param>
void ll_remove(ll_t** p_ll, size_t index) {
	//checken ob ein Parameter ungueltig ist
	if (p_ll == NULL || *p_ll == NULL || index < 0) {
		return; // Keine Aktion, ung�ltiger Index oder Liste
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
				previous->next = current->next; // Vorheriges Element �berspringen
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
/// Z�hlt die Anzahl der Elemente in der Liste.
/// </summary>
/// <param name="ll">Zu z�hlende Liste</param>
/// <returns>L�nge der Liste</returns>
size_t ll_count(const ll_t* ll) {
	//checken ob ein Parameter ungueltig ist
	if (ll == NULL) {
		return 0; // Keine Elemente in der Liste
	}
	size_t count = 0;
	const ll_t* current = ll;
	while (current != NULL) {
		count++; // Z�hler erh�hen f�r jedes Element
		current = current->next; // Zum n�chsten Element gehen
	}
	return count; // Anzahl der Elemente zur�ckgeben
}

/// <summary>
/// Funktion zum printen von int-Daten.
/// </summary>
/// <param name="data"></param>
/// <returns></returns>
int print_int(const void* data) {
	printf("%d\n", *(const int*)data);
	return 1;  // Erfolgreich ausgegeben
}
/// <summary>
/// Funktion zum printen von String-Daten.
/// </summary>
/// <param name="data"></param>
/// <returns></returns>
int print_string(const void* data) {
	printf("%s\n", (const char*)data);
	return 1;  // Erfolgreich ausgegeben
}