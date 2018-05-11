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
	fflush(stdin);

	printf("\nProcess Queue Length: ");
	scanf_s("%zu", &len);
	fflush(stdin);

	computer_init(&comp, clocks, len);

	bool ok = true;

	while (ok)
	{
		int cmd;

		print_menu_options();
		
		printf(" > ");
		scanf_s("%d", &cmd);
		fflush(stdin);

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
	char buffer[31];
	size_t clocks;
	char *t;
	ProcessControlBlock *pcb;

	printf("\nCreate a process");
	
	printf("\nProcess Name:\n > ");
	scanf_s("%c\n", &t);
	
	fgets(buffer, 31, stdin);

	buffer[strlen(buffer) - 1] = '\0';

	printf("\nClocks to be processed:\n > ");
	fflush(stdin);
	scanf_s("%zu", &clocks);

	comp->pid++;
	pcb_init(&pcb, comp->pid, buffer, clocks);

	pcb_enqueue(comp->proc_queue, pcb);

	return 0;
}

int proc_remove(Computer *comp)
{
	if (queue_is_empty(comp->proc_queue))
		return 1;


	return 0;
}

int proc_alter(Computer *comp)
{
	if (queue_is_empty(comp->proc_queue))
		return 1;

	size_t pid;

	char *t;

	printf("\nSearch PID: ");
	scanf_s("%c\n", &t);
	scanf_s("%zu", &pid);

	ProcessControlBlock *scan = comp->proc_queue->front;

	while (scan != NULL && scan->p_id != pid)
	{

	}

	if (scan == NULL) {
		printf("\nProcess Not Found");
		return 1;
	}
	
	pcb_display_single(scan);

	return 0;
}

int proc_list(Computer *comp)
{
	return pcb_display(comp->proc_queue);
}