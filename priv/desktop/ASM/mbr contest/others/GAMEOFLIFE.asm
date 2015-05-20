[bits 16]
;display mode
mov ax,0x13
int 0x10
push 0xa000
pop ds
;draw horizontal lines
mov cx,11
mov bx,15*4*320+100
push 2
hline:
push bx
call blockdraw
lea ax,[bx+80]
push ax
call blockdraw
lea ax,[bx+20*4*320]
push ax
call blockdraw
lea ax,[bx+20*4*320+80]
push ax
call blockdraw
add bx,4
loop hline
;draw vertical lines
mov cl,20
mov bx,15*4*320+120
vline:
push bx
call blockdraw
lea ax,[bx+60]
push ax
call blockdraw
lea ax,[bx+100]
push ax
call blockdraw
add bx,320*4
loop vline
;put a glider between I and O ;)
mov bx,25*4*320+154
push bx
call blockdraw
add bx,4*320+4
push bx
call blockdraw
add bx,4*320
mov cx,3
glider:
push bx
call blockdraw
sub bx,4
loop glider
;put delay for io
mov ax,0x8600
mov cl,0xf
mov dx,0xffff
int 0x15
;keep on looping 
ANIM:
mov bx,316
;go over each pixel
hloop:
mov cx,50
mov si,0
vloop:
xor ch,ch
xor dx,dx
mov di,1
starting:
cmp si,196*320
jne NORM
cmp di,0
jne QWE
cmp byte [bx],0x2
jmp step
QWE:
cmp byte [es:0x6064],0x1
jmp step
NORM:
cmp byte [bx+si+4*320],0x2
step:
jnz cont
inc dx
cont:
cmp si,0
jne step1
cmp byte [bx+196*320],0x2
jmp ASD
step1:
cmp di,0
jne NORM1
cmp byte [bx+si-4*320],0x2
jmp ASD
NORM1:
cmp byte [es:0x6065],0x1
ASD:
jnz done
inc dx
done:
cmp di,0
je ending
dec di
push bx
cmp bx,0
je gothere
sub bx,4
cmp byte [bx+si],0x2
jnz cont1
inc dx
cont1:
jmp starting
ending:
push si
mov si,1
jmp further
gothere:
mov si,2
further:
mov bx,0x6000
LOP:
mov di,50
sub di,cx
push di
mov ax,3
cmp di,0
jne sup
mov di,49
jmp cont2
sup:
dec di
cont2:
cmp byte [es:bx+di],0x1
jnz count
inc dx
count:
cmp di,49
jne sup1
mov di,0
jmp cont3
sup1:
inc di
cont3:
dec ax
jnz cont2
add bx,50
dec si
cmp si,0
jnz LOP
;count finished save state  to temp buffer here 
pop di
pop si
pop bx
mov ch,[bx+si]
cmp ch,0
je ZXC
dec ch
ZXC:
cmp bx,316
jne JKL
mov [es:0x6032+di],ch
JKL:
mov [es:0x6066+di],ch
cmp si,0
jne GOON
mov [es:0x6064],ch
GOON:
mov [es:0x6065],ch
;here goes rules
cmp dx,3
jne ABC
push 2
lea ax,[bx+si]
push ax
call blockdraw
pop ax
ABC:
cmp dx,2
jl XYZ
cmp dx,3
jle PQR
XYZ:
push 0
lea ax,[bx+si]
push ax
call blockdraw
pop ax
PQR:
add si,320*4
dec cl
jnz vloop
mov cx,50
xor di,di
;here copy tmp buffer to original buffer
SAD:
mov al,[es:0x6066+di]
mov [es:0x6000+di],al
inc di
loop SAD
sub bx,4
jnz hloop
;bios wait function
mov ax,0x8600
mov cl,0x02
mov dx,0xffff
int 0x15
jnc ANIM
;blockdrawing function
blockdraw:
push bp
mov bp,sp
pusha
mov bx,[bp+4]
mov dl,[bp+6]
mov cx,4
outdraw:
mov si,4
indraw:
mov byte [bx+si-1],dl
dec si
jnz indraw
add bx,320
loop outdraw
popa
mov sp,bp
pop bp
ret 2
times 446-($-$$) db 0
times 64 db 0xff
db 0x55,0xaa
