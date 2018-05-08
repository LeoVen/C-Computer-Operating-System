/**
 * @file Core.c
 *
 * @author Leonardo Vencovsky (https://github.com/LeoVen)
 * @date 08/05/2018
 *
 * @brief Source file for Core module
 *
 * The Core includes an @c enum type for status codes and other utility
 * functions.
 *
 */

#include "Core.h"

/**
 * @brief Visualize status codes
 *
 * This function returns a string that represents the status error for
 * better visualization.
 *
 * @param[in] status The status returned by a function
 *
 * @return A string equivalent of the status name
 */
char * status_repr(Status status)
{
	switch (status)
	{
		case DS_OK: return "DS_OK";
		case DS_ERR_INVALID_POSITION: return "DS_ERR_INVALID_POSITION";
		case DS_ERR_INVALID_OPERATION: return "DS_ERR_INVALID_OPERATION";
		case DS_ERR_INVALID_SIZE: return "DS_ERR_INVALID_SIZE";
		case DS_ERR_NOT_FOUND: return "DS_ERR_NOT_FOUND";
		case DS_ERR_ALLOC: return "DS_ERR_ALLOC";
		case DS_ERR_UNEXPECTED_RESULT: return "DS_ERR_UNEXPECTED_RESULT";
		case DS_ERR_ITER: return "DS_ERR_ITER";
		case DS_ERR_NULL_POINTER: return "DS_ERR_NULL_POINTER";
		case DS_ERR_FULL: return "DS_ERR_FULL";
		case DS_ERR_INVALID_ARGUMENT: return "DS_ERR_INVALID_ARGUMENT";
		default: return "DS_UNKNOWN_ERROR";
	}
}

/**
 * @brief Visualize status codes in the console
 *
 * This function automatically prints a status code in your console. Can be
 * used for debugging.
 *
 * @param[in] status The status returned by a function
 */
void print_status_repr(Status status)
{
	printf("\n%s", status_repr(status));
}