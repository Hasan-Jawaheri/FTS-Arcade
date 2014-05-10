import socket
import struct
import ctypes
from camera import *

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

def RECEIVE ( r, length ):
  received = CLIENTSOCKET.recv(length)
  ar = bytearray(map ((lambda x: ord(x)), list(received)))
  print "[", len(ar), "]"
  return struct.unpack(r, str(ar))

def SPEED ( units ):
  return units * fDeltaTime