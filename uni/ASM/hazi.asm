;****************************************************************************** 
;* Feladat: LCD hirdet�t�bla scrolloz� sz�veggel                              ;
;* R�vid le�r�s:                                                              ;
;                Mem�ri�b�l vett karaktersorozat megjelen�t�se                ;
;                az LCD kijelz�n, fix sebess�ggel t�rt�n� oldalra l�ptet�s.   ;
;                Figyelni kell arra, hogy a karaktersorozat hosszabb �s       ;
;                �s r�videbb is lehet mint a kijelz� m�rete!                  ;
;                Hw: timer, LCD, SRAM                                         ;
;* Szerz�k: Juh�sz B�lint, Gyur�cz Krist�f                                    ;
;* M�r�csoport: CDE17                                                         ;
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
.equ BUFFER_LENGTH_C = 20        ; t�mb inicializ�l�s�hoz konstans m�ret
.equ timer_const   = 2700        ; 10800 / 5400 / 2700 / 1350

.def ZERO          = r5          ; ne kelljen immediate utas�t�sokat h�vni
.def BUFFER_LENGTH = r6          ; A buffer hossza
.def TEXT_LENGTH   = r7          ; A sz�veg hossza
.def textIndex     = r8          ; MAIN_LOOP-ban ez iter�l v�gig a sz�vegen
.def newSecond     = r9          ; az �j m�sodperc
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
    fldi BUFFER_LENGTH, BUFFER_LENGTH_C ; buffernek megadjuk a konstans param�tert

    fldi TEXT_LENGTH, (text_end-text-1)<<1; megel�legezz�k a 0 0 padding-ot
    wldi Z, (text_end-1)<<1      ; de az�rt kipr�b�ljuk h�tha nincs padding
    lpm temp, Z                  ; text_end el�tti WORD els� BYTE-j�t n�zz�k
    cp temp, ZERO                ; temp = 0 ?
    breq TEXT_PADDING_ON         ; ha igen akkor igazunk volt, 0 0 padding van
    fldi TEXT_LENGTH, ((text_end-text)<<1)-1 ; hopp�, nincs padding!
TEXT_PADDING_ON:

    call LCD_INIT                ; LCD inicializ�l�sa
    call LCD_CURSOR_OFF          ; letiltjuk a kurzort
	ldi temp, 0xff               ;
	out DDRB,  temp              ; 
    ldi r16,   0x20              ;
    out PORTB, temp              ; megvil�g�tjuk a kijelz�t

    ; init timer
    ldi temp, 0b00000000         ; CTC m�d �s 1024 el�oszt�s
    out TCCR1A, temp
    ldi temp, 0b00001101
    out TCCR1B, temp
    ldi temp, HIGH(timer_const)
    out OCR1AH, temp
    ldi temp, LOW(timer_const)
    out OCR1AL, temp
    ldi temp, 0                  ; null�zzuk a 16 bites sz�ml�l�t
    out TCNT1H, temp
    out TCNT1L, temp
    ldi temp, 0b00010000         ; megszak�t�s, ha TCNT == OCR
    out TIMSK, temp
    eor temp, temp
    mov newSecond, temp          ; newSecond = 0
    sei                          ; glob�lis IT enged�lyez�se

;*************************************************************** 
;* MAIN program, Endless loop part
 
MAIN_LOOP:
    cp newSecond, ZERO          
    breq MAIN_LOOP               ; ha newSecond = 0 akkor nincs mit tenni
    cli                          ; ha m�gis megn�tt, el�sz�r letiltjuk az 
                                 ; interruptot �s rem�nyked�nk, hogy negyed 
                                 ; m�sodperc alatt lefut ez a p�r sor k�d
                                 ; erre az�rt van sz�ks�g mert az interrupt 
                                 ; szubrutin most r�vid, ez�rt 
                                 ; nem akarjuk hogy belepiszk�ljon a k�dunkba
    eor newSecond, newSecond     ; viszont ha newSecond != 0 akkor lenull�zzuk 
                                 ; �s �jra v�runk hogy n�vel�dj�n
    call SCROLL                  ; scrolloz�s
    call DISPLAY                 ; ki�r�s
    
    inc textIndex                ; textIndex-et mindig n�velni kell, 
                                 ; ez�rt a branching el�tt �ll
    
    cp TEXT_LENGTH, BUFFER_LENGTH; �sszehasonl�tjuk a sz�veg �s a buffer hossz�t
    brsh MAIN_LOOP_BUFFER_SHORTER; ha a buffer kisebb, ezt m�shogy kezelj�k le

    cp textIndex, BUFFER_LENGTH  ; megn�zz�k textIndex == BUFFER_LENGTH
    in temp, SREG                ; SREG -> regiszterbe
    sbrc temp, 1                 ; megn�zz�k ZERO flag �res-e. ha igen, ugr�s
    eor textIndex, textIndex     ; ZERO flag 1, teh�t ha textIndex ugyanakkora,
                                 ; mint a BUFFER_LENGTH, lenull�zzuk
    jmp MAIN_LOOP_END

MAIN_LOOP_BUFFER_SHORTER:
    cp textIndex, TEXT_LENGTH    ; l�sd 8 sorral feljebb
    in temp, SREG                ;
    sbrc temp, 1                 ;
    eor textIndex, textIndex     ;
MAIN_LOOP_END:
    sei                          ; �jra enged�lyezz�k az interruptot
    jmp MAIN_LOOP

;*************************************************************** 
;* Subroutines, Interrupt routines

