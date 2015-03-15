		;; AND - bitwise AND on the destination (first) and operand (second)
		;; OR  - bitwise OR on the destination (first) and operand (second)
		;; XOR - bitwise XOR on the destination (first) and operand (second)
		;; NOT - bitwise NOT on the destination
		;;
		;;     operand can be: and immediate, a register or a memory location

section .bss
section .data
		sys_exit	equ 1
		OK			equ 0
section .text
		global _start
_start:
		nop
AND:
		mov eax, 0xcc			; al = 1100 1100   0xcc = 204
		mov ecx, 0xaa			; cl = 1010 1010   0xaa = 170
		and eax, ecx			; al = 1000 1000   0x88 = 136
OR:
		mov eax, 0xcc			; al = 1100 1100   0xcc = 204
		mov ecx, 0xaa			; cl = 1010 1010   0xaa = 170
		or eax, ecx				; al = 1110 1110   0xee = 238
XOR:
		mov eax, 0xcc			; al = 1100 1100   0xcc = 204
		mov ecx, 0xaa			; cl = 1010 1010   0xaa = 170
		xor eax, ecx			; al = 0110 0110   0x66 = 102
NOT:
		mov eax, 0xffffffcc		; al = 1100 1100   0xcc = 204
		not eax					; al = 0011 0011   0x33 = 51

Exit:
		mov eax, sys_exit
		mov ebx, OK
		int 80h
