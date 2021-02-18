; Name: Zekai Zhang (netid: zekaiz2)
; Partner: hz39, zw53
; Introduction: This program is a stack calculator that consists of subroutines to push or pop, ;print hexadecimal value, evaluate the input, and use five operations (addition, subtraction, ;multiplication, division, power) to compute the final result. This program implements stack to ;manage data. The input expression is postfix.
; Register table:
; R0 is used to take outputs and print them
; R1 is used as a temporary register
; R2 is used as a counter in power loop
; R3 is used as a temporary register
; R4 is used as a temporary register
; R5 is used to check if there is an underflow occurs and store results
; R6 is a temporary register that store highest 4 bits of the histogram
; R7 is designated to store addresses when JSR is used
;
.ORIG x3000
	
;your code goes here
	
NEW_INPUT
IN			; input from user
JSR EVALUATE	; evaluate if input is valid
	
	JSR PRINT_HEX	; print the hexadecimal value
	HALT










;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
; R5- value to print in hexadecimal
; R3- used as a counter to store #4
; R4- used as a counter to store #4
; R1- used to store the value of R5
; R6- used to print 4 digits at a time
PRINT_HEX
; LOOP_FOUR runs 4 times to transfer the entire data value to 
; R6 which will be used to print
	AND R1,R1,#0		; clear R1
ADD R1,R1,R5		; load R5 into R1
AND R3,R3,#0		; clear R3
	ADD R3,R3,#4		; set the loop counter to 4

LOOP_FOUR				;
ADD R3,R3,#-1		; decrement the counter by 1
BRn JUMP_OUT		; if the counter reaches to negative, then jump out

;loading 4 bits from R1 to R6
AND R6,R6,#0		; clear R6
AND R4,R4,#0		; clear R4
ADD R4,R4,#4		; Set R4 as a counter to 4

SMALLER_LOOP
ADD R6,R6,R6		; left shift R6
ADD R1,R1,#0		; reset to BR of R1
BRzp SKIP1			; if the value of R1 is zero or positive, then go to SKIP
ADD R6,R6,#1		; if the value of R1 is negative, then add 1 to R6

SKIP1
ADD R1,R1,R1		; left shift R1
ADD R4,R4,#-1		; decrement the counter by 1
BRz GET_OUT1		; when the counter reaches to 0, go to GET_OUT1
BRnzp SMALLER_LOOP	; if the counter is positive, then go back
GET_OUT1				;


; print hexadecimal
ADD R0,R6,#-9		; compare digit with 9
BRnz PRINT_NUMERICAL	; if digit is 0-9, go to PRINT_NUMERICAL
LD R0, ASCII_A		; otherwise, load ASCII of ‘A’
ADD R0, R0, R6		; R0 <- R6 + ‘A’ - 10
ADD R0, R0, #-10		; R0 <- R6 + ‘A’ - 10
BRnzp DIG_LOOP_DONE	; use OUT trap

PRINT_NUMERICAL			; Load ASCII of ‘0’
LD R0, ASCII_ZERO		; load ASCII of ‘0’
ADD R0, R0, R6		;
OUT				;
BRnzp LOOP_FOUR		;

DIG_LOOP_DONE 
OUT				; 
BRnzp LOOP_FOUR

JUMP_OUT 
	HALT

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;R0 - character input from keyboard
;R6 - current numerical output
;
;
EVALUATE
;your code goes here
LD R1, ASCII_EQUAL	; load the ASCII value of “=” into R1
NOT R1, R1			; inverse the value of ASCII “=”
ADD R1, R1, #1		;
ADD R1, R1, R0		;
BRz STACK_CHECK		; check if the input character is “=”
LD R1, ASCII_SPACE	; load the ASCII value of “space” into R1
NOT R1, R1			; inverse the value of ASCII “space”
ADD R1, R1, #1		;
ADD R1, R1, R0		;
BRz NEW_INPUT		; if the input character is “space”, read next character

CHECK_NUMBER
	LD R1, ASCII_ZERO		; load the ASCII value “0” into R1
	NOT R1, R1
	ADD R1, R1, #1		; inverse the ASCII value of “0”
	ADD R1, R1, R0		;
	BRn CHECK_MULTIPLY	; if the value is negative, check if the input is “*”
	LD R1, ASCII_NINE		; load the ASCII value “9” into R1
	NOT R1, R1			;
	ADD R1, R1, #1		; inverse the ASCII value of “9”
	ADD R1, R1, R0		;
	BRp CHECK_POWER	; if the value is positive, check if the input is “^”
	LD R6, OFFSET		; Set R6 as an offset “-48”
	ADD R0, R0, R6		; add the offset to the input number
