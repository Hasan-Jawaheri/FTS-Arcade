#Small testing game

from FTSArcade import *

FTSInit ( )

pic1 = LoadImage ("C:\\Users\\Hasan\\Documents\\Visual Studio 2013\\Projects\RPG\\Map Importer\\arena.bmp")
sprite1 = CreateSprite(pic1)
SetSpritePosition(sprite1, 0, 200)

while True:
    fDeltaTime = 1.0 / 60.0
    MoveSprite ( sprite1, 5.0 * fDeltaTime )
    Sync ( )
    
