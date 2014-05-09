import HashTable
import main
import struct
import image
import math

class SPRITE:
  def __init__(self, id, imgID):
    self.ID = id
    self.imageID = imgID
    self.position = (0.0, 0.0)
    self.size = (image.GetImageWidth (imgID), image.GetImageHeight(imgID))
    self.look = (1.0, 0.0)
    self.flipState = chr(0)
    self.bHidden = False
    self.bPlaying = False
    self.bLooping = False
    self.bPaused = False
    self.pad = False
    self.pad2 = False
    self.pad3 = False
  
  # TODO: ADD SPRITE ATTRIBUTES

def SPRITEHASHFUNCTION (x):
  return x % 1000

def GetSprite(sprite):
  return HashTable.HTlookUp(main.SPRITETABLE, SPRITEHASHFUNCTION, sprite)

def DegToRad(degree):
  return (math.pi / 180.0) * degree

def RadToDeg(radian):
  return (180.0 / math.pi) * radian

def SpritesInit():
  main.SPRITETABLE = HashTable.CreateHashTable ( main.TABLESIZE )

def CreateSprite (image):
  # send function 2 to the server [2:4][imageID:4]
  main.SEND (struct.pack ("ii", 2, image))
  reply = main.RECEIVE ( "i", 4 )
  spr = SPRITE (reply[0], image)
  # TODO: DEFAULT SPRITE ATTRIBUTES
  HashTable.HTInsert ( main.SPRITETABLE, SPRITEHASHFUNCTION, spr )
  return reply[0]

def SetSpritePosition(sprite, px, py):
  x = GetSprite(sprite)
  if x != None:
    x.position = (px, py)

def MoveSprite(sprite, fUnits):
  x = GetSprite(sprite)
  if x != None:
    x.position = (x.position[0] + x.look[0] * fUnits,
                  x.position[1] + x.look[1] * fUnits)

def SetSpriteAngle(sprite, fAngle):
  x = GetSprite(sprite)
  if x != None:
    x.look = (math.cos(DegToRad(fAngle)), math.sin(DegToRad(fAngle)))

def GetSpriteAngle(sprite):
  x = GetSprite(sprite)
  if x != None:
    ang = RadToDeg(math.acos(x.look[0]))
    if x.look[1] < 0:
      return -ang
    else:
      return ang
  return 0.0

def RotateSprite(sprite, fAngle):
  x = GetSprite(sprite)
  if x != None:
    angle = GetSpriteAngle(sprite)
    SetSpriteAngle(sprite, fAngle + angle)

def StrafeSprite(sprite, fUnits):
  x = GetSprite(sprite)
  fAngle = GetSpriteAngle(sprite)
  up = (math.cos(DegToRad(fAngle + 90.0)),
        math.sin(DegToRad(fAngle + 90.0)))
  if x != None:
    x.position = (x.position[0] + up[0] * fUnits,
                  x.position[1] + up[1] * fUnits)

def SetSpriteSize(sprite, width, height):
  x = GetSprite(sprite)
  if x != None:
    x.size = (width, height)

def GetSpritePositionX(sprite):
  x = GetSprite(sprite)
  if x != None:
    return x.position[0]
  else:
    return 0

def GetSpritePositionY(sprite):
  x = GetSprite(sprite)
  if x != None:
    return x.position[1]
  else:
    return 0

def GetSpriteSizeX(sprite):
  x = GetSprite(sprite)
  if x != None:
    return x.size[0]
  else:
    return 0

def GetSpriteSizeY(sprite):
  x = GetSprite(sprite)
  if x != None:
    return x.size[1]
  else:
    return 0

def ShowSprite (sprite):
  x = GetSprite(sprtie)
  if x != None:
    x.bHidden = False

def HideSprite (sprite):
  x = GetSprite(sprtie)
  if x != None:
    x.bHidden = True

def SetSpriteImage (sprite, img):
  x = GetSprite(sprtie)
  if x != None:
    x.imageID = img

def SpritesCollide (spr1, spr2):
  x = GetSprite(spr1)
  y = GetSprite(spr2)
  if x == None or y == None:
    return False
  xRad = (x.size[0] / 2, x.size[1] / 2)
  yRad = (y.size[0] / 2, y.size[1] / 2)
  xCen = (x.position[0]+xRad[0], x.position[1]+xRad[1])
  yCen = (y.position[0]+yRad[0], y.position[1]+yRad[1])

  return abs(xCen[0]-yCen[0]) < xRad[0] + yRad[0] and\
         abs(xCen[1]-yCen[1]) < xRad[1] + yRad[1]

def SyncSprites():
  spritesList = bytearray([])
  numSprites = 0
  for i in main.SPRITETABLE:
    for j in i:
      numSprites += 1
      k = struct.pack ("iiffffffc???????", j.ID, j.imageID, j.position[0], j.position[1],
                      j.size[0], j.size[1], j.look[0], j.look[1], j.flipState,
                      j.bHidden, j.bPlaying, j.bLooping, j.bPaused, j.pad, j.pad2, j.pad3)
      spritesList += k
  return ((struct.pack("i", numSprites)) + spritesList,
          4 + numSprites * 40)

