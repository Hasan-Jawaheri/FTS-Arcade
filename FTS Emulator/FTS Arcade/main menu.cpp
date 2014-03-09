#include "main menu.h"

//******************************************************************************************
// MAIN MENU STATE
//******************************************************************************************
MainMenu::MainMenu ( HasX11* hx11 ) : hxGameState ( hx11 ) {

}
void MainMenu::Load ( void ) {
	APPHANDLE->bGameRunning = false;
	APPHANDLE->bSync = true;

	//=====================================================================
	//
	// THIS IS A HACK. MEMORY GETS RELOCATED AFTER 3 CYCLES OF GAME-MENU
	// AND __lastBoundResources ARRAY IN HasX11Effects.cpp STARTS TO POINT
	// TO WHAT SEEMS TO BE RE-USED TEXTURES (BECAUSE THEY POINT TO THE SAME
	// ADDRESS) WHILE THEY ARE ACTUALLY DIFFERENT.
	//
	core->EffectManager->Resize ( 0, 0 ); // will flush resource memory
	//=====================================================================

	core->Renderer->GetPrimaryRenderTarget ( )->SetClearColor ( 0, 0, 0 );
	bkgImg = new hxImage ( 5, core );
	bkgImg->Load ( "Data\\grid.bmp" );
	bkgSpr = new hxSprite ( 5, core );
	bkgSpr->GetMaterial ( )->SetImage ( bkgImg );
	bkgSpr->SetSize ( core->WindowsDevice->GetWindowWidth ( ),
		core->WindowsDevice->GetWindowHeight ( ) );
	bkgPS = new hxPixelShader ( core );
	bkgPS->LoadFromFile ( "Data\\background shader.ps",
		HX_MAKEPROFILE ( 4, 0 ), "PS" );
	bkgSpr->GetMaterial ( )->SetPixelShader ( bkgPS );
	sliders[0] = sliders[1] = 0.0f;
	fTimer[0] = fTimer[1] = 0;

	selection = 0;
	bSwitchingState = false;
	menu = new MENUITEM;
	strcpy_s ( menu->text, 64, "FTS Arcade" );
	{
		MENUITEM* playGame = new MENUITEM;
		playGame->parent = menu;
		strcpy_s ( playGame->text, 64, "Play Game" );
		{
			WIN32_FIND_DATAA data;
			char searchMask[MAX_PATH];
			sprintf_s ( searchMask, MAX_PATH, "%s*", GAMELIB_PATH );
			HANDLE hFile = FindFirstFileExA (
				searchMask,
				FindExInfoStandard,
				&data,
				FindExSearchLimitToDirectories,
				NULL,
				0 );
			if ( hFile != INVALID_HANDLE_VALUE ) {
				do {
					if ( strcmp ( ".", data.cFileName ) &&
						strcmp ( "..", data.cFileName ) ) {
						MENUITEM* game = new MENUITEM;
						game->parent = playGame;
						game->action = PLAYGAMEFUN;
						strcpy_s ( game->text, 64, data.cFileName );
						playGame->submenu.push_back ( game );
					}
				} while ( FindNextFileA ( hFile, &data ) );
			}
		}

		MENUITEM* help = new MENUITEM;
		help->parent = menu;
		help->action = HELPFUN;
		strcpy_s ( help->text, 64, "Help" );

		MENUITEM* credits = new MENUITEM;
		credits->parent = menu;
		credits->action = CREDITSFUN;
		strcpy_s ( credits->text, 64, "Credits" );

		MENUITEM* installGame = new MENUITEM;
		installGame->parent = menu;
		installGame->action = nullptr;
		strcpy_s ( installGame->text, 64, "Install Game" );

		menu->submenu.push_back ( playGame );
		menu->submenu.push_back ( help );
		menu->submenu.push_back ( credits );
		menu->submenu.push_back ( installGame );
	}
}
void MainMenu::Update ( float fDeltaTime ) {
	char path[256] = { '\0' };
	MENUITEM* curMenu = menu;
	while ( curMenu ) {
		char temp[256] = { '\0' };
		sprintf_s ( temp, 256, "%s > %s", curMenu->text, path );
		strcpy_s ( path, 256, temp );
		curMenu = curMenu->parent;
	}

	core->Renderer->SetFont ( UINT_MAX - 2 );
	core->Renderer->RenderText ( path, 10, 10,
		UINT_MAX - 2, hxColor ( 0.2, 0.0, 0.7 ) );
	for ( UINT i = 0; i < menu->submenu.size ( ); i++ ) {
		hxColor col = i == selection ? hxColor ( 0.01, 0.6, 0.05 )
			: hxColor ( 0.1, 0.0, 0.5 );
		if ( bSwitchingState ) {
			int ind = 0;
			if ( sliders[0] < 0.0f || sliders[0] > 1.0f )
				ind = 1;
			col.a = 1.0f * fDir[ind] - sliders[ind] * fDir[ind];
		}
		core->Renderer->RenderText ( menu->submenu[i]->text, 120, 220 + 130 * i,
			UINT_MAX - 2, col );
	}

	if ( !bSwitchingState ) {
		float fTime = core->GetBaseTimer ( )->GetElapsedTime ( );
		for ( UINT i = 0; i < 2; i++ ) {
			if ( fTime - fTimer[i] > 2500.0f ) {
				fVel[i] = float ( rand ( ) % 1000 ) / 1200.0f + 0.5f;
				if ( rand ( ) % 2 == 0 ) {
					sliders[i] = 0.0f;
					fDir[i] = 1.0f;
				} else {
					sliders[i] = 1.0f;
					fDir[i] = -1.0f;
				}
				fTimer[i] = fTime + float ( rand ( ) % 1000 ) - 500.0f;
			}
		}
	}
	sliders[0] = sliders[0] + fVel[0] * fDeltaTime * fDir[0];
	sliders[1] = sliders[1] + fVel[1] * fDeltaTime * fDir[1];
	bkgSpr->GetMaterial ( )->SetConstantBufferVariableFloatArray
		( "slide", 2, sliders );

	if ( bSwitchingState &&
		(sliders[0] > 1.0f || sliders[0] < 0.0f) &&
		(sliders[1] > 1.0f || sliders[1] < 0.0f) ) {
		app->SwitchState (
			new GameRunning ( app,
			menu->submenu[selection]->text ) );
	}
}
void MainMenu::Cleanup ( void ) {
	// delete the main menu - go back all the way to parent first
	MENUITEM* parent = menu;
	while ( true ) {
		if ( !parent->parent )
			break;
		parent = parent->parent;
	}
	delete menu;

	HX_SAFE_REMOVEREF ( bkgImg );
	HX_SAFE_REMOVEREF ( bkgPS );
	HX_SAFE_REMOVEREF ( bkgSpr );
}
void MainMenu::HELPFUN ( void* _state ) {
	MainMenu* state = (MainMenu*)_state;

}
void MainMenu::CREDITSFUN ( void* _state ) {
	MainMenu* state = (MainMenu*)_state;

}
void MainMenu::PLAYGAMEFUN ( void* _state ) {
	MainMenu* state = (MainMenu*)_state;
	state->bSwitchingState = true;
}
void MainMenu::OnKeydown ( char key ) {
	if ( key == VK_UP )
		selection = ( selection - 1 ) % menu->submenu.size ( );
	if ( key == VK_DOWN )
		selection = ( selection + 1 ) % menu->submenu.size ( );
	if ( key == VK_RETURN ) {
		if ( menu->submenu[selection]->action )
			menu->submenu[selection]->action ( this );
		else if ( menu->submenu[selection]->submenu.size ( ) ) {
			selection = 0;
			menu = menu->submenu[selection];
		}
	}
	if ( key == VK_BACK ) {
		if ( menu->parent ) {
			selection = 0;
			menu = menu->parent;
		}
	}
}