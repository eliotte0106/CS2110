.orig x0000

AND R1, R1, 0
ADD R1, R1, x0002
AND R2, R2, 0
ADD R2, R2, x0003

AND R7, R7, 0
ADD R7, R7, xffff ; set the CC to b100

LDSR R3, R1, R2

HALT

MYLABEL .fill x0015

.end

;; === post-conditions ===
;; R1 = x0002, R2 = x0003, R3 = x0015, R7 = xffff, CC = b001
