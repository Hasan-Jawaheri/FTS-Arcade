import struct
import socket
import HashTable
import FTSMain
import ctypes
import sys
from image import *
from sprite import *
from camera import *
from text import *

SCREEN_WIDTH = 640
SCREEN_HEIGHT = 480

def KeyDown ( key ):
  return getattr(FTSMain.INPUTDLL, "?KeyDown@@YAHH@Z") ( ord(key) )
def KeyUp ( key ):
  return getattr(FTSMain.INPUTDLL, "?KeyDown@@YAHH@Z") ( ord(key) ) == 1

def GetInputDirectionX ( ):
  return getattr(FTSMain.INPUTDLL, "?GetInputDirectionX@@YAHXZ") ( )

def GetInputDirectionY ( ):
  return getattr(FTSMain.INPUTDLL, "?GetInputDirectionY@@YAHXZ") ( )

def GetScreenWidth ( ):
  return SCREEN_WIDTH
def GetScreenHeight ( ):
  return SCREEN_HEIGHT

def FTSInit ( ):
  FTSMain.INPUTDLL = ctypes.CDLL ( "InputHandler.dll" )
  #import time
  #time.sleep(2)
  #while True:
  #  for i in range (0, 32):
  #    print KeyDown ( i ),
  #  print "\n", GetInputDirectionX ( ), GetInputDirectionY ( )
  #  time.sleep(1)
  port = int(sys.argv[1]) # port should be passed as an argument
  FTSMain.CLIENTSOCKET = socket.socket ( socket.AF_INET, socket.SOCK_STREAM )
  FTSMain.CLIENTSOCKET.connect (("localhost", port))
  ImagesInit ( )
  SpritesInit ( )
  Sync ( ) # set the initial width/height

def Sync ( ):
  spritesData = SyncSprites ( )
  cameraData = SyncCamera ( )
  TextData = SyncText ( )
  FTSMain.SEND ( (struct.pack("ii", 0, cameraData[1] + spritesData[1] + TextData[1])) 
            + cameraData[0] + spritesData[0] + TextData[0] )
  info = FTSMain.RECEIVE ( "ii", 8 ) # just to stay in sync
  SCREEN_WIDTH = info[0]
  SCREEN_HEIGHT = info[1]

FTSInit ( )
