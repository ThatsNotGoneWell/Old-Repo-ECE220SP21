/*      
 *
 * prog5.c - source file adapted from UIUC ECE198KL Spring 2013 Program 4
 *           student code -- GOLD VERSION by Steven S. Lumetta
 */


/*
 * The functions that you must write are defined in the header file.
 * Blank function prototypes with explanatory headers are provided
 * in this file to help you get started.
 *
 * Intro Paragraph--------------------------------------------------
 * Name: Zekai Zhang (zekaiz2)
 * Partners: hz39, zw53
 * This file has three functions in it.
 * The first function is set_seed. It will set a random seed value using 
 * srand(). The second function is start_game, which set four random values 
 * that correspond to the actual solutions.
 * The third function let the user to make up to 10 guesses 
 * unless the perfect answer is guessed.
 */

#include <stdio.h>
#include <stdlib.h>

#include "prog5.h"

int key1;
int key2;
int key3;
int key4;
int guess_number;
int max_score;
char solutions[4][10];
char* pool[] = {"Vader", "Padme", "R2-D2", "C-3PO", "Jabba", "Dooku", "Lando", "Snoke",};
/* Show guessing pool -- This function prints "pool" to stdout
 * INPUT: none
 * OUTPUT: none
 * SIDE EFFECTS: print all the strings in the output
 */
void print_pool() {
    printf("Valid term to guess:\n\t");
    for(int i = 0; i < 8 ; ++i) {
        printf("%s ", pool[i]);
    }
    printf("\n");
}

/*
 * is_valid -- This function checks whether a string is valid
 * INPUTS: str -- a string to be checked
 * OUTPUTS: none
 * RETURN VALUE: 0 if str is invalid, or 1 if str is valid
 * SIDE EFFECTS: none
 */
int is_valid(char* str) {
    int i = 0;
    if (str == NULL) {
        return 0;
    }
    for (i = 0; i < 8; i++) {
        if (strcmp(str, pool[i]) == 0) {
            return 1;
        }
    }
    return 0;
}


/*
 * set_seed -- This function sets the seed value for pseudorandom
 * number generation based on the number the user types.
 * The input entered by the user is already stored in the string seed_str by the code in main.c.
 * This function should use the function sscanf to find the integer seed value from the 
 * string seed_str, then initialize the random number generator by calling srand with the integer
 * seed value. To be valid, exactly one integer must be entered by the user, anything else is invalid. 
 * INPUTS: seed_str -- a string (array of characters) entered by the user, containing the random seed
 * OUTPUTS: none
 * RETURN VALUE: 0 if the given string is invalid (string contains anything
 *               other than a single integer), or 1 if string is valid (contains one integer)
 * SIDE EFFECTS: initializes pseudo-random number generation using the function srand. Prints "set_seed: invalid seed\n"
 *               if string is invalid. Prints nothing if it is valid.
 */
int set_seed (const char seed_str[]) {
//    Example of how to use sscanf to read a single integer and check for anything other than the integer
//    "int seed" will contain the number typed by the user (if any) and the string "post" will contain anything after the integer
//    The user should enter only an integer, and nothing else, so we will check that only "seed" is read. 
//    We declare
//    int seed;
//    char post[2];
//    The sscanf statement below reads the integer into seed. 
//    sscanf (seed_str, "%d%1s", &seed, post)
//    If there is no integer, seed will not be set. If something else is read after the integer, it will go into "post".
//    The return value of sscanf indicates the number of items read succesfully.
//    When the user has typed in only an integer, only 1 item should be read sucessfully. 
//    Check that the return value is 1 to ensure the user enters only an integer. 
//    Feel free to uncomment these statements, modify them, or delete these comments as necessary. 
//    You may need to change the return statement below
    int seed;
    char post[2];
    if (sscanf (seed_str, "%d%1s", &seed, post) != 1) {
      // your code here
      printf("set seed: invalid seed\n");
      return 0;
    }
    else {
      srand(seed);
      return 1;
    }

    
}


