		; STOS - store string
		; The string instruction operates on string of bytes, allowing them to be
		; moved to and from memory. It stores the source string element from the
		; AL (byte), AX (word), EAX (dword) into the memory location identified
		; with EDI register.
		;
		; STOS m8  - store AL  at ES:EDI   (short form: STOSB)
		; STOS m16 - store AX  at ES:EDI   (short form: STOSW)
		; STOS m32 - store EAX at ES:EDI   (short form: STOSD)
		;
		; String operation is more about calculating the location in the string
		; where the change will take place:
		; address = start + n_bytes          when counting in bytes
		; address = start + n_bytes * 2      when counting in words
		; address = start + n_bytes * 4      when counting in dwords
		;
		; STOS behaves more like a mov (except it is optimized to work with REP)
section .bss
section .data
		str8   db "012345"			; 1 byte per element
		str16  dw 0,1,2,3,4,5		; 2 bytes per element
		str32  dd 0,1,2,3,4,5		; 4 bytes per element


section .text
global _start
_start:
		; STOSB - store 1 byte at a time
		mov bl, byte [str8+2]		; ebx = '2'  0x32  50
		mov al, '*'					; source operand
		mov edi, str8+2				; destination operand (2nd item in m8)
		stosb						; store/copy
		mov bl, byte [str8+2]		; ebx = '*'  0x2a  42

		; STOSW - store 2 bytes at a time
		mov bx, word [str16+3*2]	; ebx = 3
		mov ax, 30					; source operand
		mov edi, str16+3*2			; destination operand (3rd item in m16)
		stosw						; store/copy
		mov bx, word [str16+3*2]	; ebx = 30

		; STOSD - store 4 bytes at a time
		mov ebx, dword [str32+5*4]	; ebx = 5
		mov eax, 50					; source operand
		mov edi, str32+5*4			; destination operand (5th item in m32)
		stosd						; store/copy
		mov ebx, dword [str32+5*4]	; ebx = 50

Exit:
		mov eax, 1
		mov ebx, 0
		int 80h
