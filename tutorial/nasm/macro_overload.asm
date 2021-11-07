		; Overloading multi-line macros
		; As with single−line macros, multi−line macros can be overloaded
		; by defining the same macro name several times with different numbers
		; of parameters.
section .bss
section .data
section .text
		%macro SUB 2
		sub %1, %2
		%endmacro

		%macro SUB 3
		sub %1, %2
		sub %1, %3
		%endmacro

		global _start
_start:
		mov eax, 10
		SUB eax, 1
		SUB eax, 4, 4

		mov ebx, 0
		int 80h
