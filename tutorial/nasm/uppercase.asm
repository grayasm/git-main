		;; UPPERCASE
		;; read a character from stdin
		;; convert the character to uppercase (if necessary)
		;; write the character to the stdout
		;; repeat until done

section .bss
		buff resb 1

section .data
		sys_exit	equ 1
		sys_read	equ 3
		sys_write	equ 4
		stdin		equ 0
		stdout		equ 1

section .text
		global _start
_start:
		nop
_read:
		mov eax, sys_read		; read
		mov ebx, stdin			; from stdin
		mov ecx, buff			; in buff
		mov edx, 1				; 1 character
		int 80h					; execute
		;; what is the EOF at stdin ??
		cmp	eax, 0				; is EOF
		je	 _exit
		;; is it lowercase ?
		cmp byte [buff], 0x61	; 'a'
		jl	_write				; print if < 'a'
		cmp byte [buff], 0x7a	; 'z'
		jg	_write				; print if > 'z'
_toupper:
		sub byte [buff], 0x20
_write:
		mov eax, sys_write		; print
		mov ebx, stdout			; to stdout
		mov ecx, buff			; from buff
		mov edx, 1				; 1 character
		int 80h					; execute
		jmp _read				; loop
_exit:
		mov eax, sys_exit
		mov ebx, 0
		int 80h
