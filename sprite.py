import HashTable
import main
import struct

class SPRITE:
	ID = 0
	ColNum = 0
	RowNum = 0

def SPRITEHASHFUNCTION (x):
    return x % 1000

def SpritesInit():
	main.SPRITETABLE = HashTable.CreateHashTable ( main.TABLESIZE )

def CreateSprite (image):
	main.SEND (struct.pack ("ii", 2, image))
	#HashTable.HTInsert ( SPRITETABLE, SPRITEHASHFUNCTION, main.RECEIVE ( "i", 4 ) )

def SetSpritePosition(sprite, px, py):
	return 0

def MoveSprite(sprite, x):
	return 0
	