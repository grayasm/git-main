		;; Shift and Rotate instructions
		;;
		;; SAR - shift arithmetic right
		;; SHR - shift logical right
		;; SAL - shift arithmetic left
		;; SHL - shift logical left
		;; SHRD - shift right double
		;; SHLD - shift left double
		;; ROR - rotate right
		;; ROL - rotate left
		;; RCR - rotate through carry right
		;; RCL - rotate through carry left
section .bss
section .data
		sys_exit	equ 1
		OK			equ 0
section .text
		global _start
_start:
		nop
SAR:
		;; SAR eax, r/m8 - shift to right with value of 8bit reg/mem
		mov eax, 0x731			; 0111 0011 0001 = 0x731
		mov cl, 4				; 4 bits to right
		sar eax, cl				; 0000 0111 0011 = 0x73 = 115 (eax)
SHR:
		;; SHR - same operation as SAR
		mov eax, 010010101b
		shr eax, 3				; eax=010010(101-shifted)=0x12=18, cf=1
SAL:
		;; SAL eax, r/m8 - shift to left with value of 8bit reg/mem
		mov eax, 0xffffffff
		sal eax, 16				; eax = 0xffff0000
SHL:							; similar operation with SAL
SHRD:
		;; SHRD eax, ebx, cl - shift eax with cl value to righ
		;;                     fill eax at left from right of ebx
		mov eax, 0x0f00
		mov ebx, 0xf0
		mov cl, 8
		shrd eax, ebx, cl		; eax = 0xf000 000f
SHLD:
		;; SHLD eax, ebx, cl - shift eax with cl value to left
		;;                     fill eax at right from left of ebx
		mov eax, 0x00f00000
		mov ebx, 0x0f000000
		mov cl, 8
		shld eax, ebx, cl		; eax = 0xf000 000f
ROR:
		;; ROR eax, r/m8 - rotate to right, fill at left of eax from right
		mov eax, 0x11
		mov cl, 4
		ror eax, cl				; eax = 0x1000 0001
ROL:
		;; ROL eax, r/m8 - rotate to left, fill at right of eax from left
		mov eax, 0x11000000
		mov cl, 4
		rol eax, cl				; eax = 0x1000 0001
RCR:
		;; RCR eax, r/m8 - rotate to right
		;;                 from right fill in CF
		;;                 from CF fill eax at left side
		mov eax, 0111b
		mov cl, 2
		clc						; clear cf from prev. op
		rcr eax, cl				; eax = 0x8000 0001, cf=1
RCL:
		;; RCL eax, r/m8 - rotate to left
		;;                 from left fill in CF
		;;                 from CF fill eax at right side
		mov eax, 0xe0000000		; 1110 0000 .... 0000 0000
		mov cl, 2
		clc						; clear cf from prev. op
		rcl eax, cl				; eax = 0x80000001 = 1000 0000 ... 0001, cf=1
Exit:
		mov eax, sys_exit
		mov ebx, OK
		int 80h
