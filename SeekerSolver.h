
#ifndef MILESTONE2_SEEKERSOLVER_H
#define MILESTONE2_SEEKERSOLVER_H

#include "Solver.h"
#include "Point.h"
#include "Seeker.h"



class SeekerSolver : public Solver<Seekable<Point>*,string>{
private:
    Seeker<Point>* seeker;
public:
    SeekerSolver(Seeker<Point>* seeker): seeker(seeker) {}
    string solve(Seekable<Point>* p) override;
    ~SeekerSolver()override{ delete seeker;}
};


#endif //MILESTONE2_SEEKERSOLVER_H
