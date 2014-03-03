from hash import *

class SPRITE:
	ID = 0
	ColNum = 0
	RowNum = 0

SPRITETABLE = None
TABLESIZE = 1000

def SpritesInit():
	SPRITETABLE = CreateHashTable ( TABLESIZE )

def CreateSprite (image):
	SEND (bytes([0x2]) + struct.pack ("i", image))

def SetSpitePosition(sprite, px, py):
	return 0

def MoveSprite(sprite, x):
	return 0
	