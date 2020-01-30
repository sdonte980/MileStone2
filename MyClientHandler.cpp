
#include "MyClientHandler.h"
#include "Split.h"
#include "Matrix.h"
#include <string>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>


MyClientHandler::MyClientHandler(Solver<Seekable<Point> *, string> *solver, CacheManager *cacheManager) {
    this->solver = solver;
    this->cacheManager = cacheManager;
}

void MyClientHandler::handleClient(int socketId) {
    string problem;
    vector<string> tempProblem;
    char buffer[256];
    string solution;
    ssize_t n;
    char *ch;

    if (socketId < 0) {
        perror("Error on accepting");
        exit(1);
    }

    while (true) {
        bzero(buffer, 256);
        string line;
        int numberBytesReader = read(socketId, buffer, 255);
        numberBytesReader++;
        string b;
        b = buffer;
        b = b + "\n";
        if (numberBytesReader != 0) {
            for (int i = 0; i < numberBytesReader; i++) {
                char c;
                c = b[i];
                if (c == '\n') {
                    if (line.length() > 0) {
                        if (line == "end") {
                            Seekable<Point> *matrix = makeMatrix(tempProblem);
                            if (this->cacheManager->hasSolution(problem)) {
                                solution = this->cacheManager->getSolution(problem);
                            } else {
                                solution = solver->solve(matrix);
                                cacheManager->updateData(problem, solution);
                                cacheManager->saveToDisk(problem, solution);
                            }
                            ch = const_cast<char *>(solution.c_str());
                            n = write(socketId, ch, strlen(ch));

                            if (n < 0) {
                                perror("Error writing to socket");
                                exit(1);
                            }
                            return;
                        }
                        tempProblem.emplace_back(line);
                        problem = problem + line;
                        line = "";
                    }
                } else {
                    line = line + c;
                }
            }
        } else {
            printf("Socket error or Socket closed!\n");
            return;
        }

    }
}

Seekable<Point> *MyClientHandler::makeMatrix(vector<string> tempProblem) {
    vector<State<Point> *> searchable;
    vector<string> sliced;

    sliced = Split::split(tempProblem[tempProblem.size() - 2], ",");
    State<Point> *initState = new State<Point>(Point(stoi(sliced[0]), stoi(sliced[1])), 0);
    sliced = Split::split(tempProblem[tempProblem.size() - 1], ",");
    State<Point> *targetState = new State<Point>(Point(stoi(sliced[0]), stoi(sliced[1])), 0);

    long row = tempProblem.size() - 2;
    long column = Split::split(tempProblem[0], ",").size();

    for (int i = 0; i < row; i++) {
        sliced = Split::split(tempProblem[i], ",");
        for (int j = 0; j < column; j++) {
            if (i == initState->getState().getX() && j == initState->getState().getY()) {
                initState->setCost(stod(sliced[j]));
                searchable.push_back(initState);
            } else if (i == targetState->getState().getX() && j == targetState->getState().getY()) {
                targetState->setCost(stod(sliced[j]));
                searchable.push_back(targetState);
            } else {
                searchable.push_back(new State<Point>(Point(i, j), stoi(sliced[j])));
            }
        }
    }
    Seekable<Point> *matrix = new Matrix(searchable, initState, targetState);
    return matrix;
}

