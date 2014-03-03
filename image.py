import HashTable
import main
import struct

class IMAGE:
	ID = 0 
	width = 0
	height = 0

def IMAGEHASHFUNCTION (x):
    return x.ID % 1000

def ImagesInit():
    main.IMAGETABLE = HashTable.CreateHashTable ( main.TABLESIZE )

def LoadImageSliced ( filename, sx, sy ):
    # a byte array of the filename
    ar = bytearray(map ((lambda x: ord(x)), list(filename)))
    # make it 256 bytes in length (must be fixed size!)
    for i in range(0, (256 - len(filename))):
    	ar += bytearray([0])
    # send function 1 to server [1:4][filename:256][sx:4][sy:4]
    main.SEND ( struct.pack ( "i", 1 ) + ar + struct.pack ( "ii", sx, sy ) )
    reply = main.RECEIVE ( "iii", 12 ) # get a response [ID,width,height]
    img = IMAGE()
    img.ID = reply[0]
    img.width = reply[1]
    img.height = reply[2]
    HashTable.HTInsert ( main.IMAGETABLE, IMAGEHASHFUNCTION, img )
    return reply[0] # return the ID

def LoadImage ( filename ):
	return LoadImageSliced ( filename, 1, 1 )

