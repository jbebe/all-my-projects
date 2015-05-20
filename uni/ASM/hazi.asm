;****************************************************************************** 
;* Feladat: LCD hirdetõtábla scrollozó szöveggel                              ;
;* Rövid leírás:                                                              ;
;                Memóriából vett karaktersorozat megjelenítése                ;
;                az LCD kijelzõn, fix sebességgel történõ oldalra léptetés.   ;
;                Figyelni kell arra, hogy a karaktersorozat hosszabb és       ;
;                és rövidebb is lehet mint a kijelzõ mérete!                  ;
;                Hw: timer, LCD, SRAM                                         ;
;* Szerzõk: Juhász Bálint, Gyurácz Kristóf                                    ;
;* Mérõcsoport: CDE17                                                         ;
;******************************************************************************

;******************************************************************************
; Macros
.macro fldi ; force ldi on r0 ... r15, using: fldi r1, 0xff
    push temp
    ldi temp, @1
    mov @0, temp
    pop temp
.endmacro

.macro wldi ; load 16 bit (WORD) address, using: ldi16 Z, 0xffff
    ldi @0L, low (@1)
    ldi @0H, high(@1)
.endmacro

.include "m128def.inc" ; Definition file for ATmega128 

;* Program Constants 
.equ const         = $00         ; Generic Constant Structure example  

; Personal definitions
.equ BUFFER_LENGTH_C = 20        ; tömb inicializálásához konstans méret
.equ timer_const   = 2700        ; 10800 / 5400 / 2700 / 1350

.def ZERO          = r5          ; ne kelljen immediate utasításokat hívni
.def BUFFER_LENGTH = r6          ; A buffer hossza
.def TEXT_LENGTH   = r7          ; A szöveg hossza
.def textIndex     = r8          ; MAIN_LOOP-ban ez iterál végig a szövegen
.def newSecond     = r9          ; az új másodperc
;                  = r10         ; free
;                  = ...         ; free
;                  = r15         ; free
.def temp          = r16         ; Temporary Register 
;                  = r17         ; used locally
;                  = ...         ; used locally?
;                  = r26         ; XL stb..

;*************************************************************** 
;* Reset & Interrupt Vectors  
.cseg 
.org $0000 ; Define start of Code segment 
    jmp RESET ; Reset Handler, jmp is 2 word instruction 
    jmp DUMMY_IT    ; Ext. INT0 Handler
    jmp DUMMY_IT    ; Ext. INT1 Handler
    jmp DUMMY_IT    ; Ext. INT2 Handler
    jmp DUMMY_IT    ; Ext. INT3 Handler
    jmp DUMMY_IT    ; Ext. INT4 Handler (INT gomb)
    jmp DUMMY_IT    ; Ext. INT5 Handler
    jmp DUMMY_IT    ; Ext. INT6 Handler
    jmp DUMMY_IT    ; Ext. INT7 Handler
    jmp DUMMY_IT    ; Timer2 Compare Match Handler 
    jmp DUMMY_IT    ; Timer2 Overflow Handler 
    jmp DUMMY_IT    ; Timer1 Capture Event Handler 
    jmp T1CM_IT     ; Timer1 Compare Match A Handler 
    jmp DUMMY_IT    ; Timer1 Compare Match B Handler 
    jmp DUMMY_IT    ; Timer1 Overflow Handler 
    jmp DUMMY_IT    ; Timer0 Compare Match Handler 
    jmp DUMMY_IT    ; Timer0 Overflow Handler 
    jmp DUMMY_IT    ; SPI Transfer Complete Handler 
    jmp DUMMY_IT    ; USART0 RX Complete Handler 
    jmp DUMMY_IT    ; USART0 Data Register Empty Hanlder 
    jmp DUMMY_IT    ; USART0 TX Complete Handler 
    jmp DUMMY_IT    ; ADC Conversion Complete Handler 
    jmp DUMMY_IT    ; EEPROM Ready Hanlder 
    jmp DUMMY_IT    ; Analog Comparator Handler 
    jmp DUMMY_IT    ; Timer1 Compare Match C Handler 
    jmp DUMMY_IT    ; Timer3 Capture Event Handler 
    jmp DUMMY_IT    ; Timer3 Compare Match A Handler 
    jmp DUMMY_IT    ; Timer3 Compare Match B Handler 
    jmp DUMMY_IT    ; Timer3 Compare Match C Handler 
    jmp DUMMY_IT    ; Timer3 Overflow Handler 
    jmp DUMMY_IT    ; USART1 RX Complete Handler 
    jmp DUMMY_IT    ; USART1 Data Register Empty Hanlder 
    jmp DUMMY_IT    ; USART1 TX Complete Handler 
    jmp DUMMY_IT    ; Two-wire Serial Interface Handler 
    jmp DUMMY_IT    ; Store Program Memory Ready Handler 

.org $0046

;****************************************************************
;* DUMMY_IT interrupt handler -- CPU hangup with LED pattern
;* (This way unhandled interrupts will be noticed)

