		;; Intel Manual section 5.1.6 Bit and Byte Instructions
		;; BT						- Bit test
		;; BTS						- Bit test and set
		;; BTR						- Bit test and reset
		;; BTC						- Bit test and complement
		;; BSF						- Bit scan forward
		;; BSR						- Bit scan reverse
		;; SETE / SETZ				- Set byte if equal / zero
		;; SETNE / SETNZ			- Set byte if not equal / not zero
		;; SETA / SETNBE			- Set byte if above / not below or equal
		;; SETAE / SETNB / SETNC	- Set byte if above or equal / not below / not carry
		;; SETB / SETNAE / SETC		- Set byte if below / not abover or equal / carry
		;; SETBE / SETNA			- Set byte if below or equal / not above
		;; SETG / SETNLE			- Set byte if greater / not less or equal
		;; SETGE / SETNL			- Set byte if greater or equal / not less
		;; SETL / SETNGE			- Set byte if less / not greater or equal
		;; SETLE / SETNG			- Set byte if less or equal / not greater
		;; SETS						- Set byte if sign (negative)
		;; SETNS					- Set byte if not (non-negative)
		;; SETO						- Set byte if overflow
		;; SETNO					- Set byte if not overflow
		;; SETPE / SETP				- Set byte if parity even / parity
		;; SETPO / SETNP			- Set byte if parity odd / not parity
		;; TEST						- Logical compare
		;; CRC32					- Calculate cyclic redundancy check
		;; POPCNT					- Calculate number of bits set to 1 in 2nd operand
section .bss
section .data
		sys_exit equ 1
		zero     dw  0
section .text
		global _start
_start:
		nop
		mov eax, 1				; bit 0 is set

BT:
		;; BT - test bit in 1st operand at 0 based index given in 2nd operand
		;;      the bit value is saved in CF and remains unchanged in 1st op.
		shl eax, 1
		bt eax, 3				; if 4th bit (e.g. 1000) is 1 -> CF=1
		jnc BT					; if bt FAILED (e.g. CF=0, not set) loop BT

BTS:
		;; BTS - test and set bit in source operand
		;;       the initial bit state is saved in CF
		mov eax, 0
		bts eax, 4				; 5th bit =1 eax=0x10  16  010000b

BTR:
		;; BTR - test and reset bit to zero
		;;       the initial bit state is in CF
		mov eax, 010101b
		btr eax, 2				; eax=0x11  17  10001b   (bit is reset to 0)

BTC:
		;; BTC - test and set bit to complement
		;;       the initial bit is saved in CF
		mov eax, 01011b			; eax=0xf   15
		btc eax, 1				; eax=0x9    9   01001b
		btc eax, 2				; eax=0xd   13   01101b

BSF:
		;; BSF - bit scan forward
		;;       scan source forward HO<-LO for 1st bit =1, copy bit index to dest and clear ZF.
		;;       if source is zero set an indeterminate value in dest and set ZF.
		mov eax, 01010b			; eax=0xa   10  01010b
		mov ebx, 10100b			; ebx=0x14  20  10100b
		bsf eax, ebx			; eax=0x2    2  3rd bit of ebx is =1
		bsf eax, dword [zero]	; eax=??    [.. ZF ..]

BSR:
		;; BSR - bit scan reverse
		;;       scan source backward HO->LO for 1st bit=1, copy bit index to dest and clear ZF.
		;;       if source is zero set an indeterminate value in dest and set ZF.
		mov eax, 01010b			; eax=0xa   10  01010b
		mov ebx, 10100b			; ebx=0x14  20  10100b
		bsr eax, ebx			; eax=0x4    4  5th bit of ebx is =1

SETE:
		;; SETE - set byte if equal
		;;        set source operand to 1 if ZF=1 , or to zero otherwise.
		mov ebx, 0				; to store the result
		mov eax, 1
		inc eax
		cmp eax, 2				; 'equal'  (.. ZF ..)
		sete bl					; ebx=0x1    1

SETZ:
		;; SETZ - set byte if zero
		;;        set source operand to 1 if ZF=1 , or to zero otherwise.
		mov ebx, 0x22			; ebx= random value   0010 0010b
		mov eax, 2
		dec eax
		cmp eax, 0				; not-equal
		setz bl					; ebx=0x0

SETNE:
		;; SETNE - set byte if not equal (ZF=0)
		;;        set source operand to 1 if ZF=0, or to zero otherwise
		mov ebx, 22				; random value        0001 0110b
		mov eax, 2
		dec eax
		cmp eax, 0				; not-equal
		setne bl				; ebx=1

