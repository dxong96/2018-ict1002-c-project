/*
 * ICT1002 Assignment 2, 2018-19 Trimester 1.
 *
 * This file implements all of the functions required for representing and
 * manipulating a worksheet.
 */

#include <ctype.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "sheet1002.h"


/*
 * Get the contents of a cell as a floating-point number.
 *
 * Input:
 *   ws - a pointer to the worksheet
 *   col - the column of the desired cell
 *   row - the row of the desired cell
 *
 * Returns:
 *   a floating-point number with the value specified in the cell, if the cell contains a number
 *   NAN (defined in math.h), otherwise
 */
float ws_cell_as_float(WORKSHEET *ws, int col, int row) {
  char *value = ws->cells[row][col];
	if (ws_guess_data_type(value) == WS_DATA_TYPE_FLOAT) {
    return atof(value);
  } else {
	  return NAN;
  }
}


/*
 * Get the contents of a cell a string.
 *
 * Input:
 *   ws - a pointer to the worksheet
 *   col - the column of the desired cell
 *   row - the row of the desired cell
 *   width - the number of characters in the output string
 *   prec - the number of decimal places to use for numbers (ignored if the cell contains text)
 *   buf - a pointer to a buffer to receive the string; it should be at least width + 1 characters in size
 *
 * Returns:
 *   buf
 */
char *ws_cell_as_string(WORKSHEET *ws, int col, int row, int width, int prec, char *buf) {
		
	strcpy(buf, "");
	
	return buf;
	
}


/*
 * Guess the intended data type of a string, in the manner of Excel's "General"
 * cell format.
 *
 * The input string will be assumed to represent a floating-point number if
 * either atof() returns a non-zero value, or the string looks like 0 or 0.0.
 *
 * The input string will be assumed to represent text if atof() returns
 * zero, the string is not 0 or 0.0, and it contains only characters
 * for which isalnum() returns a true value.
 *
 * Otherwise, the input string is considered to be illegal.
 *
 * Input:
 *   value - the string to be tested
 *
 * Returns:
 *   WS_DATA_TYPE_FLOAT, if the value appears to be a floating-point number
 *   WS_DATA_TYPE_TEXT, if the value appears to be text
 *   WS_DATA_TYPE_ILLEGAL, otherwise
 */
int ws_guess_data_type(const char *value) {
  // atof gives a result more than 1
	if (atof(value)) {
    return WS_DATA_TYPE_FLOAT;
  } else {
    // atof gives 0
    int dots_zero_only = 1;
    int alpha_num_only = 1;
    int length = strlen(value);
    // check that the string is 0.0 or 0
    for (int i = 0; i < length; i++) {
      char c = value[0];
      if (c != '0' || c != '.') {
        dots_zero_only = 0;
      }
      if (!isalnum(c)) {
        alpha_num_only = 0;
      }
    }

    if (dots_zero_only) {
      return WS_DATA_TYPE_FLOAT;
    } else if (alpha_num_only) {
      return WS_DATA_TYPE_TEXT;
    } else {
      return WS_DATA_TYPE_ILLEGAL;
    }
  }
}
		


/*
 * De-allocate the memory used by a worksheet.
 *
 * Input:
 *   ws - a pointer to the worksheet to be de-allocated.
 */
void ws_free(WORKSHEET *ws) {
  for (int x = 0; x < ws->rows; ++x) {
    free(ws->cells[x]);
    for (int y = 0; y < ws->cols; ++y) {
      free(ws->cells[x][y]);
    }
  }
  free(ws);
}


/*
 * Create a new worksheet.
 *
 * Input:
 *   cols - the number of columns in the sheet
 *   rows - the number of rows in the sheet
 *
 * Returns:
 *   a pointer to the new WORKSHEET structure, if successful
 *   NULL, if there was a memory allocation failure
 */
WORKSHEET *ws_new(int cols, int rows) {
	WORKSHEET *ws = malloc (sizeof(WORKSHEET));

  if (ws == NULL) {
    return NULL;
  } else {
    ws->cols = cols;
    ws->rows = rows;

    char *** cells = malloc(rows * sizeof(char **));
    for (int x = 0; x < rows; ++x) {
      cells[x] = malloc(cols * sizeof(char *));
      
      if (cells[x] == NULL) {
        return NULL;
      }

      for (int y = 0; y < cols; ++y) {
        cells[x][y] = malloc(MAX_WORD * sizeof(char));
        // set the string null char at the first char to prevent showing strange characters
        cells[x][y][0] = '\0';

        if (cells[x][y] == NULL) {
          return NULL;
        }
      }
    }
    ws->cells = cells;


    return ws;
  }
	 
}
 
 
 /*
  * Read data from a CSV file.
  *
  * If the data in the file has more columns or rows than the worksheet
  * supplied, the excess rows or columns will be ignored. If the data in the
  * file has fewer columns or rows than the worksheet, the extra rows and
  * columns will be made blank.
  *
  * If a cell in the file contains data that cannot be represented in a
  * worksheet according to the assignment specification, the cell will be
  * left blank.
  *
  * Input:
  *  ws - a pointer to the worksheet to receive the data
  *  f - a pointer to a FILE structure open for reading in text mode
  *
  * Returns:
  *   the number of rows successfully read and inserted into the worksheet (may be less than the number of rows in the file)
  */
int ws_read_csv(WORKSHEET *ws, FILE *f) {
	
	return 0;
}
 
 
 /*
  * Set the value of a cell.
  *
  * Input:
  *   ws - a pointer to the worksheet
  *   col - the column number of the cell
  *   row - the row number of the cell
  *   value - the new value of the cell (NULL to erase)
  */
void ws_set(WORKSHEET *ws, int col, int row, const char *value) {
	strncpy(ws->cells[row][col], value, MAX_WORD);
}


/*
 * Write a worksheet to a CSV file.
 *
 * Input:
 *   ws - a pointer to the worksheet
 *   f - a pointer to a FILE open for writing in text mode
 *
 * Returns:
 *   the number of rows successfully written
 */
int ws_write_csv(WORKSHEET *ws, FILE *f) {
	
	return 0;
}