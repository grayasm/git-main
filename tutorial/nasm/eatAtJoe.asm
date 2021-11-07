		;; call function "sys_write" and return
section .data
	EatMsg:	db "Eat at Jos's!", 10
	EatLen:	equ $-EatMsg

section .bss
section .text

global _start

_start:
		nop
		mov eax,4				; function: sys_write
		mov ebx,1				; param: stdout
		mov ecx,EatMsg			; param: message
		mov edx,EatLen			; param: length of message
		int 80H					; execute

		mov eax,1				; function: exit
		mov ebx,0				; return value
		int 80H					; execute
