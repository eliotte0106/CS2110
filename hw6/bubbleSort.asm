;;=============================================================
;;  CS 2110 - Summer 2022
;;  Homework 6 - Bubble Sort
;;=============================================================
;;  Name: JP
;;============================================================

;;  In this file, you must implement the 'BUBBLE_SORT' subroutine.

;;  Little reminder from your friendly neighborhood 2110 TA staff: don't run
;;  this directly by pressing 'Run' in complx, since there is nothing put at
;;  address x3000. Instead, call the subroutine by doing the following steps:
;;      * 'Debug' -> 'Simulate Subroutine Call'
;;      * Call the subroutine at the 'BUBBLE_SORT' label
;;      * Add the [arr (addr), length] params separated by a comma (,) 
;;        (e.g. x4000, 5)
;;      * Proceed to run, step, add breakpoints, etc.
;;      * BUBBLE_SORT is an in-place algorithm, so if you go to the address
;;        of the array by going to 'View' -> 'Goto Address' -> 'Address of
;;        the Array', you should see the array (at x4000) successfully 
;;        sorted after running the program (e.g [2,3,1,1,6] -> [1,1,2,3,6])

;;  If you would like to setup a replay string (trace an autograder error),
;;  go to 'Test' -> 'Setup Replay String' -> paste the string (everything
;;  between the apostrophes (')) excluding the initial " b' ". If you are 
;;  using the Docker container, you may need to use the clipboard (found
;;  on the left panel) first to transfer your local copied string over.

.orig x3000
    ;; You do not need to write anything here
    HALT

;;  BUBBLE_SORT Pseudocode (see PDF for explanation and examples)
;; 
;;  BUBBLE_SORT(int[] arr (addr), int length) {
;;      int swapped = 0;
;;      for (int i = 0; i < length - 1; i++) {
;;          if (arr[i] > arr[i + 1]) {
;;              int temp = arr[i + 1];
;;              arr[i + 1] = arr[i];
;;              arr[i] = temp;
;;              swapped = 1;
;;          }
;;      }
;;      if (swapped == 1) {
;;          BUBBLE_SORT(arr, length - 1);
;;      }
;;      return;
;;  }

BUBBLE_SORT ;; Do not change this label! Treat this as like the name of the function in a function header
    ;; Code your implementation for the BUBBLE_SORT subroutine here!
   ;;stack setup
    ADD R6, R6, -4 ;make room for RV, RA, old FP, and 1 local
    STR R7, R6, 2 ;save RA
    STR R5, R6, 1 ;R5 as old FP
    ADD R5, R6, 0 ;FP = SP
    ADD R6, R6, -6 ;make room for saving registers + 1 local variable
    STR R0, R5, -2
    STR R1, R5, -3
    STR R2, R5, -4
    STR R3, R5, -5
    STR R4, R5, -6

    ;body
    LDR R0, R5, 5 ;R1 = length
    ADD R0, R0, -1 ; length = length -= 1
    STR R0, R5, 5; length
    AND R1, R1, 0 ;i = 0
    STR R1, R5, -1 ;i = R1

    WHILE
    LDR R1, R5, -1 ;i
    LDR R0, R5, 5 ;length
    NOT R0, R0
    ADD R0, R0, 1 ;-length
    ADD R0, R1, R0
    BRzp ENDWHILE ;if i >= length, go to endwhile

    LDR R0, R5, 4 ;addr of array
    ADD R0, R0, R1 ; addr of array[i]
    LDR R3, R0, 0; array[i] ;dont need this part
    LDR R4, R0, 1 ;array[i+1]

    NOT R1, R4
    ADD R1, R1, 1 ;-array[i+1]
    ADD R1, R3, R1
    BRnz WHILECONT

    LDR R1, R0, 0
    STR R1, R5, 0 ;temp = array[i] 

    LDR R1, R0, 1
    STR R1, R0, 0 ;array[i] = array[i+1]

    LDR R1, R5, 0
    STR R1, R0, 1 ;array[i+1] = temp
    
    AND R2, R2, 0
    ADD R2, R2, 1 ;swapped = 1
    BR WHILE

    WHILECONT
    LDR R0, R5, -1
    ADD R0, R0, 1
    STR R0, R5, -1 ; i++
    BR WHILE

    ENDWHILE
    ADD R2, R2, -1
    BRnp TEAR ;if swapped != 1, go to TEAR

    LDR R0, R5, 4;ARR
    LDR R1, R5, 5;length
    ADD R6, R6, -2 ;push
    STR R0, R6, 0
    STR R1, R6, 1
    JSR BUBBLE_SORT

    TEAR
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

.orig x4000	;; Array : You can change these values for debugging!
    .fill 2
    .fill 3
    .fill 1
    .fill 1
    .fill 6
.end