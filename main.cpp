#include "BestFirstSearch.h"
#include "Solver.h"
#include "FileCacheManager.h"
#include "MyClientHandler.h"
#include "SeekerSolver.h"
#include "MyParallelServer.h"
#include "AStar.h"

namespace boot {
    class Main {
    public:
        int main(int argc, char *argv[]) {
            server_side::Server *server = new MyParallelServer();
            Solver<Seekable<Point> *, string> *solver = new SeekerSolver(new AStar<Point>());
            CacheManager *cacheManager = new FileCacheManager();
            ClientHandler *clientHandler = new MyClientHandler(solver, cacheManager);
            server->open(stoi(argv[1]), clientHandler);
            delete server;
            delete solver;
            delete cacheManager;
            delete clientHandler;

            return 0;
        }
    };
}

int main(int argc, char *argv[]) {
    boot::Main mainClass;
    mainClass.main(argc, argv);
    return 0;
}