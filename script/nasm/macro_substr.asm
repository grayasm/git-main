		; Extracting substrings:  %substr
		; Individual letters or substrings in strings can be extracted using the
		; %substr operator.
section .bss
section .data
		%substr t1 'xyzw' 1        ; equivalent to %define t1 'x'
		%substr t2 'xyzw' 2        ; equivalent to %define t2 'y'
		%substr t3 'xyzw' 3        ; equivalent to %define t3 'z'
		%substr t4 'xyzw' 2,2      ; equivalent to %define t4 'yz'
		%substr t5 'xyzw' 2,-1     ; equivalent to %define t5 'yzw'
		%substr t6 'xyzw' 2,-2     ; equivalent to %define t6 'yz'

		msg1 db "t1=",t1,10
		len1 equ $-msg1
		msg2 db "t2=",t2,10
		len2 equ $-msg2
		msg3 db "t3=",t3,10
		len3 equ $-msg3
		msg4 db "t4=",t4,10
		len4 equ $-msg4
		msg5 db "t5=",t5,10
		len5 equ $-msg5
		msg6 db "t6=",t6,10
		len6 equ $-msg6


section .text

		%macro Write 2
		mov ecx, %1
		mov edx, %2
		mov eax, 4				; sys_write
		mov ebx, 1				; stdout
		int 80h
		%endmacro

		global _start
_start:
		Write msg1, len1
		Write msg2, len2
		Write msg3, len3
		Write msg4, len4
		Write msg5, len5
		Write msg6, len6

		mov eax, 1
		mov ebx, 0
		int 80h
