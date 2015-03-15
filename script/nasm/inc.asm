		;; inc - increment value with 1
		;;
		;; eflags IF - Interrupt Enable Flag - reserved by OS
		;;        PF - Parity Flag, # of 1-bits is odd or even
		;;        ZF - Zero Flag, operand became zero
		;;        AF - Auxiliary Carry Flag
		;;        SF - Sign Flag, operand became negative
section    .data
section    .text
    global    _start

_start:
		nop						;      eflags [ IF ]
		mov al, 0xfe			; fe , elfags [ IF ]
		inc al					; ff , eflags [ PF SF IF ]
		inc al					; 00 , eflags [ PF AF ZF IF ]
		inc al					; 01 , eflags [ IF ]
		inc al					; 02 , eflags [ IF ]
		nop
section    .bss
