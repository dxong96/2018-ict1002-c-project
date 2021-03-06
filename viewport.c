/*
 * ICT1002 Assignment 2, 2018-19 Trimester 1.
 *
 * This file implements all of the functions required for drawing a worksheet
 * in the screen.
 *
 * The viewport_display() function is invoked by the main loop when it wants
 * to display the worksheet on the screen. The other functions are invoked by
 * commands such as CURSOR, PREC, etc, that modify the way in which the
 * worksheet is displayed. The display does NOT need to be updated immediately
 * after these functions have been invoked; the new settings will come into
 * effect the next time viewport_display() is invoked.
 */

#include <stdio.h>
#include <stdlib.h>
#include "sheet1002.h"

WORKSHEET *worksheet;
int cell_width = 5;
int cell_prec = 0;
int cursor_row = 0;
int cursor_col = 0;

/*
 * Print the current viewing window to the screen.
 *
 * Input:
 *   term_cols - the width of the space in which to display the window, in characters
 *   term_rows - the height of the space in which to display the window, in characters
 */
void viewport_display(int term_cols, int term_rows) {
	if (worksheet == NULL) {
		return;
	}

	// minus 1 due to the row displaying the columns
	term_rows -= 1;

	// get the rounded down number of columns that can fit into the term columns
	int columns = term_cols / cell_width;
	int rows = term_rows;
	
	// minus one for the column of row labels
	columns -= 1;
	if (rows > worksheet->rows) {
		rows = worksheet->rows;
	}

	if (columns > worksheet->cols) {
		columns = worksheet->cols;
	}

	printf("%*c",  cell_width, ' ');
	for (int i = cursor_col; i < columns; ++i) {
		printf("%*c", cell_width, 65 + i);
	}
	printf("\n");

	char *word = malloc(sizeof(char) * (cell_width + 1));
	for (int x = cursor_row; x < rows; ++x) {
		printf("%-*d", cell_width, x + 1);

		for (int y = cursor_col; y < columns; ++y) {
			printf(ws_cell_as_string(worksheet, y, x, cell_width, cell_prec, word));
		}
		printf("\n");
	}
	free(word);

	int rows_remaining = term_rows - rows;
	for (int i = 0; i < rows_remaining; ++i) {
		printf("\n");
	}
}


/*
 * Get the precisiion with which floating-point numbers will be displayed.
 *
 * Returns:
 *   the number of decimal places that will be shown
 */
int viewport_get_cellprec(void) {
	return cell_prec;
}


/*
 * Set the precision with which floating-point numbers will be displayed.
 *
 * Input:
 *   prec - the number of decimal places to show
 */
void viewport_set_cellprec(int prec) {
    cell_prec = prec;
}


/*
 * Set the width in which the cells will be displayed.
 *
 * Input:
 *   width - the number of characters in each cell to be displayed
 */
void viewport_set_cellwidth(int width) {
	cell_width = width;
}


/*
 * Set the position of the cursor.
 *
 * Input:
 *   col - the column number
 *   row - the row number
 */
void viewport_set_cursor(int col, int row) {
	cursor_col = col;
	cursor_row = row;
}


/*
 * Get a pointer to the worksheet currently being displayed.
 *
 * Returns:
 *   a pointer to the WORKSHEET structure currently displayed
 *   NULL, if there is no worksheet displayed
 */
 WORKSHEET *viewport_get_worksheet(void) {
     if (worksheet == NULL) {
         return NULL;
     }
     else{
         return worksheet;
     }

	 
 }


/*
 * Set the worksheet to be displayed.
 *
 * Input:
 *   ws - a pointer to the worksheet to be displayed
 */
void viewport_set_worksheet(WORKSHEET *ws) {
	worksheet = ws;
}
