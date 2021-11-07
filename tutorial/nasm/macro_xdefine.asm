		; %xdefine
		; - a single-line macro
		; - evaluated on spot where it is defined, not expanded
		; - can be overwritten later
		; - if not overwritten its value remains the same
		; - if definition cannot be resolved due to symbols not yet defined
		;   %xdefine will become %define

section .bss
section .data
section .text
		%define Five   5
		%define Four   Five - 1	; evaluated later to whatever Five -1 is.
		%define Five   1		; overwrite 5 with 1

		%xdefine xFive 5
		%xdefine xFour xFive - 1 ; evaluated directly here to 4
		%xdefine xFive 1		 ; overwrite 5 with 1


		global _start
_start:
		mov eax, Five			; eax = 1
		mov ebx, Four			; ebx = 0
		mov ecx, xFive			; ecx = 1
		mov edx, xFour			; edx = 4

		mov eax, 1
		mov ebx, 0
		int 80h
