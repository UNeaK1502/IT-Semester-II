#pragma once
#include "ll.h"			//muss inkludiert werden damit ll_t verwendet werden kann

int act_create_rind(ll_t** rinder);	//Anlegen eines neuen Rinds im System.
int act_swipe_rinder(ll_t** rinder);//Erm�glicht �swipen� (Auswahl) der Rinder.
int act_print_shed(ll_t** rinder);	//Gibt alle Rinder im Stall aus.
int act_milk_rinder(ll_t** rinder);	//Erm�glicht das Melken der Rinder.
int act_delete_rind(ll_t** rinder);	//L�scht ein Rind aus dem System.
int act_save_rinder(ll_t** rinder);	// Speichert die Rinder in eine Datei.
int act_load_rinder(ll_t** rinder);	// L�dt die Rinder aus einer Datei.
void app_menu(ll_t** rinder);		// 0.6 Hauptmen� der Anwendung.
