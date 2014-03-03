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
//   ID    (unsigned int)
//   sizeX (unsigned int)
//   sizeY (unsigned int)
//----------------------------------------------------------------------------------
0.  IMAGE	LoadImage			( string filename, int sliceX = 1, int sliceY = 1 )		<-- o <->
1.  int		GetImageSizeX		( IMAGE img )											--> o
2.  int		GetImageSizeY		( IMAGE img )											--> o
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
//   ID         
//   position
//   size
//   flipState
//   bPlaying
//   bLooping
//   bPaused
//----------------------------------------------------------------------------------
3.  SPRITE	CreateSprite		( IMAGE img )											<-- o <->
4.  void	SetSpritePosition	( SPRITE spr, int x, int y )							<-- o
5.  void	SetSpriteAngle		( SPRITE spr, float fAngle )							<-- o
6.  void	RotateSprite		( SPRITE spr, float fAngle )							<-- o
7.  void	MoveSprite			( SPRITE spr, float fUnits )							<-- o
8.  void	StrafeSprite		( SPRITE spr, float fUnits )							<-- o
9.	void	SetSpriteSize		( SPRITE spr, int sx, int sy )							<-- o
10. int		GetSpritePositionX	( SPRITE spr )											--> o
11. int 	GetSpritePositionY	( SPRITE spr )											--> o
12. int		GetSpriteSizeX		( SPRITE spr )											--> o
13. int		GetSpriteSizeY		( SPRITE spr )											--> o
14.	float	GetSpriteAngle		( SPRITE spr )											--> o
//----------------------------------------------------------------------------------
// sprite manipulation
//----------------------------------------------------------------------------------
15.  void	FlipSprite			( SPRITE spr, int H, int V )							<-- o
//----------------------------------------------------------------------------------
// sprite animation
//----------------------------------------------------------------------------------
16. void	PlaySprite			( SPRITE spr, int frameST, int frameND, bool bLoop )	<-- o
17. void	StopSprite			( SPRITE spr, bool bWaitCycle )							<-- o
18. void	PauseSprite			( SPRITE spr )											<-- o
19. void	ResumeSprite		( SPRITE spr )											<-- o
//=================================================================================

//=================================================================================
//=================================================================================
//----------------------------------------------------------------------------------
// basic input
//----------------------------------------------------------------------------------
20. bool	KeyDown				( int key )												--> o
21. int		GetInputDirectionX	( void )												--> o
22. int		GetInputDirectionY	( void )												--> o
//=================================================================================

//=================================================================================
//=================================================================================
//----------------------------------------------------------------------------------
// basic camera
//----------------------------------------------------------------------------------
23. void	SetCameraPosition	( float fX, float fY )									<-- o
24. void	SetCameraZoom		( float fZoom )											<-- o
//=================================================================================

//=================================================================================
//=================================================================================
//----------------------------------------------------------------------------------
// basic sound
//----------------------------------------------------------------------------------
25. SOUND	LoadSound			( string filename )										CUSTOM
26. void	PlaySound			( SOUND sound, bool bLoop )								CUSTOM
27. void	StopSound			( SOUND sound, bool bWaitCycle )						CUSTOM
28. void	PauseSound			( SOUND sound )											CUSTOM
29. void	ResumeSound			( SOUND sound )											CUSTOM
30. void	SetSoundVolume		( SOUND sound, float fVol )								CUSTOM
//----------------------------------------------------------------------------------
// global sound
//----------------------------------------------------------------------------------
31. void	StopAllSounds		( )														CUSTOM
32. void	SetMasterVolume		( float fVol )											CUSTOM
//=================================================================================

//=================================================================================
//=================================================================================
//----------------------------------------------------------------------------------
// basic fonts
//----------------------------------------------------------------------------------
33. void	CreateFont			( int ID, string name, int size )						    o -->
//----------------------------------------------------------------------------------
//basic text
//----------------------------------------------------------------------------------
34. void	DrawText			( string text, int x, int y )							<-- o
35. void	DrawText			( string text, int x, int y, int fontID )				<-- o
36. void	DrawText			( string text, int x, int y, int fontID,				
								  int r, int g, int b )									<-- o
37. void	SetTextColor		( int r, int g, int b )									<-- o
38. void	SetTextFont			( int fontID )											<-- o
//=================================================================================

//=================================================================================
//=================================================================================
//----------------------------------------------------------------------------------
// general purpose
//----------------------------------------------------------------------------------
254. void	FTSInit				( )														    o
255. void	Sync				( )														--> o -->
//=================================================================================