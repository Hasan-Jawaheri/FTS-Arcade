import struct
import socket
import HashTable
import main
import ctypes
import sys
from image import *
from sprite import *
from camera import *
from text import *

def KeyDown ( key ):
  return getattr(main.INPUTDLL, "?KeyDown@@YAHH@Z") ( key )

def GetInputDirectionX ( ):
  return getattr(main.INPUTDLL, "?GetInputDirectionX@@YAHXZ") ( )

def GetInputDirectionY ( ):
  return getattr(main.INPUTDLL, "?GetInputDirectionY@@YAHXZ") ( )

def FTSInit ( ):
  #main.INPUTDLL = ctypes.CDLL ( "InputHandler.dll" )
  #import time
  #time.sleep(2)
  #while True:
  #  for i in range (0, 32):
  #    print KeyDown ( i ),
  #  print "\n", GetInputDirectionX ( ), GetInputDirectionY ( )
  #  time.sleep(1)
  port = int(sys.argv[1]) # port should be passed as an argument
  main.CLIENTSOCKET = socket.socket ( socket.AF_INET, socket.SOCK_STREAM )
  main.CLIENTSOCKET.connect (("localhost", port))
  ImagesInit ( )
  SpritesInit ( )

def Sync ( ):
  fullmsg = SyncSprites ( )
  cameraData = SyncCamera ( )
  TextData = SyncText ( )
  print cameraData[1] + fullmsg[1] + TextData[1]
  main.SEND ( (struct.pack("ii", 0, cameraData[1] + fullmsg[1] + TextData[1])) 
            + cameraData[0] + fullmsg[0] + TextData[0] )

FTSInit ( )