/*
 * start_game -- This function is called by main.c after set_seed but before the user makes guesses.
 *               This function creates the four solution numbers using the approach
 *               described in the wiki specification (using rand())
 *               The four solution numbers should be stored in the static variables defined above. 
 *               The values at the pointers should also be set to the solution numbers.
 *               The guess_number should be initialized to 1 (to indicate the first guess)
 *               The score should be initialized to -1.  
 * INPUTS: none
 * OUTPUTS: none
 * RETURN VALUE: none
 * SIDE EFFECTS: records the solution in the static solution variables for use by make_guess, set guess_number
 */
void start_game () {
  int first;
  int second;
  int third;
  int fourth; 
  first = rand()%8;
  second = rand()%8;
  third = rand()%8;
  fourth = rand()%8;
  key1 = first;
  key2 = second;
  key3 = third;
  key4 = fourth;
  guess_number=1;
  max_score=-1;
  
    //your code here
}

/*
 * make_guess -- This function is called by main.c after the user types in a guess.
 *               The guess is stored in the string guess_str. 
 *               The function must calculate the number of perfect and misplaced matches
 *               for a guess, given the solution recorded earlier by start_game
 *               The guess must be valid (contain only 4 strings from pool). If it is valid
 *               the number of correct and incorrect matches should be printed, using the following format
 *               "With guess %d, you got %d perfect matches and %d misplaced matches.\n"
 *               If valid, the guess_number should be incremented.
 *               If invalid, the error message "make_guess: invalid guess\n" should be printed and 0 returned.
 *               For an invalid guess, the guess_number is not incremented.
 * INPUTS: guess_str -- a string consisting of the guess typed by the user
 * OUTPUTS: none
 * RETURN VALUE: 2 if guess string is valid and got all 4 perfect matches, or 1 if the guess string is valid, 
 *               or 0 if it is invalid
 * SIDE EFFECTS: prints (using printf) the number of matches found and increments guess_number(valid guess) 
 *               or an error message (invalid guess)
 *               (NOTE: the output format MUST MATCH EXACTLY, check the wiki writeup)
 */
int make_guess (const char guess_str[]) {
  // your code here
  char guesses[4][10];
  char post[20];
  if(sscanf(guess_str, "%s%s%s%s%s",guesses[0],guesses[1],guesses[2],guesses[3],post)!=4){
    printf("make_guess: invalid guess\n");
    return 0;
  }
  for(int i = 0; i<4; i++){
    if(is_valid(guesses[i])==0){
      printf("make_guess:invalid guess\n");
      return 0;
    }
  }
  return 1;
  int key_array[4]={key1,key2,key3,key4};
  // int guesses[4]={guesses[0],guesses[1],guesses[2],guesses[3]};
  // int mark_key[4]={0, 0, 0, 0};
  int mark_guess[]={0, 0, 0, 0};
  int perfect_match = 0;
  int misplaced_match = 0;
  int score, max_score = -1;
  
  int i,j,k;
  	
  	
  //logic for testing perfect or mismatched
  for (i=0; i<4; i++) {
    if (guesses [i] == key_array[i]) {
      //  mark_key[i] = 1;
      mark_guess[i] = 1;
      perfect_match += 1;
      score += 1000;
    }
  }
  for (k=0; k<4; k++) {
    if (mark_guess[k] == 0){
      for (j=0; j<4; j++){
	if (*guesses[k] == key_array[j]) {
	  //  mark_key[j] = 1;
	  mark_guess[k] = 1;
	  misplaced_match += 1;
	  break;
	}
      }
    }
  }
  
  if (score > max_score){
    max_score = score; // update max_score
  }
  
  printf("With guess %d, you got %d perfect matches and %d misplaced matches.\n", guess_number, perfect_match, misplaced_match);
  printf("Your score is %d and cur max score is %d.\n", score, max_score);
  guess_number = guess_number + 1;
  return 1;
  

     
} 
