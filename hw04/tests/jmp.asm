.orig x0000

AND R0, R0, 0
ADD R0, R0, x0004

AND R7, R7, 0
ADD R7, R7, xffff ; set the CC to 0b100

JMP R0

HALT

HALT

.end

;; === post-conditions ===
;; R0 = x0004, R7 = xffff, PC = x0005, CC = b100
