		;; mul - multiply 2 values
		;;       r/m : register/memmory
		;;       r/m8  x AL  -> AX          (16 bit value)
		;;       r/m16 x AX  -> DX and AX   (32 bit value, 16 + 16)
		;;       r/m32 x EAX -> EDX and EAX (64 bit value, 32 + 32)

section    .data
section    .text
		global    _start

_start:
		nop
		mov al, 0x2
		mov bl, 0x2
		mul bl					; ax=bl * al= 4
		;; result 16-bit
		mov eax, 1250
		mov ebx, 2
		mul ebx					; eax=ebx * eax=2500 (0x9c4)
		;; result 32-bit
		mov ax, 0xffff
		mov bx, 2
		mul bx					; ffff * 2 = 1fffe = 1 (dx) fffe (ax)
		;; result 64-bit
		mov eax, 0xffffffff
		mov ebx, 0x3b72
		mul ebx					; 3b71ffffc48e = 3b71 (edx) ffffc48e (eax)
		nop
section    .bss
