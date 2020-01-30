
#ifndef MILESTONE2_MYPARALLELSERVER_H
#define MILESTONE2_MYPARALLELSERVER_H

#include "Server.h"
#include <pthread.h>
#include <vector>
#include <stack>

class MyParallelServer : public server_side::Server {
private:
    struct parameters {
        ClientHandler *clientHandler;
        int sockfd;
    };
    struct parameters *info = new parameters();
    int serverId;
    stack <pthread_t> threads;


public:
    void open(int port, ClientHandler *c) override;

    void stop() override;

    static void *parallelService(void *parameters);

    void start(int server_sock, ClientHandler *ch);

    ~MyParallelServer() override { delete info; }
};


#endif //MILESTONE2_MYPARALLELSERVER_H
