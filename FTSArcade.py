import struct
import socket
import HashTable
import main
import ctypes
from image import *
from sprite import *

def KeyDown ( key ):
  return getattr(main.INPUTDLL, "?KeyDown@@YAHH@Z") ( key )

def GetInputDirectionX ( ):
  return getattr(main.INPUTDLL, "?GetInputDirectionX@@YAHXZ") ( )

def GetInputDirectionY ( ):
  return getattr(main.INPUTDLL, "?GetInputDirectionY@@YAHXZ") ( )

def FTSInit ( ):
  main.INPUTDLL = ctypes.CDLL ( "InputHandler.dll" )
  for i in range (0, 4):
    print KeyDown ( i ),
  print "\n", GetInputDirectionX ( ), GetInputDirectionY ( )
  main.CLIENTSOCKET = socket.socket ( socket.AF_INET, socket.SOCK_STREAM )
  main.CLIENTSOCKET.connect (("localhost", 5730))
  ImagesInit ( )
  SpritesInit ( )

def Sync ( ):
  return 0

FTSInit ( )