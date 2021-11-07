		;; Address calculation pag. 313
		;; [base + ( index * scale ) + displacement]
		;; base         = any GP register
		;; index        = any GP register
		;; scale        = 1,2,4,8  (1 does nothing)
		;; displacement = 32 bit constant


section .bss
section .data
		stdin equ 0
		stdout equ 1
		stderr equ 2

		sys_exit equ 1
		sys_read equ 3
		sys_write equ 4

		Flt: dd 10,20,30,40,50

section .text
		global _start

_start:
		nop
		mov ecx, 0				; for(i=0; Flt[i] < 50; ++i)
Loop:
		mov eax, dword [Flt + ecx*4] ; count 4 bytes at a time
		inc ecx
		cmp eax, 50
		jb Loop

		mov eax, sys_exit
		mov ebx, 0
		int 80h
