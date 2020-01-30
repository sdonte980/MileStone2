
#ifndef MILESTONE2_POINT_H
#define MILESTONE2_POINT_H

#include <iostream>
using namespace std;

class Point {
private:

    int x;
    int y;
public:
    Point(int x, int y);
    int getX() const;
    int getY() const;
    bool operator==(Point other);
    bool isLeftNeighbor(Point other);
    bool isRightNeighbor(Point other);
    bool isUpNeighbor(Point other);
    bool isDownNeighbor(Point other);
    string move(Point other);
};


#endif //MILESTONE2_POINT_H
