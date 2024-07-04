GLOBAL _nameList ; make _add globally accessible
; everything following will be placed into the code psect
    
packString MACRO c1,c2
 dw c1 & 0x7f | (c1 & 0x7f) << 7
 dw c2 & 0x7f | (c2 & 0x7f) << 7
ENDM
    
PSECT code
_nameList:
    movlw 0xed
    packString '#','E'


