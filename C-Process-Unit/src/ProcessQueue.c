/**
 * @file ProcessQueue.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 08/05/2018
 *
 * @brief Source file for Process Queue implementations
 *
 */

#include "..\include\ProcessQueue.h"

int pcq_init(ProcessQueue **pcq, size_t max_length)
{
	*pcq = malloc(sizeof(ProcessQueue));

	(*pcq)->front = NULL;
	(*pcq)->rear = NULL;
	(*pcq)->length = 0;

	(*pcq)->max_length = max_length;

	return 0;
}
