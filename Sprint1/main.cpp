#include <iostream>
#include <limits>
#include "Point.h"
#include "Triangle.h"

using namespace std;

int main() {
    Point *p1 = new Point(5, 5, 0);
    Point *p2 = new Point(3, 1, 1);
    Point *p3 = new Point(1, 4, 4);

    Triangle triangle(p1, p2, p3);

    int choice;
    char axis;

    while (true) {
        cout << "\n\n";
        cout << "Menu:\n";
        cout << "1. Display triangle coordinates\n";
        cout << "2. Translate triangle\n";
        cout << "3. Calculate triangle area\n";
        cout << "4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "\n\n";

        switch (choice) {
            case 1:
                triangle.display();
                break;
            case 2: {
                string d_str;
                cout << "Enter distance to translate: ";
                cin >> d_str;
                cout << "Enter axis (x, y, or z): ";
                cin >> axis;
                int result = triangle.translate(d_str, axis);
                break;
            }
            case 3:
                cout << "Area of the triangle: " << triangle.calcArea() << "\n";
                break;
            case 4:
                delete p1;
                delete p2;
                delete p3;
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
