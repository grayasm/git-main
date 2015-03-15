		;; unsigned division with DIV
		;;
		;; dividend / divisor = quotient + remainder
		;; edx:eax  / operand = eax      + edx
		;;
		;; div with operand(m/r) of 8,16 or 32 bit size
		;; div bh;        ax      / bh  =  al + ah
		;; div bx;        dx:ax   / bx  =  ax + dx
		;; div ebx;       edx:eax / ebx = eax + edx
		;;
		;; similar as above with operand in memory - I couldn't find how.
		;; div BYTE m8; ??
		;; div WORD m16; ??
		;; div DWORD m32; ??


section    .data
		var8:  db 255			; byte
        var16: dw 65535			; word
        var32: dd 4294967295	; dword

section    .text
		global    _start

_start:
		nop
		;; divide by 8 bit register
		mov ax, 10
		mov bh, 2
		div bh					; ax / bh = al + ah

		;; divide by 16 bit register
		;; 655340 / 65534 = 10
		;; 9 FFEC / FFFE  = A

		mov dx, 0x9
		mov ax, 0xffec
		mov bx, 65534
		div bx					; dx:ax / bx = ax + dx

		;; divide by 32 bit register
		;; 4294967297 / 65536 = 65536 + 1
		;; 0x1:00000001  / 0x10000 = 0x10000 + 1

		mov edx, 0x1
		mov eax, 0x00000001
		mov ebx, 0x10000
		div ebx					; edx:eax / ebx = eax + edx

section    .bss
