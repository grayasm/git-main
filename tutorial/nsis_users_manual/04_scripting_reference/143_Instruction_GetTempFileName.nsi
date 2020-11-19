; GetTempFileName  user_var(output)  [base_dir]
;
; Assign to the user variable $x, the name of a temporary file. 
; The file will be created for you and it will be empty. 
; The name of the temporary file is guaranteed to be unique. 
; If you want the temporary file to be created in another directory other than
; the Windows temp directory, specify a base_dir. 
; You should Delete the file when you are done with it.


Section
    GetTempFileName $0
    File /oname=$0 108_timeout.exe
    # do something with 108_timeout.exe
    DetailPrint "108_timeout.exe copied as $0"
    Delete $0
SectionEnd