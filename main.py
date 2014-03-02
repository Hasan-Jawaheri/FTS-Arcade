import struct
import socket
import hash


class IMAGE:
	ID = 0 
   	width = 0
   	height = 0

class SPRITE:
	ID = 0
	ColNum = 0
	RowNum = 0

TABLESIZE = 1000
IMAGETABLE = None
SPRITETABLE = None

funSymbol = "c"
clientsocket = None

def MyVeryCoolHashFunctionDotComOofOne (index):
	index % TABLESIZE

def SEND ( msg ):
	clientsocket.send ( msg )

def RECIEVE():
	ar = bytearray(map ((lambda x: ord(x)), list(clientsocket.recv(4))))
	return struct.unpack('i', ar)

def InitFTSArcade ( ):
	clientsocket = socket.socket ( socket.AF_INET, socket.SOCK_STREAM )
	clientsocket.connect (("localhost", 5730))
	IMAGETABLE = CreateHashTable ( TABLESIZE )
	SPRITETABLE = CreateHashTable ( TABLESIZE )


def LoadImage ( filename, sx, sy ):
    ar = bytearray(map ((lambda x: ord(x)), list(filename)))
    SEND ( bytes([0x0]) + struct.pack ( "iii", sx, sy, len(filename) ) + ar )
    HTinsert(IMAGETABLE, MyVeryCoolHashFunctionDotComOofOne, RECIEVE())

def LoadImage ( filename ):
	LoadImage ( filename, 1, 1 )

def LoadSprite (image):
	SEND (bytes([0x1]) + struct.pack ("i", image))

def SetSpitePosition(sprite, px, py):
	SEND (bytes([0x2]) + struct.pack ("iii", sprite, px, py))

def MoveSprite(sprite, x):
	SEND (bytes ([0X3]) + struct.pack ("ii",sprite, x))