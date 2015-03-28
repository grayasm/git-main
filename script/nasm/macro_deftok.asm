		; Defining tokens: %deftok
		; %deftok and its case-insensitive couterpart %idetok define or redefine
		; a single-line macro without parameters but converts the second
		; parameter after string conversion, to a sequence of tokens
		;
		; %deftok test 'TEST'          is equivalent to
		; %define test TEST
section .bss
section .data
		%deftok TOKEN '"Macro replaced with token between single quotes!"'
		strMsg db TOKEN
		lenMsg equ $-strMsg

section .text
		global _start

_start:
		mov eax, 4				; sys_write
		mov ebx, 1				; stdout
		mov ecx, strMsg
		mov edx, lenMsg
		int 80h

		mov eax, 1				; sys_exit
		mov ebx, 0				; success
		int 80h
