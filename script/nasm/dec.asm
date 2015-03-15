		;; dec - decrement value with 1
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
		mov al, 0x1				; 01 , elfags [ IF ]
		dec al					; 00 , eflags [ PF ZF IF ]
		dec al					; ff , eflags [ PF AF SF IF ]
		dec al					; fe , eflags [ SF IF ]
		dec al					; fd , eflags [ SF IF ]
		nop
section    .bss
