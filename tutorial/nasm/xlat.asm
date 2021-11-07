		;; XLAT - table lookup translation
		;;        xlat/xlatb replace the contents of the AL register with a
		;;        byte read from a translation table in memory at EBX as below:
		;;        mov byte al, [ebx + al]

section .bss
section .data
		Txtt db "ABCDEFG",10
		Txtl equ $ - Txtt
section .text
		global _start
_start:
		;; equivalent of xlat
		mov eax, 1					; clear ho-bytes in eax, not needed with xlat
		mov ebx, Txtt				; address of Txtt must be in ebx
		mov byte al, [ebx+eax]		; eax = 0x42  66   'B'
xlat:
		;; same thing using xlat
		mov eax, 0xff00ff01			; al=1, xlat ignores ho-bytes of eax
		mov ebx, Txtt
		xlat						; mov byte al, [ebx + al]
									; eax = 0xff00ff42  ....66  'B'
									; xlat uses only AL
exit:
		mov eax, 1
		mov ebx, 0
		int 80h
