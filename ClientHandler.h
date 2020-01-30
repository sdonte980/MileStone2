#ifndef MILESTONE2_CLIENTHANDLER_H
#define MILESTONE2_CLIENTHANDLER_H


using namespace std;
class ClientHandler {

public:
    virtual void handleClient(int socketId) = 0;
    virtual ~ClientHandler() = default;

};
#endif //MILESTONE2_CLIENTHANDLER_H