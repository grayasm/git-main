		;; twoLineMsg - 10 is end of line (EOL)

section .data
	oneLineMsg: db "One line message!",10
	oneLineLen:	equ $-oneLineMsg
	twoLineMsg: db "First line of text",10,"Second line of text!",10
	twoLineLen:	equ $-twoLineMsg

		;;  syscalls
		sys_write 	equ 4
		sys_exit	equ 1

		;;  syscall constants
		STDOUT		equ 1

section .bss
section .text
		global _start
	_start:
		mov eax, sys_write		; function sys_write
		mov ebx, STDOUT			; print to stdout
		mov ecx, oneLineMsg		; one line text
		mov edx, oneLineLen		; length of text
		int 80H					; execute
		;;
		mov eax, sys_write		; function sys_write
		mov ebx, STDOUT			; print to stdout
		mov ecx, twoLineMsg		; two line of text
		mov edx, twoLineLen		; length of text
		int 80H					; execute
		;;
		mov eax, sys_exit		; return
		mov ebx, 0				; zero
		int 80H					; execute
