#include <stdio.h>
#pragma once
typedef struct ll_s {
	void* data;			// void-Pointer, fuer Daten der Rinder
	struct ll_s* next;	// Zeiger auf naechstes Element der Liste
} ll_t;

ll_t* ll_new(void* data);
void ll_append(ll_t* ll, void* data);
ll_t* ll_get(ll_t* ll, size_t index);
void ll_remove(ll_t** p_ll, size_t index);
size_t ll_count(const ll_t* ll);
ll_t* ll_search(ll_t* ll, int (*search_fn)(const void*, const void*), const void* search, int* idx);
int ll_print(const ll_t* ll, int (*print_fn)(const void*));
int print_int(const void* data);
int print_string(const void* data);