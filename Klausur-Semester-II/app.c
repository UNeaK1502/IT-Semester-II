#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "app.h"
#include "rind.h"
#include "ll.h"

static int act_create_rind(ll_t** rinder) {
    char name[RIND_NAME_LEN + 1];
    int age, milk;

    printf("Name des Rinds: ");
    if (scanf_s("%30s", name, (unsigned)_countof(name)) != 1) return 0;

    printf("Alter (0-30): ");
    if (scanf_s("%d", &age) != 1 || age < 0 || age > 30) return 0;

    printf("Milchleistung (15-40 L/Tag): ");
    if (scanf_s("%d", &milk) != 1 || milk < 15 || milk > 40) return 0;

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

    if (!*rinder) {
        *rinder = ll_new(r);
    }
    else {
        ll_append(*rinder, r);
    }

    printf("Rind '%s' wurde hinzugefuegt.\n", name);
    return 1;
}

void app_menu(ll_t** rinder) {
    typedef struct {
        const char* desc;
        int (*func)(ll_t**);
    } app_action_t;

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

    while (1) {
        printf("\nRinder - Der Milchhof-Simulator!\n");
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
            break;
        }

        int result = actions[auswahl].func(rinder);
        if (result) printf("\n");
    }
}

static int act_swipe_rinder(ll_t** rinder) {
    if (!rinder || !*rinder) {
        printf("Keine Rinder im System.\n");
        return 0;
    }

    ll_t* current = *rinder;
    int changes = 0;

    while (current) {
        rind_t* r = (rind_t*)current->data;

        if (r->status == RIND_STAT_AVAIL) {
            printf("\n--- Rind verfuegbar ---\n");
            rind_print(r);

            printf("Nach [r]echts (Interesse) oder nach [l]inks (kein Interesse) wischen?");
            char antwort;
            while ((antwort = getchar()) != EOF && antwort != 'r' && antwort != 'l');

            if (antwort == 'r') {
                rind_status_t entscheidung = rind_decide(r);
                if (entscheidung == RIND_STAT_COWSHED) {
                    printf("Du hast Interesse an '%s' und sie auch an dir. Sie ist jetzt in deinem Stall.", r->name);
                    changes++;
                }
                else {
                    printf("Du hast Interesse an '%s', aber sie nicht an dir!\n", r->name);
                }
            }
        }

        current = current->next;
    }

    if (changes == 0) {
        printf("Keine neuen Rinder im Stall.\n");
    }

    return 1;
}
static int act_print_shed(ll_t** rinder) {
    if (!rinder || !*rinder) {
        printf("Keine Rinder im System.\n");
        return 0;
    }

    ll_t* current = *rinder;
    int count = 0;

    while (current) {
        rind_t* r = (rind_t*)current->data;
        if (r->status == RIND_STAT_COWSHED) {
            rind_print_shed(r);
            count++;
        }
        current = current->next;
    }

    if (count == 0) {
        printf("Der Stall ist leer.\n");
    }

    return 1;
}
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

    while (current) {
        rind_t* r = (rind_t*)current->data;
        if (r->status == RIND_STAT_COWSHED) {
            int ml = rind_milk(r, today);
            if (ml > 0) {
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
static int act_delete_rind(ll_t** rinder) {
    if (!rinder || !*rinder) {
        printf("Keine Rinder im System.\n");
        return 0;
    }

    char name[RIND_NAME_LEN + 1];
    printf("Name des zu loeschenden Rinds: ");
    if (scanf_s("%30s", name, (unsigned)_countof(name)) != 1) return 0;

    int idx = -1;
    ll_t* found = ll_search(*rinder, rind_search_name, name, &idx);

    if (!found || idx < 0) {
        printf("Kein Rind mit dem Namen '%s' gefunden.\n", name);
        return 0;
    }

    // Speicher freigeben
    rind_t* r = (rind_t*)found->data;
    ll_t* node = r->milk_log;
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
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Fehler beim oeffnen der Datei");
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
    FILE* file = fopen(filename, "rb");
    if (!file) {
        perror("Fehler beim oeffnen der Datei");
        return 0;
    }

    // Vorherige Liste loeschen (optional)
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

    while (!feof(file)) {
        rind_t temp;
        size_t count;

        if (fread(&temp, sizeof(rind_t), 1, file) != 1) break;
        if (fread(&count, sizeof(size_t), 1, file) != 1) break;

        rind_t* r = malloc(sizeof(rind_t));
        if (!r) break;
        *r = temp;
        r->milk_log = NULL;

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
