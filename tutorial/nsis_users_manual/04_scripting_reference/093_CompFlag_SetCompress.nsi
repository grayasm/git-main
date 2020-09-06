; SetCompress auto | force | off
;
; Sets the compress flag which is used by the installer to determine whether
; or not data should be compressed.
; auto: files are compressed only if compressed size is smaller than the uncompressed size.
; force: files are always compresed
; off: the compression is not used

SetCompress off


Section
    File 093_CompFlag_SetCompress.nsi
SectionEnd