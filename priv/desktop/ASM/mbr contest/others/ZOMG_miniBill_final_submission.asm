BITS 16

; set display mode
%define COLS 320
%define ROWS 200
mov ax,0x13
;mov ax,0x4F02
;mov bx,0x103
;%define COLS 800
;%define ROWS 600
int 0x10

push 0xA000
pop ds

;palette setup
xor bx, bx
mov cx, 256
pal1:
	mov ax, bx
	mov dx, 0x3c8 ;set output port
	out dx, al
	inc dx

	mov al, 0xFF
	out dx, al
	mov al, bl
	out dx, al
	mov al, 0x00
	out dx, al
	
	inc bx
loop pal1

xor bx, 0x63
mov cx, 63


push 0x2000
pop ds

; fill the screen with non-randomness
mov bx, ROWS * COLS + 1
t:
	dec bx	
	mov ax, bx
	xor dx,dx
	mov word cx, COLS
	div cx
	
	push dx
	fild word [esp]		; x

	mov word [esp], 35
	fild word [esp] 	; 35			x
	fdivp 				; x/35
	fsin				; sin(x/35)

	fild word [esp]     ; 40			sin(x/35)
	fmulp				; 40sin(x/35)

	fistp word [esp]
	pop dx

	mov byte [bx], dl
	cmp bx,0
jnz t

;draw vertical liness
mov bx, 65*COLS+110
mov cx, 74
idown:
	xor dword [bx], 0x7F7F7F7F
	add bx, 80 
	xor dword [bx], 0x7F7F7F7F
	add bx, 60
	xor dword [bx], 0x7F7F7F7F
	add bx, 180
	dec cx
jns idown

; draw horizontal lines
mov bx, 60*COLS+80
mov dx, 4
ohor:
	mov cx, 63
	ihor:
		xor byte [bx],0xFF
		xor byte [bx+110],0xFF
		xor byte [bx+110+COLS*80],0xFF
		xor byte [bx+COLS*80],0xFF
		inc bx
		dec cx
	jns ihor
	add bx, COLS-64
	dec dx
jns ohor

push 0x3000
pop ds

;clean buffer
mov bx,COLS*ROWS+1
clean:
	dec bx
	mov byte [bx], 63
jnz clean

;make room for the counter
push word 0
anim:
mov bx, COLS*ROWS+1
sub bx, COLS*2
omess:
	dec bx
	mov ax, bx
	xor dx,dx
	mov word cx, COLS
	div cx

	push word ax			; st0			st1		st2		st3
	fild word [esp]			; y

	fild word [esp+3] 		; t				y

	fldpi 					; pi			t		y
	mov word [esp], 2
	fild word [esp]			; 2				pi		t		y
	fdivp		 			; pi/2			t		y

	fmulp					; t*pi/2		y

	faddp					; t*pi/2+y <- let's call it a

	mov word [esp], 60
	fild word [esp]			; 60			a
	fdivp					; a/60
	fldpi					; pi			a/60
	fmulp					; pi*a/60
	fsin					; sin(pi*a/60) <- let's call it b

	mov word [esp], 20
	fild word [esp]			; 20			b		
	fmulp					; 20b
	fistp word [esp]		; <>
	pop word dx

	xor ax,ax
	push 0x2000
	pop ds
	push bx
	add bx, dx
	mov byte al, [bx+COLS]
	pop bx

	push 0x3000
	pop ds
	mov byte [bx+COLS], al

	cmp bx, 0
jnz omess

;transfer 0x3000 -> 0xA000
mov cx, COLS*ROWS
xor si,si
push 0x3000
pop ds
xor di,di
push 0xA000
pop es
rep movsb
push 0x2000
pop ds

inc word [esp+1]
jmp anim

hcf: jmp hcf

times 510 - ($-$$) db 0
db 0x55, 0xaa