DUMMY_IT:   
    ldi r16,   0xFF ; LED pattern:  *-
    out DDRC,  r16  ;               -*
    ldi r16,   0xA5 ;               *-
    out PORTC, r16  ;               -*
DUMMY_LOOP:
    rjmp DUMMY_LOOP ; endless loop

;*************************************************************** 
;* MAIN program, Initialization part
.org $004B;

RESET: 
;* Stack Pointer init, 
;  Set stack pointer to top of RAM 
    ldi temp, LOW(RAMEND)        ; RAMEND = "max address in RAM"
    out SPL,  temp               ; RAMEND value in "m128def.inc" 
    ldi temp, HIGH(RAMEND) 
    out SPH,  temp 

INIT:
    ; init personal 
    eor  temp, temp
    eor  zero, zero
    mov  textIndex, zero
    fldi BUFFER_LENGTH, BUFFER_LENGTH_C ; buffernek megadjuk a konstans paramétert

    fldi TEXT_LENGTH, (text_end-text-1)<<1; megelõlegezzük a 0 0 padding-ot
    wldi Z, (text_end-1)<<1      ; de azért kipróbáljuk hátha nincs padding
    lpm temp, Z                  ; text_end elõtti WORD elsõ BYTE-ját nézzük
    cp temp, ZERO                ; temp = 0 ?
    breq TEXT_PADDING_ON         ; ha igen akkor igazunk volt, 0 0 padding van
    fldi TEXT_LENGTH, ((text_end-text)<<1)-1 ; hoppá, nincs padding!
TEXT_PADDING_ON:

    call LCD_INIT                ; LCD inicializálása
    call LCD_CURSOR_OFF          ; letiltjuk a kurzort
	ldi temp, 0xff               ;
	out DDRB,  temp              ; 
    ldi r16,   0x20              ;
    out PORTB, temp              ; megvilágítjuk a kijelzõt

    ; init timer
    ldi temp, 0b00000000         ; CTC mód és 1024 elõosztás
    out TCCR1A, temp
    ldi temp, 0b00001101
    out TCCR1B, temp
    ldi temp, HIGH(timer_const)
    out OCR1AH, temp
    ldi temp, LOW(timer_const)
    out OCR1AL, temp
    ldi temp, 0                  ; nullázzuk a 16 bites számlálót
    out TCNT1H, temp
    out TCNT1L, temp
    ldi temp, 0b00010000         ; megszakítás, ha TCNT == OCR
    out TIMSK, temp
    eor temp, temp
    mov newSecond, temp          ; newSecond = 0
    sei                          ; globális IT engedélyezése

;*************************************************************** 
;* MAIN program, Endless loop part
 
MAIN_LOOP:
    cp newSecond, ZERO          
    breq MAIN_LOOP               ; ha newSecond = 0 akkor nincs mit tenni
    cli                          ; ha mégis megnõtt, elõször letiltjuk az 
                                 ; interruptot és reménykedünk, hogy negyed 
                                 ; másodperc alatt lefut ez a pár sor kód
                                 ; erre azért van szükség mert az interrupt 
                                 ; szubrutin most rövid, ezért 
                                 ; nem akarjuk hogy belepiszkáljon a kódunkba
    eor newSecond, newSecond     ; viszont ha newSecond != 0 akkor lenullázzuk 
                                 ; és újra várunk hogy növelõdjön
    call SCROLL                  ; scrollozás
    call DISPLAY                 ; kiírás
    
    inc textIndex                ; textIndex-et mindig növelni kell, 
                                 ; ezért a branching elõtt áll
    
    cp TEXT_LENGTH, BUFFER_LENGTH; összehasonlítjuk a szöveg és a buffer hosszát
    brsh MAIN_LOOP_BUFFER_SHORTER; ha a buffer kisebb, ezt máshogy kezeljük le

    cp textIndex, BUFFER_LENGTH  ; megnézzük textIndex == BUFFER_LENGTH
    in temp, SREG                ; SREG -> regiszterbe
    sbrc temp, 1                 ; megnézzük ZERO flag üres-e. ha igen, ugrás
    eor textIndex, textIndex     ; ZERO flag 1, tehát ha textIndex ugyanakkora,
                                 ; mint a BUFFER_LENGTH, lenullázzuk
    jmp MAIN_LOOP_END

MAIN_LOOP_BUFFER_SHORTER:
    cp textIndex, TEXT_LENGTH    ; lásd 8 sorral feljebb
    in temp, SREG                ;
    sbrc temp, 1                 ;
    eor textIndex, textIndex     ;
MAIN_LOOP_END:
    sei                          ; újra engedélyezzük az interruptot
    jmp MAIN_LOOP

;*************************************************************** 
;* Subroutines, Interrupt routines

T1CM_IT:
    inc newSecond                ; megnöveljük newSecond-öt. 
    reti                         ; ami igazából annyi, hogy ne 0 legyen
    
