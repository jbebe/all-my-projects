; 403 bytes version by Peter Ferrie
; inspired by 446 bytes version by keegan
; Assemble with Yasm

;;;; CONSTANTS  
 ; MBR code runs in 16-bit mode at address 0x7C00  
 bits 16  
 org 0x7C00  
 ; stack-relative address of window granularity element, in ss  
 stack_window equ -2  
 ; start of video RAM  
 vram_start equ 0xA0000  
 ; VGA palette registers  
 vga_dac_addr equ 0x3C8  
 ; VESA mode 101h: 640 x 480 x byte  
 vesa_mode equ 0x101  
 ; Feedback buffers:  
 ; width : 512 pixels  
 ; height: 3 segments of 128 pixels each  
 ;  
 ; The three segments:  
 ; buffer A: 24000 34000 44000  
 ; buffer B: 54000 64000 74000  
 ;  
 ; Use bit ops to find these from fs = 2400 or 5400  
 width equ 512 ; must be power-of-2, >= 256  
 height equ 384  
 ; viewport size = 2 log_2 e  
 ; scale by the reciprocal  
 height_scale equ height * 1000 / 2886  
 width_scale equ width * 1000 / 2886  
 ; text rendered in mode 13h  
 text_width equ 64  
 text_height equ 16  
 text_num equ 2  
 text_y equ 60  
 text_x equ 192  
 ; Color palette:  
 ; Each channel is incremented at a different rate  
 ; For stupid reasons, inc_red is rounded to a multiple of 4  
 inc_red equ 4 ; u8 red increment per palette entry  
 inc_green equ 5 ; u8 green "  
 inc_blue equ 6 ; u8 blue "  
;;;; GLOBAL VARIABLES  
 ; ds = scratch RAM  
 ; fs = initial read segment per frame  
 ;  
 ; bp = frame counter  
 ; bx = 0  
;;;; ENTRY POINT  
 ; set up segments  
 push cs  
 pop ss  
 ; set up stack  
 xor sp, sp  
 ; use mode 13h temporarily, for rendering text  
 mov ax, 0x13  
 int 0x10  
 mov bx, 0x0F  
 mov si, text  
load_text: mov ah, 0x0E  
 cs lodsb  
 int 0x10  
 cbw  
 inc ax ; stop at filler  
 jne load_text  
 ; save rendered text to RAM  
 push vram_start >> 4  
 pop ds  
 push cs  
 pop es  
 xchg si, ax  
 xchg di, ax  
 mov cx, 320*text_num*text_height / 2  
 rep movsw  
 push cs  
 pop ds  
 ; switch back to text mode  
 ; going directly from 13h to 101h upsets  
 ; some non-emulated hardware  
 xchg cx, ax  
 int 0x10  
 ; get info for VESA mode 101h  
 mov ax, 0x4F01  
 mov cx, vesa_mode  
 push cx  
 int 0x10  
 ; enter the VESA mode  
 mov ax, 0x4F02  
 pop bx  
 int 0x10  
 ; compute 64 / window_granularity  
 ; VESA call successful => ah = 0  
 mov al, 64  
 cwd  
 div word [di+4]  
 push ax ;->stack_window  
 ; set up a palette  
 ; we assume the VESA mode has a VGA-compatible DAC  
 xchg dx, ax  
 mov dx, vga_dac_addr  
 out dx, al  
 inc dx  
 ; 6-bit RGB values in al, bh, ch  
 ; cx used for termination too  
 xor cx, cx  
palette: ; worth saving al due to short operands  
 push ax  
 out dx, al  
 mov al, bh  
 out dx, al  
 mov al, ch  
 out dx, al  
 pop ax  
 %if (inc_red-4)  
 add al, inc_red >> 2  
 %else  
 inc ax ; add al, inc_red >> 2  
 %endif  
 add bx, inc_green << 6  
 add cx, inc_blue << 6  
 jnz palette  
 ; initialize the FPU with some constants  
 fninit  
 mov word [di], height_scale  
 fild word [di]  
 mov byte [di], width_scale  
 fild word [di]  
 ; select first buffer for reading  
 push si  
 ; initialize frame counter and segments  
 xor bx, bx  
 push cx  
;;;; MAIN LOOP  
main_loop: ; restore clobbered ds  
 push cs  
 pop ds  
 pop bp  
 pop ax  
 push ax  
 mov fs, ax  
;;;; TEXT BLIT  
 ; draw text into the read buffer  
 add ah, 0x10  
 mov es, ax  
 mov si, padding + 1  
 test bp, 0x400  
 jz text_first_message  
 ; draw the second message sometimes  
 add si, text_height * 320  
text_first_message: mov di, width * text_y + text_x  
text_blit: ; cx cleared by previous loop  
 mov cl, text_width  
text_blit_row: lodsb  
 add [es:di], al  
 inc di  
 loop text_blit_row  
 add si, 320 - text_width  
 add di, width - text_width  
 cmp di, width * (text_y + text_height)  
 jb text_blit  
