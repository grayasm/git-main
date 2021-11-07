		; Single-line macro
		; - using %define preprocessor directive
		; - it works in a similar way to C
		; - expanding macro happens when it is encountered in text code
		; - case-insensitive macro uses %idefine
		; - recursive macro stops expanding on 2nd encounter
section .bss
section .data
		sys_write equ 4
		stdout    equ 1
		strMsg db "0123456789"
		lenMsg equ $-strMsg

section .text
		%define a(x)        1 + b(x)    ; single-line macro
		%define b(x)        2*x
		%define foo(x)      1+x         ; overloaded single-line macro
		%define foo(x,y)    1+x*y       ; preprocessor will distinguish which foo
		                                ; to expand to by counting the parameters
		%define off(x,y,z)  x + y*z
		%idefine bAz(x)     2*x         ; Case insensitive %define


		%macro Write 2                  ; multi-line macro
		mov eax, sys_write
		mov ebx, stdout
		mov ecx, %1
		mov edx, %2
		int 80h
		%endmacro


		global _start
_start:
		mov eax, a(5)              ; eax = 1 + 2 * 5 = 11
		mov ebx, foo(3)            ; ebx = 1 + 3     = 4
		mov ecx, foo(4, 2)         ; ecx = 1 + 4 * 2 = 9
		mov edx, foo(foo(3), 2)    ; edx = xxx 4 * 2 = 8 !!! recursive expansion
		                           ; is blocked on 2nd encounter of the same macro

		mov ebx, strMsg
		mov byte [off(ebx,1,0)], 'x'             ;strMsg= x123456789
		mov byte [off(ebx,1,lenMsg-1)], 'x'      ;strMsg= x12345678x
		Write strMsg, lenMsg

		mov eax, BAZ(2)            ; matched to bAz(2) = 2*2
		mov eax, bAZ(3)            ; matched to bAz(3) = 2*3

		mov eax, 1
		mov ebx, 0
		int 80h
