/**
 * @file ProcessQueue.h
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 08/05/2018
 *
 * @brief Header file for Process Queue implementations
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include "Computer.h"

	typedef enum ProcessStatus {
		STARTING, RUNNING, READY, TERMINATED
	} ProcessStatus;

	typedef struct ProcessControlBlock {
		char * p_name;
		char * time;
		size_t p_id;
		size_t clocks;
		enum ProcessStatus status;
		struct ProcessControlBlock *prev;
	} ProcessControlBlock;

	typedef struct ProcessQueue {
		size_t length;
		size_t max_length;
		struct ProcessControlBlock *front;
		struct ProcessControlBlock *rear;
	} ProcessQueue;

	int pcq_init(ProcessQueue **pcq, size_t max_length);
	int pcb_init(ProcessControlBlock **pcb, size_t p_id, char * p_name, size_t clocks);

	int pcb_enqueue(ProcessQueue *pcq, ProcessControlBlock *block);
	int pcb_dequeue(ProcessQueue *pcq, ProcessControlBlock **block);

	int pcb_display_single(ProcessControlBlock *pcb);
	int pcb_display(ProcessQueue *pcq);

	char * proc_status_str(ProcessStatus st);

	bool queue_is_empty(ProcessQueue *pcq);

#ifdef __cplusplus
}
#endif