BITS 16

;
; Entry
;
Entry:
  ; Initialize graphics mode and clear frame buffer
  call InitGfx
  mov word [0xfc00], 1

  ; Initialize palette to something nice and fiery
  call InitPalette

  ; Main demo loop
.main:
  ; Wait for VSYNC

  ; Propogate fire (hint: heat rises and cools)
  call MakeFire

  ; Originate fire along "io"
  call DrawIO

  ; Do it again (& again...)
  jmp .main


;
; Initialize the graphics
;
InitGfx:
  ; Set up mode 13h VGA 320x200 with the awesome 8bit palette
  mov ax, 0x13
  int 0x10

  push 0xa000
  pop es
  mov cx, 0x8000
  xor di, di
  xor ax, ax
  rep stosw

  ret

;
; Initialize the palette
;
InitPalette:
  xor ax, ax

.set:
  ; Index
  mov dx, 0x3c8
  out dx, al

  mov cx, ax
  shr ax, 2
  inc dx
  out dx, al    ; Red
  shr ax, 1
  out dx, al    ; Green
  shr ax, 2
  out dx, al    ; Blue
  mov ax, cx

  inc ax
  cmp ax, 0x100
  jb .set

  ret

RandomWord:
  mov ax, [0xfc00]
  shl ax, 13
  xor ax, [0xfc00]
  mov dx, ax
  shr ax, 9
  xor ax, dx
  mov dx, ax
  shl ax, 7
  xor ax, dx
  mov [0xfc00], ax
  jnz .done
  mov word [0xfc00], 1
.done:
  ret

;
; Draw "io"
;
DrawIO:
  cld
  push 0xa000
  pop ds

  mov di, 60*320+100
  mov cx, 80

idown:
  call RandomWord  
  mov [di], al
  add di, 90
  call RandomWord
  mov [di], al
  add di, 60
  call RandomWord
  mov [di], al
  add di, 70+100
  loop idown

  mov di, 60*320+70
  mov cx, 60
ihor:
  call RandomWord  
  mov byte [di], al
  mov byte [di+120], ah
  call RandomWord  
  mov byte [di+120+320*80], al
  mov byte [di+320*80], ah
  inc di
  loop ihor

  mov cx, 320 / 2
  mov di, (320 * 195)

.draw:
  call RandomWord
;  shr al, 1
;  shr ah, 1
;  add al, 0x80
;  add ah, 0x80
  
  stosw
  loop .draw
 
  ret

;
; Propogate the fire upwards
;
MakeFire:
  push 0xa000
  pop ds
  push 0xa000
  pop es

  mov di, 320
  mov si, 640
  cld
  
.scanloop:
  xor ax, ax
  movzx dx, byte [si-1]
  add ax, dx
  movzx dx, byte [si]
  add ax, dx
  add ax, dx
  movzx dx, byte [si+1]
  add ax, dx

  shr ax, 2
  cmp ax, 2
  jbe .skip

  dec ax
  dec ax

.skip

  ; Really bad div 3 - some
  ; lea ax, [ax * 8 + ax]
  ; shr ax, 4
  
  ;mov al, 0xe0
  stosb
  inc si
  cmp si, (320 * 200)
  jb .scanloop

  ret

times 510 - ($-$$) db 0
db 0x55, 0xaa

