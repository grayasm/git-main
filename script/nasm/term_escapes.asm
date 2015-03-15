		; ANSI escape code or escape sequences is a method using in-band
		; signaling to control the formatting, color, and other output options
		; on video text terminals.
		;
		; Escape sequences are of the form= 27,"[ ... " , see below almost all
		; that are explained on wikipedia at:
		; http://en.wikipedia.org/wiki/ANSI_escape_code
		;
		; In DDD use next to step faster through the program.


section .bss
section .data
		sys_write equ 4
		stdout equ 1

		; ANSI escape sequences
		strRnd0   db "ANSI escape sequences",10,"cursor is here:"
		lenRnd0   equ $-strRnd0

		escB db 27,"[3B","ESC[3B - cursor 3 cells down"
		lenB equ $-escB

		escA   db 27,"[2A","ESC[2A - cursor 2 cells up"
		lenA   equ $-escA

		strRnd2   db 10,10,10,"3 new lines followed by new line",10
		lenRnd2   equ $-strRnd2

		escC   db 27,"[50C","ESC[50C - cursor 50 cells forward"
		lenC   equ $-escC

		escD  db 27,"[100D","ESC[100D - cursor 100 cells back"
		lenD  equ $-escD

		escE  db 27,"[3E","ESC[3E - cursor down 3 new lines"
		lenE  equ $-escE

		escF  db 27,"[2F","ESC[2F - cursor up 2 new lines"
		lenF  equ $-escF

		strRnd3  db 10,10,10,10,"cursor is here:"
		lenRnd3  equ $-strRnd3

		escG  db 27,"[40G","ESC[40G - cursor to column 40"
		lenG  equ $-escG

		escH  db 27,"[20;5H","ESC[20;5H - cursor to row=20, col=5"
		lenH  equ $-escH

		escJ  db 27,"[2J","ESC[2J - erase display"
		lenJ  equ $-escJ

		strRnd4 db 10,"cursor is here:"
		lenRnd4 equ $-strRnd4

		escK  db 27,"[2K","ESC[2K - erase line"
		lenK  equ $-escK

		strRnd5 db 27,"[1;1H","line1",10,"line2",10,"line3",10,"cursor is here:"
		lenRnd5 equ $-strRnd5

		escS  db 27,"[1S","ESC[1S - scroll page up 1 line"
		lenS  equ $-escS

		escT  db 27,"[25T","ESC[25T - scroll page down 25 lines"
		lenT  equ $-escT

		strRnd6 db 10,"cursor is here:"
		lenRnd6 equ $-strRnd6

		escs  db 27,"[s","ESC[s  - save cursor position"
		lens  equ $-escs

		strRnd7 db 10,"cursor is here:"
		lenRnd7 equ $-strRnd7

		escu  db 27,"[u","ESC[u  - restore cursor position"
		lenu  equ $-escu

		strRnd8 db 10,10,"cursor is here:"
		lenRnd8 equ $-strRnd8

		esc25l db 27,"[?25l","ESC[?25l - hides the cursor"
		len27l equ $-esc25l

		strRnd9 db 10,"cursor is here:"
		lenRnd9 equ $-strRnd9

		esc25h db 27,"[?25h","ESC[?25h - shows the cursor"
		len25h equ $-esc25h

		; select graphic rendition with
		strRnd11 db 10,"cursor is here:"
		lenRnd11 equ $-strRnd11

		esc0m db 27,"[0m","ESC[0m - all attributes off",10
		len0m equ $-esc0m

		strRnd12 db 27,"[1;1H"
		lenRnd12 equ $-strRnd12

		esc30m db 27,"[30m","ESC[30m - foreground (30 + 0=black)",10
		len30m equ $-esc30m

		esc31m db 27,"[31m","ESC[31m - foreground (30 + 1=red)",10
		len31m equ $-esc31m

		esc32m db 27,"[32m","ESC[32m - foreground (30 + 2=green)",10
		len32m equ $-esc32m

		esc33m db 27,"[33m","ESC[33m - foreground (30 + 3=yellow)",10
		len33m equ $-esc33m

		esc34m db 27,"[34m","ESC[34m - foreground (30 + 4=blue)",10
		len34m equ $-esc34m

		esc35m db 27,"[35m","ESC[35m - foreground (30 + 5=magenta)",10
		len35m equ $-esc35m

		esc36m db 27,"[36m","ESC[36m - foreground (30 + 6=cyan)",10
		len36m equ $-esc36m

		esc37m db 27,"[37m","ESC[37m - foreground (30 + 7=white)",10
		len37m equ $-esc37m

		esc3740m db 27,"[37;40m","ESC[37;40m - background (40 + 0=black)",10
		len3740m equ $-esc3740m

		esc3741m db 27,"[37;41m","ESC[37;41m - background (40 + 1=red)",10
		len3741m equ $-esc3741m

		esc3742m db 27,"[37;42m","ESC[37;42m - background (40 + 2=green)",10
		len3742m equ $-esc3742m

		esc3743m db 27,"[37;43m","ESC[37;43m - background (40 + 3=yellow)",10
		len3743m equ $-esc3743m

		esc3744m db 27,"[37;44m","ESC[37;44m - background (40 + 4=blue)",10
		len3744m equ $-esc3744m

		esc3745m db 27,"[37;45m","ESC[37;45m - background (40 + 5=magenta)",10
		len3745m equ $-esc3745m

		esc3746m db 27,"[37;46m","ESC[37;46m - background (40 + 6=cyan)",10
		len3746m equ $-esc3746m

		esc3047m db 27,"[30;47m","ESC[30;47m - background (40 + 7=white)",10
		len3047m equ $-esc3047m

		esc30471m db 27,"[30;47;1m","ESC[30;47;1m - 30=black,47=white,1=bold or increased intensity",10
		len30471m equ $-esc30471m

		esc31471m db 27,"[31;47;1m","ESC[31;47;1m - 31=red,47=white,1=bold",10
		len31471m equ $-esc31471m

		esc32471m db 27,"[32;47;1m","ESC[32;47;1m - 32=green,47=white,1=bold",10
		len32471m equ $-esc32471m

		esc33401m db 27,"[33;40;1m","ESC[33;40;1m - 33=yellow,40=black,1=bold",10
		len33401m equ $-esc33401m

		esc34471m db 27,"[34;47;1m","ESC[34;47;1m - 34=blue,47=white,1=bold",10
		len34471m equ $-esc34471m

		esc35471m db 27,"[35;47;1m","ESC[35;47;1m - 35=magenta,47=white,1=bold",10
		len35471m equ $-esc35471m

		esc36471m db 27,"[36;47;1m","ESC[36;47;1m - 36=cyan,47=white,1=bold",10
		len36471m equ $-esc36471m

		esc37401m db 27,"[37;40;1m","ESC[37;40;1m - 37=white,40=black,1=bold",10
		len37401m equ $-esc37401m

		esc30472m db 27,"[30;47;2m","ESC[30;47;2m - ... 2=faint or decreased intensity (not widely supported)",10
		len30472m equ $-esc30472m

		esc31472m db 27,"[31;47;2m","ESC[31;47;2m - 31=red,47=white,2=faint",10
		len31472m equ $-esc31472m

		esc32472m db 27,"[32;47;2m","ESC[32;47;2m - 32=green,47=white,2=faint",10
		len32472m equ $-esc32472m

		esc33402m db 27,"[33;40;2m","ESC[33;40;2m - 33=yellow,40=black,2=faint",10
		len33402m equ $-esc33402m

		esc34472m db 27,"[34;47;2m","ESC[34;47;2m - 34=blue,47=white,2=faint",10
		len34472m equ $-esc34472m

		esc35472m db 27,"[35;47;2m","ESC[35;47;2m - 35=magenta,47=white,2=faint",10
		len35472m equ $-esc35472m

		esc36472m db 27,"[36;47;2m","ESC[36;47;2m - 36=cyan,47=white,2=faint",10
		len36472m equ $-esc36472m

		esc37402m db 27,"[37;40;2m","ESC[37;40;2m - 37=white,40=black,2=faint",10
		len37402m equ $-esc37402m

		esc30473m db 27,"[30;47;3m","ESC[30;47;3m - 3=Italic:on, Now widely supported. Sometimes treated as inverse.",10
		len30473m equ $-esc30473m

		esc30474m db 27,"[30;47;4m","ESC[30;47;4m - 4=Underline: single",10
		len30474m equ $-esc30474m

		esc30475m db 27,"[30;47;5m","ESC[30;47;5m - 5=Blink: slow, less than 150 per minute",10
		len30475m equ $-esc30475m

		esc30476m db 27,"[30;47;6m","ESC[30;47;6m - 6=Blink: rapid, 150+ per minute; not widely supported",10
		len30476m equ $-esc30476m

		esc30477m db 27,"[30;47;7m","ESC[30;47;7m - 7=Image: negative, inverse or reverse; swap foreground and background (reverse video)",10
		len30477m equ $-esc30477m

		esc30438m db 27,"[30;43;8m","ESC[30;43;8m - 8=Conceal, not widely supported",10
		len30438m equ $-esc30438m

		esc30479m db 27,"[30;47;9m","ESC[30;47;9m - 9=Crossed-out, Characters legible, but marked for deletion. Not widely supported.",10
		len30479m equ $-esc30479m

		esc304710m db 27,"[30;47;10m","ESC[30;47;10m - 10=Primary(default) font",10
		len304710m equ $-esc304710m

		esc304711m db 27,"[30;47;11m","ESC[30;47;11m - 11-th alternate font",10
		len304711m equ $-esc304711m

		esc304712m db 27,"[30;47;12m","ESC[30;47;12m - 12-th alternate font",10
		len304712m equ $-esc304712m

		esc304713m db 27,"[30;47;13m","ESC[30;47;13m - 13-th alternate font",10
		len304713m equ $-esc304713m

		esc304714m db 27,"[30;47;14m","ESC[30;47;14m - 14-th alternate font",10
		len304714m equ $-esc304714m

		esc304715m db 27,"[30;47;15m","ESC[30;47;15m - 15-th alternate font",10
		len304715m equ $-esc304715m

		esc304716m db 27,"[30;47;16m","ESC[30;47;16m - 16-th alternate font",10
		len304716m equ $-esc304716m

		esc304717m db 27,"[30;47;17m","ESC[30;47;17m - 17-th alternate font",10
		len304717m equ $-esc304717m

		esc304718m db 27,"[30;47;18m","ESC[30;47;18m - 18-th alternate font",10
		len304718m equ $-esc304718m

		esc304719m db 27,"[30;47;19m","ESC[30;47;19m - 19-th alternate font",10
		len304719m equ $-esc304719m


		esc304720m db 27,"[30;47;20m","ESC[30;47;20m - 20=Fraktur, hardly ever supported",10
		len304720m equ $-esc304720m

		esc304721m db 27,"[30;47;21m","ESC[30;47;21m - 21=Bold: off or Underline: Double. Bold off not widely supported; double underline hardly ever supported.",10
		len304721m equ $-esc304721m

		esc304722m db 27,"[30;47;22m","ESC[30;47;22m - 22=Normal color or intensity. Neither bold nor faint",10
		len304722m equ $-esc304722m

		esc304723m db 27,"[30;47;23m","ESC[30;47;23m - 23=Not italic, not Fraktur",10
		len304723m equ $-esc304723m

		esc304724m db 27,"[30;47;24m","ESC[30;47;24m - 24=Underline: None. Not singly or doubly underlined",10
		len304724m equ $-esc304724m

		esc304725m db 27,"[30;47;25m","ESC[30;47;25m - 25=Blink: off",10
		len304725m equ $-esc304725m

		esc304727m db 27,"[30;47;27m","ESC[30;47;27m - 27=Image: Positive",10
		len304727m equ $-esc304727m

		esc38221910104821522170m db 27,"[38;2;219;10;10;48;2;152;217;0m","ESC[38;2;219;10;10;48;2;152;217;0m - FG(219,10,10) BG(152,217,0)",10
		les38221910104821522170m equ $-esc38221910104821522170m

		esc3949m   db 27,"[39;49m","ESC[39;49m - FG=39=default BG=49=default",10
		len3949m   equ $-esc3949m

		esc304751m db 27,"[30;47;51m","ESC[30;47;51m - 51=Framed",10
		len304751m equ $-esc304751m

		esc304752m db 27,"[30;47;52m","ESC[30;47;52m - 52=Encircled",10
		len304752m equ $-esc304752m

		esc304753m db 27,"[30;47;53m","ESC[30;47;53m - 53=Overlined",10
		len304753m equ $-esc304753m

		esc304754m db 27,"[30;47;54m","ESC[30;47;54m - 54=Not framed or encircled",10
		len304754m equ $-esc304754m

		esc304755m db 27,"[30;47;55m","ESC[30;47;55m - 55=Not overlined",10
		len304755m equ $-esc304755m


