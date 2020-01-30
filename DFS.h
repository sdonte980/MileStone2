
#ifndef MILESTONE2_DFS_H
#define MILESTONE2_DFS_H

#include "Seeker.h"
#include <stack>
using namespace std;

template <class T>
class DFS : public Seeker<T> {
public:
    string search(Seekable<T> *searchable) {
        vector<State<T> *> been;
        stack<State<T> *> stack;
        vector<State<T> *> neighbors;
        State<T> *current;

        stack.push(searchable->getInitState());

        while (!stack.empty()) {
            current = stack.top();
            stack.pop();
            this->numOfNodes++;

            if ((beenIn(been, current)) == 0) {
                been.push_back(current);
            }

            if(current->Equals(searchable->getTargetState())) {
                cout << "The num of nodes is: " << this->numOfNodes << endl;
                this->numOfNodes++;
                return searchable->getPath();
            }

            neighbors = searchable->getNeighbors(current);
            for (State<T> *neighbor : neighbors) {
                if (beenIn(been, neighbor) == 0) {
                    neighbor->setStartPos(current);
                    neighbor->addCost(current->getTCost());
                    stack.push(neighbor);
                }
            }
        }
        return "-1";
    }



    int beenIn(vector<State<T> *> been, State<T> *current ){
        for (auto state:been) {
            if (current->Equals(state)) {
                return 1;
            }
        }
        return 0;
    }
};

#endif //MILESTONE2_DFS_H
