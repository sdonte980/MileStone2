#include "FileCacheManager.h"
#include "Split.h"
#include <iostream>
#include <fstream>
#include <cstring>

FileCacheManager::FileCacheManager() {
    pthread_mutex_init(&mutex, nullptr);
    loadDataMap();
}

string FileCacheManager::getSolution(string problem) {
    pthread_mutex_lock(&mutex);
    string solution = data.find(problem)->second;
    pthread_mutex_unlock(&mutex);
    return solution;
}

int FileCacheManager::hasSolution(string problem) {
    pthread_mutex_lock(&mutex);
    for (auto pair: data) {
        if (pair.first == problem) {
            pthread_mutex_unlock(&mutex);
            return 1;
        }
    }
    pthread_mutex_unlock(&mutex);
    return 0;
}

void FileCacheManager::loadDataMap() {
    string buffer, p, s;
    int inSolutions = 0;
    ifstream fileSolutions;
    fileSolutions.open("solutions.txt", ifstream::in | istream::app);
    if (!fileSolutions) {
        throw "Failed to open file";
    }
    while (getline(fileSolutions, buffer)) {
        while (strcmp(buffer.c_str(), "$$") != 0) {
            if (strcmp(buffer.c_str(), "$") == 0) {
                inSolutions = 1;
            } else if (inSolutions == 0) {
                p = p + buffer;
            } else {
                s = s + buffer;
            }
            getline(fileSolutions, buffer);
        }
        pthread_mutex_lock(&mutex);
        data.insert(pair<string, string>(p, s));
        pthread_mutex_unlock(&mutex);
        inSolutions = 0;
        p = "";
        s = "";
    }
    fileSolutions.close();

}


void FileCacheManager::updateData(string problem, string solution) {
    pthread_mutex_lock(&mutex);
    data.insert(pair<string, string>(problem, solution));
    pthread_mutex_unlock(&mutex);
}

void FileCacheManager::saveToDisk(string problem, string solution) {
    ofstream fileSolution;
    fileSolution.open("solutions.txt", ofstream::out | ostream::app);
    if (!fileSolution) {
        throw "failed to open file";
    }
    fileSolution << problem << endl;
    fileSolution << "$" << endl;
    fileSolution << solution << endl;
    fileSolution << "$$" << endl;

    fileSolution.close();
}