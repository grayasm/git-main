		; Preprocessor variables:   %assign
		; An alternative way to define single-line macros is by means of the
		; %assign command (and its case-insensitive counterpart %iassign,
		; which differs from %assign in exactly the same way that
		; %idefine differs from %define).
section .bss
section .data
		strMsg db "using %assign for string length!"
		%assign lenMsg $-strMsg

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
