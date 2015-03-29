		; To jump to a label local to the macro we need to prefix it with %%
		; Every use of the macro will make up a different ‘real’ name to
		; substitute for the label %%
		; The names NASM invents are of the form ..@2345.label_name,
		; where the number 2345 changes with every macro call.
		; The ..@ prefix prevents macro−local labels from interfering with the
		; local label mechanism, as described in section 3.9. You should avoid
		; defining your own labels in this form (the ..@ prefix, then a number,
		; then another period) in case they interfere with macro−local labels.
section .bss
section .data
section .text

		; decrement parameter only if > 0, else jump to local label %%final
		%macro DECREMENT 1
			cmp %1, 0
			je %%final
			sub %1, 1
			%%final:
		%endmacro

global _start
_start:
		mov eax, 1
		DECREMENT eax
		DECREMENT eax
		DECREMENT eax

		mov eax, 1
		mov ebx, 0
		int 80h
