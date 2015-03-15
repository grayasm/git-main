		;; add - addition

section    .data
section    .text
		global    _start

_start:
		nop
		mov al, 0x8
		mov bl, 0x7
		add bl, al                   ; f
		add bl, 0xf0                 ; ff
		add bh, 0x8                  ; 08ff
		add bh, 0x7                  ; 0fff
		add bh, 0xf0                 ; ffff
		;; can specify "byte", "word", "dword"
		mov eax, 0x0
		add byte al, 0xfe            ; fe
		add byte ah, 0xff            ; fffe
		add word ax, 0x1             ; ffff
		add dword eax, 0xffff0000    ; ffffffff
		nop
section    .bss
