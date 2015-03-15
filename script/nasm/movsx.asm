		;; movsx - mov with sign extension

section    .data
section    .text
		global    _start

_start:
		nop
		mov	ax, 1
		neg ax					; ax is -1
		mov	ebx, eax			; ebx is not -1
		add ebx, 1
		;; movsx - mov with sign extension
		mov ebx, 0
		movsx ebx, ax			; ebx is -1 now!!
		add ebx, 1
		nop
section    .bss
