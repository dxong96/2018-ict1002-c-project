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
  int type = ws_guess_data_type(value);
  if (type == WS_DATA_TYPE_FLOAT) {
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
  char *value = ws->cells[row][col];
  int type = ws_guess_data_type(value);
  // plus one due to the null character
  // printf includes the null character to the width
  // so we add 1 to ensure that the width is correct
  int actual_width = width + 1;
  int exceeds_width = 0;
  
  if (type == WS_DATA_TYPE_TEXT) {
    exceeds_width = strlen(value) > width;
    snprintf(buf, actual_width, "%*s", width, value);
  } else if (type == WS_DATA_TYPE_FLOAT) {
    exceeds_width = strlen(value) + prec > width;
    snprintf(buf, actual_width, "%*.*f", width, prec, atof(value));
  }

  if (exceeds_width) {
    for (int i = 0; i < actual_width; i++) {
      buf[i] = '#';
    }
    buf[width] = '\0';
  }
	
    
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

    if (length == 0) {
      return WS_DATA_TYPE_TEXT;
    }

    // check that the string is 0.0 or 0
    for (int i = 0; i < length; i++) {
      char c = value[i];
      if (c != '0' && c != '.') {
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
  if (ws == NULL) {
    return;
  }
  
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
	char *buffer = malloc(sizeof(char) * 255);
  char *result;
  char *token;
  char *line_cursor;
  char *comma_substring;
  int row_count = 0;
  int col_count = 0;
  int continue_read = 0;

  result = fgets(buffer, 255, f);
  line_cursor = result;
  while(result != NULL && row_count < ws->rows) {
    int length = strlen(buffer);

    while(col_count < ws->cols) {
      comma_substring = strstr(line_cursor, ",");
      if (comma_substring != NULL) {
        // comma is found
        int token_length = comma_substring - line_cursor;
        token = malloc(sizeof(char) * (token_length + 1));
        strncpy(token, line_cursor, token_length);
        token[token_length] = '\0';
        // set cursor to after the comma
        line_cursor = comma_substring + 1;
      } else {
        // comma is not found
        // copy remaining characters into token
        int token_length = strlen(line_cursor);
        // malloc with 1 less character to remove the trailing newline
        token = malloc(sizeof(char) * token_length);
        strcpy(token, line_cursor);
        token[token_length - 1] = '\0';
        // set cursor to end of line
        line_cursor = &result[length];
      }


      char *cell = ws->cells[row_count][col_count];
      if (continue_read) {
        // append the value
        int length_left = MAX_WORD - strlen(cell);
        strncat(cell, token, length_left);
        continue_read = 0;
      } else {
        // set the value
        ws_set(ws, col_count, row_count, token);  
      }

      // if cell is invalid clear the value
      if (ws_guess_data_type(cell) == WS_DATA_TYPE_ILLEGAL) {
        ws_set(ws, col_count, row_count, "\0");
      }

      free(token);

      if (line_cursor[0] == '\0') {
        break;
      }

      col_count += 1;
    }
    
    int line_ended = result[length - 1] == '\n';
    if (line_ended) {
      result[length - 1] = '\0';
      row_count += 1;
      col_count = 0;
      continue_read = 0;
    } else {
      continue_read = 1;
    }

    result = fgets(buffer, 255, f);
    line_cursor = result;
  }

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
	for (int x = 0; x < ws->rows; ++x) {
    fputs(ws->cells[x][0], f);
    for (int y = 1; y < ws->rows; ++y) {
      fputc(',', f);
      fputs(ws->cells[x][y], f);
    }
    fputc('\n', f);
  }
	return 0;
}
