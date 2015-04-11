		; REP/REPE/REPZ/REPNE/REPNZ - repeated string operations
		; When using string instructions ESI and EDI are automatically
		; incremented (DF = 0) or decremented (DF = 1) to point to next element
		; (byte, word, dword) in the string.
		;
		; REP MOVS m8 - move ECX bytes from ESI to EDI (similar for MOVSB,MOVSW,MOVSD)
		; REP LODS AL - load ECX bytes from ESI to AL (similar for LODSB,LODSW,LODSD)
		; REP STOS m8 - fill ECX bytes at EDI with AL (similar for STOSB,STOSW,STOSD)
		; REPE CMPS m8,m8  - find nonmatching bytes is EDI and ESI
		; REPNE CMPS m8,m8 - find    matching bytes in EDI and ESI
		; REPE SCAS m8 - find non-AL byte starting at EDI
		; REPNE SCAS m8- find     AL byte starting at EDI
		;
		; Note that rep stos is the fastest way the initialize a large block of memory.
		;
section .bss
section .data
		src8  db "012345"					; rep movsb
		len8  equ $-src8
		dst8  db "......"

		src16  dw 0,1,2,3,4,5,6,7,8,9
		src32  dd 0,1,2,3,4,5,6,7,8,9
		cmp32  dd 0,1,2,3,4,5,6,7,8,9
		neq32  dd 8,7,6,5,4,3,2,1,0,0
		sca32  dd 0,0,0,3,4,5,6,7,8,9


section .text
global _start
_start:
		; rep movsb - mov ecx bytes from ESI to EDI
		mov esi, src8
		mov edi, dst8
		mov ecx, len8
		cld							; rep will increment ESI,EDI
		rep movsb					; dst8 = "012345"
		mov bl, byte [dst8+5]		; ebx= 0x35  53  '5'

		; rep lodsw - load ecx bytes from ESI to AX
		;             will change also direction with DF
		std							; set DF=1 , rep will decrement ESI,EDI
		mov esi, src16+9*2
		mov ecx, 3
		rep lodsw					; eax= 7 (3rd element in src16 tail)

		; rep stosd - fill ecx dwords at EDI with EAX
		cld
		mov eax, 0					; eax= 0
		mov edi, src32+6*4
		mov ecx, 4
		rep stosd					; [src32]= 0,1,2,3,4,5,0,0,0,0
		mov ebx, dword [src32+9*4]	; ebx = 0

		; repe cmpsd - find non-matching dword in ESI and EDI
		cld
		mov esi, src32				; [src32]= 0,1,2,3,4,5,0,0,0,0
		mov edi, cmp32				; [cmp32]= 0,1,2,3,4,5,6,7,8,9
		mov ecx, 10					; counter= 9,8,7,6,5,4,3<- here
		repe cmpsd					; ecx = 3

		; repne cmpsd - find matching dword in ESI and EDI
		cld
		mov esi, src32				; [src32]= 0,1,2,3,4,5,0,0,0,0
		mov edi, neq32				; [neq32]= 8,7,6,5,4,3,2,1,0,0
		mov ecx, 10					; counter= 9,8,7,6,5<- here
		repne cmpsd					; ecx = 5

		; repe scasd  - find non-EAX dword in EDI
		cld
		mov eax, 0
		mov edi, sca32				; [sca32] = 0,0,0,3,4,5,6,7,8,9
		mov ecx, 10					; counter = 9,8,7,6<- here
		repe scasd					; ecx = 6

		; repne scasd - find EAX dword in EDI
		std							; rep decremenent EDI
		mov eax, 0
		mov edi, sca32+9*4			; [sca32]= 0,0,0,3,4,5,6,7,8,9
		mov ecx, 10					; counter=     2,3,4,5,6,7,8,9 <- direction
		repne scasd					; ecx = 2

Exit:
		mov eax, 1
		mov ebx, 0
		int 80h
