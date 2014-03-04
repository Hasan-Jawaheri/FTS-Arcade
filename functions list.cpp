//***********************************************
// KEY:                                         *
//    python   this   C++                       *
//    <-------> o <----->                       *
//    Arrow indicates communication direction   *
//***********************************************


//=================================================================================
//=================================================================================
//----------------------------------------------------------------------------------
// BASIC IMAGE
// An image is a resource that is handled by the C++ side. Loading an image must be
// done on the C++ side, and the python side has to wait for it.
// A local copy of the image information has to be stored on python for instant
// access to size.
// IMAGE LOCAL COPY:
//   ID     (unsigned int)
//   width  (unsigned int)
//   height (unsigned int)
//----------------------------------------------------------------------------------
1.  IMAGE   LoadImage           ( string filename, int sliceX = 1, int sliceY = 1 )     <-- o <->
-.  int     GetImageWidth       ( IMAGE img )                                           --> o
-.  int     GetImageHeight      ( IMAGE img )                                           --> o
//=================================================================================

//=================================================================================
//=================================================================================
//----------------------------------------------------------------------------------
// BASIC SPRITE
// A sprite is a resource that is handled by the C++ side. Loading a sprite muist be
// done on the C++ side, and the python side has to wait for it.
// A local copy of the sprite information has to be stored on python for instant
// movement/access.
// SPRITE LOCAL COPY:
//   ID         (unsigned int)
//   position   (vector2)
//   size       (vector2)
//   look       (vector2)
//   flipState  (char)    'a' = no flip, 'b' = hFlip, 'c' = vFlip, 'd' = h+vFlip
//   bPlaying   (bool)
//   bLooping   (bool)
//   bPaused    (bool)
//----------------------------------------------------------------------------------
2.  SPRITE  CreateSprite        ( IMAGE img )                                           <-- o <->
-.  void    SetSpritePosition   ( SPRITE spr, int x, int y )                            <-- o
-.  void    SetSpriteAngle      ( SPRITE spr, float fAngle )                            <-- o
-.  void    RotateSprite        ( SPRITE spr, float fAngle )                            <-- o
-.  void    MoveSprite          ( SPRITE spr, float fUnits )                            <-- o
-.  void    StrafeSprite        ( SPRITE spr, float fUnits )                            <-- o
-.  void    SetSpriteSize       ( SPRITE spr, int sx, int sy )                          <-- o
-.  int     GetSpritePositionX  ( SPRITE spr )                                          --> o
-.  int     GetSpritePositionY  ( SPRITE spr )                                          --> o
-.  int     GetSpriteSizeX      ( SPRITE spr )                                          --> o
-.  int     GetSpriteSizeY      ( SPRITE spr )                                          --> o
-.  float   GetSpriteAngle      ( SPRITE spr )                                          --> o
//----------------------------------------------------------------------------------
// sprite manipulation
//----------------------------------------------------------------------------------
-.  void    FlipSprite          ( SPRITE spr, int H, int V )                            <-- o
//----------------------------------------------------------------------------------
// sprite animation
//----------------------------------------------------------------------------------
-.  void    PlaySprite          ( SPRITE spr, int frameST, int frameND, bool bLoop )    <-- o
-.  void    StopSprite          ( SPRITE spr, bool bWaitCycle )                         <-- o
-.  void    PauseSprite         ( SPRITE spr )                                          <-- o
-.  void    ResumeSprite        ( SPRITE spr )                                          <-- o
//=================================================================================

//=================================================================================
//=================================================================================
//----------------------------------------------------------------------------------
// BASIC INPUT
// Use a python library
//----------------------------------------------------------------------------------
-.  bool    KeyDown             ( int key )                                             --> o
-.  int     GetInputDirectionX  ( void )                                                --> o
-.  int     GetInputDirectionY  ( void )                                                --> o
//=================================================================================

//=================================================================================
//=================================================================================
//----------------------------------------------------------------------------------
// BASIC CAMERA
// A camera is a shift of coordinates for sprites.
// CAMERA LOCAL COPY
//   position (vector2)
//   zoom     (float)
//----------------------------------------------------------------------------------
-.  void    SetCameraPosition   ( float fX, float fY )                                  <-- o
-.  void    SetCameraZoom       ( float fZoom )                                         <-- o
//=================================================================================

//=================================================================================
//=================================================================================
//----------------------------------------------------------------------------------
// BASIC SOUND
// Use an external library
//----------------------------------------------------------------------------------
-.  SOUND   LoadSound           ( string filename )                                     CUSTOM
-.  void    PlaySound           ( SOUND sound, bool bLoop )                             CUSTOM
-.  void    StopSound           ( SOUND sound, bool bWaitCycle )                        CUSTOM
-.  void    PauseSound          ( SOUND sound )                                         CUSTOM
-.  void    ResumeSound         ( SOUND sound )                                         CUSTOM
-.  void    SetSoundVolume      ( SOUND sound, float fVol )                             CUSTOM
//----------------------------------------------------------------------------------
// GLOBAL SOUND
//----------------------------------------------------------------------------------
-.  void    StopAllSounds       ( )                                                     CUSTOM
-.  void    SetMasterVolume     ( float fVol )                                          CUSTOM
//=================================================================================

//=================================================================================
//=================================================================================
//----------------------------------------------------------------------------------
// BASIC FONTS
// Fonts are not stored locally.
//----------------------------------------------------------------------------------
3. void CreateFont          ( int ID, string name, int size )                           o -->
//----------------------------------------------------------------------------------
// BASIC TEXT
// Text is stored in structures on the python side and are sent to C++ in sync()
// calls. ERASE ALL TEXT DATA EVERY SYNC.
// TEXT LOCAL COPY:
//   fontID (int)
//   text   (string)
//   color  (3 characters(bytes))
//----------------------------------------------------------------------------------
-.  void    DrawText            ( string text, int x, int y )                           <-- o
-.  void    DrawText            ( string text, int x, int y, int fontID )               <-- o
-.  void    DrawText            ( string text, int x, int y, int fontID,                
                                  int r, int g, int b )                                 <-- o
-.  void    SetTextColor        ( int r, int g, int b )                                 <-- o
-.  void    SetTextFont         ( int fontID )                                          <-- o
//=================================================================================

//=================================================================================
//=================================================================================
//----------------------------------------------------------------------------------
// GENERAL PURPOSE
// FTSInit() will establish a connection between the python code and the C++ server.
// It will also initialize any internal data structures.
// Sync() is the heart of the program. Sync() will send the current state of the
// program to the C++ side asking it to draw the frame. Sync() must flush the text
// buffers because they are refilled every frame (by the user).
//----------------------------------------------------------------------------------
-.  void    FTSInit             ( )                                                         o
0.   void   Sync                ( )                                                     --> o -->
//=================================================================================