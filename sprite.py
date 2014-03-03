import HashTable
import main
import struct

class SPRITE:
    ID = 0
    # TODO: ADD SPRITE ATTRIBUTES

def SPRITEHASHFUNCTION (x):
    return x.ID % 1000

def SpritesInit():
    main.SPRITETABLE = HashTable.CreateHashTable ( main.TABLESIZE )

def CreateSprite (image):
    # send function 2 to the server [2:4][imageID:4]
    main.SEND (struct.pack ("ii", 2, image))
    reply = main.RECEIVE ( "i", 4 )
    spr = SPRITE
    spr.ID = reply[0]
    # TODO: DEFAULT SPRITE ATTRIBUTES
    HashTable.HTInsert ( main.SPRITETABLE, SPRITEHASHFUNCTION, spr )
    return reply[0]


def SetSpritePosition(sprite, px, py):
    return 0

def MoveSprite(sprite, x):
    return 0
    