/**
 * @file Computer.h
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 08/05/2018
 *
 * @brief Header file for Computer operations
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#define CLEAR_SCREEN "cls"
//#define CLEAR_SCREEN "clear"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "ProcessQueue.h"
#include "StringHandler.h"

	typedef struct Computer {
		size_t pid;                         /*!< Process ID given to each process */
		size_t clock_speed;                 /*!< How many processes can be processed at each iteration */
		ProcessControlBlock *curr_proc;     /*!< Current process being processed */
		ProcessControlBlock *curr_term;     /*!< Current process being terminated */
		ProcessQueue *proc_queue;           /*!< Process Queue */
	} Computer;

	int computer_init(Computer **cmp, size_t clock_s, size_t proc_queue_len);

#ifdef __cplusplus
}
#endif