JSR PUSH			;
	BRnzp NEW_INPUT		; after push the number, read the next input

CHECK_MULTIPLY
	LD R1, ASCII_MULTIPLY	; load the ASCII value “*” into R1
	NOT R1, R1			;
	ADD R1, R1, #1		; inverse the ASCII value of “*”
	ADD R1, R1, R0		;
	BRn INVALID			; if the value is negative, then the input is invalid
	ADD R1, R1, #0		;
	BRp CHECK_PLUS		; if the value is positive, then check if the input is “+”
	JSR POP			; if the input character is “*”, pop two values
	ADD R5, R5, #0		;
	BRp INVALID			; if underflow occurs, go to invalid
	AND R4, R4, #0		; clear R4
ADD R4, R0, R4		; Place the first popped value into R4
	JSR POP			;
ADD R5, R5, #0		;
	BRp INVALID			; if underflow occurs, go to invalid
AND R3, R3, #0		; clear R3
ADD R3, R0, R3		; Place the second popped value into R3
	JSR MUL			; do the multiplication process
	JSR PUSH			; push the value into the stack
	BRnzp NEW_INPUT		; read next input

CHECK_PLUS
	LD R1, ASCII_PLUS		; load the ASCII value of “+” into R1
	NOT R1, R1			;
	ADD R1, R1, #1		; inverse the ASCII value of “+”
	ADD R1, R1, R0		;
BRn INVALID			; if the value is negative, then the input is invalid
	ADD R1, R1, #0		;
	BRp CHECK_MINUS		; if the value is positive, then check if the input is “-”
	JSR POP			; if the input character is “+”, pop two values
	ADD R5, R5, #0		;
	BRp INVALID			; if underflow occurs, go to invalid
	AND R4, R4, #0		; clear R4
ADD R4, R0, R4		; Place the first popped value into R4
	JSR POP			;
ADD R5, R5, #0		;
	BRp INVALID			; if underflow occurs, go to invalid
	AND R3, R3, #0		; clear R3
ADD R3, R0, R3		; Place the second popped value into R3
	JSR PLUS			; do the PLUS process
	JSR PUSH			; push the value into the stack
	BRnzp NEW_INPUT		; read next input

CHECK_MINUS			
	LD R1, ASCII_MINUS	; load the ASCII value of “-” into R1
	NOT R1, R1			;
	ADD R1, R1, #1		; inverse the ASCII value of “-”
	ADD R1, R1, R0		;
	BRn INVALID			; if the value is negative, then the input is invalid
	ADD R1, R1, #0		;
	BRp CHECK_DIV		; if the value is positive, then check if the input is “/”
	JSR POP			; if the input character is “/”, pop two values
	ADD R5, R5, #0		;
	BRp INVALID			; if underflow occurs, go to invalid
AND R4, R4, #0		; clear R4
ADD R4, R0, R4		; Place the first popped value into R4
	JSR POP			;
ADD R5, R5, #0		;
	BRp INVALID			; if underflow occurs, go to invalid
AND R3, R3, #0		; clear R3
ADD R3, R0, R3		; Place the second popped value into R3
	JSR MIN			; do the MINUS process
	JSR PUSH			; push the value into the stack
	BRnzp NEW_INPUT		; read next input

CHECK_DIV
	LD R1, ASCII_DIV		; load the ASCII value of “/” into R1
	NOT R1, R1			;
	ADD R1, R1, #1		; inverse the ASCII value of “/”
	ADD R1, R1, R0		;
BRn INVALID			; if the value is negative, then the input is invalid
	JSR POP			; if the input character is “/”, pop two values
	ADD R5, R5, #0		;
	BRp INVALID			; if underflow occurs, go to invalid
AND R4, R4, #0		; clear R4
ADD R4, R0, R4		; Place the first popped value into R4
	JSR POP			;
ADD R5, R5, #0		;
	BRp INVALID			; if underflow occurs, go to invalid
AND R3, R3, #0		; clear R3
ADD R3, R0, R3		; Place the second popped value into R3
	JSR DIV			; do the DIVISION process
	JSR PUSH			; push the value into the stack
	BRnzp NEW_INPUT		; read next input

