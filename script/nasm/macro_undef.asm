		; Undefining single-line macro:  %undef

section .bss
section .data
section .text

		%define  foo    8
		%xdefine bar2   foo * 2
		%xdefine bar4   foo * 4
		%undef   foo                  ; removing foo macro

		global _start
_start:
		mov eax, bar2                 ; eax = 16
		mov ebx, bar4                 ; ebx = 32
		; mov ecx, foo                ; error: symbol `foo' undefined

		mov eax, 1
		mov ebx, 0
		int 80h
