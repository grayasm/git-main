		;; uppercase2
		;;    a) read from stdin into a buffer
		;;    b) parse the buffer from 0 to its length
		;;    c) convert lower to upper case if necessary
		;;    d) write buffer to stdout
		;;    e) repeat these until read returns EOF
		;;    f) return 0 to system

section .bss
		BUFFLEN		equ 1024
		Buff		resb BUFFLEN
section .data
		sys_exit	equ 1
		sys_read	equ 3
		sys_write	equ 4

		stdin		equ 0
		stdout		equ 1
		stderr		equ 2
		OK			equ 0
		FAIL		equ -1
section .text
		global _start
_start:
		nop
Read:
		mov eax, sys_read		; read
		mov ebx, stdin			; from stdin
		mov ecx, Buff			; in Buff
		mov edx, BUFFLEN		; maximum length
		int 80h					; execute

		mov esi, eax			; length returned by read
		cmp eax, 0				; EOF
		je  Exit				; if EOF than return to OS
		mov eax, -1				; parse the buffer from 0 to esi-1
Scan:
		inc eax					; increment before each cycle
		cmp eax, esi
		jnb Write				; if parsed entire buff then Write
		cmp byte [Buff+eax], 0x61 ; compare with 'a'
		jb  Scan
		cmp byte [Buff+eax], 0x7a ; compare with 'z'
		ja Scan
		sub byte [Buff+eax], 0x20 ; lowercase to uppercase
		jmp Scan				; parse next character

Write:
		mov eax, sys_write		; print
		mov ebx, stdout			; to stdout
		mov ecx, Buff			; buffer
		mov edx, esi			; length of buffer
		int 80h					; execute
		jmp Read				; read until EOF

Exit:
		mov eax, sys_exit		; exit call
		mov ebx, OK				; exit code
		int 80h					; execute
