//=================================================================================
//basic image
0.  IMAGE	LoadImage			( string filename, int sliceX = 1, int sliceY = 1 )
1.  int		GetImageSizeX		( IMAGE img )
2.  int		GetImageSizeY		( IMAGE img )

//=================================================================================
// basic sprite
3.  SPRITE	CreateSprite		( IMAGE img )
4.  void	SetSpritePosition	( SPRITE spr, int x, int y )
5.  void	SetSpriteAngle		( SPRITE spr, float fAngle )
6.  void	RotateSprite		( SPRITE spr, float fAngle )
7.  void	MoveSprite			( SPRITE spr, float fUnits )
8.  void	StrafeSprite		( SPRITE spr, float fUnits )
9.	void	SetSpriteSize		( SPRITE spr, int sx, int sy )
10. int		GetSpritePositionX	( SPRITE spr )
11. int 	GetSpritePositionY	( SPRITE spr )
12. int		GetSpriteSizeX		( SPRITE spr )
13. int		GetSpriteSizeY		( SPRITE spr )
14.	float	GetSpriteAngle		( SPRITE spr )

// sprite manipulation
15.  void	FlipSprite			( SPRITE spr, int H, int V )

// sprite animation
16. void	PlaySprite			( SPRITE spr, int frameST, int frameND, bool bLoop )
17. void	StopSprite			( SPRITE spr, bool bWaitCycle )
18. void	PauseSprite			( SPRITE spr )
19. void	ResumeSprite		( SPRITE spr )

//=================================================================================
// basic input
20. bool	KeyDown				( int key )
21. int		GetInputDirectionX	( void )
22. int		GetInputDirectionY	( void )

//=================================================================================
// basic camera
23. void	SetCameraPosition	( float fX, float fY )
24. void	SetCameraZoom		( float fZoom )

//=================================================================================
// basic sound
25. SOUND	LoadSound			( string filename )
26. void	PlaySound			( SOUND sound, bool bLoop )
27. void	StopSound			( SOUND sound, bool bWaitCycle )
28. void	PauseSound			( SOUND sound )
29. void	ResumeSound			( SOUND sound )
30. void	SetSoundVolume		( SOUND sound, float fVol )

// global sound
31. void	StopAllSounds		( )
32. void	SetMasterVolume		( float fVol )

//=================================================================================
// basic fonts
33. void	CreateFont			( int ID, string name, int size )

//basic text
34. void	DrawText			( string text, int x, int y )
35. void	DrawText			( string text, int x, int y, int fontID )
36. void	DrawText			( string text, int x, int y, int fontID, int r, int g, int b )
37. void	SetTextColor		( int r, int g, int b )
38. void	SetTextFont			( int fontID )

