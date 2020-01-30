
#ifndef MILESTONE2_STRINGREVERSER_H
#define MILESTONE2_STRINGREVERSER_H

#include "Solver.h"
#include <string>


using namespace std;

class StringReverser : public Solver<string,string>{
public:
    string solve(string problem) override;
};


#endif //MILESTONE2_STRINGREVERSER_H
