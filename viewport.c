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
#include "sheet1002.h"
 
/*
 * Print the current viewing window to the screen.
 *
 * Input:
 *   term_cols - the width of the space in which to display the window, in characters
 *   term_rows - the height of the space in which to display the window, in characters
 */
void viewport_display(int term_cols, int term_rows) {

}


/*
 * Get the precisiion with which floating-point numbers will be displayed.
 *
 * Returns:
 *   the number of decimal places that will be shown
 */
int viewport_get_cellprec(void) {
	
	return 0;
	
}


/*
 * Set the precision with which floating-point numbers will be displayed.
 *
 * Input:
 *   prec - the number of decimal places to show
 */
void viewport_set_cellprec(int prec) {
	
}


/*
 * Set the width in which the cells will be displayed.
 *
 * Input:
 *   width - the number of characters in each cell to be displayed
 */
void viewport_set_cellwidth(int width) {
	
}


/*
 * Set the position of the cursor.
 *
 * Input:
 *   col - the column number
 *   row - the row number
 */
void viewport_set_cursor(int col, int row) {
	
}


/*
 * Get a pointer to the worksheet currently being displayed.
 *
 * Returns:
 *   a pointer to the WORKSHEET structure currently displayed
 *   NULL, if there is no worksheet displayed
 */
 WORKSHEET *viewport_get_worksheet(void) {
	 
	 return NULL;
	 
 }


/*
 * Set the worksheet to be displayed.
 *
 * Input:
 *   ws - a pointer to the worksheet to be displayed
 */
void viewport_set_worksheet(WORKSHEET *ws) {
	
}