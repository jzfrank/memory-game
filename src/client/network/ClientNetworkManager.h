//
// Created by Jin on 5/14/22.
//

#ifndef MEMORY_GAME_CLIENTNETWORKMANAGER_H
#define MEMORY_GAME_CLIENTNETWORKMANAGER_H

#include <string>
#include "ResponseListenerThread.h"
#include "../../common/network/requests/client_request.h"

class ClientNetworkManager {

public:
    static void init(const std::string& host, const uint16_t port);

    static void sendRequest(const client_request& request);

    static void parseResponse(const std::string& message);

private:
    static bool connect(const std::string& host, const uint16_t port);


    static sockpp::tcp_connector* _connection;

    static bool _connectionSuccess;
    static bool _failedToConnect;

};

#endif //MEMORY_GAME_CLIENTNETWORKMANAGER_H

