import socket
import struct

CLIENTSOCKET = None
IMAGETABLE = None
SPRITETABLE = None
TABLESIZE = 1000

def SEND ( msg ):
	CLIENTSOCKET.send ( msg )

def RECEIVE ( r, len ):
	received = CLIENTSOCKET.recv(len)
	ar = bytearray(map ((lambda x: ord(x)), list(received)))
	return struct.unpack(r, ar)