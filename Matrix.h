
#ifndef MILESTONE2_MATRIX_H
#define MILESTONE2_MATRIX_H

#include "Point.h"
#include "Seekable.h"


class Matrix : public Seekable<Point>{

public:
    Matrix(std::vector<State<Point>*> structure, State<Point>* initState, State<Point>* target);
    vector<State<Point>*> getNeighbors(State<Point>* s) override;
    ~Matrix() override;
};


#endif //MILESTONE2_MATRIX_H
