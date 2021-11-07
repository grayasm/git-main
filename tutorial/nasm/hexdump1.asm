		;; hexdump  - resolving the first needed function
		;;   convert byte 'z' with value 0x7A into a string made of 2 bytes "7A"
		;;   "7A" is made of byte '7' = 0x37 and byte 'A' = 0x41
		;;   to convert 'z'=122 into a hexadecimal number we divide by 16
		;;   122:16=7 + 10=7+A written 0x7A
section .bss
section .data
		Txt			db "z"
		Digits		db "0123456789ABCDEF"
		Hex 		db "00"
		Hexl		equ $-Hex
		sys_exit equ 1
		sys_write equ 4
		stdin equ 0
		stdout equ 1
section .text
		global _start
_start:
		nop
Cycle:
		mov al, byte [Txt]			; 'z' = 122 decimal
		mov bl, 16					; will divide by 16 to convert dec to hex
		div bl						; 122:16=7+10 (al + ah)
		mov ebx, 0
		mov bl, al					; ebx = 7 decimal
		mov dl, byte [Digits + ebx] ; edx = '7' character, 0x37, 55
		mov byte [Hex], dl			; Hex = '70'
		mov ebx, 0
		mov bl, ah					; ebx = 10 decimal
		mov dl, byte [Digits + ebx] ; edx = 'A' character, 0x41, 65
		mov byte [Hex+1], dl		; Hex = '7A'
Write:
		mov eax, sys_write
		mov ebx, stdout
		mov ecx, Hex
		mov edx, Hexl
		int 80h
Done:
		mov eax, sys_exit
		mov ebx, 0
		int 80h
