#include "Point.h"
#include <iostream>
#include <cctype>

using namespace std;

Point::Point(int x, int y, int z) : x(x), y(y), z(z) {}

Point::~Point() {}

bool Point::isValidInteger(const string& str) {
    if (str.empty() || ((!isdigit(str[0])) && (str[0] != '-') && (str[0] != '+'))) return false;

    char * p;
    strtol(str.c_str(), &p, 10);

    return (*p == 0);
}

int Point::translate(const string& d_str, char axis) {
    // Check if d_str is a valid integer
    if (!isValidInteger(d_str)) {
        
        cout << "Invalid distance input.\n";
                
        return -2;
    }

    int d = stoi(d_str);

    // Check if axis is valid
    if (axis != 'x' && axis != 'y' && axis != 'z') {
        
        cout << "Invalid axis input.\n";
                
        return -1;
    }

    // Perform translation
    switch (axis) {
        case 'x':
            x += d;
            break;
        case 'y':
            y += d;
            break;
        case 'z':
            z += d;
            break;
    }
    
    return 0;
}

void Point::display() const {
    cout << "(" << x << ", " << y << ", " << z << ")";
}
