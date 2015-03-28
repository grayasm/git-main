		; defining strings: %defstr
		; %defstr and its case-insensitive counterpart %idefstr, define or
		; redifine a single-line macro without parameters but converts the
		; entire righ-hand side, after macro expansion to a quoted string
		; before definition
		;
		; %defstr test TEST          is equivalent to
		; %define test 'TEST'
section .bss
section .data
		%defstr TEXT  Macro replaces 'TEXT' with this text
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