;;;; FEEDBACK  
 mov si, di  
 xor di, di  
 ; initialize write segment register  
 pop ax  
 xor ah, 0x70  
 push ax  
 ; push frame count to the FPU stack and scale  
 ; by width (arbitrary, convenient)  
 mov [si], bp  
 fild word [si]  
 fdiv st1  
 ; FPU stack: t h w  
 fld st0  
 fcos  
 fxch  
 fldl2e ; rel. period of k control pt.  
 fmulp  
 fcos  
 ; Move control point in a polar flower:  
 ; j = cos(t)  
 ; k = cos(log_2(e) * t)  
 ;  
 ; stack: j k h w  
 ; offset control point to an interesting region  
 ; center at (-ln(2) + 0i)  
 ; flower radius 0.5  
 fld1  
 fadd st0  
 fdiv st2, st0  
 fdivp st1, st0  
 fldln2  
 fsubp st1, st0  
 ; loop over pixels in the write buffer  
 mov dx, height  
compute_row: push ax  
 mov es, ax  
 mov ch, width >> 8  
compute_pix: pusha  
 fldl2e ; used to offset viewport center to origin  
 ; stack: o j k h w  
 mov [si], dx  
 fild word [si]  
 fdiv st5  
 fsub st1  
 ; stack: y o j k h w  
 mov [si], cx  
 fild word [si]  
 fdiv st5  
 fsub st2  
 ; stack: x y o j k h w  
 fst st2  
 fmul st2, st0  
 fld st1  
 fmul st0  
 fsubp st3, st0  
 ; stack: x y (x^2 - y^2) j k h w  
 fmulp  
 fadd st0  
 ; stack: 2xy (x^2 - y^2) j k h w  
 fadd st3  
 fld st2  
 faddp st2, st0  
 ; stack: 2xy+k (x^2 - y^2)+j j k h w  
 fldl2e  
 fadd st2, st0  
 faddp st1, st0  
 ; stack: (2xy + o) ((x^2 - y^2) + o) j k h w  
 fmul st5  
 fistp word [si]  
 mov bx, [si]  
 ; dx <- scaled (2xy + o)  
 fmul st3  
 fistp word [si]  
 ; default color for out-of-bounds pixels is 0  
 ; al is 0 from earlier segment register load  
 ; check bounds for y coordinate  
 cmp bx, height  
 jae compute_write  
 lodsw  
 ; ax <- scaled ((x^2 - y^2) + o)  
 ; wrap x coordinate  
 and ah, 0x01  
 xchg si, ax  
 ; extract segment from top 2 bits of y  
 shl bx, 1  
 shl bh, 4  
 mov ax, fs  
 add ah, bh  
 mov gs, ax  
 ; fetch at offset (y*width + x)  
 ; width = 2**9, shifted 1 already  
 shl bx, 8  
 mov al, [gs:bx+si]  
 ; clamp color to avoid super blinky center regions  
 cmp al, 0xF0  
 jae compute_write  
 ; color shift per map iteration, varying over time  
 mov bx, bp  
 and bh, 0x0F  
 add al, bh  
compute_write: stosb  
 popa  
 ; next column, output pixel  
 inc di  
 loop compute_pix  
 ; advance write segment when di wraps  
 pop ax  
 jnz compute_no_seginc  
 add ah, 0x10  
compute_no_seginc: ; next row  
 dec dx  
 jnz compute_row  
 ; bump frame counter  
 inc bp  
 ; discard j, k from FPU stack  
 fcompp  
;;;; DRAW TO SCREEN  
 ; swap feedback buffers  
 pop ds  
 push ds  
 ; access graphics memory through segment es  
 push vram_start >> 4  
 pop es  
 ; reset our window into VRAM  
 ; dx is 0 from earlier loop  
 mov ax, 0x4F05  
 int 0x10  
 ; copy beginning of feedback buffer to  
 ; center of screen  
 mov di, 48*640 + 64  
 push bp  
 mov bp, height  
draw_row0: xor si, si  
draw_row: mov ch, width >> 8  
draw_pix: movsb  
 ; advance the graphics window by 64k when di wraps  
 test di, di  
 jnz draw_no_wininc  
 add dl, [ss:di+stack_window]  
 ; call the VESA BIOS to set the VRAM window  
 mov ax, 0x4F05  
 int 0x10  
draw_no_wininc: loop draw_pix  
 ; end of row: 128 pixels of left/right border  
 add di, 128  
 dec bp  
 jz main_loop  
 ; advance read segment when !(row & 0x7F)  
 test bp, 0x7F  
 jnz draw_row  
 mov ax, ds  
 add ah, 0x10  
 mov ds, ax  
 jmp draw_row0  
text: db "I", 3, 0x0D, 0x0A, "io", 0x0D, 0x0A  
 db "gr:", 0xEB, 0xEE, "i", 0x0D, 0x0A, "mrule"  
padding:
times 108  db 0xff 
db 0x55, 0xaa
;;;; PROGRAM END 
