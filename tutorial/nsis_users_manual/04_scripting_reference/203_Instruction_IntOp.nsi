; IntOp  user_var(output)  value1  OP  [value2]
;
; Combines value1 and (depending on OP) value2 into the specified user variable (user_var). 
; OP is defined as one of the following:
;       + ADDs                      value1 and value2
;       - SUBTRACTs                 value2 from value1
;       * MULTIPLIEs                value1 and value2
;       / DIVIDEs                   value1 by value2
;       % MODULUSs                  value1 by value2
;       | BINARY ORs                value1 and value2
;       & BINARY ANDs               value1 and value2
;       ^ BINARY XORs               value1 and value2
;       << LEFT SHIFTs              value1 by value2
;       >> ARITHMETIC RIGHT SHIFTs  value1 by value2
;       >>> LOGICALLY RIGHT SHIFTs  value1 by value2
;       ~ BITWISE NEGATEs           value1 (i.e. 7 becomes 4294967288)
;       ! LOGICALLY NEGATEs         value1 (i.e. 7 becomes 0)
;       || LOGICALLY ORs            value1 and value2
;       && LOGICALLY ANDs           value1 and value2

Section
    IntOp $0 1 + 1
    IntOp $1 $0 + 1
    IntOp $2 $0 << 2
    IntOp $3 $0 ~
    IntOp $4 $0 & 0xF
    
    DetailPrint "1 + 1 = $0"
    DetailPrint "$0 + 1 = $1"
    DetailPrint "$0 << 2 = $2"
    DetailPrint "$0 ~ = $3"
    DetailPrint "$0 & 0xF = $4"
SectionEnd