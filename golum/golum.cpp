
#include <iostream>
#include "golum.h"

using namespace std;

#pragma comment(lib, "ws2_32.lib")

WORD chatServer::WSDLLVERSION = MAKEWORD(2,2);
INT chatServer::MAXCLIENTS = 3;

unsigned int CALLBACK chatServer::clientHandlerCB(void* param) {
    struct clientHandlerData *pData = (struct clientHandlerData*) param;

    if (!(pData->pServer->clientHandlerFunc(pData->client))) {
        delete(pData);
        return 0;
    }

    return 1;
}

unsigned int chatServer::clientHandlerFunc(SOCKET client) {
    //INT clientID = (SOCKET) param;
    //SOCKET client = this->CLIENTS[clientID];

    cout << "clientHandlerFunc called" << endl;

    INT recvBytes, sendBytes;
    INT recvBufLen = 512;
    CHAR recvBuf[512];

#if DEBUG
    sendBytes = send(client, "Hello", 5, 0);
    if (sendBytes < 0) {
        cout << "sendBytes = " << sendBytes << endl;
        cout << "send failed with error: " << WSAGetLastError() << endl;
        closesocket(client);
        WSACleanup();
        return 1;
    }
    else {
        cout "send succeeded" << endl;
    }
#endif /* DEBUG */

    do {
        recvBytes = recv(client, recvBuf, recvBufLen, 0);
        if (recvBytes > 0) {
#if DEBUG
            cout << recvBytes << " bytes of data received" << endl;
#endif /* DEBUG */

            recvBuf[recvBytes] = '\0';

            sendBytes = send(client, recvBuf, recvBytes, 0);
            if (sendBytes < 0) {
                cout << "sendBytes = " << sendBytes << endl;
                cout << "send failed with error: " << WSAGetLastError() << endl;
                closesocket(client);
                WSACleanup();
                return 1;
            }
        }
        else if (recvBytes == 0)
            cout << "Connection closing..." << endl;
        else  {
            cout << "recv failed with error: " << WSAGetLastError() << endl;
            closesocket(client);
            WSACleanup();
            return 1;
        }
    } while(recvBytes > 0);

    return 0;
}

BOOLEAN chatServer::initWS() {
    if (WSAStartup(MAKEWORD(2,2), &this->wsaData) != 0) {
        cout << "WSAStartup failed" << endl;     
        WSACleanup();
        return false;
    }
    return true;
}

chatServer::chatServer(UINT port_no) {
    if (port_no == 0)
        this->srv_port = 8888;
    else
        this->srv_port = port_no;

    this->nClients = 0;

    this->srv_addr.sin_family = AF_INET;
    this->srv_addr.sin_port = htons(srv_port);
    this->srv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
   
    if (!initWS()) return;

    this->SERVER = socket(srv_addr.sin_family, SOCK_STREAM, 0);
    if (this->SERVER == INVALID_SOCKET) {
        cout << "socket failed" << endl;     
        WSACleanup();
        return;
    }

    if (bind(this->SERVER, (SOCKADDR*)&srv_addr, sizeof(srv_addr)) == SOCKET_ERROR) {
        cout << "bind failed" << endl;     
        closesocket(this->SERVER);
        WSACleanup();
        return;
    }

    if (listen(this->SERVER, SOMAXCONN) == SOCKET_ERROR) {
        cout << "listen failed" << endl;     
        closesocket(this->SERVER);
        WSACleanup();
        return;
    }
}

BOOLEAN chatServer::addClient(SOCKET client) {
    HANDLE clientHandler;

    this->CLIENTS.push_back(client);
    ++this->nClients;

    struct clientHandlerData *pData = new(struct clientHandlerData);
    pData->client = client;
    pData->pServer = this;

    clientHandler = (HANDLE) _beginthreadex(NULL, 0, &chatServer::clientHandlerCB, pData, 0, NULL);
    this->CLIENT_HANDLERS.push_back(clientHandler);

    return true;
}

VOID chatServer::Start() {
    SOCKET newClient;
    HANDLE clientHandler;
    while(this->nClients < MAXCLIENTS) {
        newClient = accept(this->SERVER, NULL, NULL);
        if (newClient == INVALID_SOCKET) {
            cout << "accept failed" << endl;     
            closesocket(this->SERVER);
            WSACleanup();
            return;
        }

#if DEBUG
    INT sendBytes = send(newClient, "Hello", 5, 0);
    if (sendBytes < 0) {
        cout << "sendBytes = " << sendBytes << endl;
        cout << "send failed with error: " << WSAGetLastError() << endl;
        closesocket(newClient);
        WSACleanup();
        return;
    }
    else {
        cout << "send succeeded" << endl;
    }
#endif /* DEBUG */

        if (!addClient(newClient)) {
            cout << "addClient failed" << endl;     
            closesocket(newClient);
            closesocket(this->SERVER);
            WSACleanup();
            return;
        }
    }

    return;
}
