BITS 16

; set display mode
mov ax, 0x13                     ; ah: 0x00 (set video mode), al: 0x13 (video mode type: 320x200 256 color graphics)
int 0x10                         ; set video mode

;load video address in ds
push 0xA000
pop ds

;set up a palette in greens
xor ax, ax                       ; ax = 0
pal:
	mov dx, 0x03c8               ; dx = 0x3c8 (0x3c7: Read VGA, 0x3c8: Write VGA)
	out dx, al
	inc dx
	xchg al,ah
	out dx, al
	xchg al,ah
	out dx, al
	xchg al,ah
	out dx, al
	xchg al,ah
	inc al
jnz pal

; fil the screen with randomness
mov bx, 0xfa01
t:
	rdtsc
	xor al,ah
	xor ax,bx
	xor ax, cx
	dec bx	
	mov byte [bx], al
	mov cx, ax
	rcr cx,3
jnz t


; run a little filter over it
mov dx, 14
forever:
	mov bx, 0xfa00-0x140
	inner:
		dec bx
		xor cx, cx
		xor ax, ax
		mov al, byte [bx]
		mov cl, byte [bx-0x140]
		add ax, cx
		mov cl, byte [bx+0x140]
		add ax,cx
		mov cl, byte [bx-1]
		add ax,cx
		mov cl, byte [bx+1]
		add ax,cx
		shl ax, 3
		mov cl, 42
		div cl
		mov byte [bx],al
		cmp bx, 0x140
	jne inner
	dec dx
jns forever


;draw vertical liness
mov bx, 60*320+100
mov cx, 80
idown:
mov byte [bx], 0    ;r
add bx, 90
mov byte [bx], 0    ;g
add bx,60
mov byte [bx],0     ;b
add bx, 70+100
dec cx
jns idown

; draw horizontal lines
mov bx, 60*320+70
mov cx, 60
ihor:
mov byte [bx],0
mov byte [bx+120],0
mov byte [bx+120+320*80],0
mov byte [bx+320*80],0
inc bx
dec cx
jns ihor


hcf:
jmp hcf

padding: times 446 - ($-$$) db 0
partitiontable: times 64 db 0xff
signature: db 0x55, 0xaa