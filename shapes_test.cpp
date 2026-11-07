#include <iostream>
#include <cmath>
#include <memory>
#include <vector>
#include <cassert>
#include "shapes.h"

// Doubles can have tiny rounding errors, so compare with a tolerance instead of ==
bool near(double a, double b)
{
    return std::abs(a - b) < 1e-9;
}

constexpr double PI = 3.14159265358979323846;

int main()
{
    // Each shape on its own
    Circle c(1.0);
    assert(near(c.area(), PI));
    assert(near(c.perimeter(), 2 * PI));
    assert(c.name() == "Circle");

    Rectangle r(3.0, 4.0);
    assert(near(r.area(), 12.0));
    assert(near(r.perimeter(), 14.0));
    assert(r.name() == "Rectangle");

    Square sq(5.0);
    assert(near(sq.area(), 25.0));
    assert(near(sq.perimeter(), 20.0));
    assert(sq.name() == "Square");

    Triangle t(3.0, 4.0, 5.0);
    assert(near(t.area(), 6.0));
    assert(near(t.perimeter(), 12.0));
    assert(t.name() == "Triangle");

    // A Square IS a Rectangle, and both ARE Shapes
    const Rectangle &asRect = sq;
    assert(near(asRect.area(), 25.0));
    assert(asRect.name() == "Square");        // virtual: still Square's name

    const Shape &asShape = t;
    assert(asShape.name() == "Triangle");

    // A mixed collection, owned by smart pointers
    std::vector<std::unique_ptr<Shape>> shapes;
    shapes.push_back(std::make_unique<Circle>(1.0));
    shapes.push_back(std::make_unique<Rectangle>(3.0, 4.0));
    shapes.push_back(std::make_unique<Square>(5.0));
    shapes.push_back(std::make_unique<Triangle>(3.0, 4.0, 5.0));

    assert(near(totalArea(shapes), PI + 12.0 + 25.0 + 6.0));

    const Shape *big = largest(shapes);
    assert(big != nullptr);
    assert(big->name() == "Square");

    // Empty collection
    std::vector<std::unique_ptr<Shape>> none;
    assert(near(totalArea(none), 0.0));
    assert(largest(none) == nullptr);

    // Abstract class: uncomment, try to compile, read the error, then comment out again
    // Shape s;

    for (const auto &s : shapes) {
        std::cout << s->name() << ": area " << s->area() << "\n";
    }
    std::cout << "All tests passed!\n";
    return 0;
}