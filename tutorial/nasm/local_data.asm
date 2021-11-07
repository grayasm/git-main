		; Constant data in procedure definitions
		; - not a must to place data in ".data" section if used only by a single procedure
		; - cannot place data inside the procedure (SIGFAULT), but after its ret instr.
		; - data has global visibility (cannot be duplicated in the same file)
		; - convenient when copy-pasting procedure code to other file.
		; - real local data is passed via stack frame cap.10, pag.346 (to learn about later)
section .bss
section .data
		sys_write equ 4
		stdout equ 1

section .text

		; ----------------------------------------------------------------------
		; UknownError - print a default error message
		; IN         : -
		; RETURNS    : -
		; MODIFIERS  : -
		; DESCRIPTION: print constant data defined at the procedure place
		;              (e.g. Serror) to stdout
UnknownError:
		pushad
		mov eax, sys_write
		mov ebx, stdout
		mov ecx, Serror
		mov edx, Lerror
		int 80h
		popad
		ret
		Serror db  "Unknow error",10
		Lerror equ $-Serror


global _start
_start:
		mov eax, 0xa
		mov ebx, 0xb
		mov ecx, 0xc
		mov edx, 0xd

		call UnknownError

		; Serror db "Known error",10      ; error: symbol `Serror' redefined

		mov eax, 1
		mov ebx, 0
		int 80h
