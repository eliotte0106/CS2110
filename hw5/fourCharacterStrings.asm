;;=============================================================
;; CS 2110 - Summer 2022
;; Homework 5 - fourCharacterStrings
;;=============================================================
;; Name: JP
;;=============================================================

;; 	Pseudocode (see PDF for explanation)
;;
;; 	int count = 0; (keep count of number of 4-letter words)
;; 	int chars = 0; (keep track of length of each word)
;; 	int i = 0; (indexer into each word)
;; 	String str = "I love CS 2110 and assembly is very fun! "; (sample string)
;;  while(str[i] != '\0') {
;;		if (str[i] != ' ')  {
;;			chars++;
;;		}
;;		else {
;;			if (chars == 4) {
;;				count++;   
;			}
;;			chars = 0;
;;		}
;;		i++;
;;	}
;;	mem[ANSWER] = count;
;;
;; ***IMPORTANT***
;; - Assume that all strings provided will end with a space (' ').
;; - Special characters do not have to be treated differently. For instance, strings like "it's" and "But," are considered 4 character strings.

.orig x3000
	;; YOUR CODE HERE
	
	AND R0, R0, #0 ;i = 0
	AND R1, R1, #0 ;count = 0
	AND R2, R2, #0 ;chars = 0

	WHILE LD R3, STRING ; R3 = mem_addr of string[0]
	ADD R3, R3, R0 ;R3 = mem_addr of string[i] 
	LDR R3, R3, #0 ;R3 = string[i]
	NOT R3, R3 
	ADD R3, R3, #1 ;R3 = -R3
	ADD R3, R3, #0 ;
	BRz END ; if string[i] = \0, go to end

	LD R4, SPACE ;R4 = SPACE(-31)
	NOT R4, R4
	ADD R4, R4, #1 ; R3 = -R3
	ADD R4, R3, R4 ;R4 = string[i] + space
	BRz ELSE ;if string[i] == space, go to else

	ADD R2, R2, #1 ;chars += 1
	BR WHILECONT ;go to whilecont
	
	ELSE AND R5, R5, #0
	NOT R5, R2
	ADD R5, R5, #1
	ADD R5, R5, #4 ; R5 = chars + 4
	BRnp ELSECONT ; if chars != 4, go to elsecont
	ADD R1, R1, #1 ;count += 1
	BR ELSECONT ;go to elsecont

	ELSECONT AND R2, R2, #0 ;set chars = 0
	BR WHILECONT ;go to whilecont

	WHILECONT ADD R0, R0, #1 ;i += 1
	BR WHILE

	END
	ST R1, ANSWER
	HALT

SPACE 	.fill #-32
STRING	.fill x4000
ANSWER 	.blkw 1
.end

.orig x4000
	.stringz "I love CS 2110 and assembly is very fun! " ;; You can change this string for debugging!
.end