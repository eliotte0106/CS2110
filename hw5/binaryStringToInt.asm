;;=============================================================
;; CS 2110 - Summer 2022
;; Homework 5 - binaryStringToInt
;;=============================================================
;; Name: JP
;;=============================================================

;;  Pseudocode (see PDF for explanation)
;;
;;  String binaryString = "00010101"; (sample binary string)
;;  int length = 8; (sample length of the above binary string)
;;  int base = 1;
;;  int value = 0;
;;  int i = length - 1;
;;  while (i >= 0) {
;;      int x = binaryString[i] - 48;
;;      if (x == 1) {
;;          value += base;
;;      }     
;;      base += base;
;;      i--;
;;  }
;;  mem[mem[RESULTIDX]] = value;

.orig x3000
    ;; YOUR CODE HERE
    LD R0, LENGTH ;LENGTH
    ADD R0, R0, #-1 ;i = LENGTH - 1
    AND R1, R1, #0 ;base
    ADD R1, R1, #1
    AND R2, R2, #0 ;value

    WHILE ADD R0, R0, #0
    BRn END ; if i < 0, go to end

    LD R4, BINARYSTRING ;R4 = mem_addr of BINARYSTRING[0]
    ADD R4, R4, R0 ;R4 = mem_addr of BINARYSTRING[i]
    LDR R4, R4, #0 ;R4 = BINARYSTRING[i]
    ADD R4, R4, #-16 ; x = R4 = BINARYSTRING[i] - 48
    ADD R4, R4, #-16 ; ^
    ADD R4, R4, #-16 ; ^
    ADD R4, R4, #-1
    BRnp WHILECONT ; if x!= 1, go to whilecont
    ADD R2, R1, R2 ; if x == 1, value += base
    BR WHILECONT

    WHILECONT
    ADD R1, R1, R1 ;base += base
    ADD R0, R0, #-1 ; i -= 1
    BR WHILE

    END
    STI R2, RESULTIDX

    HALT

BINARYSTRING    .fill x5000
LENGTH          .fill 8
RESULTIDX       .fill x4000
.end

.orig x5000
    .stringz "00010101"        ;; You can change this string for debugging!
.end