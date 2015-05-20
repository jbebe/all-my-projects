BITS 16
org 100h

BIGLOOP:
MOV     DX,0x1000          ; Number of times to repeat whole routine.
MOV     BX,1             ; Frequency value.
MOV     AL, 10110110B    ; The Magic Number (use this binary number only)
OUT     43H, AL          ; Send it to the initializing port 43H Timer 2.
NEXT_FREQUENCY:          ; This is were we will jump back to 2000 times.
push DX
;MOV     AX, BX           ; Move our Frequency value into AX.

MOV     AX, BX
MOV     CX, 0x5
MUL     CX
MOV     CX, BX
SHR     CX, 0x7
AND     AX, CX ; AX = (BX*5) & (BX>>7)
MOV     CX, AX

MOV     AX, BX
MOV     DX, 0x3
MUL     AX
MOV     DX, BX
SHR     DX, 0xA
AND     AX, DX ; CX = ((BX*3) & (BX>>10))

OR      AX, CX

pop DX

OUT     42H, AL          ; Send LSB to port 42H.
;MOV     AL, AH           ; Move MSB into AL  
;OUT     42H, AL          ; Send MSB to port 42H.
IN      AL, 61H          ; Get current value of port 61H.
OR      AL, 00000011B    ; OR AL to this value, forcing first two bits high.
OUT     61H, AL          ; Copy it to port 61H of the PPI Chip
                         ; to turn ON the speaker.
MOV     CX, 65535        ; Repeat loop 65535 times
DELAY_LOOP1:              ; Here is where we loop back too.
LOOP    DELAY_LOOP1       ; Jump repeatedly to DELAY_LOOP until CX = 0
MOV     CX, 65535        ; Repeat loop 65535 times
DELAY_LOOP2:              ; Here is where we loop back too.
LOOP    DELAY_LOOP2       ; Jump repeatedly to DELAY_LOOP until CX = 0
MOV     CX, 65535        ; Repeat loop 65535 times
DELAY_LOOP3:              ; Here is where we loop back too.
LOOP    DELAY_LOOP3       ; Jump repeatedly to DELAY_LOOP until CX = 0
MOV     CX, 65535        ; Repeat loop 65535 times
DELAY_LOOP4:              ; Here is where we loop back too.
LOOP    DELAY_LOOP4       ; Jump repeatedly to DELAY_LOOP until CX = 0
MOV     CX, 65535        ; Repeat loop 65535 times
DELAY_LOOP5:              ; Here is where we loop back too.
LOOP    DELAY_LOOP5       ; Jump repeatedly to DELAY_LOOP until CX = 0
MOV     CX, 65535        ; Repeat loop 65535 times
DELAY_LOOP6:              ; Here is where we loop back too.
LOOP    DELAY_LOOP6       ; Jump repeatedly to DELAY_LOOP until CX = 0



INC     BX               ; Incrementing the value of BX lowers 
                         ; the frequency each time we repeat the
                         ; whole routine
DEC     DX               ; Decrement repeat routine count
CMP     DX, 0            ; Is DX (repeat count) = to 0
JNZ     NEXT_FREQUENCY   ; If not jump to NEXT_FREQUENCY
                         ; and do whole routine again.
                         ; Else DX = 0 time to turn speaker OFF
IN      AL,61H           ; Get current value of port 61H.
AND     AL,11111100B     ; AND AL to this value, forcing first two bits low.
OUT     61H,AL           ; Copy it to port 61H of the PPI Chip
                         ; to
;hlt
jmp BIGLOOP

times 510 - ($-$$) db 0
db 0x55, 0xaa