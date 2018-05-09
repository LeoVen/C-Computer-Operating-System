/**
 * @file ProcessQueue.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 08/05/2018
 *
 * @brief Source file for Process Queue implementations
 *
 */

#pragma warning(disable : 4996)

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
	(*pcb)->p_name = _strdup(p_name);
	(*pcb)->clocks = clocks;

	time_t now = time(NULL);
	(*pcb)->time = _strdup(ctime(&now));
	(*pcb)->time[strlen((*pcb)->time) - 1] = '\0';

	return 0;
}

int pcb_enqueue(ProcessQueue *pcq, ProcessControlBlock *block)
{
	if (pcq == NULL)
		return 1;

	if (pcq->length >= pcq->max_length)
		return 2;

	block->prev = NULL;

	if (pcq->rear == NULL) {

		pcq->rear = block;
		pcq->front = block;

	}
	else {

		pcq->rear->prev = block;
		pcq->rear = block;

	}

	(pcq->length)++;

	return 0;
}

int pcb_dequeue(ProcessQueue *pcq, ProcessControlBlock **block)
{
	if (pcq == NULL)
		return 1;

	if (pcq->length == 0)
		return 1;

	ProcessControlBlock *pcb = pcq->front;

	pcq->front = pcq->front->prev;

	(*block) = pcb;

	(pcq->length)--;

	if (pcq->length == 0)
		pcq->rear = NULL;

	return 0;
}

int pcb_display(ProcessQueue *pcq)
{
	if (pcq == NULL)
		return 1;

	if (pcq->length == 0) {

		// PID, Name, Clocks, Status, Time
		printf("\n PID \t P-Name \t Clocks \t Status \t Time \n");
		return 0;

	}

	ProcessControlBlock *scan = pcq->front;

	printf("\n PID \t P-Name \t Clocks \t Status \t Time \n");

	while (scan != NULL)
	{
		// PID, Name, Clocks, Status, Time
		printf("\n %zu \t %s \t %6zu \t %s \t %s", scan->p_id, scan->p_name, scan->clocks, proc_status_str(scan->status), scan->time);

		scan = scan->prev;
	}

	printf("\n");

	return 0;
}

char * proc_status_str(ProcessStatus st)
{
	switch (st)
	{
		case STARTING:
			return "STARTING";
		case RUNNING:
			return "RUNNING";
		case READY:
			return "READY";
		case TERMINATED:
			return	"TERMINATED";
		default:
			return "UNKNOWN";
	}
}