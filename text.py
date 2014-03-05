import main
import struct

class TEXT():
  def __init__(self, ID, text, r, g, b, x, y):
    self.FontID = ID
    self.text = text
    self.color = (chr(r), chr(g), chr(b))
    self.position = (x,y)

def CreateFont(ID, name, size):
  # a byte array of the name
  ar = bytearray(map ((lambda x: ord(x)), list(name)))
  # make it 256 bytes in length (must be fixed size!)
  for i in range(0, (256 - len(name))):
      ar += bytearray([0])
  # send function 3 to server [3:4][ID:4][name:256][size:4]
  main.SEND ( struct.pack ( "i", 3 ) + 
              struct.pack ( "i", ID) + 
              ar + 
              struct.pack ("i", size) )

def DrawTextExt(text, x, y, fontID, r, g, b):
  x = TEXT(fontID, text, r, g, b, x, y)
  main.TEXTLIST.append(x)

def DrawText(text, x, y):
  DrawTextExt(text,
              x, 
              y,
              main.CURFONTID, 
              main.CURFONTCOLOR[0],
              main.CURFONTCOLOR[1],
              main.CURFONTCOLOR[2])

def SetTextColor(r,g,b):
  main.CURFONTCOLOR = (chr(r), chr(g), chr(b))

def function(fontID):
  main.CURFONTID = fontID

def SyncText():
  TextList = bytearray([])
  numText = 0

  for i in main.TEXTLIST:

    ar = bytearray(map ((lambda x: ord(x)), list(i.text)))
    for j in range(0, (256 - len(i.text))):
      ar += bytearray([0])

    numText += 1
    k = struct.pack ("iscccii", i.ID, ar, i.color[0], i.color[1],
                    i.color[2], i.position[0], i.position[1])
    TextList += k

  main.TEXTLIST = []
  return ((struct.pack("i", numText)) + TextList, numText * 271)

