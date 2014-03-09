#ifndef _GAME_RUNNING_H_
#define _GAME_RUNNING_H_

#include "main.h"

class GameRunning : public hxGameState {
	UINT port;

	UINT imgID, sprID;
	char curPath[256];

public:
	GameRunning ( HasX11* hx11, char* game );

	virtual void Load ( void );
	virtual void Update ( float fDeltaTime );
	virtual void Cleanup ( void );

	void Sync ( char* data, UINT len );
	hxImage* LoadImage ( LPCSTR name, UINT sliceX, UINT sliceY );
	hxSprite* CreateSprite ( UINT imgID );
};

#endif //_GAME_RUNNING_H_