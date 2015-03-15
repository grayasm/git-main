		;; Address calculation pag. 313
		;; [base + ( index * scale ) + displacement]
		;; base         = any GP register
		;; index        = any GP register
		;; scale        = 1,2,4,8  (1 does nothing)
		;; displacement = 32 bit constant

		;; lea - load effective address

section .bss
section .data
		sys_exit equ 1
		sys_read  equ 3
		sys_write equ 4
		stdin equ 0
		stdout equ 1
		Hexs db "x.......x.......x.......x.......x.......x..",10
		Hexl equ $-Hexs

section .text
		global _start
_start:
		mov ecx, -1						; ecx=-1 ; /*no cond*/; ++ecx
Count8:
		inc ecx							; increment by 1
		lea eax, [Hexs + ecx * 8]		; calculate each 8th byte address ('x')
		lea ebx, [Hexs + Hexl]			; calculate end of string address
		cmp eax, ebx					; if not outside of valid range
		jnl Write
		mov byte [eax], '8'				; modify each 8th byte 'x' with '8'
		jmp Count8
Write:
		mov eax, sys_write
		mov ebx, stdout
		mov ecx, Hexs
		mov edx, Hexl
		int 80h							;8.......8.......8.......8.......8.......8..
Exit:
		mov eax, 1
		mov ebx, 0
		int 80h
