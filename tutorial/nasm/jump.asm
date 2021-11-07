		;; What on earth is "jle" ?
		;; http://leto.net/writing/nasm.php
section .bss
section .data
		sys_exit equ 1
		success  equ 0
		error    equ -1
section .text
		global _start
_start:
		mov eax, 1
		mov ebx, 2
		cmp eax, ebx
		;;
		ja     _exit			; jump if above                 (unsigned)
		jae    _exit			; jump if above or equal        (unsigned)
		jb     _exit			; jump if below                 (unsigned)
		jbe    _exit			; jump if below or equal        (unsigned)
		jc     _exit			; jump if carry
		jcxz   _exit			; jump if CX is zero
		je     _exit			; jump if equal
		jecxz  _exit			; jump if ECX is zero
		jz     _exit			; jump if zero
		jg     _exit			; jump if greater                  (signed)
		jge    _exit			; jump if greater or equal         (signed)
		jl     _exit			; jump if less                     (signed)
		jle    _exit			; jump if less or equal            (signed)
		jmp    _exit			; unconditional jump
		jna    _exit			; jump if not above             (unsigned)
		jnae   _exit			; jump if not above or equal    (unsigned)
		jnc    _exit			; jump if not carry
		;; jncxz  _exit			; jump if CX not zero
		jne    _exit			; jump is not equal
		jng    _exit			; jump if not greater              (signed)
		jnge   _exit			; jump if not greater or equal     (signed)
		jnl    _exit			; jump if not less                 (signed)
		jnle   _exit			; jump if not less or equal        (signed)
		jno    _exit			; jump if not  overflow
		jnp    _exit			; jump if not  parity
		jns    _exit			; jump if not signed
		jnz    _exit			; jump if not zero
		jo     _exit			; jump if overflow
		jp     _exit			; jump if parity
		jpe    _exit			; jump if parity even
		jpo    _exit			; jump if parity odd
		js     _exit			; jump if signed
		jz     _exit			; jump if zero

_exit:
		mov eax, sys_exit
		mov ebx, success
		int 80h
