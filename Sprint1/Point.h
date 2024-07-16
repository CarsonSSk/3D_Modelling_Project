#ifndef POINT_H
#define POINT_H

#include <string>

class Point {
public:
    int x, y, z;

    Point(int x = 0, int y = 0, int z = 0);

    ~Point();

    int translate(const std::string& d_str, char axis);

    void display() const;

private:
    bool isValidInteger(const std::string& str);
};

#endif // POINT_H
