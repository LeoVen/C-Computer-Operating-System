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

	return 0;
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

	bool ok = true;

	while (ok)
	{
		int cmd;

		print_menu_options();
		
		printf(" > ");
		scanf_s("%d", &cmd);

		switch (cmd)
		{
		case 0:
			ok = false;
			break;
		case 1:
			proc_create(comp);
			break;
		case 2:
			proc_remove(comp);
			break;
		case 3:
			proc_alter(comp);
			break;
		case 4:
			proc_list(comp);
			break;
		default:
			printf("\nInvalid Command");
			break;
		}
		printf("\nPress enter to continue...");
		getch();
		system(CLEAR_SCREEN);
	}

	free(comp);
	return 0;
}

int print_menu_options()
{
	printf("\n  Command List                                                     ");
	printf("\n                                                                   ");
	printf("\n  0 - Exit                                                         ");
	printf("\n  1 - Create Process                                               ");
	printf("\n  2 - Remove Process                                               ");
	printf("\n  3 - Alterate Process                                             ");
	printf("\n  4 - List Process Table                                           ");
	printf("\n");
	printf("\n");
}

int proc_create(Computer *comp)
{


	return 0;
}

int proc_remove(Computer *comp)
{


	return 0;
}

int proc_alter(Computer *comp)
{


	return 0;
}

int proc_list(Computer *comp)
{


	return 0;
}