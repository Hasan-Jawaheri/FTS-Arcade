import socket

clientsocket = socket.socket ( socket.AF_INET, socket.SOCK_STREAM )
clientsocket.connect (("localhost", 5730))
clientsocket.send ( "FUCKKK" )