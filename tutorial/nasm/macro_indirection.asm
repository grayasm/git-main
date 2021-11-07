		; Macro indirection:   %[...]
		; - used to expand macro in context where macro expansion would otherwise
		;   not occur, including in the names of other macros
		; - similar with macro concatenation in C : ##
		; - ex: Foo%[32] is evaluated to Foo32
		; - ex: %[Foo%[16 + 8*2]] is evaluated to Foo32
		; - macro is evaluated when defined not expanded, similar with %xdefine

section .bss
section .data
section .text
		%define Rand  32
		%define Def32 %[Rand]          ; expanded now, set to 32
		%define Def64 %[Def]32 + 32    ; expanded now, set to 64
		%define Rand  16               ; overwrite 32 with 16


		global _start
_start:
		mov eax, %[Rand]               ; eax = 16
		mov ebx, %[Def]32              ; ebx = 32
		mov ecx, Def%[32+32]           ; ecx = 64
		mov edx, %[Def]64 - 32         ; edx = 32
		mov eax, %[%[Def]%[32 + 16*2]] ; eax = 64

		mov eax, 1
		mov ebx, 0
		int 80h
