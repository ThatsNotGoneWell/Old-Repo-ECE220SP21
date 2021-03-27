#include "sudoku.h"

//-------------------------------------------------------------------------------------------------
// Start here to work on your MP7
//-------------------------------------------------------------------------------------------------
/* Name:
 * Partners:
 * Introduction: The following code defines several functions.
 *               The first three functions, "is_val_in_row""is_val_in_col""is_val_in_3x3_zone", are checking
 *               if this value can be put in the current cell. Function "is_val_valid" integrates the above 
 *               three functions. Function "solve_sudoku" first find empty spots and test each number to decide
 *               if this input is valid. Recursion is applied in this function. It will terminate when there 
 *               is no empty spot.
 */
// You are free to declare any private functions if needed.

// Function: is_val_in_row
// Return true if "val" already existed in ith row of array sudoku.
int is_val_in_row(const int val, const int i, const int sudoku[9][9]) {

  assert(i>=0 && i<9);

  // BEG TODO
  int col;// declare column
  for (col = 0; col < 9; col++){// for each column
    if (val == sudoku[i][col]){
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_col
// Return true if "val" already existed in jth column of array sudoku.
int is_val_in_col(const int val, const int j, const int sudoku[9][9]) {

  assert(j>=0 && j<9);

  // BEG TODO
  int row;// declare row
  for (row = 0; row < 9; row++){// for each row
    if (val == sudoku[row][j]){
      return 1;
    }
  }
  return 0;
  // END TODO
}

// Function: is_val_in_3x3_zone
// Return true if val already existed in the 3x3 zone corresponding to (i, j)
int is_val_in_3x3_zone(const int val, const int i, const int j, const int sudoku[9][9]) {
   
  assert(i>=0 && i<9);
  
  // BEG TODO
  int section_row, section_col, row, col,corRow,corCol;
  
  // decide in which zone the cell should be
  section_row = i/3;
  section_col = j/3;
  
  // decide the upper left corner of that zone
  corRow = section_row*3;
  corCol = section_col*3;
  
  for (row = section_row*3; row < corRow+3; row++){// for each row
    for (col = section_col*3; col < corCol+3; col++){// for each column
      if (val == sudoku[row][col]){
	return 1;
      }
    }
  }
  
  return 0;
  // END TODO
}

// Function: is_val_valid
// Return true if the val is can be filled in the given entry.
int is_val_valid(const int val, const int i, const int j, const int sudoku[9][9]) {

  assert(i>=0 && i<9 && j>=0 && j<9);

  // BEG TODO
  int x,y,z;// store the results from three functions into three variables
  x = is_val_in_row(val, i, sudoku);
  y = is_val_in_col(val, j, sudoku);
  z = is_val_in_3x3_zone(val, i, j, sudoku);
  
  if ( x || y || z){// If true, then invalid
    return 0;
  }
  
  return 1;
  // END TODO
}

// Procedure: solve_sudoku
// Solve the given sudoku instance.
int solve_sudoku(int sudoku[9][9]) {

  // BEG TODO.
  int i,j;
  int needbreak = 0, emptyfound = 0;// set up flags
  for (i=0; i<9; i++){// for each row
    for (j=0; j<9; j++){// for each column
      if (sudoku[i][j] == 0){
	needbreak = 1;// time to break two loops
	emptyfound = 1;// empty spot is found
	break;
      }
    }
    if (needbreak){// break the outer for loop
      break;
    }
  }
  
  if (!emptyfound){// all cells are filled
  	return 1;
  }
  
  for (int num=1; num<=9; num++){// for each possible number
    if (is_val_valid(num, i, j, sudoku)){
      sudoku[i][j] = num;// fill in this number if it is valid
      if (solve_sudoku(sudoku)){// recursion until true
	return 1;
      }
      sudoku[i][j] = 0;// otherwise, fill in 0 and check another number
    }
  }
  
  return 0;
  // END TODO.
}

// Procedure: print_sudoku
void print_sudoku(int sudoku[9][9])
{
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      printf("%2d", sudoku[i][j]);
    }
    printf("\n");
  }
}

// Procedure: parse_sudoku
void parse_sudoku(const char fpath[], int sudoku[9][9]) {
  FILE *reader = fopen(fpath, "r");
  assert(reader != NULL);
  int i, j;
  for(i=0; i<9; i++) {
    for(j=0; j<9; j++) {
      fscanf(reader, "%d", &sudoku[i][j]);
    }
  }
  fclose(reader);
}
