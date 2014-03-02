#Small testing game

import main

pic1 = LoadImage ("kofta.jpeg")
sprite1 = LoadSprite(pic1,1,1)
SetSpritePosition(sprite1, 0, 200)

while true:
    fDeltaTime = 1.0 / 60.0
    MoveSprite ( sprite1, 5.0 * fDeltaTime)
    

    
