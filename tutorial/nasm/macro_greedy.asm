		; NASM allows you to define the last parameter of a macro to be greedy,
		; meaning that if you invoke the macro with more parameters than it
		; expects, all the spare parameters get lumped into the last defined one
		; along with the separating commas.
section .bss
section .data
section .text

		%macro WriteGreedy 1+
			jmp %%endstr
			%%str: db %1		; greedy parameter
			%%endstr:
			mov eax, 4			; sys_write
			mov ebx, 1			; stdout
			mov ecx, %%str
			mov edx, %%endstr - %%str
			int 80h
		%endmacro

global _start
_start:
		WriteGreedy "This text",10,"is passed",10,"in more than",10,"one parameter"

		mov eax, 1
		mov ebx, 0
		int 80h
