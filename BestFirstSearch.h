
#ifndef MILESTONE2_BESTFIRSTSEARCH_H
#define MILESTONE2_BESTFIRSTSEARCH_H


#include "Seeker.h"
#include "Point.h"
#include <iostream>
#include <queue>
#include <stack>
#include <algorithm>

template<class T>
class BestFirstSearch : public Seeker<T> {
    class Cmp {
    public:
        bool operator()(State<T>* left, State<T>* right) {
            return (left->getTCost()) > (right->getTCost());
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

        while (!(open.empty())) {
            current = open.top();
            open.pop();
            closed.push_back(current);
            this->numOfNodes++;
            if (current->Equals(searchable->getTargetState())) {
                cout << "the num of nodes is: " << this->numOfNodes << endl;
                this->numOfNodes++;
                return searchable->getPath();
            }
            neighbors = searchable->getNeighbors(current);
            for (State<T> *neighbor : neighbors) {
                if (!inOpen(open, neighbor) && !inClosed(closed, neighbor)) {
                    neighbor->setStartPos(current);
                    neighbor->addCost(current->getTCost());
                    open.push(neighbor);
                    continue;
                }else if (inClosed(closed, neighbor)){
                    continue;
                }
                else if (current->getTCost() + neighbor->getCost() < neighbor->getTCost()) {
                    neighbor->setTrailCost(current->getTCost() + neighbor->getCost());
                    neighbor->setStartPos(current);
                    open = updatePriorityQ(open);
                }
            }
        }
        searchable->getTargetState()->setTrailCost(-1);
        return to_string(-1);
    }

    bool inOpen(priority_queue<State<T> *, vector<State<T> *>, Cmp> p, State<T> *current) {
        while (!p.empty()) {
            if (current->Equals(p.top())) { return true; }
            p.pop();
        }
        return false;
    }

    bool inClosed(vector<State<T>*> closed, State<T>* current) {
        for (auto state:closed) {
            if (current->Equals(state)) {
                return true;
            }
        }
        return false;
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

};

#endif //MILESTONE2_BESTFIRSTSEARCH_H