section .text

Write:
		push eax,
		push ebx
		mov eax, sys_write
		mov ebx, stdout
		int 80h
		pop ebx
		pop eax
		ret

global _start
_start:
		mov ecx, strRnd0
		mov edx, lenRnd0
		call Write

		mov ecx, escB
		mov edx, lenB
		call Write

		mov ecx, escA
		mov edx, lenA
		call Write

		mov ecx, strRnd2
		mov edx, lenRnd2
		call Write

		mov ecx, escC
		mov edx, lenC
		call Write

		mov ecx, escD
		mov edx, lenD
		call Write

		mov ecx, escE
		mov edx, lenE
		call Write

		mov ecx, escF
		mov edx, lenF
		call Write

		mov ecx, strRnd3
		mov edx, lenRnd3
		call Write

		mov ecx, escG
		mov edx, lenG
		call Write

		mov ecx, escH
		mov edx, lenH
		call Write

		mov ecx, escJ
		mov edx, lenJ
		call Write

		mov ecx, strRnd4
		mov edx, lenRnd4
		call Write

		mov ecx, escK
		mov edx, lenK
		call Write

		mov ecx, strRnd5
		mov edx, lenRnd5
		call Write

		mov ecx, escS
		mov edx, lenS
		call Write

		mov ecx, escT
		mov edx, lenT
		call Write

		mov ecx, strRnd6
		mov edx, lenRnd6
		call Write

		mov ecx, escs
		mov edx, lens
		call Write

		mov ecx, strRnd7
		mov edx, lenRnd7
		call Write

		mov ecx, escu
		mov edx, lenu
		call Write

		mov ecx, strRnd8
		mov edx, lenRnd8
		call Write

		mov ecx, esc25l
		mov edx, len27l
		call Write

		mov ecx, strRnd9
		mov edx, lenRnd9
		call Write

		mov ecx, esc25h
		mov edx, len25h
		call Write

		mov ecx, strRnd11
		mov edx, lenRnd11
		call Write

		mov ecx, esc0m
		mov edx, len0m
		call Write

		mov ecx, escJ
		mov edx, lenJ
		call Write

		mov ecx, strRnd12
		mov edx, lenRnd12
		call Write

		mov ecx, esc30m
		mov edx, len30m
		call Write

		mov ecx, esc31m
		mov edx, len31m
		call Write

		mov ecx, esc32m
		mov edx, len32m
		call Write

		mov ecx, esc33m
		mov edx, len33m
		call Write

		mov ecx, esc34m
		mov edx, len34m
		call Write

		mov ecx, esc35m
		mov edx, len35m
		call Write

		mov ecx, esc36m
		mov edx, len36m
		call Write

		mov ecx, esc37m
		mov edx, len37m
		call Write

		mov ecx, esc3740m
		mov edx, len3740m
		call Write

		mov ecx, esc3741m
		mov edx, len3741m
		call Write

		mov ecx, esc3742m
		mov edx, len3742m
		call Write

		mov ecx, esc3743m
		mov edx, len3743m
		call Write

		mov ecx, esc3744m
		mov edx, len3744m
		call Write

		mov ecx, esc3745m
		mov edx, len3745m
		call Write

		mov ecx, esc3746m
		mov edx, len3746m
		call Write

		mov ecx, esc3047m
		mov edx, len3047m
		call Write

		mov ecx, esc0m
		mov edx, len0m
		call Write

		mov ecx, escJ
		mov edx, lenJ
		call Write

		mov ecx, strRnd12
		mov edx, lenRnd12
		call Write

		mov ecx, esc30471m
		mov edx, len30471m
		call Write

		mov ecx, esc31471m
		mov edx, len31471m
		call Write

		mov ecx, esc32471m
		mov edx, len32471m
		call Write

		mov ecx, esc33401m
		mov edx, len33401m
		call Write

		mov ecx, esc34471m
		mov edx, len34471m
		call Write

		mov ecx, esc35471m
		mov edx, len35471m
		call Write

		mov ecx, esc36471m
		mov edx, len36471m
		call Write

		mov ecx, esc37401m
		mov edx, len37401m
		call Write

		mov ecx, esc0m
		mov edx, len0m
		call Write

		mov ecx, escJ
		mov edx, lenJ
		call Write

		mov ecx, strRnd12
		mov edx, lenRnd12
		call Write

		mov ecx, esc30472m
		mov edx, len30472m
		call Write

		mov ecx, esc31472m
		mov edx, len31472m
		call Write

		mov ecx, esc32472m
		mov edx, len32472m
		call Write

		mov ecx, esc33402m
		mov edx, len33402m
		call Write

		mov ecx, esc34472m
		mov edx, len34472m
		call Write

		mov ecx, esc35472m
		mov edx, len35472m
		call Write

		mov ecx, esc36472m
		mov edx, len36472m
		call Write

		mov ecx, esc37402m
		mov edx, len37402m
		call Write

		mov ecx, esc0m
		mov edx, len0m
		call Write

		mov ecx, esc30473m
		mov edx, len30473m
		call Write

		mov ecx, esc30474m
		mov edx, len30474m
		call Write

		mov ecx, esc0m
		mov edx, len0m
		call Write

		mov ecx, esc30475m
		mov edx, len30475m
		call Write

		mov ecx, esc0m
		mov edx, len0m
		call Write

		mov ecx, esc30476m
		mov edx, len30476m
		call Write

		mov ecx, esc30477m
		mov edx, len30477m
		call Write

		mov ecx, esc30438m
		mov edx, len30438m
		call Write

		mov ecx, esc0m
		mov edx, len0m
		call Write

		mov ecx, esc30479m
		mov edx, len30479m
		call Write

		mov ecx, esc304710m
		mov edx, len304710m
		call Write

		mov ecx, esc304711m
		mov edx, len304711m
		call Write

		mov ecx, esc304712m
		mov edx, len304712m
		call Write

		mov ecx, esc304713m
		mov edx, len304713m
		call Write

		mov ecx, esc304714m
		mov edx, len304714m
		call Write

		mov ecx, esc304715m
		mov edx, len304715m
		call Write

		mov ecx, esc304716m
		mov edx, len304716m
		call Write

		mov ecx, esc304717m
		mov edx, len304717m
		call Write

		mov ecx, esc304718m
		mov edx, len304718m
		call Write

		mov ecx, esc304719m
		mov edx, len304719m
		call Write

		mov ecx, esc304720m
		mov edx, len304720m
		call Write

		mov ecx, esc304721m
		mov edx, len304721m
		call Write

		mov ecx, esc304722m
		mov edx, len304722m
		call Write

		mov ecx, esc304723m
		mov edx, len304723m
		call Write

		mov ecx, esc304724m
		mov edx, len304724m
		call Write

		mov ecx, esc304725m
		mov edx, len304725m
		call Write

		mov ecx, esc304727m
		mov edx, len304727m
		call Write

		mov ecx, esc38221910104821522170m
		mov edx, les38221910104821522170m
		call Write

		mov ecx, esc3949m
		mov edx, len3949m
		call Write

		mov ecx, esc304751m
		mov edx, len304751m
		call Write

		mov ecx, esc304752m
		mov edx, len304752m
		call Write

		mov ecx, esc304753m
		mov edx, len304753m
		call Write

		mov ecx, esc304754m
		mov edx, len304754m
		call Write

		mov ecx, esc304755m
		mov edx, len304755m
		call Write


		mov eax, 1
		mov ebx, 0
		int 80h
