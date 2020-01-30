#include "MyTestClientHandler.h"
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <strings.h>
#include <unistd.h>
#include <iostream>



MyTestClientHandler::MyTestClientHandler(Solver<string,string>* solver,FileCacheManager* fileCacheManager) {
    this->solver = solver;
    this->cacheManager = fileCacheManager;
}

void MyTestClientHandler::handleClient(int sockId) {
    char problem[256];
    string solution;
    ssize_t n;
    char* ch;
    if (sockId < 0) {
        perror("error accepting");
        exit(1);
    }

    while (true) {
        bzero(problem, 256);
        n = read(sockId, problem, 255);

        if (n < 0) {
            perror("Error reading from socket");
            exit(1);
        }

        if (strcmp(problem, "end") == 0) {
            return;
        }

        printf("Here's the message: %s\n", problem);

        if (this->cacheManager->hasSolution(problem)) {
            solution = this->cacheManager->getSolution(problem);
        } else {
            solution = solver->solve(problem);
            cacheManager->updateData(problem, solution);
            cacheManager->saveToDisk(problem, solution);
        }
        ch = const_cast<char *>(solution.c_str());
        n = write(sockId, ch, strlen(ch));
        cout<<solution<<endl;

        if (n < 0) {
            perror("Error writing to socket");
            exit(1);
        }
    }
}