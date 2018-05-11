#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE
#define _CRT_NONSTDC_NO_DEPRECATE
#define _USE_MATH_DEFINES

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <time.h>
#include <conio.h>

#define MAX_LEN 7
#define NAME_SIZE 31
#define PROC_SPEED 1
#define clear_screen system("cls")

/*
 * Typedefs
 *
 */
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

typedef struct Computer {
	size_t pid;
	struct ProcessControlBlock *curr_proc;
	struct ProcessControlBlock *curr_term;
	struct ProcessQueue *proc_queue;
} Computer;

/*
 * Functions
 *
 */
int proc_add(Computer *computer);
int proc_remove(Computer *computer);
int proc_alter(Computer *computer);
int proc_list(Computer *computer);
int print_menu();

int quick_start();

/*
 * Computer related functions
 *
 */
int init_computer(Computer **computer);
int process_all(Computer *computer);

/*
 * List related functions
 *
 */
int init_queue(ProcessQueue **queue);
int init_block(ProcessControlBlock **block, size_t pid, char *pname, size_t clocks);
int enqueue(ProcessQueue *queue, ProcessControlBlock *block);
int dequeue(ProcessQueue *queue, ProcessControlBlock **block);
bool is_empty(ProcessQueue *queue);
bool is_full(ProcessQueue *queue);

/*
 * Display
 *
 */
int display_queue(ProcessQueue *queue);
int display_block(ProcessControlBlock *block);
char * status_repr(ProcessStatus st);

/*
 * User input related functions
 *
 */
size_t get_clocks(void);
char * get_name(void);
char * get_time(void);

void u_flush(void);
char * strdup(const char *src);

int main(int argc, char const *argv[])
{
	bool ok = true;

	Computer *computer;

	init_computer(&computer);

	while (ok)
	{
		clear_screen;

		print_menu();

		fflush(stdin);
		int d;
		scanf("%d", &d);

		switch (d)
		{
		case 0:
			ok = false;
			break;
		case 1:
			proc_add(computer);
			break;
		case 2:
			proc_remove(computer);
			break;
		case 3:
			proc_alter(computer);
			break;
		case 4:
			proc_list(computer);
			break;
		case 5:
			quick_start();
			break;
		default:
			printf("\nInvalid option");
			break;
		}
		printf("\nPress enter to continue...");
		getch();
	}


	return 0;
}

/*
 * Functions
 *
 */
int proc_add(Computer *computer)
{
	if (is_full(computer->proc_queue)) {

		printf("\nProcess Queue is already full");
		return 1;
	}

	int st;

	ProcessControlBlock *block;

	(computer->pid)++;
	st = init_block(&block, computer->pid, get_name(), get_clocks());

	if (st != 0)
		printf("\nInit Block Failed");

	st = enqueue(computer->proc_queue, block);

	if (st != 0)
		printf("\nEnqueue Block Failed");

	return 0;
}

int proc_remove(Computer *computer)
{
	if (is_empty(computer->proc_queue)) {

		printf("\nProcess Queue is already empty");
		return 1;
	}



	return 0;
}

int proc_alter(Computer *computer)
{
	if (is_empty(computer->proc_queue)) {

		printf("\nProcess Queue is empty");
		return 1;
	}

	return 0;
}

int proc_list(Computer *computer)
{
	return display_queue(computer->proc_queue);
}

int print_menu()
{
	printf("\n  Command List                                                     ");
	printf("\n                                                                   ");
	printf("\n  0 - Exit                                                         ");
	printf("\n  1 - Create Process                                               ");
	printf("\n  2 - Remove Process                                               ");
	printf("\n  3 - Alterate Process                                             ");
	printf("\n  4 - List Process Table                                           ");
	printf("\n  5 - Quick Start                                                  ");
	printf("\n");
	printf("\n > ");

	return 0;
}

/*
 * Computer related functions
 *
 */
int init_computer(Computer **computer)
{
	(*computer) = malloc(sizeof(Computer));

	(*computer)->curr_proc = NULL;
	(*computer)->curr_term = NULL;

	(*computer)->pid = 0;

	init_queue(&((*computer)->proc_queue));

	return 0;
}

