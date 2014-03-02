import struct


def 


funSymbol = "d"
def SEND ( msg ):
    print (msg)
    return 0

def LoadImage ( filename ):
    fn = bytearray(map ((lambda x: ord(x)), list(filename)))
    SEND ( bytes([0x0]) + struct.pack ( "i", len(filename) ) + ar )

def 


    
LoadImage ( "kofta.jpg" )
