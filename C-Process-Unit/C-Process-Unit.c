/**
 * @file C-Process-Unit.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 08/05/2018
 *
 * @brief Header file for Directory Structure implementations
 *
 */

#include "include\Computer.h"

int main()
{
	/* Must have :
	 *
	 * - Current process being executed
	 * - Current process being terminated
	 * - Process Table at all times
	 *
	 */
	bool ok = true;

	while (ok)
	{
		print_main_menu();
		int c;
		printf("$ ");
		scanf_s("%d", &c);

		switch (c)
		{
		case 0:
			ok = false;
			break;
		case 1:
			process_unit_start();
			break;
		case 2:
			process_unit_quickstart();
			break;
		case 3:
			print_credits();
			break;
		default:
			printf("\nComando Inválido");
			break;
		}
		printf("\nPress enter to continue...");
		getch();
		system(CLEAR_SCREEN);
	}

	printf("\n");
    return 0;
}

