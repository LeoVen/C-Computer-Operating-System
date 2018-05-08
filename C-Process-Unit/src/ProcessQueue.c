/**
 * @file ProcessQueue.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 08/05/2018
 *
 * @brief Source file for Process Queue implementations
 *
 */

#include "..\include\Computer.h"

int pcq_init(ProcessQueue **pcq, size_t max_length)
{
	*pcq = malloc(sizeof(ProcessQueue));

	(*pcq)->front = NULL;
	(*pcq)->rear = NULL;
	(*pcq)->length = 0;

	(*pcq)->max_length = max_length;

	return 0;
}

int pcb_init(ProcessControlBlock **pcb, size_t p_id, char * p_name, size_t clocks)
{
	*pcb = malloc(sizeof(ProcessControlBlock));

	(*pcb)->p_id = p_id;
	(*pcb)->p_name = strdup(p_name);
	(*pcb)->clocks = clocks;

	return 0;
}

