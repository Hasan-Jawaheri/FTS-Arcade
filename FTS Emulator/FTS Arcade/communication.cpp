#include "communication.h"
#include "API map.h"
#include "main.h"

#define _SOCKET_EVENT_ WM_USER + 5513

bool winsockInitialized = false;
struct SERVER {
	bool bConnected;
	SOCKET skt, curClient;
	hostent* hostInfo;
	UINT timeout;
} *server;

void KillClient ( void ) {
	closesocket ( server->curClient );
	server->curClient = 0;
	APPHANDLE->OnStopGame ( );
}

bool ServerWndProc ( HWND wnd, UINT msg, WPARAM w, LPARAM l ) {
	if ( server && msg == _SOCKET_EVENT_ ) {
		if ( WSAGETSELECTERROR ( l ) || !server->bConnected ) {
			closesocket ( server->skt );
			server->skt = 0;
			server->bConnected = false; //error occured, disconnect the server
			return false;
		}

		switch ( WSAGETSELECTEVENT ( l ) ) {
			case FD_READ: //a message is available for reading
			{
				UINT posInBuffer = 0;
				UINT bytesReceived = 0;
				UINT leastActiveBuffer = 0;
				struct ARR8192 { char arr[8192]; };
				vector<ARR8192>* buffer = new vector<ARR8192> ();

				// get the first buffer
				ARR8192 a;
				buffer->push_back ( a );
				bytesReceived = recv ( server->curClient,
											  (char*)&(*buffer)[0], 8192, 0 );
				if ( bytesReceived == SOCKET_ERROR )
					bytesReceived = 0;

				UINT curBufSize = bytesReceived;
				while ( bytesReceived > 0 ) {
					while ( posInBuffer + 4 <= curBufSize ) {
						UINT readOffset = 0;
						UINT funID;
						memcpy ( &funID, (char*)&(*buffer)[0] + posInBuffer, 4 );
						readOffset += 4;
						if ( funID > MAX_FUNCTION_ID ) {
							KillClient ( );
							break;
						}

						int funParamSize = 0;
						if ( funID == 0 ) {
							if ( posInBuffer + readOffset + 4 <
									buffer->size ( ) * 8192 ) {
								memcpy ( &funParamSize,
											(char*)&(*buffer)[0] + posInBuffer + 4,
											4 );
								readOffset += 4;
							} else
								break; // not enough bytes to get sync size, stop reading
						} else
							funParamSize = API_MAP_FUN_SIZE ( funID );

						if ( posInBuffer + readOffset + funParamSize <= curBufSize ) {
							// we have enough bytes for the parameter too, read it
							char* tmpBuf = new char[funParamSize];
							memcpy ( tmpBuf,
										(char*)&(*buffer)[0] + posInBuffer + readOffset,
										funParamSize );
							readOffset += funParamSize;
							REPLY rep = API_CALL ( funID, tmpBuf, funParamSize );
							if ( rep.len ) {
								send ( server->curClient, rep.msg, rep.len, 0 );
								delete[] rep.msg;
							}
							delete[] tmpBuf;
						} else {
							// not enough bytes available, stop reading
							break;
						}
						posInBuffer += readOffset;
					}

					// delete buffers that were already digested
					while ( posInBuffer >= 8192 ) {
						buffer->erase ( buffer->begin ( ) );
						posInBuffer -= 8192;
						curBufSize -= 8192;
					}
					//receive the next buffer
					buffer->push_back ( a );
					bytesReceived = recv ( server->curClient,
													(char*)&(*buffer)[0] + curBufSize,
													8192, 0 );
					curBufSize += bytesReceived;
					if ( posInBuffer + bytesReceived <=
								( buffer->size ( ) - 1 ) * 8192 )
						buffer->erase ( buffer->begin ( ) + buffer->size ( ) - 1 );
					if ( bytesReceived == SOCKET_ERROR )
						bytesReceived = 0;
				}

				// delete any remaining buffers
				buffer->clear ( );
				delete buffer;

				server->timeout = timeGetTime ( );
				break;
			}

			case FD_ACCEPT: //a client connected, accept it
			{
				if ( !server->curClient ) {
					server->curClient = accept ( server->skt, NULL, NULL );
					printf ( "Client connected!\n" );
					break;
				}
			}
			case FD_CLOSE:
			{
				if ( server->curClient != (SOCKET)w ) {
					printf ( "Client rejected!\n" );
				} else {
					KillClient ( );
					printf ( "Client disconnected!\n" );
				}
			}

			default:
				break;
		}
		return true;
	}
	return true;
}

bool HostCommunication ( HasX11* hx11, UINT port ) {
	if ( !winsockInitialized ) {
		//initialize the winsock API
		WSADATA wsData;
		WSAStartup ( MAKEWORD ( 2, 2 ), &wsData );
		server = new SERVER;
		server->bConnected = false;
		server->hostInfo = nullptr;
		server->skt = 0;
		server->curClient = 0;
		winsockInitialized = true;
	}

	if ( server->bConnected ) {
		closesocket ( server->skt );
		server->bConnected = false;
	}

	server->hostInfo = gethostbyname ( "localhost" );
	if ( !server->hostInfo ) {
		return false;
	}

	// connect through internet and use TCP
	server->skt = socket ( AF_INET, SOCK_STREAM, IPPROTO_TCP );
	if ( server->skt == INVALID_SOCKET ) {
		return false;
	}

	// make winsock notify the dummy window when an even occurs
	WSAAsyncSelect ( server->skt,
						  hx11->core->WindowsDevice->GetWindow ( ),
						  _SOCKET_EVENT_,
						  FD_READ | FD_ACCEPT | FD_CLOSE );

	// Use a SOCKADDR_IN struct to fill in address information
	SOCKADDR_IN serverInfo;

	serverInfo.sin_family = AF_INET;
	serverInfo.sin_addr = *( (LPIN_ADDR)*server->hostInfo->h_addr_list );
	serverInfo.sin_port = htons ( port );

	// Bind the socket to our local server address
	if ( bind ( server->skt,
					(LPSOCKADDR)&serverInfo,
					sizeof sockaddr ) == SOCKET_ERROR ) {
		closesocket ( server->skt );
		return false;
	}

	// Make the socket listen
	if ( listen ( server->skt, 1 ) == SOCKET_ERROR ) {
		closesocket ( server->skt );
		return false;
	}

	//succeeded hosting
	server->bConnected = true;
	server->timeout = timeGetTime ( );
	return true;
}
void StopComunication ( bool bCleanup ) {
	if ( winsockInitialized && server ) {
		closesocket ( server->curClient );
		closesocket ( server->skt );
		server->curClient = 0;
		server->skt = 0;
		server->bConnected = false;
		if ( bCleanup ) {
			delete server;
			server = nullptr;
			WSACleanup ( );
		}
	}
}
void SendSyncSignal ( int w, int h ) {
	if ( server ) {
		if ( server->bConnected && server->curClient ) {
			int arr[2] = { w, h };
			send ( server->curClient, (char*)arr, 8, 0 );
		}
	}
}
bool IsServerConnected ( void ) {
	if ( !winsockInitialized )
		return false;
	if ( server->curClient && timeGetTime ( ) - server->timeout > 10000 ) {
		printf ( "Client timed out!\n" );
		KillClient ( );
	}

	return server->bConnected;
}