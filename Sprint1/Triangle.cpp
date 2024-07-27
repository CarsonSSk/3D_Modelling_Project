#include "Triangle.h"
#include <iostream>
#include <cmath>

Triangle::Triangle(Point* v1, Point* v2, Point* v3)
    : vertex_1(v1), vertex_2(v2), vertex_3(v3) {}

Triangle::Triangle() : vertex_1(nullptr), vertex_2(nullptr), vertex_3(nullptr) {}

Triangle::~Triangle() {
    delete vertex_1;
    delete vertex_2;
    delete vertex_3;
}

int Triangle::translate(const std::string& d_str, char axis) {
    int result;
    result = vertex_1->translate(d_str, axis);
    if (result != 0) return result;
    result = vertex_2->translate(d_str, axis);
    if (result != 0) return result;
    result = vertex_3->translate(d_str, axis);
    return result;
}

double Triangle::calcArea() const {
    // Calculate the vectors AB and AC
    double AB_x = vertex_2->x - vertex_1->x;
    double AB_y = vertex_2->y - vertex_1->y;
    double AB_z = vertex_2->z - vertex_1->z;

    double AC_x = vertex_3->x - vertex_1->x;
    double AC_y = vertex_3->y - vertex_1->y;
    double AC_z = vertex_3->z - vertex_1->z;

    // Calculate the cross product AB x AC
    double cross_x = AB_y * AC_z - AB_z * AC_y;
    double cross_y = AB_z * AC_x - AB_x * AC_z;
    double cross_z = AB_x * AC_y - AB_y * AC_x;

    // Calculate the magnitude of the cross product
    double cross_mag = sqrt(cross_x * cross_x + cross_y * cross_y + cross_z * cross_z);

    

    // The area of the triangle is half the magnitude of the cross product
    return 0.5 * cross_mag;
}

void Triangle::display() const {
    std::cout << "Triangle vertices:\n";
    vertex_1->display();
    std::cout << "\n";
    vertex_2->display();
    std::cout << "\n";
    vertex_3->display();
    std::cout << "\n";
}
