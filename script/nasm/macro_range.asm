		; NASM allows you to expand parameters via special construction %{x:y}
		; where x is the first parameter index and y is the last.
		; Any index can be either negative or positive but must never be zero.
section .bss
section .data

		%macro TAB5 1-*
		db %{1:5}
		%endmacro

		val TAB5 10,20,30,40,50,60

section .text

		global _start
_start:
		mov byte al, [val]		; al = 10
		mov byte bl, [val+1]	; bl = 20

		mov eax, 1				; sys_exit
		mov ebx, 0
		int 80h
