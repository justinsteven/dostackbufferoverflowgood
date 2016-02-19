#pragma once

void __cdecl handleConnection(void *param);
int __cdecl doResponse(SOCKET clientSocket, char *clientName);
int __cdecl main();