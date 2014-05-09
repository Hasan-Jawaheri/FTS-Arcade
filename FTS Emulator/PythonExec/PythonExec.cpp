// PythonExec.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

int main ( int argc, char** argv )
{
	STARTUPINFOA info;
	GetStartupInfoA ( &info );

	char cmd[512];
	sprintf_s ( cmd, 512,
		"python \"%s\" %s",
		 argv[1], argv[2]);
	printf ( cmd );
	system ( cmd );

	if ( info.wShowWindow == SW_SHOW )
		getchar ( );
}