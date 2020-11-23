; test header inclusion with !include

Function func001
    DetailPrint "Enter 001_header.nsi func001"
    Pop $0          ; requires at least one element on the stack
    IfErrors 0 show
        MessageBox MB_OK "No element on the stack!"
        Goto end
show:
    MessageBox MB_OK "func001 pop(ed) stack $$0=$0"
end:
    DetailPrint "Leave 001_header.nsi func001"
FunctionEnd