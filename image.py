
class IMAGE:
	ID = 0 
	width = 0
	height = 0

IMAGETABLE = None
TABLESIZE = 1000

def ImagesInit():
	IMAGETABLE = CreateHashTable ( TABLESIZE )

def LoadImage ( filename, sx, sy ):
    ar = bytearray(map ((lambda x: ord(x)), list(filename)))
    ret = [0]
    for i in range(1, (256 - len(filename))):
    	ret.append([0])
    ar2 = ar + ret
    SEND ( bytes([0x1]) + struct.pack ( "ii", sx, sy ) + ar2 )
    HTinsert(IMAGETABLE, MyVeryCoolHashFunctionDotComOofOne, RECIEVE())

def LoadImage ( filename ):
	LoadImage ( filename, 1, 1 )

