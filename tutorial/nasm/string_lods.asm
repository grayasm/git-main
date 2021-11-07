		; LODS/LODSB/LODSW/LODSD - instruction loads the source string element
		; identified by ESI into EL, AX or EAX register.
		;
		; LODS m8  - load byte at DS:ESI into AL   (short LODSB)
		; LODS m16 - load word at DS:ESI into AX   (short LODSW)
		; LODS m32 - load dword at DS:ESI into EAX (short LODSD)
		;
		; String operation is also about calculating the location in the string
		; where the value is copied from:
		; address = start + n_bytes          when counting in bytes
		; address = start + n_bytes * 2      when counting in words
		; address = start + n_bytes * 4      when counting in dwords
section .bss
section .data
		str8  db "012345"
		str16 dw 0,1,2,3,4,5
		str32 dd 0,11,22,33,44,55

section .text
global _start
_start:
		; lodsb - load ESI byte into AL
		mov esi, str8+2
		lodsb						; eax = 0x32  50  '2'

		; lodsw - load ESI word into AX
		mov esi, str16+3*2
		lodsw						; eax = 3

		; lodsd - load ESI dword into EAX
		mov esi, str32+5*4
		lodsw						; eax = 55

Exit:
		mov eax, 1
		mov ebx, 0
		int 80h
