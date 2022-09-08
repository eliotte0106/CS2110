;;=============================================================
;; CS 2110 - Summer 2022
;; Homework 5 - summation
;;=============================================================
;; Name: JP
;;=============================================================

;;  Pseudocode (see PDF for explanation)
;;
;;  int x = 6; (sample integer)
;;  int sum = 0;
;;  while (x > 0) {
;;      sum += x;
;;      x--;
;;  }
;;  mem[ANSWER] = sum;

.orig x3000
    ;; YOUR CODE HERE
    LD R3, x ; R3 = x
    AND R1, R1, #0 ; sum = 0
    ADD R3, R3, #0
    BRnz END
    
    WHILE ADD R3, R3, #0;check condition
    BRnz END
    ADD R1, R1, R3
    ADD R3, R3, #-1
    BR WHILE
    
    END
    ST R1, ANSWER
    
    HALT

    x      .fill 6      ;; You can change this value for debugging!
    ANSWER .blkw 1
.end