T1CM_IT:
    inc newSecond                ; megn�velj�k newSecond-�t. 
    reti                         ; ami igaz�b�l annyi, hogy ne 0 legyen
    
MOD_INPUT:                       ; *_LENGTH-et temp-be rakjuk
    cp inputMod, temp            ; �sszehasonl�tjuk inputMod-ot �s temp-et
    brlo MOD_INPUT_END           ; ha inputMod kisebb akkor nincs mit csin�lni
    sub inputMod, temp           ; ha inputMod >= temp akkor kivonjuk bel�le
    jmp MOD_INPUT                ; �s megn�zz�k m�gegyszer
MOD_INPUT_END:
    ret

; A buffer scrolloz� szubrutin
SCROLL:
.def iterator = r17              ; iter�tor a buffer elej�t�l a v�g�ig
.def inputMod = r18              ; az iter�torb�l k�pzett offset a text-hez
.def spaceLetter = r19           ; ez t�rolja a space(32) �rt�ket
    eor iterator, iterator
    ldi spaceLetter, ' '
SCROLL_LOOP:
    cp iterator, BUFFER_LENGTH   ; �sszehasonl�tjuk az iter�tort �s buffer-t
    breq SCROLL_END              ; ha az iter�tor a v�g�re �rt, exit

    mov inputMod, iterator       ; minden esetben az inputMod = iterator
    add inputMod, textIndex      ; hozz�adjuk az iter�torhoz az aktu�lis indexet
                                 ; helyesebben inputMod = textIndex 
                                 ; �s ahhoz k�pest az offszet az iterator
    cp TEXT_LENGTH, BUFFER_LENGTH; �sszehasonl�tjuk a sz�veg �s a buffer hossz�t
    brsh SCROLL_LOOP_LONGER      ; ha a sz�veg hosszabb, ugrunk
    
    mov temp, BUFFER_LENGTH      ; temp = BUFFER_LENGTH
    call MOD_INPUT               ; inputMod %= BUFFER_LENGTH

    cp inputMod, TEXT_LENGTH
    brlo SCROLL_LOOP_SHORTER_NOTEMPTY ; ha inputMod kisebb mint TEXT_LENGTH,
                                 ; m�g �rhatunk ki a sz�vegb�l, nem kell a space

    wldi Z, buffer               ; Z = buffer:buffer
    add ZL, iterator             ; hozz�adjuk iter�tort Z-hez
                                 ; ezzel adunk offszetet a pointer�nknek
    adc ZH, ZERO                 ; fels� byte-hoz hozz�adjuk a carry-t
    st  Z,  spaceLetter          ; elt�roljuk Z hely�n a space-t
    jmp SCROLL_LOOP_POST

SCROLL_LOOP_SHORTER_NOTEMPTY:
    wldi Z, text << 1            ; Z = text:text
    add ZL, inputMod             ; hozz�adjuk Z-hez az inputMod-ot
    adc ZH, ZERO                 ; fels� byte-hoz carry
    lpm temp, Z                  ; most hogy Z k�sz, kiolvassuk *Z �rt�k�t
    
    wldi Z, buffer               ; Z = buffer:buffer
    add ZL, iterator             ; hozz�adunk iter�tort Z-hez
    adc ZH, ZERO                 ; fels� byte-hoz hozz�adjuk a carry-t
    st  Z,  temp                 ; elt�roljuk Z hely�n a temp �rt�k�t

    jmp SCROLL_LOOP_POST

SCROLL_LOOP_LONGER:
    mov temp, TEXT_LENGTH
    call MOD_INPUT

    wldi Z, text << 1            ; Z = text:text 
    add ZL, inputMod             ; hozz�adjuk Z-hez az inputMod-ot
    adc ZH, ZERO                 ; fels� byte-hoz carry
    lpm temp, Z                  ; most hogy Z k�sz, kiolvassuk *Z �rt�k�t

    wldi Z, buffer               ; Z = buffer:buffer
    add ZL, iterator             ; hozz�adunk iter�tort Z-hez
    adc ZH, ZERO                 ; fels� byte-hoz hozz�adjuk a carry-t
    st  Z,  temp                 ; elt�roljuk Z hely�n a *(text+inputMod)-t

SCROLL_LOOP_POST:
    inc iterator                 ; n�velj�k iterator-t. (BUFFER_LENGTH-ig megy)
    jmp SCROLL_LOOP

SCROLL_END:
    wldi Z, buffer               ; Z = buffer:buffer
    add ZL, BUFFER_LENGTH        ; hozz�adunk BUFFER_LENGTH m�retet
    adc ZH, ZERO                 ; fels� byte-hoz hozz�adjuk a carry-t
    st  Z,  ZERO                 ; nullterminated legyen a buffer
    ret

; A ki�rat� szubrutin
DISPLAY:
    call LCD_HOME                ; visszaugrik a kurzor (0,0)-ba
    wldi Z, buffer               ; Z regiszter inicializ�l�sa SRAM:buffer-re
    rcall LCD_FLASH_STR          ; A Z-t mint karakter pointert ki�rja LCD-re
    ret

.include "lcd.inc"               ; a program lelke

;*************************************************************** 
;* A feladat nem k�rte, hogy eeprom-ba rakjam sz�val cseg-be rakom a sz�veget
text:                            ; A ki�rand� sz�veg.
    .db "Ez a szoveg az elozo merocsoport hazija. ", 0
text_end:
    ;.db    "Teszt ", 0, 0

;*************************************************************** 
;* SRAM - data segment
.dseg

buffer:
    .byte BUFFER_LENGTH_C+1      ; BUFFER_LENGTH m�ret� t�mb lefoglal�sa

