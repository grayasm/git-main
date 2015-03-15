		;; jnz - Jump if Not Zero (elfags ZF not set)

section    .data
section    .text
		global    _start

_start:
		nop
		mov al, 0x5
		mov bl, 0x5
Loop:	dec al
		jnz Loop
		;; al is zero                ; eflags [ PF ZF IF ]
		mov bl, al                   ; confirm zero value
		nop
section    .bss
