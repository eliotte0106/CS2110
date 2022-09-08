.orig x0000

AND R1, R1, 0
ADD R1, R1, x0006

AND R2, R2, 0
ADD R2, R2, x0008

AND R7, R7, 0
ADD R7, R7, xffff ; set the CC to b100

STR R2, R1, 0
STR R2, R1, 1

HALT

.fill x0000
.fill x0000

.end

;; === post-conditions ===
;; R1: x0004, R2: x0008, R7 = xffff, MEM[x0006] = x0008, MEM[x0007] = x0008, CC = b100
