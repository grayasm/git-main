; SetCompressor [/SOLID] [/FINAL] zlib | bzip2 | lzma
;
; Sets the compression algorithm used to compress files/data in the installer.
; ZLIB: is default, uses the deflate algorithm, and is quick and simple.
; BZIP2: better compression, slower and uses more memory.
; LZMA: very good compression ratios.
; /SOLID: all of the installer data is compressed in one block.
; /FINAL: subsequent calls to SetCompressor will be ignored.


SetCompressor /SOLID /FINAL lzma


Section    
    File 094_CompFlag_SetCompressor.nsi
SectionEnd