; SetDatablockOptimize on | off
;
; Datablock optimizations causes the compiler to check to see if any data being
; added to the data block is already in the data block, and if so, it is simply
; referenced as opposed to added (can save a little bit of size).


SetDatablockOptimize on


Section
    File 096_CompFlag_SetDatablockOptimize.nsi
SectionEnd