# Small testing game

from FTSArcade import *
import random
import time

Bar = LoadImage ("bat.jpg")
Bar2 = LoadImage ("bat.jpg")
LeftBar = CreateSprite(Bar)
SetSpritePosition(LeftBar, 60, 350)
RightBar = CreateSprite(Bar)
SetSpritePosition(RightBar, 1300, 350)
Kemal = LoadImage ("kemal.png")
kemal = CreateSprite(Kemal)
#KemalHit = LoadImage ("kemal2.png")
#kemalHit = CreateSprite(KemalHit) 
SetSpritePosition(kemal, (1366/2), 300)


fCurDir = random.uniform(0, 360) - 180;
kemalHeight = GetImageHeight(Kemal)
BarHight = GetImageHeight(Bar) * 2

BallSpeed = 9

BarRate = 4
BarDampRate = 0.8
LeftBarSpeed = -10.0
RightBarSpeed = 10.0

while True:
  fCurDir = fCurDir % 360.0
  
  if KeyDown('W'):
    if GetSpritePositionY(LeftBar) >= 10.0:
      LeftBarSpeed -= BarRate

  if KeyDown('S'):
    if GetSpritePositionY(LeftBar) <= 650.0:
      LeftBarSpeed += BarRate
      
  if KeyDown('O'):
    if GetSpritePositionY(RightBar) >= 10.0:
      RightBarSpeed -= BarRate
      
  if KeyDown('L'):
    if GetSpritePositionY(RightBar) <= 650.0:
      RightBarSpeed += BarRate
      
      
  LeftBarSpeed = LeftBarSpeed * BarDampRate
  RightBarSpeed = RightBarSpeed * BarDampRate

  # Collision with top wall
  if GetSpritePositionY(kemal) <= -10:
    fCurDir = 360.0 - (fCurDir % 360.0)

  # Collision with bottom wall
  if GetSpritePositionY(kemal) >= 745 - kemalHeight:
    fCurDir *= -1.0

  # Collision of left bar
  if GetSpritePositionY(kemal) + kemalHeight >= GetSpritePositionY(LeftBar)\
  and GetSpritePositionY(kemal) <= GetSpritePositionY(LeftBar) + BarHight\
  and GetSpritePositionX(kemal) >= GetSpritePositionX(LeftBar) + GetImageWidth(Bar) - 10\
  and GetSpritePositionX(kemal) <= GetSpritePositionX(LeftBar) + GetImageWidth(Bar):
    fCurDir = GetSpritePositionY(kemal) - 20 - GetSpritePositionY(LeftBar)
    fCurDir = fCurDir / (BarHight / 2)
    fCurDir = fCurDir * 60

  # Collision of right bar
  if GetSpritePositionY(kemal) + kemalHeight >= GetSpritePositionY(RightBar)\
  and GetSpritePositionY(kemal) <= GetSpritePositionY(RightBar) + BarHight\
  and GetSpritePositionX(kemal) + GetImageWidth(Kemal) >= GetSpritePositionX(RightBar) + 10\
  and GetSpritePositionX(kemal) <= GetSpritePositionX(RightBar) + GetImageWidth(Bar):
    fCurDir = (GetSpritePositionY(kemal) - 20 - GetSpritePositionY(RightBar))
    fCurDir = fCurDir / (BarHight / 2)
    fCurDir = 180 - fCurDir * 60

  # Movement of Ball (Professor Face)
  RotateSprite ( kemal, 3.0 )
  fCurAng = GetSpriteAngle ( kemal )
  SetSpriteAngle ( kemal, fCurDir )
  MoveSprite ( kemal, BallSpeed )
  SetSpriteAngle(kemal, fCurAng )


  StrafeSprite(LeftBar, LeftBarSpeed)
  StrafeSprite(RightBar, RightBarSpeed)

  Sync()
  time.sleep(0.01)




