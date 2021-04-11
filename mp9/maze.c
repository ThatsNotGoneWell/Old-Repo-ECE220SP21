#include <stdio.h>
#include <stdlib.h>
#include "maze.h"
//Name: Zekai Zhang (zekaiz2)
//Partners: hz39, zw53
//Intro Paragraph:
//The goal of this program is to implement a maze solver by using a recursive depth-first search algorithm//
//as well as a couple of functions that can be used to verify a correct solution.//
//The first two numbers indicates the size of the maze which is the width and the height of the maze.//
//For this program, we are able to find a solution to solve the maze from the starting point("S") to the ending point("E")//
//In the maze,  ‘%’ represents walls within the maze while a space represents an empty cell.//
//‘*’ represents the cells that make up the solution for the maze.//
//and ‘~’ represents the cells that aren't a part of the solution but were visited during the search.//
//You could only move right, left, up, and down in order to solve the maze.//

/*
 * createMaze -- Creates and fills a maze structure from the given file
 * INPUTS:       fileName - character array containing the name of the maze file
 * OUTPUTS:      None 
 * RETURN:       A filled maze structure that represents the contents of the input file
 * SIDE EFFECTS: None
 */
maze_t * createMaze(char * fileName)
{
	int i,j;
  char mazeChar;
  FILE *file;
  file = fopen(fileName, "r");
  
  maze_t * newMaze = malloc(sizeof(maze_t)); // allocate maze_t
  fscanf(file, "%d %d", &(newMaze->width), &(newMaze->height)); // retrieve width and height from file
  newMaze->cells = (char**)malloc(newMaze->height * sizeof(char*)); // allocate pointer array
  
  // allocate memory for each row
  for (i=0; i<newMaze->height; i++){
    newMaze->cells[i] = (char*)malloc(newMaze->width * sizeof(char));
  }
  
  // store each entry of maze to memory
  for (i=0; i<newMaze->height; i++){ // each row
  	for (j=0; j<newMaze->width; j++){ // each column
    	mazeChar = fgetc(file); // get char from file
      while (mazeChar == '\n'){ // keep getting char until it is not a new line
      	mazeChar = fgetc(file);
      }
    	if (mazeChar == 'S'){ // find starting point
        newMaze->cells[i][j] = mazeChar;
        newMaze->startColumn = j;
        newMaze->startRow = i;
      }
      else if (mazeChar == 'E'){ // find ending point
        newMaze->cells[i][j] = mazeChar;
        newMaze->endColumn = j;
        newMaze->endRow = i;
      }
      else
        newMaze->cells[i][j] = mazeChar;
    }
  }
  
  fclose(file);
	return newMaze;
}

/*
 * destroyMaze -- Frees all memory associated with the maze structure, including the structure itself
 * INPUTS:        maze -- pointer to maze structure that contains all necessary information 
 * OUTPUTS:       None
 * RETURN:        None
 * SIDE EFFECTS:  All memory that has been allocated for the maze is freed
 */
void destroyMaze(maze_t * maze)
{
	int i;
  
  // free memory starting from each data entry of array
  for (i=0; i<maze->height; i++){
  	free(maze->cells[i]);
  }
  
  free(maze->cells); // free pointer array
  free(maze); // free the structure
}

/*
 * printMaze --  Prints out the maze in a human readable format (should look like examples)
 * INPUTS:       maze -- pointer to maze structure that contains all necessary information 
 *               width -- width of the maze
 *               height -- height of the maze
 * OUTPUTS:      None
 * RETURN:       None
 * SIDE EFFECTS: Prints the maze to the console
 */
void printMaze(maze_t * maze)
{
  int i,j;  
  for(i=0;i<maze->height;i++){
    for(j=0;j<maze->width;j++){
      printf("%c", maze->cells[i][j]);
    }
    printf("\n");
  }
}

/*
 * solveMazeManhattanDFS -- recursively solves the maze using depth first search,
 * INPUTS:               maze -- pointer to maze structure with all necessary maze information
 *                       col -- the column of the cell currently beinging visited within the maze
 *                       row -- the row of the cell currently being visited within the maze
 * OUTPUTS:              None
 * RETURNS:              0 if the maze is unsolvable, 1 if it is solved
 * SIDE EFFECTS:         Marks maze cells as visited or part of the solution path
 */ 
int solveMazeDFS(maze_t * maze, int col, int row)
{
  if(maze->cells[row][col] == 'E'){
    return 1;//Successful base case: reached destination
  }
  
  if(row<0 || col<0 || row>=maze->height-1 || col>=maze->width-1){
    return 0;//Unsuccessful base case: out of bounds
  }
  
  if(maze->cells[row][col] != ' ' && maze->cells[row][col] != 'S'){
    return 0;//Unsuccessful base case: not a valid place
  }
  
  if(maze->cells[row][col] != 'S'){
  	maze->cells[row][col] = '*';//mark this as a potential solution
  }
  
  if(maze->cells[row-1][col] != 'S'){
    if(solveMazeDFS(maze,col,(row-1))){
      return 1;//Recursively check if the right cell is a possible solution
    }
  }

  if(maze->cells[row+1][col] != 'S'){
    if(solveMazeDFS(maze,col,(row+1))){
      return 1;//Recursively check if the left cell is a possible solution
    }
  }

  if(maze->cells[row][col-1] != 'S'){
    if(solveMazeDFS(maze,(col-1),row)){
      return 1;//Recursively check if the cell below is a possible solution
    }
  }
  
  if(maze->cells[row][col+1] != 'S'){
    if(solveMazeDFS(maze,(col+1),row)){
      return 1;//Recursively check if the cell above is a possible solution
    }
  }
    
  maze->cells[row][col] = '~';//mark this as visited
  
  return 0;//Everything fails, maze can't be solved
}
