#include "UniquePtr.h"
#include <iostream>

// created a simple Point class to test
struct Point {
    int x,y;
    Point(int x, int y): x(x), y(y) {}
};

int main() {
    // UniquePtr<int> ptr(new int(5));
    // they test all methods here...
    UniquePtr<Point> p (new Point(3,4));
    std::cout << "p = (" << p->x << ", " << p->y << ")\n";
    
    // Move constructor test
    UniquePtr<Point> p2 = std::move(p);
    std::cout << "p is now empty: " << (!p) << "\n";
    std::cout << "p2 = (" << p2->x << ", " << p2->y << ")\n";

    //release / reset
    p2.reset(new Point(1,2));
    std::cout << "p2 after reset = (" << p2->x << ", " << p2->y << ")\n";

    // makeUnique
    UniquePtr<Point> p3 = makeUnique<Point>(7,8);
    std::cout << "p3 = (" << p3->x << ", " << p3->y << ")\n";

    return 0;
}
