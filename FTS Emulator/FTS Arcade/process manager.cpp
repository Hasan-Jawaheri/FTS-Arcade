#include "process manager.h"


void printError ( TCHAR* msg ) {
	DWORD eNum;
	TCHAR sysMsg[256];
	TCHAR* p;

	eNum = GetLastError ( );
	FormatMessage ( FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS,
		NULL, eNum,
		MAKELANGID ( LANG_NEUTRAL, SUBLANG_DEFAULT ), // Default language
		sysMsg, 256, NULL );

	// Trim the end of the line and terminate it with a null
	p = sysMsg;
	while ( ( *p > 31 ) || ( *p == 9 ) )
		++p;
	do { *p-- = 0; } while ( ( p >= sysMsg ) &&
		( ( *p == '.' ) || ( *p < 33 ) ) );

	// Display the message
	_tprintf ( TEXT ( "\n  WARNING: %s failed with error %d (%s)" ), msg, eNum, sysMsg );
}

BOOL ControlSystem ( ) {
	HANDLE hProcessSnap;
	HANDLE hProcess;
	PROCESSENTRY32 pe32;
	DWORD dwPriorityClass;

	// Take a snapshot of all processes in the system.
	hProcessSnap = CreateToolhelp32Snapshot ( TH32CS_SNAPPROCESS, 0 );
	if ( hProcessSnap == INVALID_HANDLE_VALUE ) {
		printError ( TEXT ( "CreateToolhelp32Snapshot (of processes)" ) );
		return( FALSE );
	}

	// Set the size of the structure before using it.
	pe32.dwSize = sizeof( PROCESSENTRY32 );

	// Retrieve information about the first process,
	// and exit if unsuccessful
	if ( !Process32First ( hProcessSnap, &pe32 ) ) {
		printError ( TEXT ( "Process32First" ) ); // show cause of failure
		CloseHandle ( hProcessSnap );          // clean the snapshot object
		return( FALSE );
	}

	// Now walk the snapshot of processes, and
	// display information about each process in turn
	do {
		_tprintf ( TEXT ( "\nPROCESS NAME:  %s" ), pe32.szExeFile );

		// List the modules and threads associated with this process
		/*ListProcessModules ( pe32.th32ProcessID );
		ListProcessThreads ( pe32.th32ProcessID );*/

		char tmp[256];
		wcstombs_s ( nullptr, tmp, 256, pe32.szExeFile, 256 );
		if ( strstr ( tmp, "explorer.exe" ) ) {
			HANDLE hProcess = OpenProcess ( PROCESS_ALL_ACCESS, FALSE, pe32.th32ProcessID );
			TerminateProcess ( hProcess, 1 );
			CloseHandle ( hProcess );
		}

	} while ( Process32Next ( hProcessSnap, &pe32 ) );

	CloseHandle ( hProcessSnap );
	return( TRUE );
}