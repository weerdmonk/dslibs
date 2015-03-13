
#pragma once

#include <winsock2.h>
#include <windows.h>
#include <process.h>
#include <vector>

class chatServer {
private:
    static WORD WSDLLVERSION;
    static INT  MAXCLIENTS;

    WSADATA                     wsaData;
    sockaddr_in                 srv_addr;
    SOCKET                      SERVER;
    std::vector<SOCKET>              CLIENTS;
    std::vector<HANDLE>              CLIENT_HANDLERS;
    UINT                        srv_port;
    INT                         nClients;

    /* private methods*/
    BOOLEAN initWS();
    BOOLEAN addClient(SOCKET client);
    
    /* private callbacks*/
    unsigned int chatServer::clientHandlerFunc(SOCKET client);

    static unsigned int CALLBACK clientHandlerCB(void *param);

public:
    inline VOID setWsaVersion(WORD version) {
        this->WSDLLVERSION = version;
    }

    inline VOID setMaxClients(INT maxClients) {
        this->MAXCLIENTS = maxClients;
    }

    chatServer(UINT port_no);
    ~chatServer();

    VOID Start();
};

struct clientHandlerData {
    SOCKET client;
    chatServer *pServer;
};

