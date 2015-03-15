		; Short jump is out of range happens when a conditional jump is too far
		; from the label that it references, where "too far" means too many
		; locations away in memory.
		; This only applies to conditional jumps; the unconditional jump JMP is
		; not subject to this.
		; Short jump : within 127 bytes
		; Near jump  : between 127 B and 2GB
		; Far jump   : involves leaving the current code segment entirely

		; Code below does nothing. Compile only to see the error.
section .bss
section .data
section .text
global _start
_start:
		nop
		mov ecx, 0
		mov eax, 0
Loop:
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		mov eax, ecx
		inc ecx
		loop Loop				; error: short jump is out of range
		jmp Loop				; jmp not affected
		cmp eax, ecx
		jne near Loop			; use 'near' to extend jump range
Exit:
		mov eax, 1
		mov ebx, 0
		int 80h
