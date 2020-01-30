
#ifndef MILESTONE2_SEEKER_H
#define MILESTONE2_SEEKER_H

#include "Seekable.h"
#include <string>

template<class T>
class Seeker {
protected:
    Seekable<T> *searchable;
    int numOfNodes = 0;

public:
    virtual string search(Seekable<T> *searchable) = 0;

    virtual int getNumOfNodesEvaluated() { return numOfNodes; }

    double getTrailCost() {
        return searchable->getTargetState()->getTCost();
    }

    virtual ~Seeker() { delete searchable; }

};

#endif //MILESTONE2_SEEKER_H
