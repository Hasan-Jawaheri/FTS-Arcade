import main
import struct

class CAMERA():

  def __init__(self):
    self.position = (0.0, 0.0)
    self.zoom = 1 
    

def SetCameraPosition(fX, fY):
  main.MAINCAMERA.position = (fX, fY)
  
def SetCameraZoom(fZoom):
  main.MAINCAMERA.zoom = fZoom

def SyncCamera():
  return (struct.pack ("fff", main.MAINCAMERA.position[0],
                main.MAINCAMERA.position[1],
                main.MAINCAMERA.zoom), 12)
  