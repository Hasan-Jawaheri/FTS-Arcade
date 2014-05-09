#ifndef _COMMUNICATION_H_
#define _COMMUNICATION_H_

#include <Windows.h>
#include <winsock.h>
#include <HasX11.h>

#include "communication.h"

#define _SOCKET_EVENT_ WM_USER + 5513

bool ServerWndProc ( HWND wnd, UINT msg, WPARAM w, LPARAM l );
bool IsServerConnected ( void );
bool HostCommunication ( HasX11* hx11, UINT port );
void StopComunication ( bool bCleanup );
void SendSyncSignal ( int width, int height );
void KillClient ( void );

#endif //_COMMUNICATION_H_