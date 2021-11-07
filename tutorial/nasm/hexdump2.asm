		;; hexdump - see hexdump1 for basic convertion explanation
		;;
		;;    Take 1 byte at a time from Text string in a loop (i=0, i<Textl, ++i)
		;;    Convert it from decimal into hexadecimal by devision to 16
		;;    The quotient (Q) and remainder (R) will be written as QR (hex dump)
		;;    Get the string code for Q as offset in Digits string
		;;    Get the string code for R as offset in Digits string
		;;    Write Q in Hex at position = i * 3 + 1
		;;    Write R in Hex at position = i * 3 + 2
section .bss
section .data
		Text db "asm",10
		Textl equ $-Text
		Digits db "0123456789ABCDEF",10
		Digitsl equ $-Digits
		Hex db " 00 00 00 00 00 00 00 00",10
		Hexl equ $-Hex
		sys_read  equ 3
		sys_write equ 4
		sys_exit equ 1
		stdin equ 0
		stdout equ 1
section .text
		global _start
_start:	nop
		mov ecx, -1
Cycle:
		inc ecx							; for(ecx=0; ecx < Textl; ++ecx)
		cmp ecx, Textl
		jae Write
		mov eax, 0						; zero entire eax
		mov al, byte [Text+ecx]			; take 1 byte from Text at a time
		mov bl, 16						; division by 16 for conversion to hexadecimal
		div bl							; al : bl = al + ah
		mov ebx, 0
		mov bl, al						; ebx = Q (e.g. 10 decimal)
		mov dl, byte [Digits + ebx]		; edx = character code for Q (e.g. 'A')
		mov ebx, ecx					; ebx = i (e.g. i = 3)
		shl ebx, 1						; ebx = ebx * 2 (e.g. 6)
		add ebx, ecx					; ebx = ebx + i (e.g. 9) or i*3
		add ebx, 1						; ebx = ebx + 1 (e.g. 10) or i*3+1
		push ebx						; save ebx on stack
		mov byte [Hex+ebx], dl			; Hex = " ?? ?? ?? A0 00 00 00 00"
		mov ebx, 0
		mov bl, ah						; ebx = R (e.g. 7 decimal)
		mov dl, byte [Digits+ebx]		; edx = character code for R (e.g. '7')
		pop ebx							; ebx = 10
		inc ebx							; ebx = 11
		mov byte [Hex+ebx], dl			; Hex = " ?? ?? ?? A7 00 00 00 00"
		jmp Cycle
Write:
		mov eax, sys_write
		mov ebx, stdout
		mov ecx, Hex
		mov edx, Hexl
		int 80h
Exit:
		mov eax, sys_exit
		mov ebx, 0
		int 80h
