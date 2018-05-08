/**
 * @file StringHandler.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 08/05/2018
 *
 * @brief Source file for Input handling functions
 *
 */

#include "..\include\Computer.h"

int print_main_menu()
{
	printf("\n +-------------------------------------------------------------------+");
	printf("\n | Menu                                                              |");
	printf("\n |                                                                   |");
	printf("\n | 0 - Exit                                                          |");
	printf("\n | 1 - Start                                                         |");
	printf("\n | 2 - Quick Start                                                   |");
	printf("\n | 3 - Credits                                                       |");
	printf("\n |                                                                   |");
	printf("\n +-------------------------------------------------------------------+");
	printf("\n");

	return 0;
}

int print_credits()
{
	printf("\n +-------------------------------------------------------------------+");
	printf("\n |                                                                   |");
	printf("\n |                           Process Unit                            |");
	printf("\n |                                                                   |");
	printf("\n |  Created By:                                                      |");
	printf("\n |                                                                   |");
	printf("\n |  Guilherme Pinazza                                                |");
	printf("\n |  Leonardo Vencovsky                                               |");
	printf("\n |  Vitor Facioli                                                    |");
	printf("\n |                                                                   |");
	printf("\n +-------------------------------------------------------------------+");
	printf("\n");
}

int process_unit_quickstart()
{
	printf("\nComming Soon");
	return 0;
}

int process_unit_start()
{
	Computer *comp;

	size_t clocks, len;
	printf("\nComputer Clock Speed: ");
	scanf_s("%zu", &clocks);
	printf("\nProcess Queue Length: ");
	scanf_s("%zu", &len);

	computer_init(&comp, clocks, len);

	printf("\nProcess Queue Maximum Length: %zu", comp->proc_queue->max_length);

	free(comp);
	return 0;
}

int print_menu_options()
{
	printf("\n  Command List                                                     ");
}
