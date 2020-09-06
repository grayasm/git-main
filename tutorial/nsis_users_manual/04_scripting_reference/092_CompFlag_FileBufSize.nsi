; FileBufSize buffer_size_in_mb
;
; Default is 32MB.
; Sets the size of the compiler's internal file buffers.
; A very small number could decrease performance.
; Specifying a very large number could exhaust system resources and force the
; compiler to cancel the compilation process.


FileBufSize 200


Section
    File 092_CompFlag_FileBufSize.nsi
SectionEnd