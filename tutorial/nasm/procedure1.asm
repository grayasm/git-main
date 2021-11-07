		;; procedure - a function in assembly language (cap.10, pag.333)
		;;             Starts with a label:
		;;             pushes registers to stack before execution
		;;             executes function
		;;             pops registers
		;;             ret - return to caller
		;;             use 'call' to call the procedure
section .bss
section .data
		Texts db "0123456789"
		Textl equ $-Texts
		sys_exit equ 1
		sys_write equ 4
		stdout equ 1
section .text

		; ----------------------------------------------------------------------
		; Reverse    : function reverses the content of a string
		; IN         : EAX, EBX
		; RETURNS    : nothing
		; MODIFIERS  : nothing (exept the string at EAX)
		; DESCRIPTION: reverses the string at EAX with length in EBX
		;              All GP registers are preserved.
Reverse:
		pushad							; save all GP registers
		cmp ebx, 0						; test for 0 length string
		jle .reverse_end
		mov esi, eax					; esi = begin of string
		lea edi, [eax+ebx]				; edi = 1 past end of string
		sub edi, 1						; edi = end of string
		mov eax, 0						; clear eax, will use only al part
		mov ebx, 0						; clear ebx, will use only bl part
.reverse_start:							; loop
		cmp esi, edi					; while esi <= edi
		jg .reverse_end
		mov al, [esi]					; move 1 character
		mov bl, [edi]					; move 1 character
		mov byte [esi], bl				; exchange the 2 characters
		mov byte [edi], al
		inc esi							; advance string pointers
		dec edi
		jmp .reverse_start				; repeat
.reverse_end:
		popad							; restore all GP registers
		ret								; return to caller

		global _start
_start:
		mov eax, Texts					; 1st parameter
		mov ebx, Textl					; 2nd parameter
		call Reverse					; call procedure with 2 parameters
write:
		mov eax, sys_write
		mov ebx, stdout
		mov ecx, Texts
		mov edx, Textl
		int 80h
exit:
		mov eax, sys_exit
		mov ebx, 0
		int 80h
