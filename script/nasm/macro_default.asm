		; Default macro parameters
		; NASM allows you to define a multi−line macro with a range of
		; allowable parameter counts. If you do this, you can specify defaults
		; for omitted parameters.
section .bss
section .data
section .text
		; macro will take minimum 2 and maximum 5 parameters
		; the last 0,0,0 are the default values for the last 3 parameters
		; therefore we must pass 2 parameters, the last 3 are optional
		%macro SUMUP 2-5 0,0,0
		  mov eax, %1
		  add eax, %2
		  add eax, %3
		  add eax, %4
		  add eax, %5
		%endmacro
global _start
_start:
		SUMUP 1,1				; eax = 2
		SUMUP 1,1,1				; eax = 3
		SUMUP 1,1,1,1			; eax = 4
		SUMUP 1,1,1,1,1			; eax = 5

		mov eax, 1				; sys_exit
		mov ebx, 0
		int 80h
