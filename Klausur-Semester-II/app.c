#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "app.h"
#include "rind.h"
#include "ll.h"

typedef struct {
	const char* desc;
	int (*func)(ll_t**);
} app_action_t;
/// <summary>
/// Rind anlegen
/// </summary>
/// <param name="rinder">Doppelpointer um Wert an Adresse zu ändern</param>
/// <returns></returns>
static int act_create_rind(ll_t** rinder) {
	char name[RIND_NAME_LEN + 1];
	int age, milk;

	printf("Name des Rinds: ");
	while (1) {
		if (scanf_s("%30s", name, (unsigned)_countof(name)) == 1) {
			if (strlen(name) > 0) break;
		}
		printf("Ungueltiger Name. Bitte erneut eingeben: ");
		while (getchar() != '\n'); // Eingabepuffer leeren
	}

	printf("Alter (0-30): ");
	while (1) {
		if (scanf_s("%d", &age) == 1 && age >= 0 && age <= 30) break;
		printf("Ungueltiges Alter. Bitte Wert zwischen 0 und 30 eingeben: ");
		while (getchar() != '\n');
	}

	printf("Milchleistung (15-40 L/Tag): ");
	while (1) {
		if (scanf_s("%d", &milk) == 1 && milk >= 15 && milk <= 40) break;
		printf("Ungueltige Milchleistung. Bitte Wert zwischen 15 und 40 eingeben: ");
		while (getchar() != '\n');
	}

	// Pruefen auf Namensduplikat
	int idx;
	if (ll_search(*rinder, rind_search_name, name, &idx)) {
		printf("Ein Rind mit diesem Namen existiert bereits.\n");
		return 0;
	}

	rind_t* r = rind_create(name, age, milk);
	if (!r) {
		printf("Fehler beim Erstellen des Rinds.\n");
		return 0;
	}
	// Rind in die Liste einfuegen/anhängen
	if (!*rinder) {
		*rinder = ll_new(r);
	}
	else {
		ll_append(*rinder, r);
	}

	printf("Rind '%s' wurde hinzugefuegt.\n", name);
	return 1;
}
/// <summary>
/// Oberflächliches Menü für die Rinderverwaltung.
/// </summary>
/// <param name="rinder"></param>
void app_menu(ll_t** rinder) {

	// Text und Methoden verlinken
	app_action_t actions[] = {
		{"Rind anlegen", act_create_rind},
		{"Rinder swipen", act_swipe_rinder},
		{"Rinder im Stall anzeigen", act_print_shed},
		{"Rinder im Stall melken", act_milk_rinder},
		{"Rind loeschen", act_delete_rind},
		{"Rinder speichern (ohne Melk-Log)", act_save_rinder},
		{"Rinder laden (ohne Melk-Log)", act_load_rinder},
		{"Beenden", NULL}
	};

	const int action_count = sizeof(actions) / sizeof(actions[0]);
	//Hauptmenü-Schleife
	while (1) {
		printf("\nRinder - Der Milchhof-Simulator!\n");
		//Mit i die Aktionen auflisten und durchzählen
		for (int i = 0; i < action_count; i++) {
			printf("(%d) %s\n", i, actions[i].desc);
		}

		printf("\nAktion waehlen: ");
		int auswahl;
		if (scanf_s("%d", &auswahl) != 1 || auswahl < 0 || auswahl >= action_count) {
			printf("Ungueltige Eingabe.\n");
			while (getchar() != '\n'); // Eingabepuffer leeren
			continue;
		}

		if (actions[auswahl].func == NULL) {
			printf("Programm wird beendet.\n");
			break;	//Programm beenden
		}
		// Aufruf der gewählten Aktion mit .func und Übergabe der Rinderliste
		int result = actions[auswahl].func(rinder);
		if (result) printf("\n");
	}
}
/// <summary>
/// Kühe (t)rindern
/// </summary>
/// <param name="rinder"></param>
/// <returns></returns>
static int act_swipe_rinder(ll_t** rinder) {
	if (!rinder || !*rinder) {
		printf("Keine Rinder im System.\n");
		return 0;
	}

	ll_t* current = *rinder;
	int changes = 0;
	// Solange swipen bis e keine Rinder mehr gibt
	while (current) {
		rind_t* r = (rind_t*)current->data;

		if (r->status == RIND_STAT_AVAIL) {
			printf("\n--- Rind verfuegbar ---\n");
			// Rind anzeigen
			rind_print(r);
			printf("Nach [r]echts (Interesse) oder nach [l]inks (kein Interesse) wischen?");

			char antwort;
			while (1) {
				antwort = getchar();
				if (antwort == 'r' || antwort == 'l') {
					break;
				}
				if (antwort == '\n' || antwort == EOF) {
					continue; // Zeilenumbruch oder EOF ignorieren
				}
				printf("Ungueltige Eingabe. Bitte 'r' oder 'l' eingeben: ");
				// Eingabepuffer leeren
				while (getchar() != '\n' && getchar() != EOF);
			}
			//Antwort auswerten
			if (antwort == 'r') {
				rind_status_t entscheidung = rind_decide(r); // Entscheidung treffen
				if (entscheidung == RIND_STAT_COWSHED) {
					printf("Du hast Interesse an '%s' und sie auch an dir. Sie ist jetzt in deinem Stall.", r->name);
					changes++;
				}
				else {
					printf("Du hast Interesse an '%s', aber sie nicht an dir!\n", r->name);
					//Korb kassiert
				}
			}
		}
		current = current->next;	//Nächstes Rind in der Liste
	}

	if (changes == 0) {
		printf("Keine weiteren Rinder im Stall.\n");
	}

	return 1;
}
/// <summary>
/// Aktuellen Rinderstall anzeigen.
/// </summary>
/// <param name="rinder"></param>
/// <returns></returns>
static int act_print_shed(ll_t** rinder) {
	if (!rinder || !*rinder) {
		printf("Keine Rinder im System.\n");
		return 0;
	}

	ll_t* current = *rinder;
	int count = 0;
	// Liste durchlaufen und Rinder mit COWSHED-Status anzeigen
	while (current) {
		rind_t* r = (rind_t*)current->data;
		if (r->status == RIND_STAT_COWSHED) {
			rind_print_shed(r);			// Rind anzeigen mit mehr Informationen als nur Name
			count++;
		}
		current = current->next;
	}

	if (count == 0) {
		printf("Der Stall ist leer.\n");	//Sonderfall
	}

	return 1;
}
/// <summary>
/// Rinder melken.
/// </summary>
/// <param name="rinder"></param>
/// <returns></returns>
static int act_milk_rinder(ll_t** rinder) {
	if (!rinder || !*rinder) {
		printf("Keine Rinder im System.\n");
		return 0;
	}

	// Aktuelles Datum ermitteln
	time_t t = time(NULL);
	struct tm* tm_info = localtime(&t);
	date_t today = {
		.day = tm_info->tm_mday,
		.month = tm_info->tm_mon + 1,
		.year = tm_info->tm_year + 1900
	};

	ll_t* current = *rinder;
	int total_liters = 0;
	int count = 0;
	// iste durchlaufen und Rinder mit COWSHED-Status melken
	while (current) {
		rind_t* r = (rind_t*)current->data;
		if (r->status == RIND_STAT_COWSHED) {
			int ml = rind_milk(r, today);
			if (ml > 0) {
				// Melkeintrag erstellen
				printf("%s hat %.1f L gegeben.\n", r->name, ml / 10.0);
				total_liters += ml;
				count++;
			}
		}
		current = current->next;
	}

	if (count == 0) {
		printf("Keine Rinder im Stall oder keine Milchleistung.\n");
	}
	else {
		printf("Gesamte Milchmenge heute: %.1f L\n", total_liters / 10.0);
	}

	return 1;
}
/// <summary>
/// Rind komplett löschen.
/// </summary>
/// <param name="rinder"></param>
/// <returns></returns>
static int act_delete_rind(ll_t** rinder) {
	if (!rinder || !*rinder) {
		printf("Keine Rinder im System.\n");
		return 0;
	}

	char name[RIND_NAME_LEN + 1];
	printf("Name des zu loeschenden Rinds: ");
	if (scanf_s("%30s", name, (unsigned)_countof(name)) != 1) return 0;

	int idx = -1;
	// Suche nach dem Rind anhand des Namens
	ll_t* found = ll_search(*rinder, rind_search_name, name, &idx);

	if (!found || idx < 0) {
		printf("Kein Rind mit dem Namen '%s' gefunden.\n", name);
		return 0;
	}

	// Speicher freigeben
	rind_t* r = (rind_t*)found->data;	// Rind aus der Liste holen
	ll_t* node = r->milk_log;			// Verkettete Liste der Milcheinträge
	while (node) {
		ll_t* next = node->next;
		free(node->data); // milk_entry_t
		free(node);
		node = next;
	}
	free(r);

	// Aus Liste entfernen
	ll_remove(rinder, idx);

	printf("Rind '%s' wurde geloescht.\n", name);
	return 1;
}
/// <summary>
/// Erzeugt eine Datei mit den Rindern und ihren Milcheintraegen.
/// </summary>
/// <param name="rinder">die Liste der Rinder</param>
/// <returns> Ergebnis </returns>
static int act_save_rinder(ll_t** rinder) {
	if (!rinder || !*rinder) {
		printf("Keine Rinder zum Speichern.\n");
		return 0;
	}

	const char* filename = "rinder.bin";
	// Datei zum Schreiben oeffnen
	FILE* file = fopen(filename, "wb");
	if (!file) {
		perror("Fehler beim Oeffnen der Datei");
		return 0;
	}

	ll_t* current = *rinder;
	while (current) {
		rind_t* r = (rind_t*)current->data;

		// Temporaere Kopie ohne verkettete Liste
		rind_t temp = *r;
		temp.milk_log = NULL;

		// Anzahl der Milcheintraege zaehlen
		size_t count = ll_count(r->milk_log);

		// Rind + Anzahl schreiben
		fwrite(&temp, sizeof(rind_t), 1, file);
		fwrite(&count, sizeof(size_t), 1, file);

		// Milcheintraege schreiben
		ll_t* milk_node = r->milk_log;
		while (milk_node) {
			milk_entry_t* entry = (milk_entry_t*)milk_node->data;
			fwrite(entry, sizeof(milk_entry_t), 1, file);
			milk_node = milk_node->next;
		}

		current = current->next;
	}

	fclose(file);
	printf("Rinder wurden erfolgreich in '%s' gespeichert.\n", filename);
	return 1;
}
static int act_load_rinder(ll_t** rinder) {
	const char* filename = "rinder.bin";

	// Datei zum Lesen oeffnen
	FILE* file = fopen(filename, "rb");
	if (!file) {
		perror("Fehler beim Oeffnen der Datei");
		return 0;
	}

	// Vorherige Liste loeschen
	ll_t* current = *rinder;
	while (current) {
		rind_t* r = (rind_t*)current->data;
		ll_t* milk_node = r->milk_log;
		while (milk_node) {
			ll_t* next = milk_node->next;
			free(milk_node->data);
			free(milk_node);
			milk_node = next;
		}
		free(r);
		ll_t* next = current->next;
		free(current);
		current = next;
	}
	*rinder = NULL;
	// Während dateiende nicht erreicht ist, Rinder laden
	while (!feof(file)) {
		rind_t temp;
		size_t count;

		if (fread(&temp, sizeof(rind_t), 1, file) != 1) break;
		if (fread(&count, sizeof(size_t), 1, file) != 1) break;

		rind_t* r = malloc(sizeof(rind_t));
		if (!r) break;
		*r = temp;
		r->milk_log = NULL;
		// Melk-Log laden - optional
		for (size_t i = 0; i < count; i++) {
			milk_entry_t* entry = malloc(sizeof(milk_entry_t));
			if (!entry || fread(entry, sizeof(milk_entry_t), 1, file) != 1) {
				free(entry);
				break;
			}
			if (!r->milk_log) {
				r->milk_log = ll_new(entry);
			}
			else {
				ll_append(r->milk_log, entry);
			}
		}
		// Rind in die Liste einfuegen
		if (!*rinder) {
			*rinder = ll_new(r);
		}
		else {
			ll_append(*rinder, r);
		}
	}

	fclose(file);
	printf("Rinder wurden erfolgreich aus '%s' geladen.\n", filename);
	return 1;
}
