
#ifndef MILESTONE2_MYCLIENTHANDLER_H
#define MILESTONE2_MYCLIENTHANDLER_H

#include "ClientHandler.h"
#include "CacheManager.h"
#include "Seekable.h"
#include "Solver.h"
#include "Point.h"

class MyClientHandler : public ClientHandler{
private:
    Solver<Seekable<Point>*,string>* solver;
    CacheManager* cacheManager;
public:
    MyClientHandler(Solver<Seekable<Point>*,string>* solver, CacheManager* cacheManager);
    void handleClient(int socketId) override;
    Seekable<Point>* makeMatrix(vector<string> tempProblem);
};


#endif //MILESTONE2_MYCLIENTHANDLER_H
