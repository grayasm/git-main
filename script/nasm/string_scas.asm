		; SCAS/SCASB/SCASW/SCASD - scan string
		; It subtracts the destination string element from the contents of the
		; EAX,AX or AL register (depending on operand length) and updates the
		; the status flags (CF,ZF,OF,SF,PF,AF) according to the results.
		; The string element and register contents are not modified.
		;
		; SCAS m8  - compare AL with byte at ES:EDI (short SCASB)
		; SCAS m16 - compare AX with word at ES:EDI (short SCASW)
		; SCAS m32 - compare EAX with dword at ES:EDI (short SCASD)
		;
section .bss
section .data
		str8  db "012345"
		str16 dw 0,1,2,3,4,5
		str32 dd 0,1,2,3,4,5
section .text
global _start


_start:
		nop
		; scasb - compare AL with EDI
		mov al, '5'
		mov edi, str8+3				; [str8+3]= 0x33  51  '3'
		scasb						; al > edi+3 [ IF ]

		; scasw - compare AX with EDI
		mov ax, 4
		mov edi, str16+4*2			; [str16+4*2]= 4
		scasw						; ax == edi+4 [ PF ZF IF ]

		; scasd - compare EAX with EDI
		mov eax, 2
		mov edi, str32+5*4			; [str32+5*4]= 5
		scasd						; eax < edi  [ CF AF SF IF ]

Exit:
		mov eax, 1
		mov ebx, 0
		int 80h
