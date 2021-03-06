/**
 * @file StringHandler.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 08/05/2018
 *
 * @brief Source File for Input Handling functions
 *
 */

#include "..\include\StringHandler.h"

int hashCode(char *command)
{
	int i, hash = 0;
	for (i = 0; i < strlen(command); i++) {
		// Avoiding \0 and \n
		if (command[i] != '\0' && command[i] != '\n')
			hash += command[i] * i;
	}
	return hash;
}

void println(const char *str)
{
	printf("\n%s", str);
}

int normalizeString(char *param)
{
	int i;
	for (i = 0; i < strlen(param); i++)
		if (param[i] == '\n')
			param[i] = '\0';
}

// +-------------------------------------------------------------------------------------------------+
// |                                              Menu                                               |
// +-------------------------------------------------------------------------------------------------+

void printHelpMenu()
{
	println("  Command List                                                     ");
	println("                                                                   ");
	println("  help                Shows this help menu                         ");
	println("  exit                Exits program                                ");
	println("  cls                 Clears screen                                 ");
	println("  ls                  Lists directory content                      ");
	println("  ls -l               Lists directory content with more datail     ");
	println("  mkdir [dir_name]    Makes a directory of name dir_name           ");
	println("  rmdir [dir_name]    Removes directory of name dir_name           ");
	println("  rm [dir_name]       Removes directory either empty or not        ");
	println("  pwd                 Print working directory                      ");
	println("  cd                  Change to root directory                     ");
	println("  cd ..               Change directory to parent directory         ");
	println("  cd [dir_name]       Change to directory of name dir_name         ");
	println("  credits             Prints Credits                               ");
	println("                                                                   ");
}

void print_credits()
{
	println(" +-------------------------------------------------------------------+");
	println(" |                                                                   |");
	println(" |                         Directory Manager                         |");
	println(" |                                                                   |");
	println(" |  Created By:                                                      |");
	println(" |                                                                   |");
	println(" |  Guilherme Pinazza                                                |");
	println(" |  Leonardo Vencovsky                                               |");
	println(" |  Vitor Facioli                                                    |");
	println(" |                                                                   |");
	println(" +-------------------------------------------------------------------+");
	println(" ");
}

// +-------------------------------------------------------------------------------------------------+
// |                                           User Input                                            |
// +-------------------------------------------------------------------------------------------------+

bool getUserInput(Directory **current)
{
	printfBeforePrompt((*current));
	printf(" $ ");
	char *userInput = (char *)malloc(sizeof(char) * MAX_NAME_SIZE);
	fgets(userInput, MAX_NAME_SIZE, stdin);
	int sp = checkUserInput(userInput);
	char *next, *command, *param;
	if (sp == 0) {
		// Only one command
		command = strtok_s(userInput, "\0", &next);
		param = NULL;
		return switchCommand(current, command, param);
	}
	else if (sp == 1) {
		command = strtok_s(userInput, " ", &next);
		param = strtok_s(NULL, "\0", &next);
		if (strlen(param) > 20) {
			printf("Parameter size must not be greater than 20\n");
			return true;
		}
		return switchCommand(current, command, param);
	}
	else {
		printf("More than two arguments is not supported\n");
	}
}

bool switchCommand(Directory **current, char *command, char *parameter)
{
	int hash = hashCode(command);
	if (hash == hashCode("mkdir")) {
		if (parameter != NULL && dirNameTest(parameter)) {
			normalizeString(parameter);
			if (!dirExists((*current), parameter)) {
				if (strlen(parameter) < 3) {
					printf("Directory name must not be smaller than 3\n");
					return true;
				}
				normalizeString(parameter);
				makeDirectory(current, parameter);
			}
			else
				printf("Directory with specified name already exists\n");
		}
		else
			printf("Directory name must not be empty\n");
	}
	else if (hash == hashCode("pwd")) {
		printf("\t");
		printWorkingDirectory((*current));
		printf("\n");
	}
	else if (hash == hashCode("rmdir")) {
		if (removeDirectory(current, parameter) == 1) {
			printf("Not possible to remove a non-empty directory\n");
		}
	}
	else if (hash == hashCode("rm")) {
		forceRemoveDirectory(current, parameter);
	}
	else if (hash == hashCode("ls")) {
		if (parameter == NULL) {
			listDirectory((*current));
			printf("\n");
		}
		else if (hashCode(parameter) == hashCode("-l")) {
			listCompleteDirectory((*current));
		}
		else {
			printf("Invalid ls parameter");
			printf("\n");
		}
	}
	else if (hash == hashCode(CLEAR_SCREEN)) {
		system(CLEAR_SCREEN);
	}
	else if (hash == hashCode("help")) {
		printHelpMenu();
		printf("\n");
	}
	else if (hash == hashCode("exit")) {
		printf("Goodbye!");
		return false;
	}
	else if (hash == hashCode("cd")) {
		if (parameter == NULL) {
			changeToRoot(current);
		}
		else if (hashCode(parameter) == hashCode(".."))
			changeToParent(current);
		else
			changeDirectory(current, parameter);	
	}
	else if (hash == hashCode("credits")) {
		print_credits();
	}
	else {
		printf("No such command. Enter 'help' to see command list\n");
	}
	return true;
}

// +-------------------------------------------------------------------------------------------------+
// |                                               Checks                                            |
// +-------------------------------------------------------------------------------------------------+

int checkUserInput(char *userInput)
{
	int i, sp = 0;
	for (i = 0; i < strlen(userInput); i++) {
		// Space
		if (userInput[i] == 32)
			sp++;
	}
	return sp;
}

bool dirNameTest(char *cmd)
{
	// Dir name must not contain spaces
	int i;
	for (i = 0; i < strlen(cmd); i++) {
		if (cmd[i] == ' ')
			return false;
	}
	return true;
}