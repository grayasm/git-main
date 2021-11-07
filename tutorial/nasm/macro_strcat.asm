		; Concatenating strings:   %strcat
		; The %strcat  operator concatenates quoted strings and assigns
		; them to a single line macro.
section .bss
section .data
		%strcat TEXT "Attempt to concatenate"," string1"," with"," string3"
		strMsg db TEXT,10
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
