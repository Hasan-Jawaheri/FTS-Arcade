import HashTable
import main
import struct

class IMAGE:
  def __init__(self, id, width, height):
    self.ID = id
    self.width = width
    self.height = height

def IMAGEHASHFUNCTION (x):
  return x % 1000

def ImagesInit():
  main.IMAGETABLE = HashTable.CreateHashTable ( main.TABLESIZE )

def LoadImageSliced ( filename, sx, sy ):
  # a byte array of the filename
  ar = bytearray(map ((lambda x: ord(x)), list(filename)))
  # make it 256 bytes in length (must be fixed size!)
  for i in range(0, (256 - len(filename))):
      ar += bytearray([0])
  # send function 1 to server [1:4][filename:256][sx:4][sy:4]
  main.SEND ( struct.pack ( "i", 1 ) + ar + struct.pack ( "ii", sx, sy ) )
  reply = main.RECEIVE ( "iii", 12 ) # get a response [ID,width,height]
  img = IMAGE(reply[0], reply[1], reply[2])
  HashTable.HTInsert ( main.IMAGETABLE, IMAGEHASHFUNCTION, img )
  return reply[0] # return the ID

def LoadImage ( filename ):
  return LoadImageSliced ( filename, 1, 1 )

def GetImageWidth(image):
  x = HashTable.HTlookUp(main.IMAGETABLE, IMAGEHASHFUNCTION, image)
  if x != None:
    return x.width

def GetImageHeight(image):
  x = HashTable.HTlookUp(main.IMAGETABLE, IMAGEHASHFUNCTION, image)
  if x != None:
    return x.height
