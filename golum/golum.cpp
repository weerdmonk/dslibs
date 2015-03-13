
#include <iostream>
#include "chatServer.h"

using namespace std;

chatServer::WSDLLVERSION = MAKEWORD(2,2);
chatServer::MAXCLIENTS = 3;

UINT CALLBACK chatServer::clientHandler(LPVOID param) {
    INT client = (SOCKET) param;

    

    return 0;
}

BOOLEAN chatServer::initi_ws() {
    if (!WSAStartup(WSDLLVERSION, &this->wsaData) {
        WSACleanup;
        return false;
    }
    return true;
}

chatServer::chatServer(UINT port_no) {
    if (port_no == 0)
        this->srv_port = 8888;
    else
        this->srv_port = port_no;

    INT iRet;

    srv_addr.sin_family = AF_INET;
    srv_addr.sin_port = htons(srv_port);
    srv_addr.in.sin_addr.s_addr = INADRR_ANY;
   
    if (!init()) return;

    this->server = socket(srv_addr.sin_family, SOCK_STREAM, 0);
    if (this->server == INVALID_SOCKET) {
         WSACleanup();
         return;
    }

    if (bind(this->server, (SOCKADDR*)&srv_addr, sizeof(srv_addr)) == SOCKET_ERROR)
        closesocket(this->server);
        WSACleanup();
        return;
    }

    if (listen(this->server, SOMAXCONN) == SOCKET_ERROR) {
        closesocket(this->server);
        WSACleanup();
        return;
    }
}

BOOLEAN chatServer::addClient(SOCKET client) {
    HANDLE clientHandler;

    this->CLIENTS.push_back(client);
    ++this->nClients;

    clientHandler = (HANDLE) _beginthreadex(NULL, 0, this->clientHandlerCB, nClients, 0, NULL);
    this->CLIENT_HANDLERS.push_back(clientHandler);

    return true;
}

VOID chatServer::Start() {
    SOCKET newClient;
    HANDLE clientHandler;
    while(nClients < MAXCLIENTS) {
        if (newClient= accept(this->server, NULL, NULL) == INVALID_SOCKET) {
            closesocket(this->server);
            WSACleanup();
            return;
        }

        if (!addClient(newClient)) {
            closesocket(newClient);
            closesocket(this->server);
            WSACleanup();
            return;
        }
    }

    return true;
}
