#Small testing game

import main

FTSInit ( )

pic1 = LoadImage ("kofta.jpeg")
sprite1 = CreateSprite(pic1)
SetSpritePosition(sprite1, 0, 200)

while True:
    fDeltaTime = 1.0 / 60.0
    MoveSprite ( sprite1, 5.0 * fDeltaTime )
    Sync ( )
    
