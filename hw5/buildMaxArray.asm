;;=============================================================
;; CS 2110 - Summer 2022
;; Homework 5 - buildMaxArray
;;=============================================================
;; Name: JP
;;=============================================================

;; 	Pseudocode (see PDF for explanation)
;;
;;	int A[] = {-4, 2, 6}; (sample array)
;;	int B[] = {4, 7, -2}; (sample array)
;;	int C[3]; (sample array)
;;	int length = 3; (sample length of above arrays)
;;
;;	int i = 0;
;;	while (i < length) {
;;		if (A[i] < B[i]) {
;;			C[i] = B[i];
;;		}
;;		else {
;;			C[i] = A[i];
;;		}
;;		i++;
;;	}

.orig x3000
	;; YOUR CODE HERE
	LD R1, LENGTH ; R1 = LENGTH

	AND R0, R0, #0 ;i = 0
	ADD R0, R0, #0
	AND R2, R2, #0 ;i counter
	NOT R1, R1
	ADD R1, R1, #1
	
	WHILE ADD R2, R0, R1 ;while i < length
	BRzp END ;end while
	LD R3, A ;R3 = mem_addr of A[0]
	LD R4, B ;R4 = mem_addr of B[0]
	ADD R3, R3, R0 ;ADDRESS OF A[I]
	LDR R3, R3, #0 ;R3 = A[I]
	ADD R4, R4, R0 ;ADDRESS OF B[I]
	LDR R4, R4, #0 ;R4 = B[I]

	;if a[i] < b[i]
	NOT R5, R4
	ADD R5, R5, #1
	ADD R5, R3, R5
	BRzp ELSE ;else

	LD R6, C
	ADD R6, R6, R0
	STR R4, R6, #0 ;c[i] = b[i]
	BR WHILECONT

	ELSE
	LD R6, C
	ADD R6, R6, R0
	STR R3, R6, #0 ;else c[i] = a[i]
	BR WHILECONT

	WHILECONT
	ADD R0, R0, #1 ;i++

	BR WHILE
	
	END
	HALT

A 		.fill x3200
B 		.fill x3300
C 		.fill x3400
LENGTH 	.fill 3
.end

.orig x3200				;; Array A : You can change these values for debugging!
	.fill -4
	.fill 2
	.fill 6
.end

.orig x3300				;; Array B : You can change these values for debugging!
	.fill 4
	.fill 7
	.fill -2
.end

.orig x3400
	.blkw 3				;; Array C : Make sure to increase block size if you add more values to Arrays A and B!
.end