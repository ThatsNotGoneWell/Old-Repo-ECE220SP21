int countLiveNeighbor(int* board, int boardRowSize, int boardColSize, int row, int col){
	int num_live = 0; // the number of live neighbors
  	int i,j;
  
  	for (i=row-1; i<=row+1; i++){
    	if (i>=0 && i<boardRowSize){
        	for (j=col-1; j<=col+1; j++){
    			if (j>=0 && j<boardColSize){
                	if ((i != row) || (j != col)){
                    	if (board[i*boardColSize + j]==1){
                        	++num_live;
                        }
                    }
                }
            }
        }
    }

  	return num_live; //return the number of live numbers
}
/*
 * Update the game board to the next step.
 * Input: 
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: board is updated with new values for next step.
 */


void updateBoard(int* board, int boardRowSize, int boardColSize) {
  int max_index = boardRowSize*boardColSize;
	int k;
  	int copy_board[max_index];
  
  	for (k=0; k<max_index; k++){
    	copy_board[k] = board[k];
  	}
  	
  	int liveNeighbors;
  	
  	int i,j;
  	for (i=0; i<boardRowSize; i++){
		for (j=0; j<boardColSize; j++){
        	liveNeighbors = countLiveNeighbor(copy_board,boardRowSize,boardColSize,i,j);
          	if ((liveNeighbors < 2) || (liveNeighbors > 3)){
            	board[i*boardColSize + j] =  0;
            }
          	else if(liveNeighbors == 3){
            	board[i*boardColSize + j] = 1;
            }
        }
    
    }
}

/*
 * aliveStable
 * Checks if the alive cells stay the same for next step
 * board: 1-D array of the current game board. 1 represents a live cell.
 * 0 represents a dead cell
 * boardRowSize: the number of rows on the game board.
 * boardColSize: the number of cols on the game board.
 * Output: return 1 if the alive cells for next step is exactly the same with 
 * current step or there is no alive cells at all.
 * return 0 if the alive cells change for the next step.
 */ 

int aliveStable(int* board, int boardRowSize, int boardColSize){
  	int i;
    int ret=0;
  	int max_index = (boardRowSize-1)*boardColSize + boardColSize -1;
  	int copy_board[max_index+1];

  	for (i=0; i<=max_index; i++){
    	copy_board[i] = board[i];
  	}
  	updateBoard(copy_board, boardRowSize, boardColSize);
  	for (i=0; i<=max_index; i++){
    	if (copy_board[i] == board[i]){
        	ret = 1;
        }
      	else{
          	ret = 0;
      		break;
        }
  	}
  	
  	return ret;

}
