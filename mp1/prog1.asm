;
; The code given to you here implements the histogram calculation that 
; we developed in class.  In programming lab, we will add code that
; prints a number in hexadecimal to the monitor.
;
; Your assignment for this program is to combine these two pieces of 
; code to print the histogram to the monitor.
;
; If you finish your program, 
;    ** commit a working version to your repository  **
;    ** (and make a note of the repository version)! **


	.ORIG	x3000		; starting address is x3000


;
; Count the occurrences of each letter (A to Z) in an ASCII string 
; terminated by a NUL character.  Lower case and upper case should 
; be counted together, and a count also kept of all non-alphabetic 
; characters (not counting the terminal NUL).
;
; The string starts at x4000.
;
; The resulting histogram (which will NOT be initialized in advance) 
; should be stored starting at x3F00, with the non-alphabetic count 
; at x3F00, and the count for each letter in x3F01 (A) through x3F1A (Z).
;
; table of register use in this part of the code
;    R0 holds a pointer to the histogram (x3F00)
;    R1 holds a pointer to the current position in the string
;       and as the loop count during histogram initialization
;    R2 holds the current character being counted
;       and is also used to point to the histogram entry
;    R3 holds the additive inverse of ASCII '@' (xFFC0)
;    R4 holds the difference between ASCII '@' and 'Z' (xFFE6)
;    R5 holds the difference between ASCII '@' and '`' (xFFE0)
;    R6 is used as a temporary register
;

	LD R0,HIST_ADDR      	; point R0 to the start of the histogram
	
	; fill the histogram with zeroes 
	AND R6,R6,#0		; put a zero into R6
	LD R1,NUM_BINS		; initialize loop count to 27
	ADD R2,R0,#0		; copy start of histogram into R2

	; loop to fill histogram starts here
HFLOOP	STR R6,R2,#0		; write a zero into histogram
	ADD R2,R2,#1		; point to next histogram entry
	ADD R1,R1,#-1		; decrement loop count
	BRp HFLOOP		; continue until loop count reaches zero

	; initialize R1, R3, R4, and R5 from memory
	LD R3,NEG_AT		; set R3 to additive inverse of ASCII '@'
	LD R4,AT_MIN_Z		; set R4 to difference between ASCII '@' and 'Z'
	LD R5,AT_MIN_BQ		; set R5 to difference between ASCII '@' and '`'
	LD R1,STR_START		; point R1 to start of string

	; the counting loop starts here
COUNTLOOP
	LDR R2,R1,#0		; read the next character from the string
	BRz PRINT_HIST		; found the end of the string

	ADD R2,R2,R3		; subtract '@' from the character
	BRp AT_LEAST_A		; branch if > '@', i.e., >= 'A'
NON_ALPHA
	LDR R6,R0,#0		; load the non-alpha count
	ADD R6,R6,#1		; add one to it
	STR R6,R0,#0		; store the new non-alpha count
	BRnzp GET_NEXT		; branch to end of conditional structure
AT_LEAST_A
	ADD R6,R2,R4		; compare with 'Z'
	BRp MORE_THAN_Z         ; branch if > 'Z'

; note that we no longer need the current character
; so we can reuse R2 for the pointer to the correct
; histogram entry for incrementing
ALPHA	ADD R2,R2,R0		; point to correct histogram entry
	LDR R6,R2,#0		; load the count
	ADD R6,R6,#1		; add one to it
	STR R6,R2,#0		; store the new count
	BRnzp GET_NEXT		; branch to end of conditional structure

; subtracting as below yields the original character minus '`'
MORE_THAN_Z
	ADD R2,R2,R5		; subtract '`' - '@' from the character
	BRnz NON_ALPHA		; if <= '`', i.e., < 'a', go increment non-alpha
	ADD R6,R2,R4		; compare with 'z'
	BRnz ALPHA		; if <= 'z', go increment alpha count
	BRnzp NON_ALPHA		; otherwise, go increment non-alpha

GET_NEXT
	ADD R1,R1,#1		; point to next character in string
	BRnzp COUNTLOOP		; go to start of counting loop



PRINT_HIST
; Name: Zekai Zhang
; My netid: zekaiz2
; partners: hz39; zw53
; Introduction: the following program prints a histogram that shows the frequency of each 
;character in a string. We use the left-shifting method to extract the value of the frequency ;and store it to a temporary register. Then we compare this value with decimal number 9 to ;determine whether the output should be a number or a letter. Several loops have been set up to print the entire 27-bin histogram.
; We have set R1 to -27 indicates the outer loop counter
; We have set R2 to be histogram string address
; We have set R3 to be the frequency stored in histogram string address
; We have set R4 to 4 as the counter of LOOP_FOUR 
; We have set R5 to 4 as the SMALL_LOOP counter
; We have set R6 to be a temporary register in order to store highest 4 bits of the histogram 
;

	LD R1, NUM_BINS		; set outer loop counter to #-27 
; (negative due to future increments)
	LD R2, HIST_ADDR		; load the histogram starting address 

