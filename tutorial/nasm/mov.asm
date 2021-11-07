		;; mov instruction
		;; 1) data or from memory -> register
		;; 2) data or from register -> memory
section		.data
		EatMsg:	db "Eat at Joe's!"
		MyMsg :	db "mesaj"

section		.text
		global		_start

_start:
		nop
		;; mov data into register
		mov eax, 01199h
		mov ebx, eax
		;; mov address into register
		mov eax, [EatMsg]			; content " taE"
		mov ebx, EatMsg				; address of EatMsg location
		mov eax, 0x0
		mov al, [EatMsg]			; space for 1 character only 'E' 0x45
		mov al, [EatMsg+1]			; character 'a' 0x61
		mov al, [EatMsg+2]			; character 't' 0x74
		mov al, [EatMsg+0xc]		; 13th character '!' 0x21
		;; mov data into memory
		mov [MyMsg], byte 'M' 		; "Mesaj"
		mov [MyMsg], word 'Ma'		; "Masaj"
		mov [MyMsg], dword 'Cola'	; "Colaj"
		mov [MyMsg+4], byte 'c'		; "Colac"
		mov al, [MyMsg+4]			; character 'c' 0x63
		nop

section		.bss
