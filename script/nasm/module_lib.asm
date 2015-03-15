		; Procedure library is an assembly file with following characteristics:
		; - has no "_start" label
		; - does not return to system (sys_exit)
		; - cannot be translated by linker into its own executable program
		; - exports procedures and data with keyword "GLOBAL"
		; - can call/use exported procedures and data from other files by
		;   declaring them "EXTERN"


		; Build using these commands:
		; nasm -f elf -g -F stabs module_lib.asm -l module_lib.lst -o module_lib.o
		; nasm -f elf -g -F stabs module_main.asm -l module_main.lst -o module_main.o
		; ld -m elf_i386 -o module module_lib.o module_main.o

section .bss
section .data
		Text		db  "Text located in module.",10
		Size		equ $ - Text
		sys_write	equ 4
		stdout		equ 1
section .text

global PrintExt					; export procedure
global Text, Size				; export data

PrintExt:
		pushad
		mov eax, sys_write
		mov ebx, stdout
		mov ecx, Text
		mov edx, Size
		int 80h
		popad
		ret
