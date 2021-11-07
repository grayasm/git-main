		; Macros
		; - a label that stands for some sequence of text lines
		; - can be a set of instructions but not necessary
		; - the assembler expands the macro label with the text lines
		; - define a macro as:
		; %macro macro_name number_of_params
		; <macro body>
		; %endmacro
		;
		; - inside macro body %1 is the 1st parameter, %2 the second, etc
		; - "calling" a macro from inside a macro is allowed
		; - a macro without parameters must have explicit 0: %macro Exit 0
		;
		; - a local label to a macro is prefixed by %% (e.g.   %%exit:  )

section .bss
section .data
		sys_write equ 4
		stdout    equ 1
		esc38245144482254255226m db 27,"[38;2;45;14;4;48;2;254;255;226m"
		len38245144482254255226m equ $-esc38245144482254255226m
		escJ  db 27,"[2J"
		lenJ  equ $-escJ
		strMsg db "Example of a macro in assembly with nasm",10
		       db "%macro Write 2",10
		       db "... (instructions)",10
		       db "%endmacro",10
		       db 10,10,10
		       db "Write Text, LENGTH",10
		lenMsg equ $-strMsg


section .text

		%macro Write 2
		pushad
		mov ecx, %1
		mov edx, %2
		mov eax, sys_write
		mov ebx, stdout
		int 80h
		popad
		%endmacro

		global _start
_start:
		Write esc38245144482254255226m, len38245144482254255226m
		Write escJ, lenJ
		Write strMsg, lenMsg

		mov eax, 1
		mov ebx, 0
		int 80h
