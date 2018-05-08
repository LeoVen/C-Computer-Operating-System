/**
 * @file Directory.h
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 08/05/2018
 *
 * @brief Header file for Directory Structure implementations
 *
 */

#pragma once

#ifdef __cplusplus
extern "C" {
#endif


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>

#define MAX_NAME_SIZE 30

// Change if on linux / windows
// #define CLEAR_SCREEN "clear"
#define CLEAR_SCREEN "cls"


	typedef struct Directory {
		char *name;
		char *time;
		struct Directory *parent;
		struct Directory *list;
		struct Directory *next;
	} Directory;

	Directory * getDirectoryByName(char *name);

	void changeDirName(Directory *dir, char *name);

	int makeDirectory(Directory **current, char *name);

	int removeDirectory(Directory **curr, char *param);

	int forceRemoveDirectory(Directory **curr, char *param);
	
	int listDirectory(Directory *current);

	int listCompleteDirectory(Directory *curr);

	bool dirExists(Directory *curr, char *param);

	int changeDirectory(Directory **curr, char *param);

	int printWorkingDirectory(Directory *curr);

	int printfBeforePrompt(Directory *curr);

#ifdef __cplusplus
}
#endif