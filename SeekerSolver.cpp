
#include "SeekerSolver.h"

string SeekerSolver::solve(Seekable<Point>* p) {
    return seeker->search(p);
}