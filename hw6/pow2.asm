;; In this file, you must implement the 'pow2' subroutine.
;; Little reminder from your friendly neighborhood 2110 TA staff:
;; don't run this directly by pressing 'RUN' in Complx, since there is nothing
;; put at address x3000. Instead, load it and use 'Debug' -> 'Simulate
;; Subroutine Call' and choose the 'pow2' label.
.orig x3000
HALT
pow2
;; See the PDF for more information on what this subroutine should do.
;;
;; Arguments of pow2: integer n
;;   you may assume n is always 0 or positive
;;
;; Pseudocode:
;; pow2(int n) {
;;     if (n == 0) {
;;         return 1;
;;     }
;;     return 2 * pow2(n-1);
;; }
;; STACK BUILD UP
    
ADD R6, R6, -4 ; allocate RV space, save RA, save old FP, alocate local variable 
space
STR R5, R6, 1  ; save old FP
STR R7, R6, 2  ; save RA
ADD R5, R6, 0  ; update FP to point at first local variable
ADD R6, R6, -5 ; save register state
STR R0, R6, 4
STR R1, R6, 3
STR R2, R6, 2
STR R3, R6, 1
STR R4, R6, 0
;; BODY OF SUBROUTINE
;; EXTRACT ARGS
LDR R0, R5, 4      ; R0 = n
;; BASE CASE
BRnp pow2recursion ; if n != 0, then go to recursion
ADD R1, R0, #1     ; R1 = 1 (because we know R0 is 0 at this point)
BRnzp pow2return   ; go to return (skip over recursion)
;; RECURSIVE CASE
pow2recursion
ADD R0, R0, -1     ; R1 = n-1
ADD R6, R6, -1     ; allocate space for argument
STR R0, R6, 0      ; push n-1 to stack
JSR pow2           ; call pow2(n-1)
LDR R2, R6, 0      ; retrieve RV from stack
ADD R6, R6, 2      ; deallocate space for RV and arg
ADD R1, R2, R2     ; R1 = 2 * R2 = 2*pow2(n-1)
;; STORE RETURN VALUE
pow2return
STR R1, R5, 3      ; store result into allocated RV space
;; STACK TEAR DOWN
LDR R4, R6, 0 ; restore register state
LDR R3, R6, 1
LDR R2, R6, 2
LDR R1, R6, 3
LDR R0, R6, 4
ADD R6, R5, 0 ; reset SP to FP
LDR R5, R6, 1 ; restore old FP
LDR R7, R6, 2 ; retrieve original RA
ADD R6, R6, 3 ; pop past local variables, old FP, and RA -- R6 points to RV now
RET
; Needed by Simulate Subroutine Call in Complx
STACK .fill xF000
.end
