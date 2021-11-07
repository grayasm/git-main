		; Procedure library cotaining the main program:
		; - the single assembly file with a "_start" label
		; - it contains the main program and returns to system (sys_exit)
		; - can call/use procedures and data defined outside this file, by
		;   declaring them "EXTERN"
		; - can export procedures and data by declaring them "GLOBAL"


		; Build using these commands:
		; nasm -f elf -g -F stabs module_lib.asm -l module_lib.lst -o module_lib.o
		; nasm -f elf -g -F stabs module_main.asm -l module_main.lst -o module_main.o
		; ld -m elf_i386 -o module module_lib.o module_main.o


section .bss
section .data
		Text2		db "Printed from main!",10
		Size2		equ $ - Text2
		Text3		db "Printed from module!",10
		Size3		equ $ - Text3
		sys_exit	equ 1
		sys_write	equ 4
		stdout		equ 1
section .text

extern PrintExt					; import procedure
extern Text, Size				; import data

global _start

_start:
		mov eax, Text3
		mov ebx, Size3
		call PrintLoc			; Print: "Printed from module"

		call PrintExt			; call external procedure

		mov eax, Text2
		mov ebx, Size2
		call PrintLoc			; Print: "Printed from main"

		mov eax, Text
		mov ebx, Size
		Call PrintLoc			; call local procedure with external data

Exit:
		mov eax, sys_exit
		mov ebx, 0
		int 80h

		; ----------------------------------------------------------------------
		; PrintLoc - local Print procedure
		; IN: eax, ebx
		; RETURNS: -
		; MODIFIERS: -
		; DESCRIPTION: print a text passed in EAX with length in EBX
PrintLoc:
		pushad
		mov ecx, eax
		mov edx, ebx
		mov eax, sys_write
		mov ebx, stdout
		int 80h
		popad
		ret
