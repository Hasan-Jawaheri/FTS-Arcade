import socket
import struct
import ctypes
import camera

CLIENTSOCKET = None
IMAGETABLE = None
SPRITETABLE = None
TABLESIZE = 1000
DELTATIME = 1.0 / 60.0
INPUTDLL = None
MAINCAMERA = CAMERA()
TEXTLIST = []
CURFONTID = 0
CURFONTCOLOR = (chr(255), chr(0), chr(0)) 


def SEND ( msg ):
  CLIENTSOCKET.send ( msg )

def RECEIVE ( r, len ):
  received = CLIENTSOCKET.recv(len)
  ar = bytearray(map ((lambda x: ord(x)), list(received)))
  return struct.unpack(r, ar)

def SPEED ( units ):
  return units * fDeltaTime