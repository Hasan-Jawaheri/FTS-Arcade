import struct
import socket
import image
import sprite

clientsocket = None

def SEND ( msg ):
	clientsocket.send ( msg )

def RECIEVE():
	ar = bytearray(map ((lambda x: ord(x)), list(clientsocket.recv(4))))
	return struct.unpack('i', ar)

def FTSInit ( ):
	clientsocket = socket.socket ( socket.AF_INET, socket.SOCK_STREAM )
	clientsocket.connect (("localhost", 5730))
	ImagesInit ( )
	SpritesInit ( )

def Sync():
	return 0