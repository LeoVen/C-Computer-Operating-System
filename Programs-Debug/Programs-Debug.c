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

// Sleep Function
//#include <unistd.h> // -- Linux
#include <windows.h>  // -- Windows

#define SLEEP(n) Sleep(n)

#define MAX_LEN 13
#define MAX_END_LEN 999999
#define NAME_SIZE 31
#define PROC_SPEED 1
#define clear_screen system("cls")

/*
 * Typedefs
 *
 */
typedef struct ProcessControlBlock {
	char * p_name;
	char * time;
	size_t p_id;
	size_t clocks;
	size_t effective_clocks;
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
	size_t proc_speed;
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
int proc_all(Computer **computer);
int print_choices();
int print_menu();

int quick_start();

/*
 * Computer related functions
 *
 */
int init_computer(Computer **computer, size_t proc_speed, size_t max_len);
int process_all(Computer **computer, size_t msecs);

/*
 * List related functions
 *
 */
int init_queue(ProcessQueue **queue, size_t max_len);
int init_block(ProcessControlBlock **block, size_t pid, char *pname, size_t clocks);
ProcessControlBlock * get_block(size_t pid, char *pname, size_t clocks);
int enqueue(ProcessQueue *queue, ProcessControlBlock *block);
int dequeue(ProcessQueue *queue, ProcessControlBlock **block);
int search(ProcessQueue *queue, size_t pid, ProcessControlBlock **block);
bool is_empty(ProcessQueue *queue);
bool is_full(ProcessQueue *queue);

/*
 * Display
 *
 */
int display_queue(ProcessQueue *queue);
int display_effective_queue(ProcessQueue *queue);
int display_block(ProcessControlBlock *block);

/*
 * User input related functions
 *
 */
size_t get_pid();
size_t get_clocks(void);
char * get_name(void);
char * get_time(void);

char * strdup(const char *src);

int main(int argc, char const *argv[])
{
	bool ok = true;

	Computer *computer;

	init_computer(&computer, PROC_SPEED, MAX_LEN);

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
			proc_all(&computer);
			break;
		case 6:
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

	char *name = get_name();
	size_t clocks = get_clocks();

	(computer->pid)++;
	st = init_block(&block, computer->pid, name, clocks);

	if (st != 0)
		printf("\nInit Block Failed");

	st = enqueue(computer->proc_queue, block);

	if (st == 2)
		printf("\nProcess Queue is Full");
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

	ProcessControlBlock *block;

	size_t pid = get_pid();

	search(computer->proc_queue, pid, &block);

	if (block == NULL) {

		printf("\nProcess with specified PID not found");
		return 1;
	}

	if (computer->proc_queue->front->p_id == block->p_id)
	{
		computer->proc_queue->front = computer->proc_queue->front->prev;

		if (computer->proc_queue->front == NULL)
			computer->proc_queue->rear = NULL;

		free(block);
	}
	else
	{
		ProcessControlBlock *scan = computer->proc_queue->front;

		while (scan->prev->p_id != block->p_id)
		{
			scan = scan->prev;
		}

		scan->prev = scan->prev->prev;

		computer->proc_queue->rear = scan;

		free(block);
	}

	(computer->proc_queue->length)--;

	return 0;
}

int proc_alter(Computer *computer)
{
	if (is_empty(computer->proc_queue)) {

		printf("\nProcess Queue is empty");
		return 1;
	}

	ProcessControlBlock *block;

	size_t pid = get_pid();

	search(computer->proc_queue, pid, &block);

	if (block == NULL) {
		
		printf("\nProcess with specified PID not found");
		return 1;
	}

	bool ok = true;

	size_t clocks;
	char * name;

	while (ok)
	{
		clear_screen;
		display_block(block);
		print_choices();
		int c;
		scanf("%d", &c);

		switch (c)
		{
		case 0:
			ok = false;
			break;
		case 1:
			name = get_name();
			block->p_name = name;
			break;
		case 2:
			clocks = get_clocks();
			block->clocks = clocks;
			block->effective_clocks = clocks;
			break;
		default:
			printf("\nInvalid Option");
			break;
		}
	}

	return 0;
}

int proc_list(Computer *computer)
{
	return display_queue(computer->proc_queue);
}

int proc_all(Computer **computer)
{
	process_all(computer, 500);
	return 0;
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
	printf("\n  5 - Process All                                                  ");
	printf("\n  6 - Quick Start                                                  ");
	printf("\n");
	printf("\n > ");

	return 0;
}

int print_choices()
{
	printf("\n                                                                   ");
	printf("\n  0 - Exit                                                         ");
	printf("\n  1 - Change Name                                                  ");
	printf("\n  2 - Change Clocks                                                ");
	printf("\n > ");

	return 0;
}

/*
 * Computer related functions
 *
 */
int init_computer(Computer **computer, size_t proc_speed, size_t max_len)
{
	(*computer) = malloc(sizeof(Computer));

	(*computer)->pid = 0;
	(*computer)->proc_speed = proc_speed;

	init_queue(&((*computer)->proc_queue), max_len);

	return 0;
}

int process_all(Computer **computer, size_t msecs)
{
	ProcessControlBlock *block;
	ProcessQueue *queue = (*computer)->proc_queue;

	size_t proc_speed = (*computer)->proc_speed;
	printf("\n%u", proc_speed);
	ProcessQueue *term;
	init_queue(&term, MAX_END_LEN);

	while (queue->length > 0)
	{
		clear_screen;

		printf("\n Queue Length: %d", queue->length);

		printf("\n Current Process in CPU: ");
		if (!is_empty(queue))
			printf("%s", queue->front->p_name);

		dequeue(queue, &block);
		block->clocks -= proc_speed;

		if (block->clocks <= 0) {

			printf("\n Current Process Terminating: ");
			enqueue(term, block);
			printf("%s", term->rear->p_name);
		}
		else {

			printf("\n Current Process Terminating: ");
			enqueue(queue, block);
			if (term->rear != NULL)
				printf("%s", term->rear->p_name);
		}

		display_queue(queue);

		SLEEP(msecs);
	}

	printf("\n Process Terminated\n");
	display_effective_queue(term);

	return 0;
}

/*
 * List related Functions
 *
 */
int init_queue(ProcessQueue **queue, size_t max_len)
{
	*queue = malloc(sizeof(ProcessQueue));

	(*queue)->front = NULL;
	(*queue)->rear = NULL;
	(*queue)->length = 0;

	(*queue)->max_length = max_len;

	return 0;
}

int init_block(ProcessControlBlock **block, size_t pid, char *pname, size_t clocks)
{
	*block = malloc(sizeof(ProcessControlBlock));

	(*block)->p_id = pid;
	(*block)->p_name = strdup(pname);
	(*block)->clocks = clocks;
	(*block)->effective_clocks = clocks;

	(*block)->time = get_time();

	return 0;
}

ProcessControlBlock * get_block(size_t pid, char *pname, size_t clocks)
{
	ProcessControlBlock *block = malloc(sizeof(ProcessControlBlock));

	block->p_id = pid;
	block->p_name = strdup(pname);
	block->clocks = clocks;
	block->effective_clocks = clocks;

	block->time = get_time();

	return block;
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

int search(ProcessQueue *queue, size_t pid, ProcessControlBlock **block)
{
	*block = NULL;

	ProcessControlBlock *scan = queue->front;

	while (scan != NULL)
	{
		if (scan->p_id == pid)
			*block = scan;

		scan = scan->prev;
	}

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

		// PID, Name, Clocks, Time
		printf("\n PID \t Clocks \t Time \t\t\t\t P-Name \n");
		return 0;

	}

	ProcessControlBlock *scan = queue->front;

	printf("\n\n PID \t Clocks \t Time \t\t\t\t P-Name \n");

	while (scan != NULL)
	{
		// PID, Clocks, Time, Command
		printf("\n %u \t %6u \t %s \t %s", scan->p_id, scan->clocks, scan->time, scan->p_name);

		scan = scan->prev;
	}

	printf("\n");

	return 0;
}

int display_effective_queue(ProcessQueue *queue)
{
	if (queue == NULL)
		return 1;

	if (is_empty(queue)) {

		// PID, Effective Clocks, Clocks, Time, Command
		printf("\n PID \t TClocks \t Clocks \t Time \t\t\t\t P-Name \n");
		return 0;

	}

	ProcessControlBlock *scan = queue->front;

	printf("\n\n PID \t TClocks \t Clocks \t Time \t\t\t\t P-Name \n");

	while (scan != NULL)
	{
		// PID, Effective Clocks, Clocks, Time, Command
		printf("\n %u \t %u \t %6u \t %s \t %s", scan->p_id, scan->effective_clocks, scan->clocks, scan->time, scan->p_name);

		scan = scan->prev;
	}

	printf("\n");

	return 0;
}

int display_block(ProcessControlBlock *block)
{
	if (block == NULL)
		return 1;
	printf("\n PID \t Clocks \t Time \t\t\t\t P-Name \n");
	printf("\n %u \t %6u \t %s \t %s", block->p_id, block->clocks, block->time, block->p_name);

	return 0;
}

/*
 * User input related functions
 *
 */
size_t get_pid()
{
	size_t pid;

	printf("\nEnter PID: ");

	fflush(stdin);
	scanf("%u", &pid);

	return pid;
}

size_t get_clocks()
{
	size_t clocks;

	printf("\nProcess total clocks: ");

	fflush(stdin);
	scanf("%u", &clocks);

	return clocks;
}

char * get_name(void)
{
	char name[NAME_SIZE], newline;

	printf("\nProcess name: ");

	fflush(stdin);
	scanf("%c", &newline);
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
	Computer *computer;

	init_computer(&computer, 1, 100);

	ProcessQueue *queue = computer->proc_queue;

	enqueue(queue, get_block( 1, "/sbin/init", 11));
	enqueue(queue, get_block( 2, "[kthreadd]", 10));
	enqueue(queue, get_block( 3, "[ksoftirqd/0]", 9));
	enqueue(queue, get_block( 4, "[kworker/0:0H]", 8));
	enqueue(queue, get_block( 5, "[kdevtmpfs]", 6));
	enqueue(queue, get_block( 6, "[netns]", 7));
	enqueue(queue, get_block( 7, "[perf]", 5));
	enqueue(queue, get_block( 8, "[charger_manager]", 10));
	enqueue(queue, get_block( 9, "/lib/systemd/sy", 10));
	enqueue(queue, get_block(10, "[bioset]", 6));
	enqueue(queue, get_block(11, "/usr/sbin/openv", 5));
	enqueue(queue, get_block(12, "python -c from", 6));
	enqueue(queue, get_block(13, "openvpn-openssl", 9));
	enqueue(queue, get_block(14, "/usr/sbin/mysql", 5));
	enqueue(queue, get_block(15, "sshd: leoven@pt", 4));
	enqueue(queue, get_block(16, "python -c from", 4));;
	enqueue(queue, get_block(17, "/usr/sbin/winbi", 3));
	enqueue(queue, get_block(18, "/usr/sbin/winbi", 3));
	enqueue(queue, get_block(19, "[bioset]", 3));
	enqueue(queue, get_block(20, "[kblockd]", 4));
	enqueue(queue, get_block(21, "[kswapd0]", 4));
	enqueue(queue, get_block(22, "zeeeeeeeeeem", 7));
	enqueue(queue, get_block(23, "[ecryptfs-kthre]", 6));
	enqueue(queue, get_block(24, "[scsi_eh_0]", 3));
	enqueue(queue, get_block(25, "[edac-poller]", 2));
	enqueue(queue, get_block(26, "/usr/sbin/atd -", 4));
	enqueue(queue, get_block(27, "-bash", 6));
	enqueue(queue, get_block(28, "ps aux", 2));

	process_all(&computer, 150);

	return 0;
}