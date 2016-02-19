#include "stdafx.h"
#include "dostackbufferoverflowgood.h"

#define LHOST NULL		// 0.0.0.0
#define LPORT "31337"	// hack the planet
#define RECVBUFSIZE 58623	// causes "JMP ESP" opcodes to be compiled in during
						// handleConnection()'s "SUB ESP,n"

int __cdecl main()
{
	// [+] socket setup
	// borrowed from MSDN - https://msdn.microsoft.com/en-us/library/windows/desktop/ms738545%28v=vs.85%29.aspx

	// Initialize Winsock
	WSADATA wsaData = { 0 };
	int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (result != 0) {
		printf("WSAStartup failed: %d\n", result);
		return -1;
	}

	struct addrinfo hints = { 0 };
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the local address and port to be used by the server
	struct addrinfo *ainfo;
	result = getaddrinfo(LHOST, LPORT, &hints, &ainfo);
	if (result != 0) {
		printf("getaddrinfo failed: %d\n", result);
		WSACleanup();
		return -1;
	}

	// Create a SOCKET for the server to listen for client connections
	SOCKET listenSocket;
	if ((listenSocket = socket(ainfo->ai_family, ainfo->ai_socktype, ainfo->ai_protocol)) == INVALID_SOCKET) {
		printf("socket() failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(ainfo);
		WSACleanup();
		return -1;
	}

	// Setup the TCP listening socket
	if ((bind(listenSocket, ainfo->ai_addr, (int)ainfo->ai_addrlen)) == SOCKET_ERROR) {
		printf("bind() failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(ainfo);
		closesocket(listenSocket);
		WSACleanup();
		return -1;
	}
	freeaddrinfo(ainfo);

	// Listen on the socket
	if (listen(listenSocket, SOMAXCONN) == SOCKET_ERROR) {
		printf("listen() failed with error: %ld\n", WSAGetLastError());
		closesocket(listenSocket);
		WSACleanup();
		return -1;
	}

	printf("[+] Listening for connections.\n");
	
	// [+] handle connections
	// borrowed from http://stackoverflow.com/a/15185627
	while (1) {
		// Accept a connection
		SOCKET clientSocket;
		if ((clientSocket = accept(listenSocket, NULL, NULL)) == INVALID_SOCKET) {
			printf("accept failed: %d\n", WSAGetLastError());
			continue;
		}
		printf("Received connection from remote host.\n");

		// Create thread to handle connection
		_beginthread(&handleConnection, 0, (void*)clientSocket);
		printf("Connection handed off to handler thread.\n");
	}
}

void __cdecl handleConnection(void *param) {
	SOCKET clientSocket = (SOCKET)param;

	// Receive until the peer shuts down the connection
	// recv spooling borrowed from http://stackoverflow.com/a/6090610
	// in a loop, we recv() off the network, handle complete lines, then shift the remainder down
	char recvbuf[RECVBUFSIZE] = { '\0' };
	size_t recvbufUsed = 0;
	const char* msgPleaseSendShorterLines = "Please send shorter lines.";
	const char* msgBye = "Bye!";
	while (1) {
		// establish how much room we have left in recvbuf
		size_t buf_remain = sizeof(recvbuf) - recvbufUsed;

		// check that we still have room for another recv
		if (buf_remain < 1) {
			printf("[!] recvbuf exhausted. Giving up.\n");
			send(clientSocket, msgPleaseSendShorterLines, strlen(msgPleaseSendShorterLines), 0);
			break;
		}

		// recv() up to buf_remain bytes, put them after pending data in recvbuf
		int result = recv(clientSocket, (void*)&recvbuf[recvbufUsed], buf_remain, 0);

		if (result == 0) {
			printf("Client disconnected.\n");
			break;
		}
		else if (result < 0) {
			printf("recv() failed: %d.\n", WSAGetLastError());
			break;
		}

		printf("Bytes received: %d\n", result);

		// we're now using more of recvbuf than we were before
		recvbufUsed += result;

		// starting at recvbuf[0] look for newlines, pass each found line off to doResponse()
		char *line_start = recvbuf;
		char *line_end;
		while ((line_end = (char*)memchr((void*)line_start, '\n', recvbufUsed - (line_start - recvbuf))) != 0)
		{
			// we found a line

			// null-terminate it
			*line_end = '\0';

			// if the user is done with us, disconnect them
			if (strcmp(line_start, "exit") == 0) {
				printf("Client requested exit.\n");
				send(clientSocket, msgBye, strlen(msgBye), 0);
				closesocket(clientSocket);
				return;
			}

			// process the line
			doResponse(clientSocket, line_start);

			// continue looking for lines from after the now-processed line
			line_start = line_end + 1;
		}
		
		// having (perhaps) processed some data we are (perhaps) using less of recvbuf than we were before
		recvbufUsed -= (line_start - recvbuf);

		// slide unprocessed data down to start of recvbuf
		memmove_s(recvbuf, sizeof(recvbuf), line_start, recvbufUsed);
	}
	closesocket(clientSocket);
	return;
}

int __cdecl doResponse(SOCKET clientSocket, char *clientName) {
	char response[128];

	// Build response
	sprintf(response, "Hello %s!!!\n", clientName);

	// Send response to the client
	int result = send(clientSocket, response, strlen(response), 0);
	if (result == SOCKET_ERROR) {
		printf("send failed: %d\n", WSAGetLastError());
		closesocket(clientSocket);
		return -1;
	}
	printf("Bytes sent: %d\n", result);
	return 0;
}