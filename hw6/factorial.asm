;;=============================================================
;;  CS 2110 - Summer 2022
;;  Homework 6 - Factorial
;;=============================================================
;;  Name: JP
;;============================================================

;;  In this file, you must implement the 'MULTIPLY' and 'FACTORIAL' subroutines.

;;  Little reminder from your friendly neighborhood 2110 TA staff: don't run
;;  this directly by pressing 'Run' in complx, since there is nothing put at
;;  address x3000. Instead, call the subroutine by doing the following steps:
;;      * 'Debug' -> 'Simulate Subroutine Call'
;;      * Call the subroutine at the 'MULTIPLY' or 'FACTORIAL' labels
;;      * Add the [a, b] or [n] params separated by a comma (,) 
;;        (e.g. 3, 5 for 'MULTIPLY' or 6 for 'FACTORIAL')
;;      * Proceed to run, step, add breakpoints, etc.
;;      * Remember R6 should point at the return value after a subroutine
;;        returns. So if you run the program and then go to 
;;        'View' -> 'Goto Address' -> 'R6 Value', you should find your result
;;        from the subroutine there (e.g. 3 * 5 = 15 or 6! = 720)

;;  If you would like to setup a replay string (trace an autograder error),
;;  go to 'Test' -> 'Setup Replay String' -> paste the string (everything
;;  between the apostrophes (')) excluding the initial " b' ". If you are 
;;  using the Docker container, you may need to use the clipboard (found
;;  on the left panel) first to transfer your local copied string over.

.orig x3000
    ;; You do not need to write anything here
    HALT

;;  MULTIPLY Pseudocode (see PDF for explanation and examples)   
;;  
;;  MULTIPLY(int a, int b) {
;;      int ret = 0;
;;      while (b > 0) {
;;          ret += a;
;;          b--;
;;      }
;;      return ret;
;;  }

MULTIPLY ;; Do not change this label! Treat this as like the name of the function in a function header
    ;; Code your implementation for the MULTIPLY subroutine here!

    ;;stack setup
    ADD R6, R6, -4 ;make room for RV, RA, old FP, and 1 local
    STR R7, R6, 2 ;save RA
    STR R5, R6, 1 ;R5 as old FP
    ADD R5, R6, 0 ;FP = SP
    ADD R6, R6, -5 ;make room for saving registers
    STR R0, R5, -1
    STR R1, R5, -2
    STR R2, R5, -3
    STR R3, R5, -4
    STR R4, R5, -5

    ;body
    AND R0, R0, 0 ;R0 = 0
    STR R0, R5, 0 ;ret = R0
    WHILE LDR R0, R5, 5 ;R0 = b
    BRnz ENDWHILE
    LDR R0, R5, 0 ;R0 = ret
    LDR R1, R5, 4 ;R1 = a
    ADD R0, R0, R1 ;R0 = ret + a
    STR R0, R5, 0 ;ret = R0
    LDR R0, R5, 5 ;R0 = b
    ADD R0, R0, -1 ;b -= 1
    STR R0, R5, 5 ;R0 = b
    BR WHILE

    ENDWHILE
    LDR R0, R5, 0 ;R0 = ret
    STR R0, R5, 3 ;set ret val to answer

    ;stack teardown
    LDR R4, R5, -5
    LDR R3, R5, -4
    LDR R2, R5, -3
    LDR R1, R5, -2
    LDR R0, R5, -1
    ADD R6, R5, 0 ;reset SP to FP
    LDR R5, R6, 1 ;restore old FP
    LDR R7, R6, 2 ;retrieve original RA
    ADD R6, R6, 3 ;pop past local variables, old FP, and RA -- R6 points to RV now
    RET

;;  FACTORIAL Pseudocode (see PDF for explanation and examples)
;;
;;  FACTORIAL(int n) {
;;      int ret = 1;
;;      for (int x = 2; x <= n; x++) {
;;          ret = MULTIPLY(ret, x);
;;      }
;;      return ret;
;;  }

FACTORIAL ;; Do not change this label! Treat this as like the name of the function in a function header
    ;; Code your implementation for the FACTORIAL subroutine here!
    
    ;;stack setup
    ADD R6, R6, -4 ;make room for RV, RA, old FP, and 1 local(ret)
    STR R7, R6, 2 ;save RA
    STR R5, R6, 1 ;R5 as old FP
    ADD R5, R6, 0 ;FP = SP
    ADD R6, R6, -6 ;make room for saving registers + 1 local(x)
    STR R0, R5, -2
    STR R1, R5, -3
    STR R2, R5, -4
    STR R3, R5, -5
    STR R4, R5, -6

    ;body
    AND R0, R0, 0 ;ret = 0
    ADD R0, R0, 1 ;ret = 1
    STR R0, R5, 0 ;ret = R0
    AND R1, R1, 0 ;x = 0
    ADD R1, R1, 2 ;x = 2
    STR R1, R5, -1 ;x = R1

    WHILE1
    LDR R2, R5, 4 ;n
    NOT R2, R2
    ADD R2, R2, 1 ;n = -n
    LDR R1, R5, -1 ;get x
    ADD R2, R1, R2
    BRp END1 ;if x > n, go to END1

    LDR R0, R5, 0
    LDR R1, R5, -1
    ADD R6, R6, -2 ;push
    STR R0, R6, 0 ;ret
    STR R1, R6, 1 ;x
    ;ADD R6, R6, -1
    ;LDR R0, R5, -1
    ;STR R0, R6, 0
    ;ADD R6, R6, -1
    ;LDR R0, R5, 0
    ;STR R0, R6, 0
    JSR MULTIPLY
    LDR R0, R6, 0 ;R0 = MULTIPLY(ret, x)
    ADD R6, R6, 2 ;pop
    STR R0, R5, 0 ;ret = R0
    ;LDR R1, R5, -1 ;x
    ADD R1, R1, 1 ;x += 1
    STR R1, R5, -1 ;x = R1
    BR WHILE1

    END1
    LDR R0, R5, 0
    STR R0, R5, 3

    ;stack teardown
    LDR R4, R5, -6
    LDR R3, R5, -5
    LDR R2, R5, -4
    LDR R1, R5, -3
    LDR R0, R5, -2
    ADD R6, R5, 0 ;reset SP to FP
    LDR R5, R6, 1 ;restore old FP
    LDR R7, R6, 2 ;retrieve original RA
    ADD R6, R6, 3 ;pop past local variables, old FP, and RA -- R6 points to RV now
    RET

;; Needed to Simulate Subroutine Call in Complx
STACK .fill xF000
.end