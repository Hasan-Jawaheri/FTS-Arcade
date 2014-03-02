import struct

class IMAGE:
	ID = 0 
   	width = 0
   	height = 0

class SPRITE:
	ID = 0
	ColNum = 0
	RowNum = 0


funSymbol = "c"
def SEND ( msg ):
    print (msg)
    return 0

def RECIEVE(something):
	return something

def LoadImage ( filename, sx, sy ):
    ar = bytearray(map ((lambda x: ord(x)), list(filename)))
    SEND ( bytes([0x0]) + struct.pack ( "iii", sx, sy, len(filename) ) + ar )

def LoadImage ( filename ):
	LoadImage ( filename, 1, 1 )

def LoadSprite (image, ColNum, RowNum):
	SEND (bytes([0x1]) + struct.pack ("iii", image, ColNum, RowNum)

def LoadSprite (image):
	LoadSprite(image, 1, 1)

def SetSpitePosition(sprite, px, py):
	SEND (bytes([0x2]) + struct.pack ("iii", sprite, px, py))

def MoveSprite(sprite, x):
	SEND (bytes ([0X3]) + struct.pack ("ii",sprite, x))
	





    
LoadImage ( "kofta.jpg" )