SETNZ:
		;; SETNZ - set byte if not zero (ZF=0). Same with SETNE.
		nop

SETA:
		;; SETA - set byte if above
		;;        set source operand to 1 if above (CF=0 and ZF=0), or to zero otherwise.
		clc						; clear CF
		mov eax, 11
		mov ebx, 10
		cmp eax, ebx			; eax > ebx is true
		seta bl					; ebx=0x1

SETNBE:
		;; SETNBE - set byte if not below or equal
		;;        set source operand to 1 if not below or equal (CF=0 and ZF=0), or to zero otherwise.
		clc						; clear CF
		mov eax, 5
		mov ebx, 10
		cmp eax, ebx			; !(eax <= ebx) - is false
		setnbe bl				; ebx=0

SETAE:
		;; SETAE - set byte if above or equal
		;;        set source operand to 1 if above or equal (CF=0), or to zero otherwise.
		clc						; clear CF
		mov eax, 15
		mov ebx, 10
		cmp eax, ebx			; eax >= ebx ->true
		setae al				; eax = 0x1

SETNB:
		;; SETNB - set byte if not below
		;;        set source operand to 1 if above or equal (CF=0), or to zero otherwise.
		clc						; clear CF
		mov eax, 10
		mov ebx, 15
		cmp eax, ebx			; !(eax < ebx) or eax >= ebx ->false
		setnb al				; eax = 0

SETNC:
		;; SETNC - set byte if not carry (CF=0)
		;;        set source operand to 1 if not caryy (CF=0), or to zero otherwise.
		clc						; clear CF
		mov eax, 1001b
		shr eax, 1				; eax = 0100b  CF=1
		setnc al				; eax = 0

SETB:
		;; SETB - set byte if below (CF=1)
		;;        set source operand to 1 if below (CF=1), or to zero otherwise.
		clc						; clear CF
		mov eax, 15
		mov ebx, 16
		cmp eax, ebx			; eax < ebx ->true
		setb al					; eax = 1

SETNAE:
		;; SETNAE - set byte if not above or equal (CF=1)
		;;        set source operand to 1 if not above or equal (CF=1), or to zero otherwise.
		clc						; clear CF
		mov eax, 15
		mov ebx, 10
		cmp eax, ebx			; !(eax >= ebx) ->false
		setnae al				; eax = 0

SETC:
		;; SETC - set byte if carry (CF=1)
		;;        set source operand to 1 if carry (CF=1), or to zero otherwise.
		clc						; clear CF
		mov eax, 010101b		; less significant bit =1
		shr eax, 1				; eax= 01010b  ->drop 1 bit into CF
		setc al					; eax= 1

SETBE:
		;; SETBE - set byte if below or equal (CF=1 or ZF=1)
		;;        set source operand to 1 if below or equal, or to zero otherwise.
		clc						; clear CF
		mov eax, 5
		mov ebx, 5
		cmp eax, ebx			; eax <= ebx ->true
		setbe al				; eax = 1

SETNA:
		;; SETNA - set byte if not above (CF=1 or ZF=1)
		;;        set source operand to 1 if not above, or to zero otherwise.
		clc						; clear CF
		mov eax, 15
		mov ebx, 10
		cmp eax, ebx			; !(eax > ebx) ->false
		setna al				; eax = 0

SETG:
		;; SETG - set byte if greater (ZF=0 or SF=OF)
		;;        set source operand to 1 if greater, or to zero otherwise.
		mov eax, -10
		mov ebx, -10
		inc eax
		cmp eax, ebx			; eax > ebx   ->true (signed compare)
		setg al					; eax = 0xffffff01   (al = 1)

SETNLE:
		;; SETNLE - set byte if not less or equal (ZF=0 or SF=OF)
		;;        set source operand to 1 if not less or equal, or to zero otherwise.
		mov eax, -22
		mov ebx, -22
		inc ebx
		cmp eax, ebx			; !(eax <= ebx)   ->false
		setnle al				; eax = 0xffffff00  (al = 0)

SETGE:
		;; SETGE - set byte if not greater or equal (SF=OF)
		;;        set source operand to 1 of not greater or equal, or to zero otherwise.
		mov eax, -10
		mov ebx, -10
		inc eax
		cmp eax, ebx			; eax >= ebx  ->true
		setge al				; eax = 0xffffff01  (al = 1)

SETNL:
		;; SETNL - set byte if not less (SF=OF)
		;;        set source operand to 1 if not less, or to zero otherwise
		mov eax, -10
		mov ebx, -10
		cmp eax, ebx			; !(eax < ebx)  ->false
		setnl al				; eax = 0xffffff00  (al = 0)

