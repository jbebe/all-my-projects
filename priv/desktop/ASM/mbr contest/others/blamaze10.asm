;bla
BITS 16
ORG  0x7C00

;configurable at assemble time
%define logocolor 150
%define logox 7
%define logoy 13
%define conecolor 100



;set graphics mode
mov ax, 0x13
int 0x10

;palette setup, grayscale , further away, darker color 
mov cx, 64
xor al, al
mov dx, 0x3c8 
out dx, al
inc dx
pal1:
	out dx, al
	out dx, al
	out dx, al
	inc ax
loop pal1


;not relying on initial state, pedantically putting segment registers to a valid state
;particularly important when trying to run it using real hardware/bioses

push cs
push cs
pop ds
pop ss
mov sp, 0x7b00
mov bp, sp

; draw map
mov si, data
mov dx, logoy<<8|logox
s:
	mov di, bp
	mov bx, symbols
	r: lodsw
	shl eax, 16
	mov cx, 5
	l: xor ax, ax
	rol eax, 3
	xlatb
	stosb
	loop l
	rcl eax, 1
	jnc r

	mov bx, logocolor
	mov ax, 0x1301
	mov cl, 25
	int 0x10
	inc dh
	cmp dh, logoy + 11
jne s


; copy map to safe location
xor si, si
xor di, di
;mov cx, 320*200
not cx							; this will make cx large enough, we don't mind copying more

mov ax, 0xa000
mov ds, ax
shl ax, 2
mov es, ax

rep movsb
push ds
push es
pop ds
pop es


; initialize view vector
mov bp, ddata
fldz
fild word [bp]
fild word [bp+2]
							; x=160; y=100; angle=0 



; main loop
draw:
	xor ax,ax
	int 0x16

	shr ax, 9
	jc leftright
	undo:   shr ax, 3
		fld st2
		mov al, 0
		jc up
			not al
			fldpi
			fadd
		up:
		fsincos
		faddp st2
		faddp st2

		jmp arrowend
	leftright:
		fld1
		fldpi
		fmul st0
		fdivp st1				; we change the viewing angle 1/(pi*pi) radians (about 7degrees)
		shr ax, 2
		jc right
			fchs
		right:
			faddp st3
	arrowend:



	; blank screen but copy logo
	;mov cx, 320*200
	not cx						; this will make cx large enough, we don't mind copying more
	xor di, di
	xor si, si
	rep movsb


	; collision detection.
	call calcaddr
	cmp byte [di], logocolor
	je undo


	; initialize rayangle
	fld st2
	fldpi
	fidiv word  [bp+4]
	fadd						; angle +30 degrees;x ; y; angle


	mov bl, 60
	newrayangle:
		fld st2
		fld st2                         	; rayx=x; ray=y; rayangle= angle +30; x; y; angle



		mov cl, 40
		castray:
			fld st2
			fsincos
			faddp st2, st0
			faddp st2, st0			; rax+cos(rayangle); rayy+sin(rayangle); rayangle;x; y; angle
			

			call calcaddr
			cmp byte [di], logocolor
			je hitwall			; could remove this instruction and make it loopne, but minimap visual artifacts
			mov al, conecolor
			stosb
		loop castray
		hitwall:
		fcompp					; discard top two items from fpu stack (ray x, ray y)

		fldpi
		fidiv word  [bp+6]
		fsub					; rayangle - 1; x; y; angle


		mov dx, 49
		sub dx, cx

		inc bx
		mov si, bx
		shl si, 2
		add si, bx
		dec bx
		
		call mul320

		mov al, cl
		shl cx, 1
		inc cx					; make sure cx isn't zero .. 
		
		line:
			stosb
			stosb
			stosb
			stosb
			stosb
			add di, 315
		loop line

		dec bx
	jnz newrayangle

	
	fstp st0					; discard top item from fpu stack ( ray angle)

jmp draw




calcaddr:
	fld st1
	fistp word [bp]
	mov dx, word [bp]
	fld st0
	fistp word [bp]
	mov si, word [bp]

mul320:	lea di, [edx+edx*4]
	shl di, 6
	add di, si

	ret


ddata: 
dw 100,160,6,
db 180		; cheekily use the null byte from the next section too for this value
data:
dw 0x0000, 0x0000, 0x0000, 0x02da, 0x0000+1
dw 0x0000, 0xb680, 0x0000, 0x0402, 0x4000+1
dw 0x0002, 0xb4a0, 0x0000, 0x2016, 0x6800+1
dw 0x0004, 0xb534, 0x0002, 0x00b2, 0x4d00+1
dw 0x0002, 0x00b6, 0x4010, 0x0590, 0x09a0+1
dw 0x1690, 0x0594, 0x20da, 0x2c84, 0xb534+1
dw 0x3694, 0x2cc8, 0x0100, 0x4d02, 0x00b2+1
dw 0x4026, 0x6400, 0x0020, 0x09a0, 0x0590+1
dw 0x0804, 0x6800, 0x0004, 0x0134, 0x2c80+1
dw 0x015a, 0x4400, 0x0000, 0x4026, 0x6400+1
dw 0x0000, 0x0000, 0x0000, 0x0ad4, 0x2000+1
symbols: db ' /\:~_'


%ifdef sizedebug
	times 510 - ($ - $$) db 'U'
%else
	times 446 - ($ - $$) db 'U'
	times 64 db 'x'
%endif
db 0x55,0xaa


