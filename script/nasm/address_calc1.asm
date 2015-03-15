		;; ?
section .bss
section .data
		sys_exit equ 1
		Text db "01234",10		; 5 elements in a string of bytes, terminated
								; with new line (10 in ascii table)

section .text
		global _start
_start:
		mov eax, Text			; move string address in eax
		mov byte [eax], 65		; change string from '01234' into 'ABCDE'
		mov byte [eax+1], 66
		mov byte [eax+2], 67
		mov byte [eax+3], 68
		mov byte [eax+4], 69
		;; pass string content into eax, first 4 bytes fit into eax GP register
		mov eax, [Text]			; eax = 0x44434241  eax= DCBA

Exit:
		mov eax, sys_exit
		mov ebx, 0
		int 80h
