#include <xc.inc>

    GLOBAL _nameList ; make _add globally accessible
; everything following will be placed into the code psect
    
packString MACRO c1,c2,c3,c4
 dw c1 and 0x7f | ((c2 and 0x7f) << 7)
 dw c3 and 0x7f | ((c4 and 0x7f) << 7)
ENDM
    
PSECT code
_nameList:
packString	'#',	'A',	'j',	'a'
packString	'#',	'A',	'k',	'i'
packString	'#',	'A',	'l',	'i'
packString	'#',	'A',	'm',	'a'
packString	'#',	'A',	'r',	'i'
packString	'#',	'A',	's',	'h'
packString	'#',	'A',	'v',	'a'
packString	'#',	'A',	'v',	'i'
packString	'#',	'A',	'x',	'l'
packString	'#',	'A',	'y',	'a'
packString	'#',	'B',	'e',	'n'
packString	'#',	'C',	'a',	'i'
packString	'#',	'C',	'a',	'l'
packString	'#',	'C',	'a',	'm'
packString	'#',	'D',	'a',	'x'
packString	'#',	'D',	'e',	'e'
packString	'#',	'D',	'o',	'n'
packString	'#',	'E',	'l',	'i'
packString	'#',	'E',	'v',	'a'
packString	'#',	'E',	'v',	'e'
packString	'#',	'F',	'l',	'o'
packString	'#',	'F',	'o',	'x'
packString	'#',	'G',	'e',	'o'
packString	'#',	'G',	'i',	'a'
packString	'#',	'H',	'a',	'l'
packString	'#',	'I',	'a',	'n'
packString	'#',	'I',	'd',	'a'
packString	'#',	'I',	'r',	'a'
packString	'#',	'I',	'v',	'y'
packString	'#',	'J',	'a',	'n'
packString	'#',	'J',	'a',	'x'
packString	'#',	'J',	'e',	'b'
packString	'#',	'J',	'o',	'y'
packString	'#',	'K',	'a',	'y'
packString	'#',	'K',	'i',	'a'
packString	'#',	'K',	'i',	'm'
packString	'#',	'K',	'i',	'p'
packString	'#',	'K',	'i',	't'
packString	'#',	'K',	'o',	'a'
packString	'#',	'K',	'y',	'a'
packString	'#',	'L',	'e',	'o'
packString	'#',	'L',	'e',	'x'
packString	'#',	'L',	'u',	'x'
packString	'#',	'M',	'a',	'i'
packString	'#',	'M',	'a',	'x'
packString	'#',	'M',	'e',	'g'
packString	'#',	'N',	'e',	'o'
packString	'#',	'N',	'i',	'a'
packString	'#',	'N',	'y',	'x'
packString	'#',	'P',	'a',	'z'
packString	'#',	'R',	'a',	'y'
packString	'#',	'R',	'e',	'i'
packString	'#',	'S',	'a',	'l'
packString	'#',	'S',	'a',	'm'
packString	'#',	'S',	'k',	'y'
packString	'#',	'S',	'y',	'd'
packString	'#',	'T',	'a',	'j'
packString	'#',	'T',	'i',	'a'
packString	'#',	'U',	'l',	'a'
packString	'#',	'V',	'a',	'l'
packString	'#',	'V',	'o',	'x'
packString	'#',	'Z',	'e',	'b'
packString	'#',	'Z',	'e',	'n'
packString	'#',	'Z',	'o',	'e'




