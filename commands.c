/*
 * ICT1002 Assignment 2, 2018-19 Trimester 1.
 *
 * This file contains one function corresponding to each command understood
 * by the spreadsheet. Each function accepts zero, one or two input arguments
 * (arg1 and/or arg2) as documented in the assignment specification, and a
 * pointer to buffer (output) into which the results of the command should be
 * placed. The contents of the output buffer will be displayed on the screen
 * at the end of the command loop (make it empty if you don't want to print
 * anything).
 *
 * The contents of arg1 and arg2 are guaranteed to be no more than MAX_INPUT
 * characters in length. The contents of the output buffer should not exceed
 * MAX_OUTPUT characters (including the terminating null).
 */

#include <ctype.h>
#include <errno.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "sheet1002.h"
 
/*
 * Execute a command.
 *
 * Input:
 *   command - the name of the command
 *   arg1 - the first argument (may be NULL)
 *   arg2 - the second argument (may be NULL)
 *   output - a buffer into which the output of the command is to be placed (must be at least MAX_OUTPUT characters long)
 *
 * Returns:
 *   0, if the program should continue
 *   1, if the command indicates that the interpreter should exit
 */
int do_command(const char *command, const char *arg1, const char *arg2, char *output) {

	int done = 0;	/* return value */

	if (command == NULL || strlen(command) == 0) {
		/* blank line; do nothing and return */
		return 0;
	}
	
	/* determine which command was given and execute the appropriate function */
	if (compare_token(command, "avg") == 0)
		do_avg(arg1, arg2, output);
	else if (compare_token(command, "cursor") == 0)
		do_cursor(arg1, output);
	else if (compare_token(command, "load") == 0)
		do_load(arg1, output);
	else if (compare_token(command, "new") == 0)
		do_new(arg1, arg2, output);
	else if (compare_token(command, "prec") == 0)
		do_prec(arg1, output);
	else if (compare_token(command, "save") == 0)
		do_save(arg1, output);
	else if (compare_token(command, "set") == 0)
		do_set(arg1, arg2, output);
	else if (compare_token(command, "sum") == 0)
		do_sum(arg1, arg2, output);
	else if (compare_token(command, "width") == 0)
		do_width(arg1, output);
	else if (compare_token(command, "exit") == 0)
		done = 1;
	else
		snprintf(output, MAX_OUTPUT, "Unrecognised command: %s.", command);
	
	return done;
	
}


/*
 * AVG command.
 *
 * Input:
 *   arg1 - one corner of the rectangle to be averaged
 *   arg2 - the opposite corner of the rectangle to be averaged
 */
void do_avg(const char *arg1, const char *arg2, char *output) {
	
	snprintf(output, MAX_OUTPUT, "Not implemented.");
	
}


/*
 * CURSOR command.
 *
 * Input:
 *   arg1 - the identifier of the cell to which to move the cursor
 */
void do_cursor(const char *arg1, char *output) {
	
	snprintf(output, MAX_OUTPUT, "Not implemented.");
	
}


/*
 * LOAD command.
 *
 * Input:
 *   arg1 - the filename
 */
void do_load(const char *arg1, char *output) {
	
	snprintf(output, MAX_OUTPUT, "Not implemented.");

}


/*
 * NEW command.
 *
 * Input:
 *   arg1 - the number of columns
 *   arg2 - the number of rows
 */
void do_new(const char *arg1, const char *arg2, char *output) {
	
	snprintf(output, MAX_OUTPUT, "Not implemented.");
	
}


/*
 * PREC command.
 *
 * Input:
 *   arg1 - the number of decimal places to show
 */
void do_prec(const char *arg1, char *output) {
	
	snprintf(output, MAX_OUTPUT, "Not implemented.");
	
}


/*
 * SAVE command.
 *
 * Input:
 *  arg1 - the filename
 */
void do_save(const char *arg1, char *output) {
	
	snprintf(output, MAX_OUTPUT, "Not implemented.");
	
}


/*
 * SET command.
 *
 * Input:
 *   arg1 - the cell identifier
 *   arg2 - the value for the cell (NULL to make the cell blank)
 */
void do_set(const char *arg1, const char *arg2, char *output) {
	
	snprintf(output, MAX_OUTPUT, "Not implemented.");
	
}


/*
 * SUM command.
 *
 * Input:
 *   arg1 - one corner of the rectangle to be summed
 *   arg2 - the opposite corner of the rectangle to be summed
 */
void do_sum(const char *arg1, const char *arg2, char *output) {
	
	snprintf(output, MAX_OUTPUT, "Not implemented.");
	
}


/*
 * WIDTH command.
 *
 * Input:
 *   arg1 - the number of characters for each column
 */
void do_width(const char *arg1, char *output) {
	
	snprintf(output, MAX_OUTPUT, "Not implemented.");
	
}
