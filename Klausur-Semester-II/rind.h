#pragma once
#include "ll.h" // ll_t muss inkludiert werden, damit es verwendet werden kann

# define RIND_NAME_LEN 30
typedef enum { RIND_STAT_AVAIL, RIND_STAT_COWSHED } rind_status_t;

typedef struct {
	char name[RIND_NAME_LEN + 1];			// Name des Rinds (fuer Laenge siehe Zeile 1)
	int age;								// Alter des Rinds
	int milkPerDay;							// Milchleistung pro Tag (in Liter)
	rind_status_t status;					// Status des Rinds (siehe Datentyp aus Zeile 2)
	ll_t* milk_log;							// Verkettete Liste fuer Milch-Historie
} rind_t;

#ifndef DATE_T_DEFINED
#define DATE_T_DEFINED
typedef struct {
	int day;		
	int month;		
	int year;		
} date_t;			// Neuer Datentyp fuer ein Datum
#endif

typedef struct {
	date_t date;	// Datum des Melkens
	int liters;		// Milchabgabe in Liter (mit einer Nachkommastelle!)	
} milk_entry_t;		// Neuer Datentyp fuer Milch-Historie

rind_t* rind_create(const char* name, int age, int milkperday);
int rind_print(const void* rind);
int rind_print_shed(const void* rind);
int rind_milk(rind_t * rind, date_t date);
rind_status_t rind_decide(rind_t * rind);
int rind_search_name(const void* rind, const void* name);
