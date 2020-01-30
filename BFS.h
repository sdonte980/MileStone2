
#ifndef MILESTONE2_BFS_H
#define MILESTONE2_BFS_H

#include "Seeker.h"
#include <algorithm>
#include <queue>
#include <list>


template<class T>
class BFS : public Seeker<T> {
public:
    string search(Seekable<T> *searchable) {
        vector<State<T> *> been;
        queue<State<T>*> queue;
        vector<State<T> *> neighbors;
        State<T> *current;
        
        queue.push(searchable->getInitState());
        been.push_back(searchable->getInitState());

        while (!(queue.empty())) {
            
            current = queue.front();
            
            if(current->Equals(searchable->getTargetState())){
                cout << "the num of nodes is: " << this->numOfNodes << endl;
                this->numOfNodes++;
                return searchable->getPath();
            }
            neighbors = searchable->getNeighbors(current);
            queue.pop();
            this->numOfNodes++;

            for (State<T> *neighbor : neighbors) {
                if (!(beenIn(been, neighbor))) {
                    neighbor->setStartPos(current);
                    neighbor->addCost(current->getTCost());
                    been.push_back(neighbor);
                    queue.push(neighbor);
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

#endif //MILESTONE2_BFS_H
