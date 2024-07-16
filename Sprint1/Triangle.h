#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Point.h"
#include <string>

class Triangle {
public:
    Point *vertex_1, *vertex_2, *vertex_3;

    Triangle(Point* v1, Point* v2, Point* v3);

    Triangle();

    ~Triangle();

    int translate(const std::string& d_str, char axis);

    double calcArea() const;

    void display() const;
};

#endif // TRIANGLE_H
