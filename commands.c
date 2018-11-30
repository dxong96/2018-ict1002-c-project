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

WORKSHEET *worksheet;
 
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
	else if (compare_token(command, "exit") == 0) {
		ws_free(worksheet);
		done = 1;
	} else
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
	if (!is_cell_valid(arg1, output) || !is_cell_valid(arg2, output)) {
		return;
	}

    char col = arg1[0];
    char col2 = arg2[0];
    
    int row_num = atoi(arg1+1) - 1;
    int row_num2 = atoi(arg2+1) - 1;

    int col_num = col - 65;
    int col_num2 = col2 - 65;

    int row_diff = abs(row_num - row_num2);
    int col_diff = abs(col_num - col_num2);

    int row_start;
    int col_start;

    if (row_num > row_num2) {
		row_start = row_num2;
	} else {
		row_start = row_num;
	}

	if (col_num > col_num2) {
		col_start = col_num2;
	} else {
		col_start = col_num;
	}

    float sum = 0;
    int number_count = 0;
    int row_end = row_start + row_diff;
    int col_end = col_start + col_diff;

    for(int x = row_start; x <= row_end; x++) {
    	for (int y = col_start; y <= col_end; ++y) {
	    	float f = ws_cell_as_float(worksheet, y, x);
	        if (!isnan(f)) {
	            sum = sum + f;
	            number_count += 1;
	        }
    	}
    }

    float average = sum/number_count;
    if (isnan(average)) {
    	average = .0;
    }

    snprintf(output, MAX_OUTPUT, "The average of cells between %s and %s is %.*f", 
    	arg1, arg2, viewport_get_cellprec(), average);
}


/*
 * CURSOR command.
 *
 * Input:
 *   arg1 - the identifier of the cell to which to move the cursor
 */
void do_cursor(const char *arg1, char *output) {
	if (!is_cell_valid(arg1, output)) {
		return;
	}

	char col = arg1[0] - 65;
	int row = atoi(arg1+1) - 1;
	
	viewport_set_cursor(col, row);
	snprintf(output, MAX_OUTPUT, "Cursor set to %s.", arg1);
}


/*
 * LOAD command.
 *
 * Input:
 *   arg1 - the filename
 */
void do_load(const char *arg1, char *output) {
	FILE *fp = fopen(arg1, "r");
	if (fp == NULL) {
		snprintf(output, MAX_OUTPUT, "Failed to load csv file, %s", arg1);
	} else {
		ws_read_csv(worksheet, fp);
		fclose(fp);
		snprintf(output, MAX_OUTPUT, "Loaded csv file, %s", arg1);
	}
}


/*
 * NEW command.
 *
 * Input:
 *   arg1 - the number of columns
 *   arg2 - the number of rows
 */
void do_new(const char *arg1, const char *arg2, char *output) {
	int cols = atoi(arg1);
	int rows = atoi(arg2);

	if (cols > MAX_COLUMNS) {
		snprintf(output, MAX_OUTPUT, "You are allowed only up to 26 columns");
	} else if (cols <= 0 || rows <= 0) {
		snprintf(output, MAX_OUTPUT, "Please enter valid row and column size");
	} else {
		if (worksheet != NULL) {
			ws_free(worksheet);
		}

		worksheet = ws_new(cols, rows);
		if (worksheet == NULL) {
			snprintf(output, MAX_OUTPUT, "Failed to create worksheet");
		} else {
			viewport_set_worksheet(worksheet);
			snprintf(output, MAX_OUTPUT, "Successfully created worksheet with %d cols and %d rows.", cols, rows);
		}
	}
}


/*
 * PREC command.
 *
 * Input:
 *   arg1 - the number of decimal places to show
 */
void do_prec(const char *arg1, char *output) {
	if (arg1 == NULL) {
		snprintf(output, MAX_OUTPUT, "Current precision is %d", viewport_get_cellprec());
		return;
	}
    int prec = atoi(arg1);
    if (prec < 0) {
    	snprintf(output, MAX_OUTPUT, "Enter a positive precision.");	
    } else {
    	viewport_set_cellprec(prec);

		snprintf(output, MAX_OUTPUT, "Precision set to %d.", prec);	
    }
}


/*
 * SAVE command.
 *
 * Input:
 *  arg1 - the filename
 */
