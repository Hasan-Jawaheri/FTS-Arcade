import struct
import socket
import HashTable
import main
from image import *
from sprite import *

def FTSInit ( ):
  main.CLIENTSOCKET = socket.socket ( socket.AF_INET, socket.SOCK_STREAM )
  main.CLIENTSOCKET.connect (("localhost", 5730))
  ImagesInit ( )
  SpritesInit ( )

def Sync ( ):
  return 0

FTSInit ( )