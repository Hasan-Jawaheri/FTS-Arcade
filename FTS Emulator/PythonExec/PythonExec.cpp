// PythonExec.cpp : Defines the entry point for the console application.
//

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#include <fstream>
using namespace std;

int main ( int argc, char** argv )
{
	STARTUPINFOA info;
	GetStartupInfoA ( &info );

	FILE* fp;
	char bootFile[512], gameFile[512];
	sprintf_s ( bootFile, 512, "%s\\FTS Collection\\%s\\bootstrap.py", argv[1], argv[3] );
	sprintf_s ( gameFile, 512, "%s\\FTS Collection\\%s\\%s.py", argv[1], argv[3], argv[3] );
	printf ( "gameFile: %s", gameFile );
	fstream f;
	f.open ( gameFile, ios::in );
	if ( f.is_open ( ) ) {
		f.seekg ( 0, ios::end );
		UINT dataSize = f.tellg ( );
		f.seekg ( 0, ios::beg );
		char* data = new char[dataSize+1];
		f.read ( data, dataSize );
		f.close ( );
		data[dataSize] = 0;

		fopen_s ( &fp, bootFile, "w" );
		if ( fp ) {
			fprintf ( fp, "import sys\nsys.path.insert(0, \"%s\\FTS Arcade\\API\")\n\n%s", argv[1], data );
			fclose ( fp );
		}

		delete[] data;

		char cmd[1024];
		sprintf_s ( cmd, 1024,
			"python \"%s\" %s",
			bootFile, argv[2] );
		printf ( cmd );
		system ( cmd );

		if ( info.wShowWindow == SW_SHOW )
			getchar ( );
	}
}