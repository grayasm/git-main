		; String length:  %strlen
		; The  %strlen  operator assigns the length of a string to a macro.
section .bss
section .data
		%defstr TEXT  A text of relative short length.
		%strlen LEN   TEXT
		strMsg db TEXT
		lenMsg equ LEN

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