CHECK_POWER
	LD R1, ASCII_POWER	; load the ASCII value of “^” into R1
	NOT R1, R1			;
	ADD R1, R1, #1		; inverse the ASCII value of “^”
	ADD R1, R1, R0		;
	BRnp INVALID		; if the value is not zero, go to invalid
	JSR POP			; 
	ADD R5, R5, #0		; check if underflow occurs
	BRp INVALID			; if underflow occurs, then go to INVALID
	AND R4, R4, #0		; clear R4
ADD R4, R0, R4		; Place the first popped value into R4
	JSR POP			;
ADD R5, R5, #0		;
	BRp INVALID			; if underflow occurs, go to invalid
AND R3, R3, #0		; clear R3
ADD R3, R0, R3		; Place the second popped value into R3
JSR EXP			; do the power process
JSR PUSH			; push the value into the stack
BRnzp NEW_INPUT		; read next input

STACK_CHECK			
	JSR POP			; pop the value from the stack
	ADD R5, R5, #0		;
	BRp INVALID			; CHECK UNDERFLOW
	AND R5, R5, #0		; CLEAR R5
	ADD R5, R5, R0		; STORE THE FINAL RESULT INTO R5
	LD R3, STACK_TOP		; load the stack_top into R3
	LD R4, STACK_START	; load the stack_start into R4
	NOT R4, R4			;
	ADD R4, R4, #1		; inverse R4
	ADD R3, R3, R4		;
	BRnp INVALID		; if R3+ (-R4) is not 0, then it is invalid
	BRnzp PRINT_HEX		; if R3+ (-R4) is 0, then go to print_hex
	





; Add R3 to R4 and put it in R0
; (R0 = R3 + R4)
; input R3, R4
; out R0
PLUS	
	ADD R0, R3, R4
	RET

; Subtract R4 from R3
; (R0 = R3 - R4)
; input R3, R4
; out R0
MIN	
	NOT R4, R4
	ADD R4, R4, #1
	ADD R0, R4, R3
	RET
	
; multiply R3 by R4
; (R0 = R3 * R4)
; input R3, R4
; out R
MUL
	AND R0, R0, #0		; clear R0

	ADD R4, R4, #0		; copy R4
	BRn MUL_N_R4
	BRz MUL_Z_R4

MUL_P_R4
ADD R0, R0, R3		; increment R0 by R3
ADD R4, R4, #-1		; decrement R4 by 1	
	BRp MUL_P_R4		; keep looping if R4 is positive
	BRnzp DONE_MUL		; exit loop

MUL_N_R4
	ADD R0, R0, R3		; increment R0 by R3
ADD R4, R4, #1		; increment R4 by 1	
	BRn MUL_N_R4			; keep looping if R4 is negative
	NOT R0, R0			; negate R0
	ADD R0, R0, #1		; 
	BRnzp DONE_MUL		; exit loop

MUL_Z_R4
	BRnzp DONE_MUL		; if R4 is zero, R0 is zero

DONE_MUL
	RET
	


; divide R3 by R4
; (R0 = R3 / R4)
; input R3, R4
; out R
DIV	
	ADD R4, R4, #0		; set BR to R4
	BRz PRINT_INVALID		; if R4 is 0
	BRp ONE_POS		; if R4 is positive
	NOT R4, R4			; else
	ADD R4, R4, #1		; invert R4
	ADD R3, R3, #0		; set BR to R3
	BRp DIFF_SIGN		; if R3 is positive
BRz ZERO			; if R3 is 0
	NOT R3, R3			; else
	ADD R3, R3, #1		; invert R3
	BRnzp SAME_SIGN		; 

ONE_POS
	ADD R3, R3, #0		; set BR to R3
BRp SAME_SIGN		; if R3 is positive
NOT R3, R3		; else
	ADD R3, R3, #1		; invert R3
	BRnzp DIFF_SIGN		;
	
SAME_SIGN
	AND R0, R0, #0		; clear R0
	ADD R0, R0, #-1		;
NOT R4, R4			;
	ADD R4, R4, #1		; invert R4
DIV_AGAIN1
	ADD R0, R0, #1		; add R0 by 1
	ADD R3, R4, R3		; R3+(-R4)
	BRzp DIV_AGAIN1		; subtract again
	BRn DONE_DIV		;

DIFF_SIGN
	AND R0, R0, #0		; clear R0
	ADD R0, R0, #-1		;
NOT R4, R4			;
	ADD R4, R4, #1		; invert R4
