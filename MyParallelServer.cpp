#include "MyParallelServer.h"
#include <sys/socket.h>
#include <netinet/in.h>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <stack>

struct thread_data {
    int sockt;
    ClientHandler *ch;
};

void MyParallelServer::open(int port, ClientHandler *clientHandler) {
    info->sockfd = port;
    info->clientHandler = clientHandler;
    int server_fd;
    struct sockaddr_in address{};
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(port);

    int n = 1;
    setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &n, sizeof(4));
    if (bind(server_fd, (struct sockaddr *) &address, sizeof(address)) == -1) {
        perror("socket binded");
        exit(1);
    }
// 5
    if (listen(server_fd, 10) == -1) {
        perror("socket listening");
        exit(1);
    }

    start(server_fd, clientHandler);
}

void *start_thread_client(void *parameters) {
    auto data = (thread_data *) parameters;
    data->ch->handleClient(data->sockt);
    delete data;
}

void MyParallelServer::start(int server_sock, ClientHandler *ch) {
    stack<pthread_t> threads_stack;
    sockaddr_in address{};
    int addressLength = sizeof(address);
    timeval timeout;
    int new_socket;
    while (true) {
        new_socket = accept(server_sock, (struct sockaddr *) &address, (socklen_t *) &addressLength);
        timeout.tv_sec = 10;
        timeout.tv_usec = 0;
        setsockopt(server_sock, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
        if (new_socket < 0) {
            if (errno == EWOULDBLOCK || errno == EAGAIN) {
                cout << "timeout" << endl;
                stop();
                break;
            }
            perror("accept");
            exit(EXIT_FAILURE);
        }
        setsockopt(new_socket, SOL_SOCKET, SO_RCVTIMEO, (char *) &timeout, sizeof(timeout));
        auto data = new thread_data;
        data->ch = ch;
        data->sockt = new_socket;
        pthread_t tr;
        if (pthread_create(&tr, nullptr, start_thread_client, data) < 0) {
            perror("error creating thread");
            exit(1);
        }
        threads_stack.push(tr);
    }
}

void MyParallelServer::stop() {
    while (!threads.empty()) {
        pthread_join(threads.top(), nullptr);
        threads.pop();
    }
}