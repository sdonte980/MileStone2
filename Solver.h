
#ifndef MILESTONE2_SOLVER_H
#define MILESTONE2_SOLVER_H

template <class P, class S>
class Solver {
public:
virtual S solve(P problem) = 0;
virtual ~Solver() = default;
};

#endif //MILESTONE2_SOLVER_H