; The OUTER_LOOP runs 27 times to print the entire histogram.
OUTER_LOOP
	LDR R3, R2, #0		; load the data stored in the histogram address
	ADD R1, R1, #0		; copy outer loop counter
	BRzp DONE			; end the program when counter becomes zero

; Print each label and space at the beginning of each row.
PRINT_LABEL
<<<<<<< HEAD
	LD R0, ASCII_AT		; load the ASCII value of ‘@’ to R0
=======
	LD R0, ASCII_AT		; load the ASCII value of \u2018@\u2019 to R0
>>>>>>> 9a8b5862cb0b30878a2335d771057a88b19d672d
	ADD R0, R0, R1		; add offset and print corresponding ASCII label
	OUT
	LD R0, SPACE		; load and print a space
	OUT

; LOOP_FOUR runs 4 times to transfer the entire data value to R6 which will be used to print
	AND R4,R4,#0		; clear R4
	ADD R4,R4,#4		; set the loop counter to 4

LOOP_FOUR				;
ADD R4,R4,#-1		; decrement the counter by 1
BRn JUMP_OUT		; if the counter reaches to negative, then jump out

;loading 4 bits from R3 to R6
AND R6,R6,#0		; clear R6
AND R5,R5,#0		; clear R5
ADD R5,R5,#4		; Set R5 as a counter to 4

SMALLER_LOOP
ADD R6,R6,R6		; left shift R6
ADD R3,R3,#0		; reset to BR of R3
BRzp SKIP			; if the value of R3 is zero or positive, then go to SKIP
ADD R6,R6,#1		; if the value of R3 is negative, then add 1 to R6

SKIP
ADD R3,R3,R3		; left shift R3
ADD R5,R5,#-1		; decrement the counter by 1
BRz GET_OUT		; when the counter reaches to 0, go to GET_OUT
BRnzp SMALLER_LOOP	; if the counter is positive, then go back
GET_OUT				;


; print hexadecimal
ADD R0,R6,#-9		; compare digit with 9
BRnz PRINT_NUMERICAL	; if digit is 0-9, go to PRINT_NUMERICAL
<<<<<<< HEAD
LD R0, A			; otherwise, load ASCII of ‘A’
ADD R0, R0, R6		; R0 <- R6 + ‘A’ - 10
ADD R0, R0, #-10		; R0 <- R6 + ‘A’ - 10
BRnzp DIG_LOOP_DONE	; use OUT trap

PRINT_NUMERICAL			; Load ASCII of ‘0’
LD R0, ZERO			; load ASCII of ‘0’
=======
LD R0, A			; otherwise, load ASCII of \u2018A\u2019
ADD R0, R0, R6		; R0 <- R6 + \u2018A\u2019 - 10
ADD R0, R0, #-10		; R0 <- R6 + \u2018A\u2019 - 10
BRnzp DIG_LOOP_DONE	; use OUT trap

PRINT_NUMERICAL			; Load ASCII of \u20180\u2019
LD R0, ZERO			; load ASCII of \u20180\u2019
>>>>>>> 9a8b5862cb0b30878a2335d771057a88b19d672d
ADD R0, R0, R6		;
OUT				;
BRnzp LOOP_FOUR		;

DIG_LOOP_DONE 
OUT				; use OUT trap
BRnzp LOOP_FOUR

JUMP_OUT				;
	LD R0, NEW_L		; print a new line
OUT				;
ADD R1, R1, #1		; increment the outer loop counter by 1
ADD R2, R2, #1

BRnzp OUTER_LOOP




; do not forget to write a brief description of the approach/algorithm
; for your implementation, list registers used in this part of the code,
; and provide sufficient comments



DONE	HALT			; done


; the data needed by the program
NUM_BINS	.FILL #-27	; 27 loop iterations
NEG_AT		.FILL xFFC0	; the additive inverse of ASCII '@'
AT_MIN_Z	.FILL xFFE6	; the difference between ASCII '@' and 'Z'
AT_MIN_BQ	.FILL xFFE0	; the difference between ASCII '@' and '`'
HIST_ADDR	.FILL x3F00     ; histogram starting address
STR_START	.FILL x4000	; string starting address



; the data added by us
<<<<<<< HEAD
ASCII_AT	.FILL #91	; the ASCII value of ‘@+27’
=======
ASCII_AT	.FILL #91	; the ASCII value of \u2018@+27\u2019
>>>>>>> 9a8b5862cb0b30878a2335d771057a88b19d672d
SPACE	.FILL x0020	; the ASCII value of space
NEW_L	.FILL x000A	; the ASCII value of a new line

ZERO		.FILL #48
A		.FILL #65

; for testing, you can use the lines below to include the string in this
; program...
; STR_START	.FILL STRING	; string starting address
; STRING		.STRINGZ "This is a test of the counting frequency code.  AbCd...WxYz."



	; the directive below tells the assembler that the program is done
	; (so do not write any code below it!)

	.END