void do_save(const char *arg1, char *output) {
	if (arg1 == NULL) {
		snprintf(output, MAX_OUTPUT, "Please enter a file name to save");
		return;
	}

	FILE *fp = fopen(arg1, "w");
	int rows_written = ws_write_csv(worksheet, fp);
	if (rows_written == 0) {
		snprintf(output, MAX_OUTPUT, "Error saving worksheet");
	} else {
		snprintf(output, MAX_OUTPUT, "%d rows saved at %s", rows_written, arg1);
	}
	fclose(fp);
}


/*
 * SET command.
 *
 * Input:
 *   arg1 - the cell identifier
 *   arg2 - the value for the cell (NULL to make the cell blank)
 */
void do_set(const char *arg1, const char *arg2, char *output) {
	if (!is_cell_valid(arg1, output)) {
		return;
	}
	char col = arg1[0];

	// minus 65 as 'A' = 65
	int col_num = col - 65;
	// Convert the chars after first character to int
	int row_num = atoi(arg1+1) - 1;

	if (arg2 == NULL) {
		ws_set(worksheet, col_num, row_num, "\0");
		snprintf(output, MAX_OUTPUT, "Cell %s has been erased", arg1);
	} else {
		if (ws_guess_data_type(arg2) == WS_DATA_TYPE_ILLEGAL) {
			snprintf(output, MAX_OUTPUT, "Invalid cell value");
		} else {
			ws_set(worksheet, col_num, row_num, arg2);
			snprintf(output, MAX_OUTPUT, "Cell %s set to %s", arg1, arg2);
		}
	}
}


/*
 * SUM command.
 *
 * Input:
 *   arg1 - one corner of the rectangle to be summed
 *   arg2 - the opposite corner of the rectangle to be summed
 */
void do_sum(const char *arg1, const char *arg2, char *output) {
	if (!is_cell_valid(arg1, output) || !is_cell_valid(arg2, output)) {
		return;
	}

    char col = arg1[0];
    char col2 = arg2[0];
    
    int row_num = atoi(arg1+1) - 1;
    int row_num2 = atoi(arg2+1) - 1;

    int col_num = col - 65;
    int col_num2 = col2 - 65;

    int row_diff = abs(row_num - row_num2);
    int col_diff = abs(col_num - col_num2);

    int row_start;
    int col_start;

    if (row_num > row_num2) {
		row_start = row_num2;
	} else {
		row_start = row_num;
	}

	if (col_num > col_num2) {
		col_start = col_num2;
	} else {
		col_start = col_num;
	}

    float sum = 0;
    int row_end = row_start + row_diff;
    int col_end = col_start + col_diff;

    for(int x = row_start; x <= row_end; x++) {
    	for (int y = col_start; y <= col_end; ++y) {
	    	float f = ws_cell_as_float(worksheet, y, x);
	        if (!isnan(f)) {
	            sum = sum + f;
	        }
    	}
    }

    snprintf(output, MAX_OUTPUT, "The sum of cells between %s and %s is %.*f", 
    	arg1, arg2, viewport_get_cellprec(), sum);
}

/*
 * WIDTH command.
 *
 * Input:
 *   arg1 - the number of characters for each column
 */
void do_width(const char *arg1, char *output) {
    int width = atoi(arg1);
    if (width <= 0) {
    	snprintf(output, MAX_OUTPUT, "Enter a width greater than 0.");	
    } else {
    	viewport_set_cellwidth(width);

		snprintf(output, MAX_OUTPUT, "Width changed to %d.", width);
    }
}

int is_cell_valid(const char *arg, char *output) {
	if (arg == NULL) {
		snprintf(output, MAX_OUTPUT, "Invalid cell");
		return 0;
	}

	char col = arg[0];

	if (col < 'A' || col > 'Z') {
		snprintf(output, MAX_OUTPUT, "Enter a column from A to Z only.");
		return 0;
	}

	int cell_input_length = strlen(arg);

	if (cell_input_length == 1) {
		snprintf(output, MAX_OUTPUT, "Missing row number");
		return 0;
	}

	for (int i = 1 ; i < cell_input_length; i++) {
		if (!isdigit(arg[i])) {
			snprintf(output, MAX_OUTPUT, "Invalid row number");
			return 0;
		}
	}

	return 1;
}