#ifndef _MAIN_MENU_H_
#define _MAIN_MENU_H_

#include "main.h"


class MainMenu : public hxGameState {
	hxImage* bkgImg;
	hxSprite* bkgSpr;
	hxPixelShader* bkgPS;
	float sliders[2];
	float fVel[2];
	float fDir[2];
	float fTimer[2];

	struct MENUITEM {
		char text[64];
		MENUITEM* parent;
		vector<MENUITEM*> submenu;
		void ( *action ) ( void* state );

		MENUITEM ( ) {
			strcpy_s ( text, 64, "" );
			parent = nullptr;
			action = nullptr;
		}
		~MENUITEM ( ) {
			for ( UINT i = 0; i < submenu.size ( ); i++ )
				delete submenu[i];
		}
	};
	MENUITEM* menu;
	int selection;
	bool bSwitchingState;

	static void HELPFUN ( void* state );
	static void CREDITSFUN ( void* state );
	static void PLAYGAMEFUN ( void* state );
	friend void HELPFUN ( void* state );
	friend void CREDITSFUN ( void* state );
	friend void PLAYGAMEFUN ( void* state );

public:
	MainMenu ( HasX11* hx11 );

	virtual void Load ( void );
	virtual void Update ( float fDeltaTime );
	virtual void Cleanup ( void );
	virtual void OnKeydown ( char key );
};

#endif //_MAIN_MENU_H_