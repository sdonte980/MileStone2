#ifndef MILESTONE2_MYTESTCLIENTHANDLER_H
#define MILESTONE2_MYTESTCLIENTHANDLER_H

#include "Solver.h"
#include "ClientHandler.h"
#include "FileCacheManager.h"

class MyTestClientHandler : public ClientHandler {
private:
    Solver<string,string>* solver;
    FileCacheManager* cacheManager;
public:
    MyTestClientHandler(Solver<string,string>* solver, FileCacheManager* cacheManager);
    void handleClient(int sockId) override;
};


#endif //MILESTONE2_MYTESTCLIENTHANDLER_H