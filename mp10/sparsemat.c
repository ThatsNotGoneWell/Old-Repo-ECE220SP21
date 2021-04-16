#include "sparsemat.h"

#include <stdio.h>
#include <stdlib.h>
//Name: Zekai Zhang
//Partners:hz39, zw53

//intro paragraph:
//This program is intended to store a sparse matrix by only storing the non-zero elements
//We used the linked list method to store a sparse matrix
//because the usual way (2D array) to store a sparse matrix will cause a large memory space in runtime stack
//Each node in the linked list holds a tuple, which indicates the location and value in the matrix
//In such a case, once we found the right position in the linked list
//we could do add, delete in a more efficent way



sp_tuples * load_tuples(char* input_file)
{
	int row,col;
  double val;
  
  FILE *file;
  file = fopen(input_file, "r");
  
  sp_tuples * list = malloc(sizeof(sp_tuples)); // allocate structure
  fscanf(file, "%d %d", &(list->m), &(list->n)); // retrieve width and height from file
  list->nz = 0; // init tuples
  list->tuples_head = NULL; //set the head node
  
  while (feof(file) == 0){ // call set_tuples when file is not ending
  	fscanf(file, "%d %d %lf", &row, &col, &val);
    set_tuples(list, row, col, val);
  }
  
  fclose(file);
  
  return list;
}



double gv_tuples(sp_tuples * mat_t,int row,int col)

{
  sp_tuples_node *currNode;
  currNode = mat_t->tuples_head;
  while (currNode!=NULL){
    if(currNode->row==row && currNode->col==col){
      return currNode->value;
    }
    else{
    	currNode = currNode->next;
    }
  }
  
  return 0;
}


void delete_node(sp_tuples * mat_t, int row, int col){
  sp_tuples_node *currNode = mat_t->tuples_head; //create new pointer C_node
  
  if(currNode == NULL){
    return; //There's nothing in the matrix
  }
  else if(currNode->row == row && currNode->col == col){//delete the head node
    free(currNode);
    mat_t->nz -= 1;
    mat_t->tuples_head = NULL;
    return;
  }

  while(currNode != NULL){   
  	if(currNode->next == NULL){
      break; //brake when tail node is reached
    }
    else if(currNode->next->row == row && currNode->next->col == col){ //update the ones that shouldn't be deleted
      sp_tuples_node *temp = currNode->next;
      currNode->next = temp->next;
      free(temp);
      mat_t->nz -= 1;
      return;
    }
    currNode = currNode->next; //go to the next node
  }

  return;

}


void set_tuples(sp_tuples * mat_t, int row, int col, double value)
{
  //if value is 0, it will need to find the node at row and col if it exists, and delete it from the list. 
  //Be sure to free the nodes from memory or they will be lost forever.  
	if(value == 0){
    delete_node(mat_t,row,col);
    return;
  }
  mat_t->nz += 1;
  sp_tuples_node * new_node = malloc(sizeof(sp_tuples_node)); // allocate memory for new node
	new_node->col = col; // set new node values based on input
  new_node->row = row;
  new_node->value = value;
  sp_tuples_node *currNode = mat_t->tuples_head; // set the current pointer to the start of the node
  
  //special case one: if the list is empty
  if (currNode == NULL){
    mat_t->tuples_head = new_node;
    new_node->next = NULL;
    return;
  }
  //special case two: if the position to insert the new node is at the very beginning
  if (currNode->row > row || (currNode->row == row && currNode->col > col)){
    new_node->next = currNode;
    mat_t->tuples_head = new_node;
    return;
  }
  //Iterate through the linked list to find the right position to insert the node
  while (currNode != NULL){
    if (currNode->row == row && currNode->col == col){ // entry already exists, replace the old value 
      currNode->value = value;
      free(new_node);
      mat_t->nz -= 1;
      return;
    }
    //if the new node is inserted at the tail of the linked list
    if (currNode->next == NULL){
      currNode->next = new_node;
      new_node->next = NULL;
      return;
    }
    //if the new node is inserted at the middle of the linked list
    if (currNode->next->row > row || (currNode->next->row == row && currNode->next->col > col)){
      new_node->next = currNode->next;
      currNode->next = new_node;
      return;
    }
    //iterate the next node in the linked list
    currNode = currNode->next;
  }
  
  
  return;
}



void save_tuples(char * file_name, sp_tuples * mat_t)
{
  FILE *file;
  file = fopen(file_name, "w");
  sp_tuples_node *currNode;
  currNode = mat_t->tuples_head;
  
  fprintf(file, "%d %d", mat_t->m, mat_t->n); // write row and col to file
  
  while (currNode != NULL){ // for each non-zero entry
  	fprintf(file, "%d %d %lf\n", currNode->row, currNode->col, currNode->value); // write data in each tuple to file
    currNode = currNode->next; // update node
  }
  
  fclose(file);
	
  return;
}



sp_tuples * add_tuples(sp_tuples * matA, sp_tuples * matB){

  int i,j;  
  double sumA = 0, sumB = 0; // init sum for matA and matB
  
  if (matA->m != matB->m || matA->n != matB->n) return NULL; // check if addition is possible
  
  // init matrix C
  sp_tuples * matC = malloc(sizeof(sp_tuples));
  matC->m = matA->m;
  matC->n = matA->n;
  matC->nz = 0;
  
  sp_tuples_node *currA = matA->tuples_head; // create pointers
  sp_tuples_node *currB = matB->tuples_head;
  
  while (currA != NULL){
  	i = currA->row;
    j = currA->col;
    sumA = gv_tuples(matC, i, j) + currA->value; // C_(i,j) = C_(i,j) + A_(i,j)
    set_tuples(matC, i, j, sumA);
    currA = currA->next; // update matA pointer
  }
  
  while (currB != NULL){
  	i = currB->row;
    j = currB->col;
    sumB = gv_tuples(matC, i, j) + currB->value; // C_(i,j) = C_(i,j) + B_(i,j)
    set_tuples(matC, i, j, sumB);
    currB = currB->next; // update matB pointer
  }
  
	return matC;
}



sp_tuples * mult_tuples(sp_tuples * matA, sp_tuples * matB){ 
  //optional  
  return matA;

}


	
void destroy_tuples(sp_tuples * mat_t){
	
  sp_tuples_node *currNode = mat_t->tuples_head;
  sp_tuples_node *temp; // temp pointer to be freed
  
  while (currNode != NULL){
  	temp = currNode;
    currNode = currNode->next; // update node
    free(temp);
  }
  
  free(mat_t); // free the structure
  
  return;
}
