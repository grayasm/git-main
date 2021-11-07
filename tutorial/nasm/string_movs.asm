		; MOVS/MOVSB/MOVSW/MOVSD - Move data from String to String
		; It moves the string element addressed by ESI register to the location
		; addressed by EDI register.
		;
		; MOVS m8, m8   - move byte from address  DS:ESI to ES:EDI (short MOVSB)
		; MOVS m16,m16  - move word from address  DS:ESI to ES:EDI (short MOVSW)
		; MOVS m32,m32  - move dword from address DS:ESI to ES:EDI (short MOVSD)
		;
		; - with mov one can move from reg to mem or from mem to reg
		; - with movs we move from memory to memory
		; - movs is optimized instruction for aligned arrays in memory
		; - string operation is also about calculating the offset address in the
		;   source and destination
		; address = start + n_bytes          when counting in bytes
		; address = start + n_bytes * 2      when counting in words
		; address = start + n_bytes * 4      when counting in dwords
		;
section .bss
section .data
		src8  db "******"
		dst8  db "012345"
		src16 dw 0,10,20,30,40,50
		dst16 dw 0,1,2,3,4,5
		src32 dd 0,11,22,33,44,55
		dst32 dd 0,1,2,3,4,5

section .text
global _start
_start:
		; movsb - move 1 byte from ESI to EDI
		mov bl, byte [dst8+2]		; ebx = 0x32  50  '2'
		mov esi, src8+2				; source byte in ESI
		mov edi, dst8+2				; dest   byte in EDI
		movsb
		mov bl, byte [dst8+2]		; ebx = 0x2a  42  '*'

		; movsw - move 2 bytes from ESI to EDI
		mov bx, word [dst16+3*2]	; ebx = 3
		mov esi, src16+3*2			; source word in ESI
		mov edi, dst16+3*2			; dest   word in EDI
		movsw
		mov bx, word [dst16+3*2]	; ebx = 30

		; movsd - move 4 bytes from ESI to EDI
		mov ebx, dword [dst32+5*4]	; ebx = 5
		mov esi, src32+5*4			; source dword in ESI
		mov edi, dst32+5*4			; dest   dword in EDI
		movsd
		mov ebx, dword [dst32+5*4] ; ebx = 55

Exit:
		mov eax, 1
		mov ebx, 0
		int 80h
