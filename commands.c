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
	
    int col_num = arg1[0];
    int col_num2 = arg2[0];
    //    int temp_num = arg2[0] -65;
    int row_num = atoi(arg1+1);
    int row_num2 = atoi(arg2+1);
    int temp_row = atoi(arg1+1);
    int diff = col_num - col_num2;
    if(diff < 0){
        diff = diff * -1;
    }
    int col_int = col_num -65;
    int col_int2 = col_num2 -65;
    int temp_int = col_int;
    float sum = 0;
    int counter = 0;
    float avg_num = 0;
    char ***cells = worksheet->cells;
    //    printf("%c\n",col_num);
    //    printf("%d\n",col_num-65);
    //    printf("%d\n",col_num2-65);
    //    printf("row num %d\n",row_num);
    //    printf("row num2 %d\n",row_num2);
    //    printf("%d\n",diff);
    if(col_int2 < col_int){
        //        printf("works");
        col_int  = col_int2;
        col_int2 = temp_int;
        //        printf("%d\n",col_int);
        //        printf("%d\n",col_int2);
    }
    if(row_num2 < row_num){
        row_num  = row_num2;
        row_num2 = temp_row;
        //        printf("%d\n",row_num);
        //        printf("%d\n",row_num2);
    }
    for(int i = col_int ; i <= col_int2 ; i++){
        //        printf("col_works\n");
        int c = i;
        for(int k = row_num-1 ; k < row_num2  ; k++){
            printf("row_works, %d%d\n", k,c);
            int f = atof(cells[k][c]);
            sum = sum + f;
            if(f > 0){
            counter += 1;
            }
            
        }
    }avg_num = sum / counter;
    snprintf(output, MAX_OUTPUT,"The avg is %f", avg_num);
	
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
	int cols = atoi(arg1);
	int rows = atoi(arg2);

	if (cols > MAX_COLUMNS) {
		snprintf(output, MAX_OUTPUT, "You are allowed only up to 26 columns");
	} else {
		if (worksheet != NULL) {
			ws_free(worksheet);
		}

		worksheet = ws_new(cols, rows);
		viewport_set_worksheet(worksheet);
		snprintf(output, MAX_OUTPUT, "Successfully created worksheet with %d cols and %d rows.", cols, rows);
	}
}


/*
 * PREC command.
 *
 * Input:
 *   arg1 - the number of decimal places to show
 */
void do_prec(const char *arg1, char *output) {
    int decimalpoint = atoi(arg1);
    viewport_set_cellprec(decimalpoint);
  
//    printf("%*.*f",5,2,number);
//    ws_cell_as_string(worksheet, decimalpoint);
    
//    ws_set(worksheet, col_num, row_num, arg2);
	snprintf(output, MAX_OUTPUT, "Precision set to %d.", decimalpoint);
//    snprintf(output, MAX_OUTPUT, "Not implemented.");
	
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
	char col = arg1[0];

	if (col < 'A' || col > 'Z') {
		snprintf(output, MAX_OUTPUT, "Enter a column from A to Z only.");
		return;
	}

	int cell_input_length = strlen(arg1);

	if (cell_input_length == 1) {
		snprintf(output, MAX_OUTPUT, "Missing row number");
		return;
	}

	for (int i = 1 ; i < cell_input_length; i++) {
		if (!isdigit(arg1[i])) {
			snprintf(output, MAX_OUTPUT, "Invalid row number");
			return;
		}
	}

	// minus 65 as 'A' = 65
	int col_num = col - 65;
	// Convert the chars after first character to int
	int row_num = atoi(arg1+1) - 1;

	// snprintf(output, MAX_OUTPUT, "Setting row %d and col %d", row_num, col_num);

	ws_set(worksheet, col_num, row_num, arg2);
}


/*
 * SUM command.
 *
 * Input:
 *   arg1 - one corner of the rectangle to be summed
 *   arg2 - the opposite corner of the rectangle to be summed
 */
void do_sum(const char *arg1, const char *arg2, char *output) {
//    int col_num = arg1[0];
//    int col_num2 = arg2[0];
//    int col_diff = col_num - col_num2;
//    int col1 = col_num;
//    int col2 = col_num2;
//    int rows1 = 0;
//    int rows2 = atoi(arg2+1)-1;
//    int row_diff = rows1 - rows2;
//    int minRow = rows1;
//    int minCol = col1;
//    // Convert the chars after first character to int
////    int row_num = atoi(arg1+1) - 1;
//
//    float sum = 0;
//
////    snprintf(output, MAX_OUTPUT, "%c,%d", arg1, arg2);
//    if(col_diff < 0 ){
//        col_diff = col_diff *-1;
//        col_num = arg2[0];
//    }
//
//    if(col2 < minCol){
//        minCol = col2;
//    }
//    for(int i = 0; i <= col_diff ; i++){
//        int c = minCol + i - 65;
//        int f = atof(cells[rows1][c]);
//        sum += f;
//    const char *arg1 = "B1";
//    const char *arg2 = "D3";
    
    int col_num = arg1[0];
    int col_num2 = arg2[0];
//    int temp_num = arg2[0] -65;
    int row_num = atoi(arg1+1);
    int row_num2 = atoi(arg2+1);
    int temp_row = atoi(arg1+1);
    int diff = col_num - col_num2;
    if(diff < 0){
        diff = diff * -1;
    }
    int col_int = col_num -65;
    int col_int2 = col_num2 -65;
    int temp_int = col_int;
    float sum = 0;
    char ***cells = worksheet->cells;
    //    printf("%c\n",col_num);
    //    printf("%d\n",col_num-65);
    //    printf("%d\n",col_num2-65);
    //    printf("row num %d\n",row_num);
    //    printf("row num2 %d\n",row_num2);
    //    printf("%d\n",diff);
    if(col_int2 < col_int){
        //        printf("works");
        col_int  = col_int2;
        col_int2 = temp_int;
//        printf("%d\n",col_int);
//        printf("%d\n",col_int2);
    }
    if(row_num2 < row_num){
        row_num  = row_num2;
        row_num2 = temp_row;
//        printf("%d\n",row_num);
//        printf("%d\n",row_num2);
    }
    for(int i = col_int ; i <= col_int2 ; i++){
//        printf("col_works\n");
        int c = i;
        for(int k = row_num-1 ; k < row_num2  ; k++){
            printf("row_works, %d%d\n", k,c);
            int f = atof(cells[k][c]);
            sum = sum + f;
            
        }
    }
        snprintf(output, MAX_OUTPUT,"The sum is %f", sum);
    
//     snprintf(output, MAX_OUTPUT, "%c,%d", i, k);
	
	

}

/*
 * WIDTH command.
 *
 * Input:
 *   arg1 - the number of characters for each column
 */
void do_width(const char *arg1, char *output) {
//    int width = arg1;
    
	
	snprintf(output, MAX_OUTPUT, "Not implemented.");
	
}
