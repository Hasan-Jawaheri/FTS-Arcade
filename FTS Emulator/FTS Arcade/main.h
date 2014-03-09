#ifndef _MAIN_H_ //header guard
#define _MAIN_H_

#include <HasX11.h>
#include "main menu.h"
#include "game running.h"

#define APPNAME "HasX11 App"

#define EMULATOR_MODE

//******************************************************************************************
//This is the main class that inherits from HasX11. This is the "container" of the game
//******************************************************************************************
class Application : public HasX11 {

public:
	Application ( void ); //constructor

	//***************************************************************************************
	//This is called once at the beginning of the application asking it to initialize
	//***************************************************************************************
	bool Setup ( void );

	//***************************************************************************************
	//This is called every frame asking the application to update
	//This occurs before rendering and rendering should NOT be done here
	//***************************************************************************************
	bool Loop ( float fDeltaTime );

	//***************************************************************************************
	//This is called once at the end of the program if it passes the Setup function
	//***************************************************************************************
	void Cleanup ( void );

	//***************************************************************************************
	//This is called twice, once with bBeforceProcessing set to true and then false. This
	//happens everytime windows sends a message to the window.
	//***************************************************************************************
	int WindowCallback ( HWND wnd, UINT msg, WPARAM w, LPARAM l, bool bBeforeProcessing );

private:
	friend class MainMenu;
	friend class GameRunning;
	bool bGameRunning;
	bool bSync;
public:

	//API functions
	void Sync ( char* data, UINT len );
	hxImage* LoadImage ( LPCSTR name, UINT sliceX, UINT sliceY );
	hxSprite* CreateSprite ( UINT imgID );
	void CreateFont ( UINT ID, LPCSTR name, UINT size );
	void OnStopGame ( void );
};

extern Application* APPHANDLE;
extern char* GAMELIB_PATH;

#endif //_MAIN_H_
