
#ifndef MILESTONE2_STATE_H
#define MILESTONE2_STATE_H

#include <vector>
#include <cfloat>

using namespace std;

template<class T>
class State {
private:
    T state;
    double fHeuristics;
    State<T> *comeFrom;
    double cost;
    double trailCost;




public:

    State<T>(T state, double cost) : state(state), cost(cost), trailCost(cost), comeFrom(nullptr), fHeuristics(FLT_MAX) {}

    double getCost() const { return cost; }

    double getTCost() { return trailCost; }

    bool Equals(State<T> *s) { return this->state == s->state; }

    void setStartPos(State<T> *comeFrom) { this->comeFrom = comeFrom; }

    void setTrailCost(double cost) { this->trailCost = cost; }

    void addCost(double c) { trailCost = trailCost + c; }

    T getState() { return state; }

    void setCost(double cost) {
        this->cost = cost;
        this->trailCost = cost;
    }

    State<T>* getComeFrom() { return comeFrom; }
    double getFHeuristics(){
        return fHeuristics;
    }
    void setFHeuristics(double f){
        this->fHeuristics = f;
    }

};


#endif //MILESTONE2_STATE_H