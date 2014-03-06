# Small testing game

from FTSArcade import *
import time

pic1 = LoadImage ("fire.png")
sprite1 = CreateSprite(pic1)
SetSpritePosition(sprite1, 0, 200)
sprite2 = CreateSprite(pic1)
SetSpritePosition(sprite2, 10, 10)

tm = time.time ( )
while time.time ( ) - tm < 15.0:
  fDeltaTime = 1.0 / 60.0
  MoveSprite ( sprite1, 1.0 * fDeltaTime )
  MoveSprite ( sprite2, 2.0 * fDeltaTime )
  DrawText ( "yal3an thalwajh", 5, 6 )
  Sync ( )
