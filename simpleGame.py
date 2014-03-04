# Small testing game

from FTSArcade import *
import time

pic1 = LoadImage ("C:\\Users\\Hasan\\Documents\\Visual Studio 2013\\Projects\RPG\\Map Importer\\arena.bmp")
sprite1 = CreateSprite(pic1)
SetSpritePosition(sprite1, 0, 200)

counter = 0
while counter < 5:
  counter += 1
  fDeltaTime = 1.0 / 60.0
  MoveSprite ( sprite1, 5.0 * fDeltaTime )
  Sync ( )
  time.sleep(1)