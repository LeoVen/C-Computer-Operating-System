/**
 * @file Computer.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 08/05/2018
 *
 * @brief Source file for Computer operations
 *
 */

#include "..\include\Computer.h"
#include "..\include\ProcessQueue.h"

int computer_init(Computer **cmp, size_t clock_s, size_t proc_queue_len)
{
	*cmp = malloc(sizeof(Computer));

	(*cmp)->clock_speed = clock_s;

	(*cmp)->pid = 0;

	(*cmp)->curr_proc = NULL;
	(*cmp)->curr_term = NULL;

	pcq_init(&((*cmp)->proc_queue), proc_queue_len);

	return 0;
}

int computer_process(Computer *comp, ProcessQueue *pcq)
{
	// Start processing all processes in queue
	return 0;
}