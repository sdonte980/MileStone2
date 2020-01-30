#include "MySerialServer.h"
#include <thread>


void MySerialServer::open(int port, ClientHandler* c) {
    int sockfd, port_no;

    struct sockaddr_in serv_addr;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0) {
        perror("Error opening socket");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));
    port_no = port;

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port_no);

    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("Error binding");
        exit(1);
    }

    thread t(serialService, sockfd,c);
    t.detach();
}

void MySerialServer::serialService(int sockfd, ClientHandler* c) {
    int newSockfd, clientLength;
    struct sockaddr_in client_addr;

    while (true) {
        listen(sockfd, SOMAXCONN);
        clientLength = sizeof(client_addr);
        newSockfd = accept(sockfd, (struct sockaddr *) &client_addr, (socklen_t *) &clientLength);
        c->handleClient(newSockfd);
    }
}

void MySerialServer::stop() {

}