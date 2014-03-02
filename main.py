import struct


funSymbol = "c"
def SEND ( msg ):
    print (msg)
    return 0

def LoadImage ( filename ):
    ar = bytearray(map ((lambda x: ord(x)), list(filename)))
    SEND ( bytes([0x0]) + struct.pack ( "i", len(filename) ) + ar )

def LoadFuckYou ( ):
	return 1


    
LoadImage ( "kofta.jpg" )