MOD_INPUT:                       ; *_LENGTH-et temp-be rakjuk
    cp inputMod, temp            ; összehasonlítjuk inputMod-ot és temp-et
    brlo MOD_INPUT_END           ; ha inputMod kisebb akkor nincs mit csinálni
    sub inputMod, temp           ; ha inputMod >= temp akkor kivonjuk belõle
    jmp MOD_INPUT                ; és megnézzük mégegyszer
MOD_INPUT_END:
    ret

; A buffer scrollozó szubrutin
SCROLL:
.def iterator = r17              ; iterátor a buffer elejétõl a végéig
.def inputMod = r18              ; az iterátorból képzett offset a text-hez
.def spaceLetter = r19           ; ez tárolja a space(32) értéket
    eor iterator, iterator
    ldi spaceLetter, ' '
SCROLL_LOOP:
    cp iterator, BUFFER_LENGTH   ; összehasonlítjuk az iterátort és buffer-t
    breq SCROLL_END              ; ha az iterátor a végére ért, exit

    mov inputMod, iterator       ; minden esetben az inputMod = iterator
    add inputMod, textIndex      ; hozzáadjuk az iterátorhoz az aktuális indexet
                                 ; helyesebben inputMod = textIndex 
                                 ; és ahhoz képest az offszet az iterator
    cp TEXT_LENGTH, BUFFER_LENGTH; összehasonlítjuk a szöveg és a buffer hosszát
    brsh SCROLL_LOOP_LONGER      ; ha a szöveg hosszabb, ugrunk
    
    mov temp, BUFFER_LENGTH      ; temp = BUFFER_LENGTH
    call MOD_INPUT               ; inputMod %= BUFFER_LENGTH

    cp inputMod, TEXT_LENGTH
    brlo SCROLL_LOOP_SHORTER_NOTEMPTY ; ha inputMod kisebb mint TEXT_LENGTH,
                                 ; még írhatunk ki a szövegbõl, nem kell a space

    wldi Z, buffer               ; Z = buffer:buffer
    add ZL, iterator             ; hozzáadjuk iterátort Z-hez
                                 ; ezzel adunk offszetet a pointerünknek
    adc ZH, ZERO                 ; felsõ byte-hoz hozzáadjuk a carry-t
    st  Z,  spaceLetter          ; eltároljuk Z helyén a space-t
    jmp SCROLL_LOOP_POST

SCROLL_LOOP_SHORTER_NOTEMPTY:
    wldi Z, text << 1            ; Z = text:text
    add ZL, inputMod             ; hozzáadjuk Z-hez az inputMod-ot
    adc ZH, ZERO                 ; felsõ byte-hoz carry
    lpm temp, Z                  ; most hogy Z kész, kiolvassuk *Z értékét
    
    wldi Z, buffer               ; Z = buffer:buffer
    add ZL, iterator             ; hozzáadunk iterátort Z-hez
    adc ZH, ZERO                 ; felsõ byte-hoz hozzáadjuk a carry-t
    st  Z,  temp                 ; eltároljuk Z helyén a temp értékét

    jmp SCROLL_LOOP_POST

SCROLL_LOOP_LONGER:
    mov temp, TEXT_LENGTH
    call MOD_INPUT

    wldi Z, text << 1            ; Z = text:text 
    add ZL, inputMod             ; hozzáadjuk Z-hez az inputMod-ot
    adc ZH, ZERO                 ; felsõ byte-hoz carry
    lpm temp, Z                  ; most hogy Z kész, kiolvassuk *Z értékét

    wldi Z, buffer               ; Z = buffer:buffer
    add ZL, iterator             ; hozzáadunk iterátort Z-hez
    adc ZH, ZERO                 ; felsõ byte-hoz hozzáadjuk a carry-t
    st  Z,  temp                 ; eltároljuk Z helyén a *(text+inputMod)-t

SCROLL_LOOP_POST:
    inc iterator                 ; növeljük iterator-t. (BUFFER_LENGTH-ig megy)
    jmp SCROLL_LOOP

SCROLL_END:
    wldi Z, buffer               ; Z = buffer:buffer
    add ZL, BUFFER_LENGTH        ; hozzáadunk BUFFER_LENGTH méretet
    adc ZH, ZERO                 ; felsõ byte-hoz hozzáadjuk a carry-t
    st  Z,  ZERO                 ; nullterminated legyen a buffer
    ret

; A kiírató szubrutin
DISPLAY:
    call LCD_HOME                ; visszaugrik a kurzor (0,0)-ba
    wldi Z, buffer               ; Z regiszter inicializálása SRAM:buffer-re
    rcall LCD_FLASH_STR          ; A Z-t mint karakter pointert kiírja LCD-re
    ret

.include "lcd.inc"               ; a program lelke

;*************************************************************** 
;* A feladat nem kérte, hogy eeprom-ba rakjam szóval cseg-be rakom a szöveget
text:                            ; A kiírandó szöveg.
    .db "Ez a szoveg az elozo merocsoport hazija. ", 0
text_end:
    ;.db    "Teszt ", 0, 0

;*************************************************************** 
;* SRAM - data segment
.dseg

buffer:
    .byte BUFFER_LENGTH_C+1      ; BUFFER_LENGTH méretû tömb lefoglalása

