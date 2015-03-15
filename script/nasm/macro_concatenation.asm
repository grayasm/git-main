		; Concatenating single line macro tokens: %+
		; - concatenate single-line macros to produce larger tokens
		; - a space is required after %+ to disambiguate it from syntax %+1
		;   used in multi-line macros

section .bss
section .data
section .text
		Val8   equ 8
		Val8z  equ 80
		Val8z2 equ 80*2

		global _start
_start:
		mov eax, Val %+ 8           ; eax = 8     macro expanded to Val8
		mov ebx, Val8 %+ z          ; ebx = 80    macro expanded to Val8z
		mov ecx, Val8 %+ z %+ 2     ; ecx = 160   macro expanded to Val8z2

		mov eax, 1
		mov ebx, 0
		int 80h
