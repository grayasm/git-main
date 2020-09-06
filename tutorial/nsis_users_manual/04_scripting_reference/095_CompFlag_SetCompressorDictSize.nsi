; SetCompressorDictSize dict_size_mb
;
; Sets the dictionary size in megabytes (MB) used by the LZMA compressor (default is 8 MB).


SetCompressor /SOLID /FINAL lzma
SetCompressorDictSize 10

Section
    File 095_CompFlag_SetCompressorDictSize.nsi
SectionEnd