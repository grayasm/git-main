		; The macro name itself: %?  and  %??
		; - supported for both single- and multi-line macros
		; - %?   refers to the macro name as invoked
		; - %??  refers to the macro name as declared
		; - the two are the same for case-sensitive macros but can differ for
		;   case-insensitive macros
section .bss
section .data
section .text

		%define   VAL8    8
		%define   VAL16  16
		%idefine  Val(x) %? %+ x        ; %? = name as invoked (VAL, vAL, etc)

		%define   vala32  32
		%define   vala64  64
		%define   vala(x) %?? %+ x      ; %?? = name as declared "vala"

		global _start
_start:
		mov eax, VAL(8)                 ; eax = 8
		mov ebx, VAL(16)                ; ebx = 16
		mov ecx, vala(32)               ; ecx = 32
		mov edx, vala(64)               ; edx = 64

		mov eax, 1
		mov ebx, 0
		int 80h
