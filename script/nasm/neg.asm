		;; neg - negate a value (calculate two's complement value)

section    .data
section    .text
		global    _start

_start:
		nop
		mov al, 42              ; 2a
		neg al                  ; d6
		add al, 42              ; 0
		mov bl, 42              ; 2a
		neg bl                  ; d6
		neg bl                  ; 2a
		nop
section    .bss
