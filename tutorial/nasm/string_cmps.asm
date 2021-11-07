		; CMPS/CMPSB/CMPSW/CMPSD - compare string operands
		; Instruction subtracts the destination string element from the source
		; string element and updates the status flags (CF,ZF,OF,SF,PF,AF) in
		; EFLAGS register according to the results.
		; Neither string element is written back to memory.
		;
		; CMPS  m8,m8   - compare byte at  DS:ESI with byte at  ES:EDI (short CMPSB)
		; CMPSW m16,m16 - compare word at  DS:ESI with word at  ES:EDI (short CMPSW)
		; CMPSD m32,m32 - compare dword at DS:ESI with dword at ES:EDI (short CMPSD)
		;
section .bss
section .data
		esi8   db  "abcde"				; esi+0 > edi+0
		edi8   db  "ABCDE"
		esi16  dw  0,10,20,30,40,50		; esi+0 < edi+0
		edi16  dw  0,11,22,33,44,55
		esi32  dd  0,-1,-2,-3,-4,-5		; esi+0 == edi+0
		edi32  dd  0,-1,-2,-3,-4,-5

section .text
global _start
_start:
		; cmpsb - compare byte in ESI vs EDI
		mov esi, esi8+3					; 0x64  100  'd'
		mov edi, edi8+3					; 0x44  68   'D'
		cmpsb							; esi > edi [ IF ]

		; cmpsw - compare 2 bytes in ESI vs EDI
		mov esi, esi16+3*2				; [esi16+3*2]= 30
		mov edi, edi16+3*2				; [edi16+3*2]= 33
		cmpsw							; esi < edi [ CF SF IF ]

		; cmpsd - compare 4 bytes in ESI vs EDI
		mov esi, esi32+5*4				; [esi32+5*4]= -5
		mov edi, edi32+5*4				; [edi32+5*4]= -5
		cmpsd							; esi == edi [ PF ZF IF ]

Exit:
		mov eax, 1
		mov ebx, 0
		int 80h