DIV_AGAIN2
	ADD R0, R0, #1		; add R0 by 1
	ADD R3, R4, R3		; R3+(-R4)
	BRzp DIV_AGAIN2		; subtract again
	NOT R0, R0			;
	ADD R0, R0, #1		; invert R0
	BRn DONE_DIV		;
ZERO
	AND R0, R0, #0		; result is 0
BRnzp DONE_DIV		; finish
PRINT_INVALID
	LEA R0, INVALID_STRING	; print “Invalid Expression” 
	PUTS				; 

DONE_DIV 

	
	RET
	

	
	
	
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;input R3, R4
;out R0
EXP
	ST R5, EXP_SAVER5	; save R5
	ST R6, EXP_SAVER6	; save R6

ADD R0, R3, #0		; load R3 into R0
ADD R6, R4, #0		; set R5 as a counter
EXP_LOOP
ADD R6, R6, #-1		; decrement R5
BRz DONE_POWER		; jump out
ADD R5, R3, #0		; load R3 into R2 and use it as a counter
ADD R5, R5, #-1
ADD R2, R0, #0		; load R0 into R2
MUL_LOOP 
	ADD R0, R0, R2		;
	ADD R5, R5, #-1		; decrement R2
	BRp MUL_LOOP		;
	BRnz EXP_LOOP		;

DONE_POWER 

	LD R5, EXP_SAVER5	; restore R5
	LD R6, EXP_SAVER6	; restore R6
	RET

ASCII_ZERO		.FILL #48	;
ASCII_NINE		.FILL #57	;
ASCII_A		.FILL #65	;
ASCII_F		.FILL #70	;
ASCII_PLUS		.FILL #43	;
ASCII_MINUS		.FILL #45	;
ASCII_MULTIPLY	.FILL #42	;
ASCII_DIV		.FILL #47	;
ASCII_POWER	.FILL #94	;
ASCII_EQUAL	.FILL #61	;
ASCII_SPACE	.FILL #32	;


;IN:R0, OUT:R5 (0-success, 1-fail/overflow)
;R3: STACK_END R4: STACK_TOP
;
PUSH	
	ST R3, PUSH_SaveR3	;save R3
	ST R4, PUSH_SaveR4	;save R4
	AND R5, R5, #0		;
	LD R3, STACK_END	;
	LD R4, STACK_TOP	;
	ADD R3, R3, #-1		;
	NOT R3, R3		;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz OVERFLOW		;stack is full
	STR R0, R4, #0		;no overflow, store value in the stack
	ADD R4, R4, #-1		;move top of the stack
	ST R4, STACK_TOP	;store top of stack pointer
	BRnzp DONE_PUSH		;
OVERFLOW
	ADD R5, R5, #1		;
DONE_PUSH
	LD R3, PUSH_SaveR3	;
	LD R4, PUSH_SaveR4	;
	RET


PUSH_SaveR3	.BLKW #1	;
PUSH_SaveR4	.BLKW #1	;




;OUT: R0, OUT R5 (0-success, 1-fail/underflow)
;R3 STACK_START R4 STACK_TOP
;
POP	
	ST R3, POP_SaveR3	;save R3
	ST R4, POP_SaveR4	;save R3
	AND R5, R5, #0		;clear R5
	LD R3, STACK_START	;
	LD R4, STACK_TOP		;
	NOT R3, R3			;
	ADD R3, R3, #1		;
	ADD R3, R3, R4		;
	BRz UNDERFLOW		;
	ADD R4, R4, #1		;
	LDR R0, R4, #0		;
	ST R4, STACK_TOP		;
	BRnzp DONE_POP		;
UNDERFLOW
	ADD R5, R5, #1		;
DONE_POP
	LD R3, POP_SaveR3		;
	LD R4, POP_SaveR4		;
	RET



NUM_ZERO			.FILL #0	;
NUM_NINE			.FILL #9	;

POP_SaveR3	.BLKW #1		;
POP_SaveR4	.BLKW #1		;
EXP_SAVER5 .BLKW #1		;
EXP_SAVER6	 .BLKW #1		;
STACK_END	.FILL x3FF0		;
STACK_START	.FILL x4000	;
STACK_TOP		.FILL x4000	;

INVALID
	LEA R0, INVALID_STRING	;print “Invalid Expression”
	PUTS				;

OFFSET		.FILL #-48


INVALID_STRING	.STRINGZ "Invalid_Expression"	;







.END
