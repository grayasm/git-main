		; Local label ".label:" starts with a dot and is visible only in the
		; procedure where it is defined.
		; One cannot jump at a local label outside current procedure.
		; gdb cannot set a beakpoint on a local label, outside of the current context.

section .bss
section .data
section .text

		; ----------------------------------------------------------------------
		; shift a given number (eax) to left, a given number of bits (ebx)
		; IN         : eax, ebx
		; RETURNS    : eax
		; MODIFIERS  : eax
		; DESCRIPTION: shifts eax to left with given number of bits in ebx
Shift_left:
		push ecx				; save ecx, to be restored before ret
		mov ecx, 0
.start:
		cmp ecx, ebx
		jae .stop
		shl eax, 1
		inc ecx
		jmp .start
.stop:
		pop ecx					; restore ecx
		ret
		; ----------------------------------------------------------------------

		global _start
_start:
		mov eax, 1b				; to be shifted to left
		mov ebx, 5				; 5 times
		mov ecx, 0xc			; must not change after call
		mov edx, 0xd			; must not cahnge after call
		call Shift_left
		; check eax = 100000b   0x20   32
		; check ebx = 5
		; check ecx = 0xc
		; check edx = 0xd


		; jmp .start			; error: symbol `_start.start' undefined ;
exit:
		mov eax, 1
		mov ebx, 0
		int 80h
