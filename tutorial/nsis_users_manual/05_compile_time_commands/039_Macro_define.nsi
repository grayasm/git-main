; !define   [/ifndef  |  /redef]
;           ([/date|/utcdate]  gflag  [value])  | 
;           (/file    gflag  filename.txt)        |
;           (/intfmt  gflag  fmtstr  value)     |
;           (/math    gflag  val1  OP  val2)

; This command will add gflag to the global define list.
; This will have a similar effect as using the /D switch on the command line
; (the define only becomes effective after the !define command).

; If /date or /utcdate are used, value will be passed to strftime() 
; and the result will be used as the value of gflag. 
; strftime converts special symbols into certain parts of the current time or date.
; For example, %H will be converted into the current hour in 24-hour format. 

; If /file is used, the entire text file specified (including whitespace and newlines) 
; will be read and placed into gflag.

; If /intfmt is used, value is interpreted as a integer and 
; formated using the same syntax as IntFmt.

; If /math is used, the result of 'val1 OP val2', where OP may be
; +,-,*,/,%,<<,>>,>>>,&,|,^,~,!,&& or ||, will be used as the value of gflag. 
; Note that val1 AND val2 MUST be integer values!

!define USE_SOMETHING
!define VERSION 1.2
!define /date NOW "%H:%M:%S %d %b, %Y"
!define /math RESULT 3 + 10
!define /math REST 15 % ${RESULT}
!define /file BunchaStuff somesourcefile.cpp
!define /redef USE_SOMETHING ${RESULT} ;redefine USE_SOMETHING
!define /intfmt HEX "0x%X" 3133078222

; default
Section
SectionEnd

; compiler output:
/*
!define: "USE_SOMETHING"=""
!define: "VERSION"="1.2"
!define: "NOW"="11:48:49 25 Dec, 2020"
!define: "RESULT"="13"
!define: "REST"="2"
!define: "BunchaStuff"="int main(int argc, char* argv[])
{
	return 0;
}"
!define: "USE_SOMETHING"="13"
!define: "HEX"="0xBABEFACE"
*/