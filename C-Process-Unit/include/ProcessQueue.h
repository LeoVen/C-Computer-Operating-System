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

#include <stdio.h>
#include <stdlib.h>

	typedef enum ProcessStatus {
		RUNNING, READY, TERMINATED
	} ProcessStatus;

	typedef struct ProcessControlBlock {
		char p_name[31];
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

#ifdef __cplusplus
}
#endif