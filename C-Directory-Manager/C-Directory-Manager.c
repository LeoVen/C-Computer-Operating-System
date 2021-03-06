/**
 * @file C-Directory-Manager.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 08/05/2018
 *
 * @brief Entry point for project
 *
 */

#include "include\Directory.h"

int main()
{
	printf("Enter 'help' to see command list\n");
	Directory *root = getDirectoryByName("/");

	while (getUserInput(&root)) {}

	free(root);
	printf("\n");
	return 0;
}
