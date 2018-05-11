/**
 * @file StringHandler.h
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 08/05/2018
 *
 * @brief Header file for Input handling functions
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Computer.h"

	int print_main_menu();
	int process_unit_start();
	int process_unit_quickstart();
	int print_menu_options();

	int proc_create(Computer *comp);
	int proc_remove(Computer *comp);
	int proc_alter(Computer *comp);
	int proc_list(Computer *comp);
	

#ifdef __cplusplus
}
#endif