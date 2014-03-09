#include "API map.h"
#include <memory>
#include "main.h"

const unsigned short mappingTable[] = {
	0,
	sizeof ( _LoadImage ),
	sizeof ( _CreateSprite ),
	sizeof ( _CreateFont )
};

REPLY API_CALL ( unsigned int funID, char* pParams, unsigned int len ) {
	REPLY rep;
	rep.msg = nullptr;
	rep.len = 0;
	switch ( funID ) {
		case 0: { // Sync
			APPHANDLE->Sync ( pParams, len );
			rep.msg = new char[4];
			rep.len = 4;
			UINT temp = 0;
			memcpy ( rep.msg, (void*)&temp, 4 );
			break;
		} case 1: { // LoadImage
			struct _LoadImage params;
			memcpy ( (char*)&params, pParams, mappingTable[funID] );
			hxImage* img = APPHANDLE->LoadImage ( params.filename,
															  params.sliceX,
															  params.sliceY );
			rep.msg = new char[12];
			rep.len = 12;
			if ( img ) {
				UINT temp = img->GetID ( );
				memcpy ( rep.msg, (void*)&temp, 4 );
				temp = img->GetWidth ( );
				memcpy ( rep.msg + 4, (void*)&temp, 4 );
				temp = img->GetHeight ( );
				memcpy ( rep.msg + 8, (void*)&temp, 4 );
			} else {
				ZeroMemory ( rep.msg, 12 );
			}
			break;
		} case 2: { // CreateSprite
			struct _CreateSprite params;
			memcpy ( (char*)&params, pParams, mappingTable[funID] );
			hxSprite* spr = APPHANDLE->CreateSprite ( params.imageID );
			rep.msg = new char[4];
			rep.len = 4;
			if ( spr ) {
				UINT temp = spr->GetID ( );
				memcpy ( rep.msg, (void*)&temp, 4 );
			} else {
				ZeroMemory ( rep.msg, 4 );
			}
			break;
		} case 3: { // CreateFont
			struct _CreateFont params;
			memcpy ( (char*)&params, pParams, mappingTable[funID] );
			APPHANDLE->CreateFont ( params.ID, params.name, params.size );
			break;
		}
	}

	return rep;
}