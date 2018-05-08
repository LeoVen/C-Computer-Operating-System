/**
 * @file C-Process-Unit.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 08/05/2018
 *
 * @brief Header file for Directory Structure implementations
 *
 */

#include "include\ProcessQueue.h"

int main()
{
	/* Must have :
	 *
	 * - Current process being executed
	 * - Current process being terminated
	 * - Process Table at all times
	 *
	 */
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

	ProcessQueue *pcq;

	size_t len;

	printf("\nDefine maximum Queue length: ");
	scanf_s("%zu", &len);

	pcq_init(&pcq, len);

	printf("\n");
    return 0;
}

