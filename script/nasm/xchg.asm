; use mov to exchage data between registers or xchg
section		.data
section		.text
    global	_start

_start:
		nop
		mov ax,067FEh
		mov bl,ah
		mov bh,al
		; or switch in 1 instruction
		xchg ax,bx
		xchg al,ah
		nop

section		.bss
