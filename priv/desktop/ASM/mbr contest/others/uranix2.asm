BITS 16

fninit

%define perPixel 10
%define numParticles 35*perPixel

; init graph mode
mov ax, 0x13
int 0x10

push 0x1000
pop ds

xor dx, dx
; targets
push 'io'
mov cx, 2
mov bx, cx
xor ax, ax
cwd
push ss
pop es
mov bp, sp
mov ah, 13h
int 10h

push 0xa000
pop es


mov bp, 0x8000
xor bx, bx
; init patricles' start and velocity 
init:
	push dx

	mov cx, 2
	mov di, 320
xy:	
	rdtsc
;	xor ax, bx for rand
	div di
	mov word [bx], dx
	fild word [bx]
	fst  dword [bx]
	fist word [bp+4]
	fsin
	fstp dword [bx+8] ; u
	add bx, byte 4
	add bp, byte 4
	sub di, 120
	loop xy

	sub bp, 8

	mov ax, word [bp+8]
	mov cx, 320
	mul cx
	add ax, word [bp+4]

	pop dx
	xor si, si
	fill:
		mov word [bx+24+si], ax ;bx=bx+8
		inc si
		inc si
		cmp si, 64
	jne fill

	inc dx
	add bx, 88 ; bx=bx+8
	cmp dx, numParticles
jne init

xor dx, dx
xor bx, bx 
mov word [bp], 25 ; dy
fild word [bp]
mov word [bp], 20 ; dx
fild word [bp]
mov word [bp], 12 ; y
fild word [bp]
mov word [bp], 25 ; x
fild word [bp]
mov word [bp], 320 ; w
xor si, si

initIO:
	mov cx, perPixel

	mov al, byte [es:si]
	test al, al
	jz nextpix
	pixel:
		fst dword [bx+16]
		fld st1
		fstp dword [bx+20]
		inc dx
		add bx, byte 96
	loop pixel
	nextpix:
	inc si
	; st0 - x, st1 - y, st2 - dx, st3 - dy
	fld st2
	faddp st1, st0
	test si, 15
	jnz notend
		add si, 320-16
		fild word [bp]
		fsubp st1, st0
		fld st3
		faddp st2, st0
	notend:
	cmp dx, numParticles
jne initIO
mov cx, 4
popfpu:
fstp st0
loop popfpu

mov bx, 320*200
zero:
	dec bx
	mov byte [es:bx], 255
jnz zero

xor di, di
;b 0xcc, 0x90
xor si, si
mov word [bp+12], 1000
mov word [bp+16], 200
mov word [bp+20], 696
time:
	mov word [bp], di
	fild word [bp]
	fild word [bp+20]
	fdivp st1, st0
	fsin
	fstp dword [bp]
	xor dx, dx
	xor bx, bx
	particle:
		push dx

		xor cx, cx
		loongloop:
			fld dword [bx] ; x
			fld dword [bx+8] ; u
			fld dword [bx+16] ;xend
			fld st2
			fsubp st1, st0
			fild word [bp+12]
			fdivp st1, st0
			fld st1
			fild word [bp+16]
			fdivp st1, st0
			fsubp st1, st0
			fld dword [bp] ; dt
			fmulp st1, st0
			faddp st1, st0
			fst dword [bx+8]
			fld dword [bp] ; dt
			fmulp st1, st0
			faddp st1, st0
			fst dword [bx] ; x
			add cx, byte 4
			add bp, cx
			fistp word [bp]; i
			sub bp, cx
			add bx, byte 4
			cmp cx, 8
		jne loongloop
;		sub bx, 8

		mov ax, word [bp+8]
		mov cx, 320
		mul cx
		add ax, word [bp+4]
		mov dx, ax

		; dx = new addr
;		mov cx, word [bx+32+si]
		mov cx, word [bx+24+si]
		; cx = old addr
		xchg bx, cx
		; dx = new, bx = old, cx = particle
		mov ax, si
		mov ah, byte [es:bx]
		cmp al, ah
		jne not_erase
			mov byte [es:bx], 255
		not_erase:
		xchg dx, bx
		; dx = old, bx = new, cx = particle
		mov byte [es:bx], al
		xchg cx, bx
		; dx = old, cx = new, bx = particle
;		mov word [bx+32+si], cx
		mov word [bx+24+si], cx
		pop dx
		inc dx
;		add bx, 96
		add bx, byte 88
		cmp dx, numParticles
	jne particle
	inc si
	inc si
	and si, byte 63
	inc di
mov cx, 1000
outer:
	mov ax, cx
	inner:
		dec ax
	jnz inner
	dec cx
jnz outer

	call palette

jmp time

palette:
mov ax, si
mov bl, 63
mov dx, 0x3c8
loo:
and al, 63
out dx, al
inc dx
xchg al, bl
out dx, al 
out dx, al 
out dx, al 
xchg al, bl
dec dx
dec bl
dec bl
dec al
dec al
cmp bl, 255
jne loo
ret

times 446 - ($ - $$) db 'U'
times 64 db 'x'
db 0x55,0xaa
