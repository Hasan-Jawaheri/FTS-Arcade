import FTSMain
import struct

class CAMERA():
  def __init__(self):
    self.position = (0.0, 0.0)
    self.zoom = 1 
    

def SetCameraPosition(fX, fY):
  FTSMain.MAINCAMERA.position = (fX, fY)
  
def SetCameraZoom(fZoom):
  FTSMain.MAINCAMERA.zoom = fZoom

def SyncCamera():
  return (struct.pack ("fff", FTSMain.MAINCAMERA.position[0],
                FTSMain.MAINCAMERA.position[1],
                FTSMain.MAINCAMERA.zoom), 12)
  