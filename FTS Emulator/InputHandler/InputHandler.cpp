// InputHandler.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include <stdio.h>

#define DIRECTINPUT_VERSION 0x0800
#include <dinput.h>
#pragma comment (lib, "dinput8.lib")
#pragma comment (lib, "dxguid.lib")

#define EXPORT _declspec(dllexport)

HWND dummyWnd;
IDirectInput8A* didev = nullptr;
IDirectInputDevice8A* inputDevice = nullptr;

LRESULT CALLBACK wndProc ( HWND wnd, UINT msg, WPARAM w, LPARAM l ) {
	if ( msg == WM_ACTIVATE && w != WA_INACTIVE ) {
		if ( inputDevice ) {
			HRESULT hr = inputDevice->Acquire ( );
		}
	}
	return DefWindowProcA ( wnd, msg, w, l );
}

BOOL EnumCallback (
	LPCDIDEVICEINSTANCEA lpddi,
	LPVOID pvRef ) {
	MessageBoxA ( NULL, lpddi->tszProductName, "Found device!", MB_OK );
	HRESULT hr = didev->CreateDevice ( lpddi->guidInstance, &inputDevice, nullptr );
	if ( FAILED ( hr ) )
		MessageBoxA ( NULL, "CreateDevice failed", "Error", MB_OK );

	MessageBoxA ( NULL, "done", "", MB_OK );
	return DIENUM_STOP;
}

void OnAttach ( void ) {
/*	HRESULT hr;

	MessageBoxA ( NULL, "OnAttach()", "", MB_OK );

	hr = DirectInput8Create (
		GetModuleHandle ( nullptr ),
		DIRECTINPUT_VERSION,
		IID_IDirectInput8A,
		(void**)&didev,
		NULL
		);

	WNDCLASSEXA wc;
	ZeroMemory ( &wc, sizeof ( WNDCLASSEXA ) );
	wc.cbSize = sizeof ( WNDCLASSEXA );
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hIcon = NULL;
	wc.hIconSm = NULL;
	wc.lpfnWndProc = wndProc;
	wc.lpszClassName = "YEL3ANTHALCLASS";
	wc.hInstance = NULL;
	wc.hbrBackground = (HBRUSH)( 1 + COLOR_WINDOW );
	wc.style = CS_SAVEBITS | CS_HREDRAW;
	wc.hCursor = LoadCursorA ( NULL, MAKEINTRESOURCEA ( 32512 ) );
	if ( !RegisterClassExA ( &wc ) ) {
		DWORD err = GetLastError ( );
		MessageBoxA ( NULL, "class failed", "", MB_OK );
	}


	dummyWnd = CreateWindowA ( "YEL3ANTHALCLASS", "", WS_VISIBLE | WS_POPUP,
		0, 0, 100, 100, NULL, NULL,
		GetModuleHandleA ( NULL ), NULL );
	if ( !dummyWnd )
		MessageBoxA ( NULL, "window failed", "", MB_OK );

	hr = didev->EnumDevices (
		DI8DEVCLASS_GAMECTRL,
		(LPDIENUMDEVICESCALLBACKA)EnumCallback,
		nullptr,
		DIEDFL_ATTACHEDONLY
		);

	if ( inputDevice->SetCooperativeLevel ( dummyWnd, DISCL_EXCLUSIVE | DISCL_BACKGROUND ) != DI_OK ) {
		MessageBoxA ( NULL, "YAL3AN THALWAJH", "", MB_OK );
	}

	hr = inputDevice->SetDataFormat ( &c_dfDIJoystick );
	if ( FAILED ( hr ) )
		MessageBoxA ( NULL, "SDF failed", "Error", MB_OK );*/
}

void OnDetach ( void ) {
/*	if ( inputDevice ) {
		inputDevice->Unacquire ( );
		inputDevice->Release ( );
	}
	didev->Release ( );*/
}

EXPORT int KeyDown ( int key ) {
	return GetAsyncKeyState ( key );
/*	DIJOYSTATE data;
	HRESULT hr = inputDevice->GetDeviceState (
		sizeof ( DIJOYSTATE ),
		(LPDIDEVICEOBJECTDATA)&data );
	if ( FAILED ( hr ) ) {
		char text[256];
		switch ( hr ) {
			case DIERR_NOTACQUIRED:
				hr = 0;
				break;
			case DIERR_INPUTLOST:
				hr = 1;
				break;
			case DIERR_INVALIDPARAM:
				hr = 2;
				break;
			case DIERR_NOTBUFFERED:
				hr = 3;
				break;
			case DIERR_NOTINITIALIZED:
				hr = 4;
				break;
		}
		sprintf_s ( text, 256, "Error %d, received %d, HR = %d", GetLastError ( ), 0, hr );
		MessageBoxA ( NULL, "KeyDown failed", text, MB_OK );
	}
	char text[256];
	sprintf_s ( text, 256, "inpuit: %d", key );
	MessageBoxA ( NULL, "KeyDown failed", text, MB_OK );
	return data.rgbButtons[key];*/
}
EXPORT int GetInputDirectionX ( void ) {
	DIJOYSTATE data;
	HRESULT hr = inputDevice->GetDeviceState (
		sizeof ( DIJOYSTATE ),
		(LPDIDEVICEOBJECTDATA)&data );
	if ( FAILED ( hr ) )
		MessageBoxA ( NULL, "GIDX failed", "Error", MB_OK );
	return data.lRx;
}
EXPORT int GetInputDirectionY ( void ) {
	DIJOYSTATE data;
	HRESULT hr = inputDevice->GetDeviceState (
		sizeof ( DIJOYSTATE ),
		(LPDIDEVICEOBJECTDATA)&data );
	if ( FAILED ( hr ) )
		MessageBoxA ( NULL, "GIDY failed", "Error", MB_OK );
	return data.lRy;
}