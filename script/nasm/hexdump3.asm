		;; hexdump - read hexdump1.asm & hexdump2.asm for previous steps
		;;
		;;         Buff is limited to 8 characters to match Hex 8 '00' tokens.
		;;         Read from stdin a number of characters, take 8 at a time.
		;;         Convert each character's code (e.g. 'A' 0x41, 65) in hex string representation
		;;         65:16 = 4 + 1 (ah : bh = al + ah)
		;;         Convert number to character using Digits '0123456789ABCDEF'
		;;         4 to '4' converted with: Digits + 4 = '4'
		;;         Calculate position in Hex for 41 depending on current character converted.
		;;         '41' Hex position = i * 3 + 1 for '4' and i * 3 + 2 for '1'
		;;         If Buff is less then 8, fill the rest of Hex with '00' because
		;;         Hex may contain different values from previous conversions.
		;;         When Read returns EOF jump to Exit.
section .bss
		Buffl equ 8
		Buff resb Buffl
section .data
		sys_exit equ 1
		sys_read equ 3
		sys_write equ 4
		stdin equ 0
		stdout equ 1
		Hex db " 00 00 00 00 00 00 00 00",10
		Hexl equ $-Hex
		Digits db "0123456789ABCDEF",10
		Digitsl equ $-Digits
section .text
		global _start
_start:
		nop
Read:
		mov eax, sys_read			; read
		mov ebx, stdin				; from stdin; can use also ./hexdump < file
		mov ecx, Buff				; in Buff
		mov edx, Buffl				; 8 characters at a time
		int 80h
		cmp eax, 0					; test EOF
		je  Exit					; exit if reached end of file
		push eax					; no of chars returned by Read, saved on stack.
		mov ecx, -1
Cycle:
		inc ecx						; for(i=0; i < Buffl; ++i)
		pop eax						; remember how many chars are in Buff
		cmp ecx, eax				; did we convert all of them ?
		je PreWrite					; go to PreWrite is yes
		push eax					; save no of chars in Buff
		mov eax, 0
		mov al, byte [Buff+ecx]		; take 1 char from Buff (e.g. 'A')
		mov ebx, 16					; prepare to divide by 16 (dec->hex)
		div bl						; ax : bl = al + ah   (65:16=4+1)
		mov bl, al					; ebx = 4
		mov dl, byte [Digits+ebx]	; edx = '4'
		mov ebx, ecx				; i (e.g. i = 3)
		shl ebx, 1					; j = i*2 (j = 3*2 = 6)
		add ebx, ecx				; j = j+i (j = 6+3 = 9)
		add ebx, 1					; j = j+1 (j = 9+1 = 10)
		push ebx					; save j
		mov byte [Hex+ebx], dl		; Hex = ' ?? ?? ?? 40 00 00 00 00'
		mov ebx, 0
		mov bl, ah					; ebx = 1
		mov dl, byte [Digits+ebx]	; edx = '1'
		pop ebx						; j = 10
		inc ebx						; j = j+1 = 11
		mov byte [Hex+ebx], dl		; Hex = ' ?? ?? ?? 41 00 00 00 00'
		jmp Cycle
PreWrite:
		cmp ecx, 8					; Is Buff smaller than 8 chars ?
		jae Write					; If not go to Write
		mov ebx, ecx				; If yes get i (e.g. i = 5)
		shl ebx, 1					; j = i * 2 = 10
		add ebx, ecx				; j = j + i = 10 + 5 = 15
		add ebx, 1					; j = j + 1 = 16
		push ebx					; save j
		mov dl, byte [Digits]		; edx = '0'
		mov byte [Hex+ebx], dl		; Hex = ' ?? ?? ?? ?? ?? 0? ?? ??'
		inc ebx						; j = j + 1 = 17
		mov byte [Hex+ebx], dl		; Hex = ' ?? ?? ?? ?? ?? 00 ?? ??'
		inc ecx						; ++i = 6
		jmp PreWrite
Write:
		mov eax, sys_write
		mov ebx, stdout
		mov ecx, Hex
		mov edx, Hexl
		int 80h
		jmp Read					; Read until EOF

Exit:
		mov eax, sys_exit
		mov ebx, 0
		int 80h
