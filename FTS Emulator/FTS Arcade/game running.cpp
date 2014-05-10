#include "game running.h"
#include "communication.h"
#include <shellapi.h>

//******************************************************************************************
// GAME RUNNING STATE
//******************************************************************************************
GameRunning::GameRunning ( HasX11* hx11, char* game ) : hxGameState ( hx11 ) {
	imgID = sprID = 1;
	strcpy_s ( curPath, 256, game );
}
void GameRunning::Load ( void ) {
	// TODO: Launch python code, passing a the port to the python code as a
	// command line argument (port is randomly generated every run).
	UINT numTries = 0;
	bool bHosted = false;
	do {
		port = rand ( ) % 2000;
		port += 5000;
		bHosted = HostCommunication ( app, port );
		numTries++;
	} while ( !bHosted && numTries < 5 );

	if ( bHosted ) {
		char command[1024];
		sprintf_s ( command, 1024,
			"\"%s..\" %d \"%s\"",
			GAMELIB_PATH, port, curPath );
		HINSTANCE err = ShellExecute ( nullptr,
			"open",
			"PythonExec.exe",
			command,
			"",
#ifndef EMULATOR_MODE
			SW_HIDE
#else
			SW_SHOW
#endif
			);
		APPHANDLE->bGameRunning = true;
		APPHANDLE->bSync = false;
	}
}
void GameRunning::Update ( float fDeltaTime ) {
	if ( !IsServerConnected ( ) ) {
		APPHANDLE->SwitchState ( new MainMenu ( APPHANDLE ) );
	}
}
void GameRunning::Cleanup ( void ) {
	StopComunication ( false );

	printf ( "GAME TERMINATING!\n" );
	for ( UINT i = 1; i < sprID; i++ ) {
		hxSprite* spr = core->SpriteManager->GetEntity ( i );
		if ( spr )
			HX_SAFE_REMOVEREF ( spr );
	}
	for ( UINT i = 1; i < imgID; i++ ) {
		hxImage* img = core->ImageManager->GetEntity ( i );
		if ( img )
			HX_SAFE_REMOVEREF ( img );
	}
	core->SpriteManager->GetDefaultSpriteEffect ( )->GetPixelShader ( )->SetTexture ( 0, nullptr );
	printf ( "GAME TERMINATION ENDED!\n" );
}
void GameRunning::Sync ( char* data, UINT len ) {
	struct CAMERA {
		hxVector2 pos;
		float fZoom;
	};
	struct SPRITE {
		UINT ID;
		UINT imgID;
		hxVector2 pos;
		hxVector2 size;
		hxVector2 look;
		char flipState;
		bool bHidden;
		bool bPlaying;
		bool bLooping;
		bool bPaused;
		bool pad[3];
	};

	struct TEXT {
		UINT fontID;
		char text[256];
		BYTE color[4];
		int x, y;
	};
	UINT camSize = sizeof CAMERA;
	UINT spriteSize = sizeof SPRITE;
	UINT textSize = sizeof TEXT;
	UINT p = 0;

	CAMERA cam;
	memcpy ( (char*)&cam, data + p, camSize );
	p += camSize;

	UINT numSprites;
	memcpy ( (char*)&numSprites, data + p, 4 );
	p += 4;
	if ( numSprites ) {
		SPRITE* sprites = new SPRITE[numSprites];
		memcpy ( (char*)sprites, data + p, spriteSize * numSprites );
		p += spriteSize * numSprites;
		for ( UINT i = 0; i < numSprites; i++ ) {
			hxSprite* spr = core->SpriteManager->GetEntity ( sprites[i].ID );
			if ( !spr ) {
				delete[] sprites;
				KillClient ( );
				return;
			}
			spr->GetMaterial ( )->SetImage ( core->ImageManager->GetEntity ( sprites[i].imgID ) );
			spr->SetPosition ( sprites[i].pos );
			spr->SetSize ( sprites[i].size );
			spr->SetAngle ( acos ( sprites[i].look.x ) *
				( sprites[i].look.y >= 0.0f ? 1 : -1 ) *
				180.0f / HX_PI );
			if ( sprites[i].bHidden )
				spr->Hide ( );
			else
				spr->Show ( );
		}
		delete[] sprites;
	}

	UINT numTexts;
	memcpy ( (char*)&numTexts, data + p, 4 );
	p += 4;
	if ( numTexts ) {
		TEXT* texts = new TEXT[numTexts];
		memcpy ( (char*)texts, data + p, numTexts * textSize );
		p += numTexts * textSize;
		for ( UINT i = 0; i < numTexts; i++ ) {
			core->Renderer->RenderText
				( texts[i].text, texts[i].x, texts[i].y, texts[i].fontID,
				hxColor ( float ( texts[i].color[0] ) / 255.0f,
				float ( texts[i].color[1] ) / 255.0f,
				float ( texts[i].color[2] ) / 255.0f ) );
		}
		delete[] texts;
	}

	if ( p != len )
		int x = 0;
}
hxImage* GameRunning::LoadImage ( LPCSTR name, UINT sliceX, UINT sliceY ) {
	char filename[MAX_PATH];
	sprintf_s ( filename, MAX_PATH,
		"%s%s\\%s",
		GAMELIB_PATH, curPath, name );
	hxImage* img = new hxImage ( imgID++, core );
	HX_ERROR err = img->Load ( filename );
	if ( err == HX_SUCCEED )
		return img;

	HX_SAFE_REMOVEREF ( img );
	return nullptr;
}
hxSprite* GameRunning::CreateSprite ( UINT imgID ) {
	hxImage* img = core->ImageManager->GetEntity ( imgID );
	if ( img ) {
		if ( img->Valid ( ) ) {
			hxSprite* spr = new hxSprite ( sprID++, core );
			HX_ERROR err = spr->GetMaterial ( )->SetImage ( img );
			spr->SetSize ( img->GetWidth ( ), img->GetHeight ( ) );
			spr->SetPosition ( core->WindowsDevice->GetWindowWidth ( ) + 1,
									 core->WindowsDevice->GetWindowHeight ( ) + 1 );
			if ( err != HX_SUCCEED ) {
				HX_SAFE_REMOVEREF ( spr );
				return nullptr;
			}
			return spr;
		}
	}

	return nullptr;
}