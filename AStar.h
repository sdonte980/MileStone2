
#ifndef MILESTONE2_ASTAR_H
#define MILESTONE2_ASTAR_H

#include "Seeker.h"
#include "Point.h"
#include <cstring>
#include <cfloat>
#include <stack>
#include <set>
#include <queue>


using namespace std;

template<class T>

class AStar : public Seeker<T> {
    class Cmp {
    public:
        int operator()(State<T>* left, State<T>* right) {
            return (left->getFHeuristics()) > (right->getFHeuristics());
        }
    };

public:
    string search(Seekable<T>* searchable) override {
        this->searchable = searchable;
        State<T> *current;
        vector<State<T> *> neighbors;
        priority_queue<State<T>*, vector<State<T>*>, Cmp> open;
        open.push(searchable->getInitState());
        vector<State<T> *> closed;

        while (!open.empty()) {
            current = open.top();
            open.pop();
            this->numOfNodes++;
            closed.push_back(current);
            if (current->Equals(searchable->getTargetState())) {
                this->numOfNodes++;
                return searchable->getPath();
            }
            neighbors = searchable->getNeighbors(current);
            for (State<T> *neighbor : neighbors) {
                if (!inOpen(open, neighbor) && !inClosed(closed, neighbor)) {
                    neighbor->setStartPos(current);
                    neighbor->addCost(current->getTCost());
                    neighbor->setFHeuristics(calculateF(neighbor, searchable->getTargetState()));
                    open.push(neighbor);
                    continue;
                } else if (inClosed(closed, neighbor)){
                    continue;
                }
                else if (current->getTCost() + neighbor->getCost() < neighbor->getTCost()) {
                    neighbor->setTrailCost(current->getTCost() + neighbor->getCost());
                    neighbor->setFHeuristics(calculateF(neighbor, searchable->getTargetState()));
                    neighbor->setStartPos(current);
                    open = updatePriorityQ(open);
                }
            }
        }
        searchable->getTargetState()->setTrailCost(-1);
        return "-1";
    }

    int inOpen(priority_queue<State<T> *, vector<State<T> *>, Cmp> p, State<T> *current) {
        while (!p.empty()) {
            if (current->Equals(p.top())) { return 1; }
            p.pop();
        }
        return 0;
    }

    int inClosed(vector<State<T>*> closed, State<T>* current) {
        for (auto state:closed) {
            if (current->Equals(state)) {
                return 1;
            }
        }
        return 0;
    }

    priority_queue<State<T>*, vector<State<T> *>, Cmp> updatePriorityQ(priority_queue<State<T> *,
            vector<State<T> *>, Cmp> p ){
        priority_queue<State<T> *, vector<State<T> *>, Cmp> newQ;
        while (!p.empty()) {
            newQ.push(p.top());
            p.pop();
        }
        return newQ;
    }

    double calculateF(State<T>* state,State<T>* target) {

        double h = abs(state->getState().getX() - target->getState().getX()) +
                   abs(state->getState().getY() - target->getState().getY());
        double g = state->getTCost();
        return g + h;
    }





};

#endif //MILESTONE2_ASTAR_H