int process_all(Computer *computer)
{
	printf("\nComing soon");

	return 0;
}

/*
 * List related Functions
 *
 */
int init_queue(ProcessQueue **queue)
{
	*queue = malloc(sizeof(ProcessQueue));

	(*queue)->front = NULL;
	(*queue)->rear = NULL;
	(*queue)->length = 0;

	(*queue)->max_length = MAX_LEN;

	return 0;
}

int init_block(ProcessControlBlock **block, size_t pid, char *pname, size_t clocks)
{
	*block = malloc(sizeof(ProcessControlBlock));

	(*block)->p_id = pid;
	(*block)->p_name = strdup(pname);
	(*block)->clocks = clocks;

	(*block)->status = READY;

	(*block)->time = get_time();

	return 0;
}

int enqueue(ProcessQueue *queue, ProcessControlBlock *block)
{
	if (queue == NULL)
		return 1;

	if (is_full(queue))
		return 2;

	block->prev = NULL;

	if (queue->rear == NULL) {

		queue->rear = block;
		queue->front = block;

	}
	else {

		queue->rear->prev = block;
		queue->rear = block;

	}

	(queue->length)++;

	return 0;
}

int dequeue(ProcessQueue *queue, ProcessControlBlock **block)
{
	if (queue == NULL)
		return 1;

	if (is_empty(queue))
		return 1;

	(*block) = queue->front;

	queue->front = queue->front->prev;

	(*block)->prev = NULL;

	(queue->length)--;

	if (is_empty(queue))
		queue->rear = NULL;

	return 0;
}

bool is_empty(ProcessQueue *queue)
{
	return (queue->length == 0);
}

bool is_full(ProcessQueue *queue)
{
	return (queue->length >= queue->max_length);
}

/*
 * Display
 *
 */
int display_queue(ProcessQueue *queue)
{
	if (queue == NULL)
		return 1;

	if (is_empty(queue)) {

		// PID, Name, Clocks, Status, Time
		printf("\n PID \t P-Name \t Clocks \t Status \t Time \n");
		return 0;

	}

	ProcessControlBlock *scan = queue->front;

	printf("\n PID \t P-Name \t Clocks \t Status \t Time \n");

	while (scan != NULL)
	{
		// PID, Name, Clocks, Status, Time
		printf("\n %zu \t %s \t %6zu \t %s \t %s", scan->p_id, scan->p_name, scan->clocks, status_repr(scan->status), scan->time);

		scan = scan->prev;
	}

	printf("\n");

	return 0;
}

int display_block(ProcessControlBlock *block)
{
	if (block == NULL)
		return 1;

	printf("\n %zu \t %s \t %6zu \t %s \t %s", block->p_id, block->p_name, block->clocks, status_repr(block->status), block->time);

	return 0;
}

char * status_repr(ProcessStatus st)
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

/*
 * User input related functions
 *
 */
size_t get_clocks()
{
	size_t clocks;

	printf("\nProcess total clocks: ");

	fflush(stdin);
	u_flush();
	scanf("%zu", &clocks);

	return clocks;
}

char * get_name(void)
{
	char name[NAME_SIZE];

	printf("\nProcess name: ");

	fflush(stdin);
	u_flush();
	fgets(name, NAME_SIZE, stdin);

	name[strlen(name) - 1] = '\0';

	return strdup(name);
}

char * get_time(void)
{
	time_t now = time(NULL);
	char * time = strdup(ctime(&now));
	time[strlen(time) - 1] = '\0';

	return time;
}

void u_flush(void)
{
	char *t;
	scanf("%c\n", &t);
}

char * strdup(const char *src) {
	size_t len = strlen(src) + 1;

	char * s = malloc(len);

	if (s == NULL)
		return NULL;

	return (char *)memcpy(s, src, len);
}

/*
 * Others
 *
 */
int quick_start()
{
	printf("\nComing soon");

	return 0;
}