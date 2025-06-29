#pragma once
#include "ll.h"			//muss inkludiert werden damit ll_t verwendet werden kann

int act_create_rind(ll_t** rinder);
int act_swipe_rinder(ll_t** rinder);
int act_print_shed(ll_t** rinder);
int act_milk_rinder(ll_t** rinder);
int act_delete_rind(ll_t** rinder);
int act_save_rinder(ll_t** rinder);
int act_load_rinder(ll_t** rinder);
void app_menu(ll_t** rinder);