SETL:
		;; SETL - set byte if less (SF != OF)
		;;        set source operand to 1 if less, or to zero otherwise.
		mov eax, -1
		mov ebx, 1
		cmp eax, ebx			; eax < ebx  ->true
		setl al					; eax = 0xffffff01  (al = 1)

SETNGE:
		;; SETNGE - set byte if not greater or equal (SF != OF)
		;;        set source operand to 1 if not greater or equal, or to zero otherwise.
		mov eax, -3
		mov ebx, -2
		inc eax
		cmp eax, ebx			; !(eax >= ebx)  ->false
		setnge al				; eax = 0xffffff00  (al = 0)

SETLE:
		;; SETLE - set byte if less or equal (ZF=1 or SF != OF)
		;;        set source operand to 1 if less or equal, or to zero otherwise.
		mov eax, -10
		mov ebx, 0
		sub ebx, 5
		cmp eax, ebx			; eax <= ebx  ->true
		setle al				; eax = 0xffffff01  (al = 1)

SETNG:
		;; SETNG - set byte if not greater (ZF=1 or SF != OF)
		;;        set source operand to 1 if not greater, or to zero otherwise.
		mov eax, 5
		mov ebx, -5
		sub eax, 10
		cmp eax, ebx			; !(eax > ebx)  ->true
		setng al				; eax = 0xffffff01  (al = 1)

SETS:
		;; SETS - set byte if sign (SF=1)
		;;        set source operand to 1 if sign, or to zero otherwise.
		mov eax, 0
		mov ebx, -1
		test ebx, ebx			; set SF=1 if ebx < 0 (negative)
		sets al					; eax=1

SETNS:
		;; SETNS - set byte if not sign (SF=0)
		;;        set source operand to 1 if not sign, or to zero otherwise.
		mov eax, 20
		test eax, eax			; set SF=0 if eax >= 0 (positive)
		setns al				; eax = 1

SETO:
		;; SETO - set byte if overflow (OF=1)
		;;        set source operand to 1 if overflow, or to zero otherwise.
		;;        OF=1 when most significant bit changes (0->1 or 1->0)
		mov al, 128				; al = 1000 0000b
		sub al, 1				; al = 0111 1111b ->most significat bit 1->0
		seto al					; eax = 1   (due to OF=1 in flags)

		test eax, eax			; clear OF
		mov al, 127				; al = 0111 1111b
		add al, 1				; al = 1000 0000b ->most significat bit 0->1
		seto al					; eax = 1

SETNO:
		;; SETNO -  set byte if not overflow (OF=0)
		mov al, 100
		test eax, eax			; clear OF
		setno al				; eax = 1

SETPE:
		;; SETPE - set byte if parity even (PF=1)
		;;        Parity of bits set to 1 in a binary number.
		mov eax, 11100110b		; eax = 1110 0110   ->5 bits =1
		test eax, eax			; PF=0
		setpe al				; eax = 0   ->not parity
		mov eax, 11100111b		; eax = 1110 0111   ->6 bits =1
		test eax, eax			; PF=1
		setpe al				; eax = 1   ->parity

SETP:
		;; SETP - set byte if parity (PF=1)
		mov eax, 00110011b		; eax = 0011 0011   ->4 bits of 1
		test eax, eax			; PF=1
		setp al					; eax = 1

SETPO:
		;; SETPO - set byte if parity odd (PF=0)
		mov eax, 00010001b		; eax = 0001 0001   ->2 bits =1
		not al					; eax = 1110 1110   ->6 bits =1
		shl al, 1				; eax = 1101 1100   ->5 bits =1
		test eax, eax			; PF=0
		setpo al				; eax = 1

SETNP:
		;; SETNP - set byte if not parity (PF=0)
		mov eax, 00010001b		; eax = 0001 0001   ->2 bits =1
		not al					; eax = 1110 1110   ->6 bits =1
		and al, 00001110b		; eax = 0000 1110   ->3 bits =1
		test eax, eax			; PF=0
		setnp al				; eax = 1

TEST:
		;; TEST - execute AND between operands and set SF,ZF,PF according to result.
		mov eax, 0				; al = 0000 0000
		test al, al				; PF=1  ZF=1
		dec al					; al = 1111 1111   -1
		test al, al				; PF=1  SF=1

CRC32:
		;; don't know it

POPCNT:
		;; don't know it

_exit:
		mov eax, sys_exit
		mov ebx, 0
		int 80h
