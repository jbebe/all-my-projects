        BITS 16
				ORG 0x7c00
%define back 71
%define color 41
%define gens  20
%define offset 50
        call graphics
        push 0xA000
 				pop es
				push 0x8000
				pop fs
				
				mov ax, back
				mov dx, 1
				mov cx, 0xffff
				call drawline ; fill the screen with the background color
				
				
				
				
io:     call drawIO       
        mov cx, gens	; compute "gens" generations before redrawing IO							
        
gol:    push cx
        call generation
        pop cx
			  loop gol
			  
			  jmp io
								
compute_px:
        mov si, bx ; save the pixel being computed
        sub bx, 0x141 ; point to the upper-left pixel
        mov cx, 3 ; loop control
        mov dx, 3 ; loop control
        xor ax, ax ; zero out ax, ax stores the count of alive pixels

l1:     push cx ; for i=3; i>0 ; i++
        mov cx, dx  
l2:                ;for j=3; j>0; j++
       ; pop si ;
       ; push si ;
        cmp bx, si ;if we are pointing at the central pixel, just skip
        je skip     
        cmp byte [es:bx] , back ; if the pixel is dead doesnt increase ax
        je skip
        inc ax  ; the pixel is alive, increase ax   
skip:   inc bx  ; next pixel
        loop l2
        add bx, 0x140-3  ; next line
        pop cx
        loop l1
        ;pop bx
        mov bx, si
        cmp ax, 3 ; if there are 3 alive pixels there's a "birth"
        jne nobirth
        mov byte [fs:bx], color
        ret
nobirth:
        cmp ax, 2
        jne dead
        ret       ;if there are 2 alive pixels, nothing happens         
dead:   mov byte [fs:bx], back ; less than 2 or more than 3 alives => dead

        ret

generation:
        mov  cx, 320*200
onepx:  mov  bx, cx
				push cx
        call compute_px
        pop cx
        loop onepx
        call sleep
        call swap_buffer
      
        ret        
        
swap_buffer:
        push ds
      	push fs
      	pop  ds
      	xor  si, si
      	xor  di, di
      	mov  cx, 320*200/2
      	rep  movsw
      	pop  ds
        ret

drawIO:
        mov ax, color
        mov bx, 0x4160 
        mov dx, bx
        add dx, 60
        push dx
        mov dx, 1
        mov cx, 50
        call drawline
        mov cx, 60
        sub bx, 25
        call drawbar
        mov cx, 50
        sub bx, 25
        call drawline
        pop bx
        mov cx, 50
        call drawline
        mov cx, 60
        call drawbar
        mov dx, -1
        mov cx, 50
        call drawline
        mov cx, 60
        call drawbar
        ret

        
;drawing procedures : al->color, bx->place, cx->lenght, dx->direction (1 right, -1 left)        
drawline:
        mov BYTE [es:bx],al
        add bx, dx
        loop drawline
        ret

drawbar:
        mov BYTE [es:bx],al
        cmp dx, -1
        je L
        add bx, 0x140
        jmp R
  L:    sub bx, 0x140
  R:    loop drawbar
        ret

sleep: push dx
       push cx
       push ax
       xor cx, cx
       mov cx, 1
       mov dx, 0xf000
       mov ah,0x86
       int 0x15
       pop ax
       pop cx
       pop dx
       ret
       
graphics: mov ax, 0x13
          int 0x10
          ret     
end:    jmp end        
        times 446-($-$$) db 0
        times 64 db 0xff
        db 0x55,0xaa
