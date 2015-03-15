		;; Simple stack operation: push pushf pusha pushad
		;;                         pop  popf  popa  popad
section .bss
section .data
section .text
		global _start
_start:
		nop
		;; push & pop 16bit register ax
		mov ebx, esp			; current stack address
		mov ax, 65535
		push ax
		mov ax, 0
		sub ebx, esp			; ebx = 2
		pop ax
		;; push + pop 32bit register eax
		mov ebx, esp			; current stack address
		mov eax, 0xffffffff		; 4,294,967,295
		push eax
		mov eax, 0
		sub ebx, esp			; ebx = 4
		pop eax
		;; pushf - the Flags register
		mov ebx, esp			; current stack address
		mov eax, 10
		pushf					; eflags = [AF IF]
		sub ebx, esp			; ebx = 4
		neg eax					; eflags = [CF PF AF SF IF]
		popf					; eflags = [AF TF IF]
		;;pusha - push 16 bit general purpose registers
		;;        AX CX DX BX SP BP SI DI (DDD lists them in the same order :)
		mov eax, 0
		mov ax, 10
		mov cx, 11
		mov dx, 12
		mov bx, 13
		;; esp, ebp, esi, edi - unchanged
		pusha
		mov ax, 0
		mov cx, 0
		mov dx, 0
		mov bx, 0
		popa					; esp stack pointer left unchanged
		;; pushad - push 32 bit general purpose registers
		;;          EAX ECX EDX EBX ESP EBP ESI EDI
		mov eax, 0xffff0010
		mov ecx, 0xffff0011
		mov edx, 0xffff0012
		mov ebx, 0xffff0013
		pushad
		mov eax, 0
		mov ecx, 0
		mov edx, 0
		mov ebx, 0
		popad					; restored registers
		nop
