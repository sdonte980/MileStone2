#ifndef MILESTONE2_MYSERIALSERVER_H
#define MILESTONE2_MYSERIALSERVER_H

#include "ClientHandler.h"
#include "Server.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <netdb.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>


class MySerialServer : public server_side::Server {
public:
    void open(int port, ClientHandler *c) override;

    void stop() override;

    static void serialService(int sockfd, ClientHandler *c);

};


#endif //MILESTONE2_MYSERIALSERVER_H