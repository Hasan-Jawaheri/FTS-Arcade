#include "main.h"
#include "process manager.h"
#include "communication.h"
#include <ShlObj.h>
#pragma comment ( lib, "shell32.lib" )

Application* APPHANDLE = nullptr;
char* GAMELIB_PATH;

Application::Application ( void ) : HasX11 ( ) { //call the base constructor
}
bool Application::Setup ( void ) {
	//
	//Initialize the core. This must be done to create the window and initialize it
	//
	int scrW = GetSystemMetrics ( SM_CXSCREEN );
	int scrH = GetSystemMetrics ( SM_CYSCREEN );
#ifdef _DEBUG
	int width = 640;	//640 pixels wide
	int height = 480;	//480 pixels high
#else
	int width = scrW;
	int height = scrH;
#endif
	bool vsync = false;//enable vsync (prevents screen tearing)
	HX_ERROR err = core->Init ( width, height, vsync );
	if ( err != HX_SUCCEED ) { //An error occured. Very rare but should always be checked
		//retrieve the error as a string and print it
		char errorStr[256];
		hxGetError ( err, errorStr, 256 );
		MessageBoxA ( nullptr, errorStr, APPNAME, MB_ICONERROR | MB_OK );
		return false; //returning false from Setup will stop the application
	}
	maxFPS = 60;
	renderFlags = RENDERFLAG_NO3D |
					  RENDERFLAG_NOLIGHTING |
					  RENDERFLAG_NOPARTICLES |
					  RENDERFLAG_NOOBJECTSORT;

#if (!defined(_DEBUG) && !defined(EMULATOR_MODE))
	core->WindowsDevice->SetFullScreenState ( true );
#endif

	core->Renderer->CreateFont ( UINT_MAX - 1, "Agency FB", 150 );
	core->Renderer->CreateFont ( UINT_MAX - 2, "Agency FB", 100 );
	core->Renderer->CreateFont ( UINT_MAX - 3, "Agency FB", 50 );

	GAMELIB_PATH = new char[MAX_PATH];
	strcpy_s ( GAMELIB_PATH, MAX_PATH, "" );
	SHGetFolderPathA ( NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, GAMELIB_PATH );
	strcat_s ( GAMELIB_PATH, MAX_PATH, "\\FTS Collection\\" );

#ifndef EMULATOR_MODE
	ControlSystem ( );
#endif

	SwitchState ( new MainMenu ( this ) );
	return true;
}

bool Application::Loop ( float fDeltaTime ) {
#if (!defined(EMULATOR_MODE) && !defined(_DEBUG))
	if ( !core->WindowsDevice->GetFullScreenState ( ) )
		core->WindowsDevice->SetFullScreenState ( true );
#endif
	if ( !bSync ) {
		renderFlags =	RENDERFLAG_NO3D |
							RENDERFLAG_NOLIGHTING |
							RENDERFLAG_NOPARTICLES |
							RENDERFLAG_NOOBJECTSORT |
							RENDERFLAG_NO2D |
							RENDERFLAG_NOCLEAR;
	} else {
		renderFlags =	RENDERFLAG_NO3D |
							RENDERFLAG_NOLIGHTING |
							RENDERFLAG_NOPARTICLES |
							RENDERFLAG_NOOBJECTSORT;
	}
	return true;
}

void Application::Cleanup ( void ) {
	StopComunication ( true );
	delete[] GAMELIB_PATH;
}

int Application::WindowCallback ( HWND wnd, UINT msg,
											 WPARAM w, LPARAM l,
											 bool bBeforeProcessing ) {
	if ( bBeforeProcessing )
		ServerWndProc ( wnd, msg, w, l ); // intercept any socket messages
	return 0;
}

void Application::Sync ( char* data, UINT len ) {
	if ( bGameRunning )
		((GameRunning*)curState)->Sync ( data, len );
	bSync = true;
}
hxImage* Application::LoadImage ( LPCSTR name, UINT sliceX, UINT sliceY ) {
	if ( bGameRunning )
		return ((GameRunning*)curState)->LoadImage ( name, sliceX, sliceY );

	return nullptr;
}
hxSprite* Application::CreateSprite ( UINT imgID ) {
	if ( bGameRunning )
		return ((GameRunning*)curState)->CreateSprite ( imgID );

	return nullptr;
}
void Application::CreateFont ( UINT ID, LPCSTR name, UINT size ) {
	core->Renderer->CreateFont ( ID, name, size );
}
void Application::OnStopGame ( void ) {
	SwitchState ( new MainMenu ( this ) );
}

//******************************************************************************************
//This function is always needed. Every new HasX11 will be registered by the HasX11 system
//and will be automatically freed. Each new HasX11 class will run on its own thread. This
//can be used for multiuthreading. Note that the HasX11 class is completely generic and can
//run without core->Init and still work, thus you don't need to have 2 windows to use this
//multithreading feature.
//******************************************************************************************
void HasX11Init ( void ) {
	APPHANDLE = new Application; //The base construction, HasX11(), will take care of the rest.
}