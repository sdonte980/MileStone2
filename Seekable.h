
#ifndef MILESTONE2_SEEKABLE_H
#define MILESTONE2_SEEKABLE_H

#include "State.h"
#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <bits/stdc++.h>


template<class T>
class Seekable {
protected:
    std::vector<State<T> *> structure;
    State<T> *target;
    State<T> *initState;


public:

    State<T> *getTargetState() { return target; }

    State<T> *getInitState() { return initState; }


    virtual vector<State<T> *> getNeighbors(State<T> *s) = 0;

    string getPath() {
        State<T> *current = getTargetState();
        string path;
        while (current->getComeFrom() != nullptr) {
            for (State<T> *state:structure) {
                if (state->getComeFrom() != nullptr) {
                    if (current->getComeFrom()->Equals(state)) {

                        std::ostringstream strStream;
                        strStream << current->getTCost();
                        std::string str = current->getState().move(state->getState()) + " (" + strStream.str() + ") ,";
                        reverse(str.begin(), str.end());
                        path += str;
                        break;
                    }
                }
            }
            current = current->getComeFrom();
            if (current->getComeFrom()->Equals(getInitState())) {
                break;
            }
        }
        std::ostringstream strStream;
        strStream << current->getTCost();
        std::string str = current->getState().move(getInitState()->getState()) + " (" + strStream.str() + ") ,";
        reverse(str.begin(), str.end());
        path = path + str;
        reverse(path.begin(), path.end());
        return path;
    }

    virtual ~Seekable() = default;
};

#endif //MILESTONE2_SEEKABLE_H