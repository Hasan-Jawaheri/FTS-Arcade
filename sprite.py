import HashTable
import main
import struct

class SPRITE:
  
  def __init__(self, id):
    self.ID = id
    self.position = (0.0, 0.0)
    self.size = (0.0, 0.0)
    self.look = (1.0, 0.0)
    self.flipState = 'a'
    self.bPlaying = False
    self.bLooping = False
    self.bPaused = False
  
  # TODO: ADD SPRITE ATTRIBUTES

def SPRITEHASHFUNCTION (x):
  return x % 1000

def SpritesInit():
  main.SPRITETABLE = HashTable.CreateHashTable ( main.TABLESIZE )

def CreateSprite (image):
  # send function 2 to the server [2:4][imageID:4]
  main.SEND (struct.pack ("ii", 2, image))
  reply = main.RECEIVE ( "i", 4 )
  spr = SPRITE (reply[0])
  # TODO: DEFAULT SPRITE ATTRIBUTES
  HashTable.HTInsert ( main.SPRITETABLE, SPRITEHASHFUNCTION, spr )
  return reply[0]

def SetSpritePosition(sprite, px, py):
  x = HashTable.HTlookUp(main.SPRITETABLE, SPRITEHASHFUNCTION, sprite)
  if x != None:
    x.position = (px, py)

def MoveSprite(sprite, fUnits):
  x = HashTable.HTlookUp(main.SPRITETABLE, SPRITEHASHFUNCTION, sprite)
  if x != None:
    x.position = (x.position[0] * fUnits, x.position[1] * fUnits)
  

def SyncSprites():
  spritesList = bytearray([])
  numSprites = 0
  for i in main.SPRITETABLE:
    for j in i:
      numSprites += 1
      k = struct.pack ("iffffffc???", j.ID, j.position[0], j.position[1],
                      j.size[0], j.size[1], j.look[0], j.look[1], j.flipState,
                      j.bPlaying, j.bLooping, j.bPaused)
      spritesList += k
  return ((struct.pack("i", numSprites)) + spritesList,
          4 + numSprites * 32)

